## Variables

BINDIR=./bin
SRCDIR=./src
INCDIR=./include

KERNEL=${BINDIR}/kernel

CC=i386-elf-gcc
LD=i386-elf-ld

CFLAGS=-m32 --std=gnu99 -ffreestanding
CFLAGS+=-O2 -Wall -Wextra

INCLUDE=-I ${INCDIR}
## Rules

all: kernel

qemu: all
	qemu-system-i386 --kernel ${KERNEL}

# Produce the kernel executable
kernel: entrypoint main ${SRCDIR}/link.ld
	${LD} -m elf_i386 -T ${SRCDIR}/link.ld -o ${KERNEL} ${BINDIR}/*.o


# Produce the entrypoint for the bootload now what to launch at boot
entrypoint: ${SRCDIR}/kernel.asm
	nasm -f elf ${SRCDIR}/kernel.asm -o ${BINDIR}/kasm.o

vga: ${SRCDIR}/vga.c ${INCDIR}/vga.h
	${CC} ${CFLAGS} ${INCLUDE} -c ${SRCDIR}/vga.c -o ${BINDIR}/vga.o

keyboard: ${SRCDIR}/keyboard.c ${INCDIR}/keyboard.h
	${CC} ${CFLAGS} ${INCLUDE} -c ${SRCDIR}/keyboard.c -o ${BINDIR}/keyboard.o

string: ${SRCDIR}/string.c ${INCDIR}/string.h
	${CC} ${CFLAGS} ${INCLUDE} -c ${SRCDIR}/string.c -o ${BINDIR}/string.o

stdlib: ${SRCDIR}/stdlib.c ${INCDIR}/stdlib.h
	${CC} ${CFLAGS} ${INCLUDE} -c ${SRCDIR}/stdlib.c -o ${BINDIR}/stdlib.o

# Produce the main executable
main: string stdlib keyboard vga ${SRCDIR}/kernel.c
	${CC} ${CFLAGS} ${INCLUDE} -c ${SRCDIR}/kernel.c -o ${BINDIR}/kc.o

## Clean up the project

.PHONY: clean mrproper

clean:
	rm -f ${BINDIR}/*.o

mrproper: clean
	rm ${BINDIR}/kernel
