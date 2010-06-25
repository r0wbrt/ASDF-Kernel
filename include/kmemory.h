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

#ifndef _KMEMORY_H_
#define _KMEMORY_H_

#include <stdint.h>

#define KPAGE_SIZE 4096                //Size of page
#define KPAGE_ALIGN 0x1000             //Alighnment of pages

#define KPAGE_TABLE 0xFFC00000        //The address of the current page table in use
#define KPAGE_PROCESSOR 0xFF800000    //The address of the CPU specific Block

#define KPAGE_KERNEL_START 0xC0000000

#define KSIZE_MB_1MB 0x01
#define KSIZE_MB_2MB 0x02
#define KSIZE_MB_4MB 0x04
#define KSIZE_MB_8MB 0x08
#define KSIZE_MB_16MB 0x10
#define KSIZE_MB_32MB 0x20
#define KSIZE_MB_64MB 0x40
#define KSIZE_MB_128MB 0x80



/*returns physical address*/
void * kmem_getblock(uint8_t size);
/*takes physical address of block*/
void kmem_freeblock(void *p);

#define KSIZE_LB_8KB KSIZE_MB_1MB
#define KSIZE_LB_16KB KSIZE_MB_2MB
#define KSIZE_LB_32KB KSIZE_MB_4MB
#define KSIZE_LB_64KB KSIZE_MB_8MB
#define KSIZE_LB_128KB KSIZE_MB_16MB
#define KSIZE_LB_256KB KSIZE_MB_32MB
#define KSIZE_LB_512KB KSIZE_MB_64MB
#define KSIZE_LB_1024KB KSIZE_MB_128MB

typedef struct page_directory_t
{
  uint32_t tables[1024];
}  __attribute__((__packed__)) page_directory_t;
typedef struct page_table_t
{
  uint32_t pages[1024];
}  __attribute__((__packed__)) page_table_t;


/*Kernel page directory physical pointer*/
page_directory_t * kpagedir;
/*pointers to the pointers to the physical address of the page tables that the kernel will use */
page_table_t ** kpagetbls;

/*gets a block of memory from the local allocator uses KPAGE_PROCESOR*/
void * kloc_getblock(uint8_t size);
/*frees a block of memory from the local allocator uses KPAGE_PROCESOR*/
void kloc_freeblock(uint8_t size);


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
void    k_switchspace(page_directory_t *pd, page_table_t *ps);


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

typedef void * KPOOL;
KPOOL pool_new(size_t size);
int pool_free(KPOOL pool);
void * pool_grab(KPOOL pool);
void pool_return(KPOOL pool, void * addr);

typedef void * KHEAP;
KHEAP heap_new();
void heap_free(KHEAP heap);
void heap_alloc(KHEAP heap, size_t size);
void heap_dealloc(KHEAP heap, void *p);

/*instalilizes memory managment systems, for the whole kernel and the execuiting cpu*/
int init_memsystem(void * mbds, void * pt);

/*instalizes cpu memory managment system*/
int init_memsystem_cpu();

#endif
