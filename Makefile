ASM = nasm
CC = gcc
LD = ld
CFLAGS = -m32 -ffreestanding -nostdlib -nostartfiles -Wall -fno-stack-protector -fno-pie
LDFLAGS = -m elf_i386 -T linker.ld

OBJS = boot.o kernel.o

all: myos.bin

boot.o: boot.asm
	 $(ASM) -f elf32 boot.asm -o boot.o

kernel.o: kernel.c
	  $(CC) $(CFLAGS) -c kernel.c -o kernel.o

myos.bin: $(OBJS)
	  $(LD) $(LDFLAGS) -o myos.bin $(OBJS)

clean:
	rm -f *.o myos.bin

run: myos.bin
	qemu-system-i386 -kernel myos.bin
