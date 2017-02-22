/* Kernel.c */

/* The screen is composed of 25 lignes of 80 columns. */
#define NB_LINES_SCREEN 25
#define NB_CHAR_PER_LINE 60
#define NB_BYTES_TOTAL (NB_CHAR_PER_LINE * NB_CHAR_PER_LINE)

typedef unsigned short int  uint16_t;
typedef unsigned char       uint8_t;
typedef unsigned int        size_t;

uint16_t *video_ptr = (uint16_t *) 0xb8000; /* Beginning of the video memory */

size_t  current_row     = 0;
size_t  current_column  = 0;

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
 *  This function clear the current screen by writing blank characters on it.
 */
void clear_screen()
{
  unsigned int cpt;

  current_row     = 0;
  current_column  = 0;

  for (cpt = 0 ; cpt < NB_BYTES_TOTAL ; cpt += 1)
  {
    *(video_ptr + cpt) = vga_entry(' ', vga_entry_color());
  }
}

/**
 *  This function print the 'text' string onto the screen.
 */
void write_string(char *text)
{
  unsigned int cpt;
  char c;
  cpt = 0;

  /* We go through the text to print */
  while ((c = *(text + cpt)) != '\0')
  {
    if (c == '\n') {
      current_row ++;
      cpt ++;
      continue;
    }

    *(video_ptr + (current_column + NB_CHAR_PER_LINE * current_row)) = vga_entry(c, vga_entry_color());

    current_column ++;
    cpt ++;

    if (current_column == NB_CHAR_PER_LINE) {
      current_row ++;
      current_column = 0;
    }
  }
}

/**
 * This function is the entrypoint of the built kernel.
 * In this version, it only print a message on the screen.
 */
void kmain(void)
{
  clear_screen();
  write_string("Welcome to my Kernel\nI'm very happy to see you !");
  return;
}
