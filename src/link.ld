/* link.ld */
OUTPUT_FORMAT(elf32-i386) /* Produce 32 bit Executable and Linkable Format */
                          /* (aka : binary file) */
ENTRY(start)              /* EntryPoint is the start symbol (see kernel.asm) */
SECTIONS
{
  .     = 0x100000;       /* . is the location counter */
                          /* The kernel must be started at this address */

  /* All those sections will be placed in the memory */
  .text : { *(.text) }    /* Look for any .text section on all files */
  .data : { *(.data) }
  .bss  : { *(.bss)  }
}
