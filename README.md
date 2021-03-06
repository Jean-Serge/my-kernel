# my-kernel
Self-made Kernel

This project consists in building my own minimal kernel.
It starts following [this site](http://arjunsreedharan.org/post/82710718100/kernel-101-lets-write-a-kernel).

## Current Version

This version allow to build a simple bootable 32-bit kernel that will print a phrase (here it is *Welcome to my Kernel*) and allow keyboard input.

## Requirements

To build this project you need some tools :

+ Linux
+ nasm  (to compile assembly)
+ gcc   (to compile your main function)
+ ld    (to link your files)
+ qemu  (to test your kernel)
+ make

*Note that make is optional, it is of course possible to manually write each command.
But it will become really exhausting while the project is getting bigger.*

*Note also that using qemu is not necessary but it is a good and lightweight solution
to test your kernel.
You can use another virtualizer or even test it directly on a computer
(as long as you know what you are doing).*

### OSX

On OSX you can use the shell script to build a cross-compiler for this project.

## Build

The following command will build a kernel executable called **kernel**.

```bash
make
```


## Run in Qemu

You can test your kernel with Qemu running the following command.

```bash

qemu-system-i386 -kernel kernel

```

## Links

+ http://arjunsreedharan.org/post/82710718100/kernel-101-lets-write-a-kernel
+ http://arjunsreedharan.org/post/99370248137/kernel-201-lets-write-a-kernel-with-keyboard
+ https://github.com/arjun024/mkernel/
+ http://wiki.osdev.org
