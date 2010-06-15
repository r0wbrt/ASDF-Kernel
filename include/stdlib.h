/*Copyright 2010 Robert Christian Taylor. All Rights Reserved.*/
#ifndef _STDLIB_H_
#define _STDLIB_H
#ifndef NULL
#define NULL 0
#endif
#include <stddef.h>
void* malloc(size_t size);
void free(void *p);
#endif
