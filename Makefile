## Variables

BINDIR=./bin
SRCDIR=./src

KERNEL=${BINDIR}/kernel

## Rules

all: kernel

qemu: all
	qemu-system-x86_64 --kernel ${KERNEL}

# Produce the kernel executable
kernel: entrypoint main ${SRCDIR}/link.ld
	ld -m elf_i386 -T ${SRCDIR}/link.ld -o ${KERNEL} ${BINDIR}/kasm.o ${BINDIR}/kc.o

# Produce the entrypoint for the bootload now what to launch at boot
entrypoint: ${SRCDIR}/kernel.asm
	nasm -f elf32 ${SRCDIR}/kernel.asm -o ${BINDIR}/kasm.o

# Produce the main executable
main: ${SRCDIR}/kernel.c
	gcc -m32 -c ${SRCDIR}/kernel.c -o ${BINDIR}/kc.o

## Clean up the project

.PHONY: clean mrproper

clean:
	rm -f ${BINDIR}/*.o

mrproper: clean
	rm ${BINDIR}/kernel
