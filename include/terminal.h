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
static uint16_t * term_vaddr;
static void       term_scroll(int count);
static void       term_putchar(char c, uint8_t t_color_s);
static int        term_lock;
#endif

void  term_setaddr(void * p);
int   term_setpos(int32_t r, int32_t c);
void  term_color(uint8_t front, uint8_t back);
void  term_write(const char * string);
void  term_init();
