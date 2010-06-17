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

/*
 *
 * string.h
 * Definitions for memory and string functions.
 *
 */

#ifndef _STRING_H_
#define	_STRING_H_
#include <stdlib.h>
#include <stddef.h>

void* 	memchr (const void*, int, size_t);
int 		memcmp (const void*, const void*, size_t);
void* 	memcpy (void*, const void*, size_t);
void* 	memmove (void*, const void*, size_t);
void* 	memset (void*, int, size_t);
char* 	strcat (char*, const char*);
char*	strchr (const char*, int);
int		strcmp (const char*, const char*);
char*	strcpy (char*, const char*);
size_t	strcspn (const char*, const char*);
char*	strerror (int);
size_t	strlen (const char*);
char*	strncat (char*, const char*, size_t);
int		strncmp (const char*, const char*, size_t);
char*	strncpy (char*, const char*, size_t);
char*	strpbrk (const char*, const char*);
char*	strrchr (const char*, int);
size_t	strspn (const char*, const char*);
char*	strstr (const char*, const char*);
/*This function is non-thread safe. Calls strtok_r internally, use is discouraged*/
char*	strtok (char*, const char*);
char* strtok_r(char*, char*, char*); /*strtok replacement functions, conforms to the posix guidelines*/

#endif
