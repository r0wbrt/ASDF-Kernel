/*Copyright 2010 Robert Christian Taylor. All Rights Reserved.*/

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
