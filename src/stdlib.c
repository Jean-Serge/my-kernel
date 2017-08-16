#include "stdlib.h"
#include "string.h"

/**
 * Move the n bytes of src into dest.
 */
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

/**
 * Return 1 if the given character is a letter [a-z]|[A-Z], 0 otherwise.
 */
uint8_t is_letter(unsigned char c)
{
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

uint8_t is_lowercase(unsigned char c)
{
  return (c >= 'a' && c <= 'z');
}

/**
 * Return the uppercase version of the given character.
 */
unsigned char uppercase(unsigned char c)
{
  if (is_lowercase(c)) {
     c += ('A' - 'a');
  }

  return c;
}

char * itoa(int num, int base)
{
  /* TODO : Add memory allocation */
  char * str;
  size_t i = 0;
  uint8_t isNegative = 0;

  /* Handle 0 explicitely, otherwise empty string is printed for 0 */
  if (num == 0)
  {
    str[i++] = '0';
    str[i] = '\0';
    return str;
  }

  // In standard itoa(), negative numbers are handled only with
  // base 10. Otherwise numbers are considered unsigned.
  if (num < 0 && base == 10)
  {
    isNegative = 1;
    num = -num;
  }

  // Process individual digits
  while (num != 0)
  {
    int rem = num % base;
    *(str + i++) = (rem > 9)? (rem-10) + 'a' : rem + '0';
    num = num/base;
  }

  // If number is negative, append '-'
  if (isNegative)
    str[i++] = '-';

  str[i] = '\0'; // Append string terminator

  // Reverse the string
  reverse(str, i);

  return str;
}

void switch_flag(uint8_t * flag)
{
  *flag = *flag == 0 ? 1 : 0;
}
