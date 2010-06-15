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
