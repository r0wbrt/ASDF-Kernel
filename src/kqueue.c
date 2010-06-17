/*
    Advanced Simulated Filesystem Flora Kernel
    Copyright (C) 2010  Robert Christian Taylor

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 2
    of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <kqueue.h>

int kqueue_create(struct kqueue_message_main * mm, struct kqueue_message * message, uint32_t type, void * data)
{
  if(mm->status == -1)
  {
    return KQUEUE_MM_INVALID;
  }

	message->data = data;
	message->type = type;
	message->next = NULL;
	message->done = 0;
	message->mm = mm;

	return KQUEUE_SUCCESS;
}

int kqueue_insert(struct kqueue_message * message)
{
  struct kqueue_message * last;

  if(message->mm->status == -1)
  {
    return KQUEUE_MM_INVALID;
  }

  last = (struct kqueue_message *)message->mm->last;

  if(cas(&message->mm->last, (uint32_t)last, (uint32_t)message) == (uint32_t)last)
  {
    if(last != NULL)
    {
      atomic_set(&last->next, (uint32_t)message);
    }

    return KQUEUE_SUCCESS;
  }

	return KQUEUE_FAIL;
}

int kqueue_read(struct kqueue_message * message, uint32_t * type, void ** p)
{
  if(message->done != 1)
  {
    if(message->mm->status == -1)
    {
      return KQUEUE_MM_INVALID;
    }

    return KQUEUE_FAIL;
  }

  *p = (void *)message->data;
  *type = message->type;

	return KQUEUE_SUCCESS;
}

int kqueue_remove(struct kqueue_message * message)
{

	if(message->done != 1 && message->mm->status != -1)
	{
		return KQUEUE_FAIL;
	}

	if(message->next != NULL)
	{
		return KQUEUE_SUCCESS;
	}

	return KQUEUE_FAIL;
}

struct kqueue_message * kqueue_grab(struct kqueue_message_main * mm)
{
  struct kqueue_message * retmes;
  struct kqueue_message * prevv = (struct kqueue_message *)mm->next;

  if(prevv->next == NULL)
  {
    return NULL;
  }

  retmes = (struct kqueue_message *)prevv->next;

  if(cas(&mm->next, (uint32_t)prevv, (uint32_t)retmes) == (uint32_t)prevv)
  {
    if(retmes == mm->dummy)
    {
      return NULL;
    }

    return retmes;
  }

  return NULL;
}

int kqueue_set(struct kqueue_message * message, uint32_t type, void * p)
{
  message->type = type;
  message->data = p;

  return KQUEUE_SUCCESS;
}

int kqueue_get(struct kqueue_message * message, uint32_t * type, void ** p)
{
  *type = message->type;
  *p = (void *)message->data;

  return KQUEUE_SUCCESS;
}

int kqueue_dismis(struct kqueue_message * message)
{
  if(message == message->mm->next || message->next == NULL)
  {
    if(message->next != NULL)
    {
      return KQUEUE_FAIL;
    }
    else
    {
      message->mm->dummy->next = NULL;
      if(cas(&message->mm->last, (uint32_t)message, (uint32_t)message->mm->dummy) == (uint32_t)message)
      {
        atomic_set(&message->next, (uint32_t)message->mm->dummy);
      }

      return KQUEUE_FAIL;
    }
  }

  message->done = 1;

  return KQUEUE_SUCCESS;
}

int kqueue_init(struct kqueue_message_main * mm, struct kqueue_message * dummy)
{
  mm->status = 1;
  mm->next = dummy;
  mm->last = dummy;
  mm->dummy = dummy;

  memset(dummy, 0, sizeof(struct kqueue_message) );
  mm->dummy->mm = mm;

  return KQUEUE_SUCCESS;
}

struct kqueue_message * kqueue_invl(struct kqueue_message_main * mm)
{
  mm->next = NULL;
  atomic_set((void *)&mm->status, (uint32_t)-1);
  struct kqueue_message * message = (struct kqueue_message *)mm->last;
  if(message != mm->dummy)
  {
    mm->dummy->next = NULL;
    if(cas(&mm->last, (uint32_t)message, (uint32_t)mm->dummy) == (uint32_t)message)
    {
      atomic_set(&message->next, (uint32_t)mm->dummy);
    }
    else
    {
      return NULL;
    }
  }

  return mm->dummy;
}
