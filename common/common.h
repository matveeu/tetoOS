#ifndef COMMON_H
#define COMMON_H

#define VIDMEM 0xB8000
#define WHITEONBLACK 0x0F
#define MAX_CMD 512

extern char* video;
extern int cursor_x;
extern int cursor_y;
extern char cmd_buffer[MAX_CMD];
extern int cmd_index;

unsigned char inb(unsigned short port);
void outb(unsigned short port, unsigned char data);
void outw(unsigned short port, unsigned short data);

#endif