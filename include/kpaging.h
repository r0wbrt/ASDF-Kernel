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
#include <multiboot.h>
#include <kpagemap>



#ifndef _KPAGING_H_INCLUDE_
#define _KPAGING_H_INCLUDE_

#define PAGE_SIZE 4096
#define PAGE_ALIGN 0xFFFF1000

typedef struct page_directory_t
{
  uint32_t[1024];
} page_directory_t;
typedef struct page_table_t
{
  uint32_t[1024];
} page_table_t;

/*inserts a page into kernel space where p is a pointer to a physical page*/
void*   k_insertpage(void *p, uint32_t flags);
/*map page where  p is physical and v is virtual*/
void*   k_mappage(void *p, void *vp, uint32_t flags);
/*finds a block of free memory*/
void*   k_findblock(uint32_t size);
/*unmmaps a page*/
void*   k_unmappage(void *p);
/*gets real address*/
void*   k_vtoreal(void *p);
/*switches page space*/
void    k_switchspace(page_directory_t *pd);
/*links the page directory to the kernel's*/
void    k_linkspace(page_directory_t *pd);

/*inserts a page into process space where p is a pointer to a physical page*/
void*   p_insertpage(void *p, uint32_t flags);
/*map page where  p is physical and v is virtual*/
void*   p_mappage(void *p, void *vp, uint32_t flags);
/*finds a block of free memory*/
void*   p_findblock(uint32_t size);
/*unmmaps a page, will free a page directory*/
void*   p_unmappage(void *p);
/*gets real address*/
void*   p_vtoreal(void *p);

/*Creates a new page directory*/
page_directory_t *   p_createspace();
/*frees all user pages, does not touch kernel pages*/
void   p_freespace(page_directory_t *pd);

/*instalizes paging*/
int     init_paging(void * mbds, void * pt);

#endif


#ifdef _KPAGING_H_INCLUDE_SYS
#define KERNEL_PAGE_DIRECTORIES 256
/*Kernel page directory pointer*/
static  page_directory_t *kpagedir;
/*pointers to the page tables that the kernel will use 1MB!*/
static  page_table_t *kpagetbls[KERNEL_PAGE_DIRECTORIES];
#endif
