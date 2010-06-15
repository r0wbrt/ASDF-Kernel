/*Copyright 2010 Robert Christian Taylor. All Rights Reserved.*/
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
