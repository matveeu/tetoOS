#include "terminal.h"
#include "../../common/common.h"

void update_cursor() {
        int pos = cursor_y * 80 + cursor_x;
        outb(0x3D4, 0x0F);
        outb(0x3D5, (unsigned char)(pos & 0xFF));
        outb(0x3D4, 0x0E);
        outb(0x3D5, (unsigned char)((pos >> 8) & 0xFF));
}

void clear_screen() {
        for (unsigned int i = 0; i < 80 * 25 * 2; i += 2) {
                video[i] = ' ';
                video[i+1] = WHITEONBLACK;
        }
        cursor_x = 0;
        cursor_y = 0;
        //update_cursor();
}

void putchar(char c) {
        if (c == '\n') {
                cursor_x = 0;
                cursor_y++;
                //update_cursor();
        } else if (c == '\b') {
                if (cursor_x > 0) {
                        cursor_x--;
                        int pos = (cursor_y * 80 + cursor_x) *2;
                        video[pos] = ' ';
                        video[pos + 1] = WHITEONBLACK;
                        //update_cursor();
                }
        } else {
                int pos = (cursor_y * 80 + cursor_x) * 2;
                video[pos] = c;
                video[pos + 1] = WHITEONBLACK;
                cursor_x++;
                if (cursor_x >= 80) {
                        cursor_x = 0;
                        cursor_y++;
                }
                //update_cursor();
        }
        if (cursor_y >= 25) {
                for (unsigned int i = 0; i < 24 * 80 * 2; i++) {
                        video[i] = video[i + 80 * 2];
                }
                for (unsigned int i = 24 * 80 * 2; i < 25 * 80 * 2; i+=2) {
                        video[i] = ' ';
                        video [i + 1] = WHITEONBLACK;
                }
                cursor_y = 24;
                //update_cursor();
        }
        update_cursor();
}

void print(const char* str) {
        for (unsigned int i = 0; str[i] != '\0'; i++) {
                putchar(str[i]); 
        }
}