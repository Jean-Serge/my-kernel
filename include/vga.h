#ifndef H_VGA
#define H_VGA

#include "types.h"

#define NB_LINES_SCREEN 25
#define NB_CHAR_PER_LINE 60
#define NB_BYTES_TOTAL (NB_CHAR_PER_LINE * NB_CHAR_PER_LINE)

extern void clear_screen();
extern void write_string(char *text);

#endif
