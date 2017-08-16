#include "string.h"

void reverse(char * str, int length)
{
  char tmp;
  int start = 0;
  int end = length -1;

  while (start < end)
  {
    /* Swap values */
    tmp = *(str + end);
    *(str + end) = *(str + start);
    *(str + start) = tmp;

    start++;
    end--;
  }
}
