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

#include <stdint.h>
static inline void outb(uint16_t port, uint8_t data)
{
 __asm__ __volatile__("outb %0,%1"::"a"(data), "Nd" (port));
}
static inline uint32_t cas(void *p, uint32_t old, uint32_t new)
{
 uint32_t ret = 0;
 __asm__ __volatile__ ("lock; cmpxchg %1, %2;"
 :"=a"(ret)
 :"r"(new),"m"(p),"a"(old)
 );
return ret;
}
static inline void atomic_set(void *p, uint32_t data)
{
 __asm__ __volatile__ ("lock; movl %0, %1"
 :
 :"r"(data),"m"(p)
 );
}
