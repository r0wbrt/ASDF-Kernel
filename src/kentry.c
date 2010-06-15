/*Copyright 2010 Robert Christian Taylor. All Rights Reserved.*/
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
  cas(NULL,0,0);
  kentry_panic("\r\nKernel kentry has no where to go!\r\n");

  return ;
}
