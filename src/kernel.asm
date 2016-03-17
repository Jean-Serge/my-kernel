;; kernel.asm

;; This file contains assembly code to run the kernel.

bits 32                   ; NASM directive to produce 32 bit code
section .text             ; Begin the code (text) section
  ; multiboot spec
  align 4
  dd 0x1BADB002            ;magic
  dd 0x00                  ;flags
  dd - (0x1BADB002 + 0x00) ;checksum. m+f+c 

global start              ; NASM directive to set the start symbol as global
                          ; It is useful for linker to know where the start symbol is
extern kmain              ; Declare kmain as an external function (declared in kernel.c)

start:                    ; Start function
  cli                     ; Disable interruptions (CLear Interrups)
                          ; Otherwise CPU will be awake by them
  call kmain              ; Run the kernel
  hlt                     ; Halt the CPU TODO : Why ?

section .bss              ; TODO : What is the bss section ?
resb 8192                 ; Alloc 8KB for the stack
