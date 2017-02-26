#include "stdlib.h"

void memmove(void *dest, void *src, size_t n)
{
   char *c_src = (char *)src;
   char *c_dest = (char *)dest;
   char temp[n];
   size_t i;

   for (i = 0 ; i < n ; i++) {
     temp[i] = c_src[i];
   }

   for (i = 0 ; i < n ; i++) {
     c_dest[i] = temp[i];
   }
}
