## Variables

BINDIR=./bin
SRCDIR=./src
INCDIR=./include

KERNEL=${BINDIR}/kernel

## Rules

all: kernel

qemu: all
	qemu-system-i386 --kernel ${KERNEL}

# Produce the kernel executable
kernel: entrypoint main ${SRCDIR}/link.ld
	i386-elf-ld -m elf_i386 -T ${SRCDIR}/link.ld -o ${KERNEL} ${BINDIR}/kasm.o ${BINDIR}/kc.o ${BINDIR}/vga.o ${BINDIR}/keyboard.o

# Produce the entrypoint for the bootload now what to launch at boot
entrypoint: ${SRCDIR}/kernel.asm
	nasm -f elf ${SRCDIR}/kernel.asm -o ${BINDIR}/kasm.o

vga: ${SRCDIR}/vga.c ${INCDIR}/vga.h
	i386-elf-gcc -m32 -Wall -I include -c ${SRCDIR}/vga.c -o ${BINDIR}/vga.o

keyboard: ${SRCDIR}/keyboard.c ${INCDIR}/keyboard.h
	i386-elf-gcc -m32 -Wall -I include -c ${SRCDIR}/keyboard.c -o ${BINDIR}/keyboard.o


# Produce the main executable
main: keyboard vga ${SRCDIR}/kernel.c
	i386-elf-gcc -m32 -Wall -I include -c ${SRCDIR}/kernel.c -o ${BINDIR}/kc.o

## Clean up the project

.PHONY: clean mrproper

clean:
	rm -f ${BINDIR}/*.o

mrproper: clean
	rm ${BINDIR}/kernel
