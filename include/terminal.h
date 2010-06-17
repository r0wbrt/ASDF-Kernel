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
/*Textmode vga driver, this should be expanded to include other vga modes*/

#include <stdint.h>


#ifdef _INCLUDE_TERMINAL_H_SETTINGS_

#include <string.h>
#include <inlineasm.h>

#define VIDEO_MEMORY  0xB8000
#define TERM_ROWS     24
#define TERM_COLUMNS  79
#define TERM_MAXPOS   4000

static int32_t    term_row;
static int32_t    term_col;
static uint8_t    term_color_t;
static volatile uint16_t * term_vaddr;
static void       term_scroll(int count);
static void       term_putchar(char c, uint8_t t_color_s);
#endif

void  term_setaddr(void * p);
int   term_setpos(int32_t r, int32_t c);
void  term_color(uint8_t front, uint8_t back);
void  term_write(const char * string);
void  term_init();
