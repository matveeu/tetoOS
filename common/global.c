#include "common.h"

char* video = (char*) VIDMEM;
int cursor_x = 0;
int cursor_y = 0;

char cmd_buffer[MAX_CMD];
int cmd_index = 0;

// Ввод-вывод через порты
unsigned char inb(unsigned short port) {
        unsigned char result;
        __asm__ volatile ("inb %1, %0" : "=a"(result) : "Nd"(port));
        return result;
}

void outb(unsigned short port, unsigned char data) {
        __asm__ volatile ("outb %0, %1" : : "a"(data), "Nd"(port));
}

void outw(unsigned short port, unsigned short data) {
        __asm__ volatile ("outw %0, %1" : : "a"(data), "Nd"(port));
}