char* video = (char*) 0xB8000;
int cursor_x = 0;
int cursor_y = 0;

char cmd_buffer[64];
int cmd_index = 0;

void clearScreen() {
        for (unsigned int i = 0; i < 80 * 25 * 2; i += 2) {
                video[i] = ' ';
                video[i+1] = 0x0F;
        }
        cursor_x = 0;
        cursor_y = 0;
}

unsigned char inb(unsigned short port) {
        unsigned char result;
        __asm__ volatile ("inb %1, %0" : "=a"(result) : "Nd"(port));
        return result;
}

void putchar(char c) {
        if (c == '\n') {
                cursor_x = 0;
                cursor_y++;
        } else {
                int pos = (cursor_y * 80 + cursor_x) * 2;
                video[pos] = c;
                video[pos + 1] = 0x0F;
                cursor_x++;
                if (cursor_x >= 80) {
                        cursor_x = 0;
                        cursor_y++;
                }
        }
        if (cursor_y >= 25) {
                for (unsigned int i = 0; i < 24 * 80 * 2; i++) {
                        video[i] = video[i + 80 * 2];
                }
                for (unsigned int i = 24 * 80 * 2; i < 25 * 80 * 2; i+=2) {
                        video[i] = ' ';
                        video [i + 1] = 0x0F;
                }
                cursor_y = 24;
        }
}

void print(const char* str) {
        for (unsigned int i = 0; str[i] != '\0'; i++) {
                putchar(str[i]);
        }
}

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

void kmain() {
        clearScreen();
        print("TetoOS v1.0.1\n");
        print("Type something...\n");
        print("> ");

        while(1) {
                char ch = getchar();

                if (ch == '\n') {
                        putchar('\n');
                        cmd_buffer[cmd_index] = '\0';
                        print("> ");

                        cmd_index = 0;
                        for (unsigned int i = 0; i < 64; i++) cmd_buffer[i] = '\0';
                }
                else if (ch == '\b') {
                        if (cmd_index > 0) {
                                cmd_index--;
                                putchar('\b');
                                putchar(' ');
                                putchar('\b');
                        }
                }
                else {
                        if (cmd_index < 64 - 1) {
                                cmd_buffer[cmd_index++] = ch;
                                putchar(ch);
                        }
                }
        }
}
