## Variables

BINDIR=./bin
SRCDIR=./src
INCDIR=./include

KERNEL=${BINDIR}/kernel

## Rules

all: kernel

qemu: all
	qemu-system-x86_64 --kernel ${KERNEL}

# Produce the kernel executable
kernel: entrypoint main ${SRCDIR}/link.ld
	x86_64-pc-elf-ld -m elf_i386 -T ${SRCDIR}/link.ld -o ${KERNEL} ${BINDIR}/kasm.o ${BINDIR}/kc.o ${BINDIR}/vga.o

# Produce the entrypoint for the bootload now what to launch at boot
entrypoint: ${SRCDIR}/kernel.asm
	nasm -f elf ${SRCDIR}/kernel.asm -o ${BINDIR}/kasm.o

vga: ${SRCDIR}/vga.c ${INCDIR}/vga.h
	x86_64-pc-elf-gcc -m32 -Wall -I include -c ${SRCDIR}/vga.c -o ${BINDIR}/vga.o

# Produce the main executable
main: vga ${SRCDIR}/kernel.c
	x86_64-pc-elf-gcc -m32 -Wall -I include -c ${SRCDIR}/kernel.c -o ${BINDIR}/kc.o

## Clean up the project

.PHONY: clean mrproper

clean:
	rm -f ${BINDIR}/*.o

mrproper: clean
	rm ${BINDIR}/kernel
