ASM = nasm
CC = gcc
LD = ld
CFLAGS = -m32 -ffreestanding -nostdlib -nostartfiles -Wall -fno-stack-protector -fno-pie -I./
LDFLAGS = -m elf_i386 -T linker.ld

SRC = main.c common/global.c modules/terminal/terminal.c modules/keyboard/keyboard.c modules/commands/commands.c
OBJS = $(SRC:.c=.o) boot.o 

all: myos.bin

boot.o: boot.asm
	$(ASM) -f elf32 boot.asm -o boot.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

myos.bin: $(OBJS)
	$(LD) $(LDFLAGS) -o myos.bin $(OBJS)

clean:
	rm -f *.o */*.o */*/*.o myos.bin

run: myos.bin
	qemu-system-i386 -kernel myos.bin
