/* Kernel.c */

/* The screen is composed of 25 lignes of 80 columns. */
#define NB_LINES_SCREEN 25
#define NB_CHAR_PER_LINE 80

char *video_ptr = (char *)0xb8000; /* Beginning of the video memory */

/**
 *  This function clear the current screen by writing blank characters on it.
 */
void clear_screen()
{
  unsigned int cpt;
  /* Each column contains 2 bytes of data : the char to print and their colors */
  unsigned const int nb_byte_total = 2 * NB_LINES_SCREEN * NB_CHAR_PER_LINE;

  for(cpt = 0 ; cpt < nb_byte_total  ; cpt += 2)
  {
    *(video_ptr + cpt)     = ' ';    /* Write a blank character */
    *(video_ptr + cpt + 1) = 0xF0;   /* Write it black on white screen */
  }
}

/**
 *  This function print the 'text' string onto the screen.
 */
void write_string_on_screen(char *text)
{
  unsigned int cpt;
  cpt = 0;

  /* We go through the text to print */
  while(*(text + cpt) != '\0')
  {
    *(video_ptr + (2 *cpt))      = *(text + cpt);
    *(video_ptr + (2 * cpt) + 1)  = 0xF0;

    cpt ++;
  }
}

void kmain(void)
{
  clear_screen();
  write_string_on_screen("Welcome to my Kernel");
  return;
}
