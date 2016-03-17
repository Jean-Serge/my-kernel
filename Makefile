## Variables

BINDIR=./bin
SRCDIR=./src

## Rules

# Produce the kernel executable
kernel: entrypoint main ${SRCDIR}/link.ld
	ld -m elf_i386 -T ${SRCDIR}/link.ld -o ${BINDIR}/kernel ${BINDIR}/kasm.o ${BINDIR}/kc.o

# Produce the entrypoint for the bootload now what to launch at boot
entrypoint: ${SRCDIR}/kernel.asm
	nasm -f elf32 ${SRCDIR}/kernel.asm -o ${BINDIR}/kasm.o

# Produce the main executable
main: ${SRCDIR}/kernel.c
	gcc -m32 -c ${SRCDIR}/kernel.c -o ${BINDIR}/kc.o
