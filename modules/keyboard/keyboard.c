#include "keyboard.h"
#include "../../common/common.h"

// Таблица символов
char keymap[] = {
        0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0, 0,
        'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', 0, 0,
        'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,
        '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' '
};

char getchar() {
        unsigned char scancode;
        while (1) {
                while ((inb(0x64) & 1) == 0);
                scancode = inb(0x60);

                /*if (scancode >= 0x80) continue;
                if (scancode == 0xE0) {
                                while ((inb(0x64) & 1) == 0);
                                scancode = inb(0x60);
                                if (scancode >= 0x80) continue;
                                if (scancode == 0x48) return 0x80;
                                if (scancode == 0x50) return 0x81;
                                continue;
                } */
                if (scancode < 0x80) {
                        if (scancode == 0x1C) return '\n';
                        if (scancode == 0x0E) return '\b';
                        if (scancode < sizeof(keymap)) {
                                char ch = keymap[scancode];
                                if (ch != 0) return ch;
                        }
                }
        }
}