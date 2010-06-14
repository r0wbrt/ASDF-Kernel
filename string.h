/*
###############################################################################################
# Copyright 2010 Robert Christian Taylor. All rights reserved.                                #
#                                                                                             #
# Redistribution and use in source and binary forms, with or without modification, are        #
# permitted provided that the following conditions are met:                                   #
#                                                                                             #
#  1. Redistributions of source code must retain the above copyright notice, this list of     #
#     conditions and the following disclaimer.                                                #
#                                                                                             #
# THIS SOFTWARE IS PROVIDED BY Robert Christian Taylor ``AS IS'' AND ANY EXPRESS OR IMPLIED   #
# WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND    #
# FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL Robert Christian Taylor  #
# OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR      #
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR    #
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON    #
# ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING          #
# NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF        #
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                                                  #
#                                                                                             #
# The views and conclusions contained in the software and documentation are those of the      #
# authors and should not be interpreted as representing official policies, either expressed   #
# or implied, of Robert Christain Taylor.                                                     #
###############################################################################################
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
char*	strtok (char*, const char*); /*This function is non-thread safe. This function will always return NULL*/
char* strtok_r(char*, char*, char*); /*strtok replacement functions, conforms to the posix guidelines*/

#endif
