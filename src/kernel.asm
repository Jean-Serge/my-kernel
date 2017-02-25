;; kernel.asm

;; This file contains assembly code to run the kernel.

bits 32                     ; NASM directive to produce 32 bit code
section .text               ; Begin the code (text) section
  ; MultiBoot Header
  align 4                   ; NASM directive that 'align' the next instruction,
                            ; It will align the next instruction on the next address that is a 4 multiple
                            ; This instruction is facultative but can improve performance
  dd 0x1BADB002             ; Magic Number to identify the header
  dd 0x00                   ; Flags (TODO : see multiple boot specification for further information)
  dd - (0x1BADB002 + 0x00)  ; CheckSum. m+f+c must be equal to 0

global start                ; NASM directive to set the start symbol as global
                            ; It is useful for linker to know where the start symbol is
global read_port
global write_port
global load_idt
global keyboard_handler

extern kmain                ; Declare kmain as an external function (declared in kernel.c)
extern keyboard_handler_main

; Allow to read byte from the given port
read_port:
  mov edx, [esp + 4]
  in al, dx ;al is the lower 8 bits of eax
            ;dx is the lower 16 bits of edx
  ret

; Allow to write a byte to the given port
write_port:
  mov   edx, [esp + 4]
  mov   al, [esp + 4 + 4]
  out   dx, al
  ret

; load the IDT table
load_idt:
  mov edx, [esp + 4]
  lidt [edx]
  sti          ;turn on interrupts
  ret

; declaring handler for Keyboard IRQs
keyboard_handler:
  call    keyboard_handler_main
  iretd

start:                      ; Start function
  cli                       ; Disable interruptions (CLear Interrups)
                            ; Otherwise CPU will be awake by them
  call kmain                ; Run the kernel
  hlt                       ; Halt the CPU TODO : Why ?

section .bss                ; TODO : What is the bss section ?
resb 8192                   ; Alloc 8KB for the stack
