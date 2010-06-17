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
/*
 Standard String C Runtime implementation done just for ASDF to avoid
 licensing issues. All control data is done in standard ASCII. Unicode functions
 can just use the memcmp interfaces to compare unicode strings. Full local support
 and font rendering should be done on the user application side not in the kernel.

* Modified on June 10 of 2010. The code's FOR loops conditions were
  moved into the FOR loop's body. This was done for better readability,
  and to prevent segment faults of the code.
* Modified on June 11 of 2010. Code reformated for better readability.
*/


#include <string.h>

void * memcpy(void * dest, const void * src, size_t n)
{
  char *srcp = (char *)src;
  char *destp = (char *)dest;
  size_t i;

  for(i = 0; i < n; i++)
  {
    *destp++ = *srcp++;
  }

  return (void *)dest;
}

void * memmove(void * dest, const void * src, size_t n)
{
  char *dst = (char *)dest;
  char *sr = (char *)src;
  size_t i;

  if( sr < dst && dst < sr + n)
  {
    sr += n;
    dst += n;
    for(i = 0; i < n; i++)
    {
      *--dst=*--sr;
    }
  }
  else
  {
    for(i = 0; i < n; i++)
    {
      *dst++ = *sr++;
    }
  }

  return (void *)dest;
}

void * memchr(const void * s, int c, size_t n)
{
  char *sp = (char *)s;
  size_t i;

  for(i = 0;i < n; i++, sp++)
  {
    if(c == *sp)
    {
      break;
    }
  }
  if(i >= n)
  {
    return NULL;
  }

  return (void *)sp;
}

void * memset(void * p, int value, size_t n)
{
  char *dp = (char *)p;
  size_t i;

  for(i = 0; i < n; i++)
  {
    *dp++ = (char)value;
  }

  return (void *)p;
}

int memcmp(const void * src, const void * src2, size_t n)
{
  char *p1 = (char *)src;
  char *p2 = (char *)src2;
  size_t i;

  for(i = 0; i < n; p1++, p2++, i++)
  {
    if(*p1 != *p2)
    {
      break;
    }
  }
  if(i >= n)
  {
    return 0;
  }

  return (*(unsigned char *) p1) - (*(unsigned char *) p2);
}

char * strcat(char * dest, const char * src)
{
  char *destp = dest;
  char *srcp = (char *)src;

  for(; *destp != '\0'; destp++)
  {}
  while(*srcp != '\0')
  {
    *destp++ = *srcp++;
  }
  *destp = '\0';

  return dest;
}

char * strcpy(char * dest, const char * src)
{
  char *d = dest;
  char *s = (char *)src;

  while(*s != '\0')
  {
    *d++ = *s++;
  }
  *d = '\0';

  return dest;
}

size_t strcspn(const char * string, const char * keys)
{
  char *strp = (char *)string;
  char *keyl = (char *)keys;
  size_t sl;
  size_t kl = strlen(keys) + 1;

  for(sl = 1; ; sl++, strp++)
  {
    char *keys = keyl;
    size_t i;

    for(i = 0; i < kl; i++, keys++)
    {
      if(*keys == *strp)
      {
        return sl;
      }
    }
  }

  return sl;
}

size_t strlen(const char * string)
{
  size_t length;
  char *str = (char *)string;

  for(length = 0; *str != '\0'; str++, length++)
  {}

  return length;
}

char * strncat(char * dest, const char * src, size_t n)
{
  char *dst = (char *)dest;
  char *srp = (char *)src;
  size_t i;

  for(; *dst != '\0'; dst++)
  {}
  for(i = 0; i < n; i++)
  {
    if(*srp == '\0')
    {
      *dst++ = *srp++;
      return dest;
    }
  *dst++ = *srp++;
  }


  return dest;
}

int strncmp(const char * s1, const char * s2, size_t n)
{
  char *c1 = (char *)s1;
  char *c2 = (char *)s2;
  size_t i;

  for(i = 0; i < n; c1++, c2++, i++)
  {
    if(*c1 != *c2 || *c1 == '\0')
    {
      break;
    }
  }
  if(i >= n)
  {
    return 0;
  }
  if(*c1 == '\0')
  {
    return 0;
  }

  return (* (unsigned char *) c1) - (* (unsigned char *) c2);
}

char * strncpy(char * dest, const char * src, size_t n)
{
  char *d = dest;
  char *s = (char *)src;
  size_t i;

  for(i = 0; i < n; i++)
  {
    if(*s == '\0')
    {
      break;
    }
    *d++ = *s++;
  }
  for(; i < n; i++)
  {
    *d++ = '\0';
  }

  return dest;
}

char * strpbrk(const char * str1, const char * str2)
{
  char *strp = (char *)str1;
  char *str2p = (char *)str2;
  size_t str2l = strlen(str2p);

  for(; *str2p != '\0'; str2p++)
  {
    char *strs = str2p;
    size_t i;

    for(i = 0; i < str2l; i++, strs++)
    {
      if(*strs == *strp)
      {
        return strp;
      }
    }
  }
}

char  * strrchr(const char * string, int charecter)
{
  char *str = (char *)string;

  for(; *str != '\0' && *str != (char)charecter; str++)
  {}
  if(str == '\0')
  {
    return NULL;
  }

  return str;
}

size_t strspn(const char * s1, const char * match)
{
  char *strp =(char*)s1;
  char *strsp =(char *)match;
  size_t strsl = strlen(strsp);
  size_t stringl = 0;
  int ind = 1;

  for(; strsp != '\0' && ind == 1; strp++, stringl++)
  {
    size_t i;
    char *strs = strsp;

    for(i = 0, ind = 0; i < strsl; i++, strs++)
    {
      if(*strs == *strp)
      {
        ind = 1;
        break;
      }
    }
  }

  return stringl;
}

char * strstr(const char * s1, const char * sub_string)
{
  char *strp =(char *)s1;
  char *sstrp =(char *)sub_string;
  size_t sstrl = strlen(sstrp);

  for(; *strp != '\0'; strp++)
  {
    if(*strp == *sstrp)
    {
      size_t i;
      char *searchstr = sstrp;
      char *regularp = strp;

      searchstr++;
      regularp++;
      for(i = 1; i < sstrl; i++, searchstr++, regularp++)
      {
        if(*regularp=='\0')
        {
          return NULL;
        }
        if(*searchstr != *regularp)
        {
          break;
        }
      }
      if(i==sstrl)
      {
        return strp;
      }
    }
  }

  return NULL;
}

char * strtok(char * string, const char * token)
{
  return strtok_r(string, (char *)token, (char *)NULL);
}

char * strtok_r(char * s1, char * s2, char * s3)
{
  char *strp = (char *)s1;
  char *sstrp = (char *)s2;
  char *tstrp;
  size_t slen = strlen(sstrp);

  /*Find end of string*/
  if(s3 != NULL)
  {
    strp =(char *)s3;
    for(; *strp != '\0'; strp++)
    {}
    strp++;
  }

  /*search string*/
  tstrp = strp;
  for(; *tstrp!='\0'; tstrp++)
  {
    char *searchp = sstrp;
    size_t i;
    /*check if charecter matches charcter in search string*/
    for(i = 0; i < slen; i++, searchp++)
    {
      if(*tstrp == *searchp)
      {
        /*insert terminator, return pointer*/
        *tstrp = '\0';
        return strp;
      }
    }
  }

  return NULL;
}

char * strchr(const char * s1, int charecter)
{
  char *sp = (char *)s1;

  for(; *sp != '\0'; sp++)
  {
    if(*sp == (char)charecter)
    {
      return sp;
    }
  }
  /*Handle charecter == '\0'*/
  if(*sp == (char)charecter)
  {
    return sp;
  }

  return NULL;
}

int strcmp(const char * s1, const char * s2)
{
  char *c1 = (char *)s1;
  char *c2 = (char *)s2;
  size_t i;

  for(; *c1 == *c2 && *c1 != '\0'; c1++, c2++)
  {}
  if(*c1 == '\0')
  {
    return 0;
  }

  return (* (unsigned char *) c1) - (* (unsigned char *) c2);
}
