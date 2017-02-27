#ifndef H_STDLIB
#define H_STDLIB

#include "types.h"

extern void           memmove(void *dest, void *src, size_t n);
extern uint8_t        is_letter(unsigned char c);
extern unsigned char  uppercase(unsigned char c);
extern char *         itoa(int num, int base);

#endif
