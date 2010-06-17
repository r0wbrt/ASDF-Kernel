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
#define _INCLUDE_KENTRY_H_SETTINGS_
#include <kentry.h>
#include <inlineasm.h>

void kentry_panic(const char * string)
{
  term_write(string);
  while(1 == 1)
  {
    __asm__ __volatile__ ("hlt;");
  }
}

void kentry(void * mbd, unsigned int magic, void * ptable)
{
  term_init();
  term_write(ki_about_message);

  if(magic!=0x2BADB002 || mbd == NULL)
  {
    kentry_panic("\r\nError: Booted by non-compliant bootloader");
  }

  kentry_panic("\r\nKernel kentry has no where to go!");

  return ;
}
