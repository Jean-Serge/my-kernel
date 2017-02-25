/* Kernel.c */
#include "vga.h"
#include "keyboard.h"

/**
 * This function is the entrypoint of the built kernel.
 * In this version, it only print a message on the screen.
 */
void kmain(void)
{
  clear_screen();
  write_string("Welcome to my Kernel\nI'm very happy to see you !\n");

  idt_init();
  kb_init();

  while(1);
}
