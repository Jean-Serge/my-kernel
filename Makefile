# Produce the kernel executable
kernel: entrypoint main
	ld -m elf_i386 -T link.ld -o kernel kasm.o kc.o

# Produce the entrypoint for the bootload now what to launch at boot
entrypoint: kernel.asm
	nasm -f elf32 kernel.asm -o kasm.o

# Produce the main executable
main: kernel.c
	gcc -m32 -c kernel.c -o kc.o
