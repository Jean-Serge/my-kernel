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
extern kmain                ; Declare kmain as an external function (declared in kernel.c)

start:                      ; Start function
  cli                       ; Disable interruptions (CLear Interrups)
                            ; Otherwise CPU will be awake by them
  call kmain                ; Run the kernel
  hlt                       ; Halt the CPU TODO : Why ?

section .bss                ; TODO : What is the bss section ?
resb 8192                   ; Alloc 8KB for the stack
