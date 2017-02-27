#ifndef H_STDLIB
#define H_STDLIB

#include "types.h"

extern void           memmove(void *dest, void *src, size_t n);
extern unsigned char  uppercase(unsigned char c);
extern char *         itoa(int num, int base);
extern void           switch_flag(uint8_t * flag);

#endif
