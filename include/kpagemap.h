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
#include <kpaging.h>


#ifdef _KPAGEMAP_H_SYS
#define KTABLE_BITMAP_SIZE PAGE_SIZE/4
#define KTABLE_BITMAPS 64
typedef struct page_bitmap_t
{
 uint32_t bitmap[KTABLE_BITMAP_SIZE];
} page_bitmap_t;
typedef struct page_bitmap_table_t
{
 int locks[KTABLE_BITMAPS];
 page_bitmap_t *tables[KTABLE_BITMAPS];
} page_bitmap_table_t;
/*Page bitmap pool*/
static  page_bitmap_table_t *page_bitmap;
#endif


#ifndef _KPAGEMAP_H_
#define _KPAGEMAP_H_

/*gets a page*/
void*   page_get();
/*frees a page*/
void    page_free(void *p);
/*disables a page for use*/
void    page_disable(uint32_t pageid);
/*enables a page for use*/
void    page_enable(uint32_t pageid);
/*reads a pages status*/
int     page_status(uint32_t pageid);

#endif
