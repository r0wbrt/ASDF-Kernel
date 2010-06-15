/*Copyright 2010 Robert Christian Taylor. All Rights Reserved.*/
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
