/*Copyright 2010 Robert Christian Taylor. All Rights Reserved.*/

#define _INCLUDE_TERMINAL_H_SETTINGS_
#include <terminal.h>


void term_color(unsigned char front, unsigned char back)
{
  term_color_t = (back << 4) & (front & 0x0F);
}

void term_setcursor(int row, int col)
{
  uint16_t position = (row * 80) + col;

  outb(0x3D4, 0x0F);
  outb(0x3D5, (uint8_t)(position & 0xFF) );
  outb(0x3D4, 0x0E);
  outb(0x3D5, (uint8_t)( (position >> 8) & 0xFF) );
}

void term_write(const char * string)
{
  char *str = (char *)string;

  for(;*str!='\0';str++)
  {
    term_putchar((const char)*str, term_color_t);
  }
  term_setcursor(term_row, term_col);
}

void term_putchar(const char c, uint8_t t_color_s)
{
  switch(c)
  {
    case '\r':
    {
      term_col=0;
    }
      break;

    case '\n':
    {
      term_row++;
      if(term_row > TERM_ROWS)
      {
        term_scroll(1);
        term_row--;
      }
    }
      break;

    case '\b':
    {
      term_col--;
      if(term_col < 0)
      {
        term_row--;
        if(term_row < 0)
        {
          term_row = 0;
        }
      }
    }
      break;

    default:
    {
      uint16_t *write = (uint16_t *)term_vaddr;

      write[ (term_row * 80) + term_col ] = (t_color_s << 8) | c;

      term_col++;
      if(term_col > TERM_COLUMNS)
      {
        term_row++;
        term_col = 0;
        if(term_row>TERM_ROWS)
        {
          term_scroll(1);
          term_row--;
        }
      }
    }
      break;
  }
}

void term_scroll(int count)
{
  if(count > TERM_ROWS || count < 1)
  {
    return ;
  }
  int offset = count * 80;

  memcpy((void *)term_vaddr, (const void*)(term_vaddr + offset), (TERM_MAXPOS - offset) );
  memset((void *)(term_vaddr + (TERM_MAXPOS - offset ) ), 0, offset);
}

void term_init()
{
  term_row = 0;
  term_col = 0;
  term_color_t = 0x0F;
  term_vaddr = (uint16_t *)VIDEO_MEMORY;

  memset((void *)term_vaddr, 0, (TERM_ROWS * TERM_COLUMNS) );
  term_lock = 0;
}

void term_setaddr(void * p)
{
  term_vaddr = (uint16_t *)p;
}
