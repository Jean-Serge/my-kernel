#include "vga.h"
#include "stdlib.h"
#include "keyboard.h"
#include "keyboard_map.h"

/* Import assembly functions */
extern char read_port(unsigned short port);
extern void write_port(unsigned short port, unsigned char data);
extern void load_idt(unsigned long *idt_ptr);
extern void keyboard_handler(void);

extern unsigned char keyboard_map[128];

struct IDT_entry IDT[IDT_SIZE];

void kb_init(void)
{
  /* 0xFD is 11111101 - enables only IRQ1 (keyboard)*/
  write_port(0x21 , 0xFD);
}

void idt_init(void)
{
  unsigned long keyboard_address;
  unsigned long idt_address;
  unsigned long idt_ptr[2];

  /* populate IDT entry of keyboard's interrupt */
  keyboard_address = (unsigned long)keyboard_handler;
  IDT[0x21].offset_lowerbits = keyboard_address & 0xffff;
  IDT[0x21].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
  IDT[0x21].zero = 0;
  IDT[0x21].type_attr = 0x8e; /* INTERRUPT_GATE */
  IDT[0x21].offset_higherbits = (keyboard_address & 0xffff0000) >> 16;


  /* ICW1 - begin initialization */
  write_port(0x20 , 0x11);
  write_port(0xA0 , 0x11);

  /* ICW2 - remap offset address of IDT */
  /*
  * In x86 protected mode, we have to remap the PICs beyond 0x20 because
  * Intel have designated the first 32 interrupts as "reserved" for cpu exceptions
  */
  write_port(0x21 , 0x20);
  write_port(0xA1 , 0x28);

  /* ICW3 - setup cascading */
  write_port(0x21 , 0x00);
  write_port(0xA1 , 0x00);

  /* ICW4 - environment info */
  write_port(0x21 , 0x01);
  write_port(0xA1 , 0x01);
  /* Initialization finished */

  /* mask interrupts */
  write_port(0x21 , 0xff);
  write_port(0xA1 , 0xff);

  /* fill the IDT descriptor */
  idt_address = (unsigned long)IDT ;
  idt_ptr[0] = (sizeof (struct IDT_entry) * IDT_SIZE) + ((idt_address & 0xffff) << 16);
  idt_ptr[1] = idt_address >> 16 ;

  load_idt(idt_ptr);
}

/**
 * This function is call each time a keyboard IRQ is raise.
 */
void keyboard_handler_main(void) {
  static uint8_t caps_lock = 1;
  unsigned char status;
  unsigned char keycode, c;

  /* Send EOI to reactivate IRQs */
  write_port(0x20, 0x20);

  status = read_port(KEYBOARD_STATUS_PORT);

  /* Lowest bit of status will be set if buffer is not empty */
  if (status & 0x01) {
    keycode = read_port(KEYBOARD_DATA_PORT);

    if (keycode == 0x2A) {
      caps_lock = 1;
      // write_string(itoa((int)caps_lock, 10));
      return;
    }

    if (keycode == 0xAA) {
      caps_lock = 0;
      // write_string(itoa((int)caps_lock, 10));
      return;
    }

    c = keyboard_map[(unsigned char) keycode];

    if (caps_lock) {
      c = uppercase(c);
    }

    write_char(c);
  }
}
