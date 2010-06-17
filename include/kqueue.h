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

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <inlineasm.h>

#define KQUEUE_SUCCESS 1
#define KQUEUE_FAIL -1
#define KQUEUE_MM_INVALID -2

/*  This is where the kernel queue implementation function lives.
    All functions that insert and remove messages are thread safe
    for manipulation of the kqueue_message_main structure. The
    actual message structure manipulation it's self is non thread
    safe. So keep messages locked or in their own threads. The server
    functions that grab messages out of the queue are thread safe. The
    message handling code is not.
*/


struct kqueue_message;

struct kqueue_message_main
{
  volatile int32_t status;                 /*status of queue*/
  volatile uint32_t reference;             /*Number of reference, used for global queue database*/
  uint32_t id;                    /*Id of queue in global database*/
  struct kqueue_message * dummy; /*dummy message to prevent memory leaks*/
  volatile struct kqueue_message * next; /*Pointer to the last message returned by the message get functions*/
  volatile struct kqueue_message * last;   /*Last message pointer*/
};

struct kqueue_message
{
  volatile void * data;
  volatile uint32_t done;
  volatile uint32_t type;
  struct kqueue_message_main * mm;
  volatile struct kqueue_message * next;
};



/*asycronous functions*/
int kqueue_create(struct kqueue_message_main * mm, struct kqueue_message * message, uint32_t type, void * data);
int kqueue_insert(struct kqueue_message * message);
int kqueue_read(struct kqueue_message * message, uint32_t * type, void ** p);
int kqueue_remove(struct kqueue_message * message);

/*Owner functions*/
struct kqueue_message * kqueue_grab(struct kqueue_message_main * mm);

int kqueue_set(struct kqueue_message * message, uint32_t type, void * p);
int kqueue_get(struct kqueue_message * message, uint32_t * type, void ** p);
int kqueue_dismis(struct kqueue_message * message);

int kqueue_init(struct kqueue_message_main * mm, struct kqueue_message * dummy);
struct kqueue_message * kqueue_invl(struct kqueue_message_main * mm);

