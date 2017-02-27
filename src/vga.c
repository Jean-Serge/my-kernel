#include "vga.h"

uint16_t *video_ptr = (uint16_t *) 0xb8000; /* Beginning of the video memory */
size_t   cursor_position = 0;

/**
 * This function build a tuple with foreground and background color.
 */
static inline uint8_t vga_entry_color() {
  return 0x0 | 0xF << 4;
}

/**
 * This function build a tuple char + color to be printed on screen.
 */
static inline uint16_t vga_entry(unsigned char c, uint8_t color) {
  return (uint16_t) color << 8 | (uint16_t) c;
}

/**
 * Clear only the last line of the screen (used for scrolling purpose).
 */
static void clear_last_line()
{
  size_t cpt;

  for (cpt = NB_BYTES_TOTAL - NB_CHAR_PER_LINE ; cpt < NB_BYTES_TOTAL ; cpt++) {
    *(video_ptr + cpt) = vga_entry(' ', vga_entry_color());
  }

  cursor_position -= NB_CHAR_PER_LINE;
}

/**
 *  This function clear the current screen by writing blank characters on it.
 */
void clear_screen()
{
  unsigned int cpt;
  cursor_position = 0;

  for (cpt = 0 ; cpt < NB_BYTES_TOTAL ; cpt ++)
  {
    *(video_ptr + cpt) = vga_entry(' ', vga_entry_color());
  }
}

/**
 * Write the given char at the current cursor position on the screen.
 */
void write_char(char c)
{
  if (c == '\n') {
    cursor_position += NB_CHAR_PER_LINE - cursor_position % NB_CHAR_PER_LINE;
  } else {
    *(video_ptr + cursor_position) = vga_entry(c, vga_entry_color());
    cursor_position ++;
  }

  /* Scrolling */
  if (cursor_position >= NB_BYTES_TOTAL) {
    memmove(video_ptr, video_ptr + NB_CHAR_PER_LINE, 2 * (NB_BYTES_TOTAL - NB_CHAR_PER_LINE));
    clear_last_line();
  }
}

/**
 *  This function print the 'text' string onto the screen.
 */
void write_string(char * text)
{
  unsigned int cpt;
  char c;
  cpt = 0;

  /* We go through the text to print */
  while ((c = *(text + cpt)) != '\0')
  {
    write_char(c);
    cpt ++;
  }
}
