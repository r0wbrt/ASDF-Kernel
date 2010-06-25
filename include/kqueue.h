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

/**
 * @param KQUEUE_SUCCESS return value of kqueue functions on success
 */
#define KQUEUE_SUCCESS 1
/**
 * @param KQUEUE_FAIL return value of kqueue functions on fail
 */
#define KQUEUE_FAIL -1
/**
 * @param KQUEUE_MM_INVALID return value of kqueue functions if struct kqueue_message_main is invalid
 */
#define KQUEUE_MM_INVALID -2
/**
 * @author Robert Christian Taylor
 * @file kqueue.h
 * @brief
 * This is where the kernel queue implementation function lives.
 * All functions that insert and remove messages are thread safe
 * for manipulation of the kqueue_message_main structure. The
 * actual message structure manipulation it's self is non thread
 * safe. So keep messages locked or in their own threads. The server
 * functions that grab messages out of the queue are thread safe. The
 * message handling code is not.
 */


struct kqueue_message;
/**
 * This structure is used for book keeping of the kqueue functions.
 *
 * @param status status of the queue
 * @param reference Reference count of the structure
 * @param id Id of structure free to use by the allocator
 * @param dummy pointer to the dummy message to be used by the kqueue
 * @param Pointer to the next message to be accessed by the consumer
 * @param Pointer to the last message on the queue
 */
struct kqueue_message_main
{
  volatile int32_t status;
  volatile uint32_t reference;
  uint32_t id;
  struct kqueue_message * dummy;
  volatile struct kqueue_message * next;
  volatile struct kqueue_message * last;
};
/**
 * This structure holds the data for a kqueue message.
 *
 * @param data Pointer to data held in the message.
 * @param done Status of the message.
 * @param type Field that holds the type value
 * @param mm Pointer to the message main structure.
 * @param next Pointer to the next message.
 */
struct kqueue_message
{
  volatile void * data;
  volatile uint32_t done;
  volatile uint32_t type;
  struct kqueue_message_main * mm;
  volatile struct kqueue_message * next;
};



/*asycronous functions*/
/**
 * This function prepares a message to be inserted into the queue.
 *
 * @param mm A valid pointer to an kqueue_message_main.
 * @param message A valid pointer to a kqueue_message to be prepared.
 * @param type A user supplied value that will be read by the recieving end.
 * @param data A pointer to the data to be supplied via the queue.
 * @return KQUEUE_SUCCESS on success, else KQUEUE_MM_INVALID if the queue is no longer accepting messages.
 */
int kqueue_create(struct kqueue_message_main * mm, struct kqueue_message * message, uint32_t type, void * data);
/**
 * This function is asycronous and will attempt to insert the message into the queue.
 *
 * @param message A valid pointer to an kqueue_message to be inserted into the queue.
 * @return KQUEUE_SUCCESS on success, else KQUEUE_MM_INVALID if the queue is no longer accepting messages. KQUEUE_FAIL will
 * be returned if it fails to insert the message.
 */
int kqueue_insert(struct kqueue_message * message);
/**
 * This function reads a message inserted into the queue.
 *
 * @param message A valid pointer to a kqueue_message to be read.
 * @param type A user supplied pointer to a uint32_t that will recieve the value.
 * @param data A pointer to a pointer for the address of the value to be stored into.
 * @return KQUEUE_SUCCESS on success, else KQUEUE_MM_INVALID if the queue is no longer accepting messages. Returns KQUEUE_FAIL
 * if the message is not ready.
 */
int kqueue_read(struct kqueue_message * message, uint32_t * type, void ** p);
/**
 * This function removes a message from the queue
 *
 * @param message A pointer to a valid kqueue_message structure
 * @return KQUEUE_SUCCESS if the message is removed else returns KQUEUE_FAIL
 */
int kqueue_remove(struct kqueue_message * message);
/**
 * This function grabs a message off the queue
 *
 * @param mm A pointer to valid kqueue_message_main structure to grab the message from
 * @return A valid pointer else NULL
 */
struct kqueue_message * kqueue_grab(struct kqueue_message_main * mm);
/**
 * This function modifies a message.
 *
 * @param message A valid pointer to a kqueue_message structure.
 * @param type A uint32_t value to be placed in the type field of the message
 * @param p A pointer value to be placed in the pointer field of the message.
 * @return KQUEUE_SUCCESS on success
 */
int kqueue_set(struct kqueue_message * message, uint32_t type, void * p);
/**
 * This function gets the values of a message.
 */
int kqueue_get(struct kqueue_message * message, uint32_t * type, void ** p);
/**
 * This function dismisses a message notifying the producer that the consumer is done.
 */
int kqueue_dismiss(struct kqueue_message * message);
/**
 * This function instalizes the message main structure.
 */
int kqueue_init(struct kqueue_message_main * mm, struct kqueue_message * dummy);
/**
 * This function invalidates the message main structure.
 */
struct kqueue_message * kqueue_invl(struct kqueue_message_main * mm);

