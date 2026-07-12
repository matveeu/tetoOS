char* video = (char*) 0xB8000;
int cursor_x = 0;
int cursor_y = 0;

#define MAX_CMD 128
char cmd_buffer[MAX_CMD];
int cmd_index = 0;

// Очистка экрана
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

void outb(unsigned short port, unsigned char data) {
        __asm__ volatile ("outb %0, %1" : : "a"(data), "Nd"(port));
}

// Размещение символа в видеопамять
void putchar(char c) {
        if (c == '\n') {
                cursor_x = 0;
                cursor_y++;
        } else if (c == '\b') {
                if (cursor_x > 0) {
                        cursor_x--;
                        int pos = (cursor_y * 80 + cursor_x) *2;
                        video[pos] = ' ';
                        video[pos + 1] = 0x0F;
                }
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

// Печать строки
void print(const char* str) {
        for (unsigned int i = 0; str[i] != '\0'; i++) {
                putchar(str[i]);
        }
}

// Таблица символов
char keymap[] = {
        0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0, 0,
        'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', 0, 0,
        'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,
        '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' '
};

// Получение символа с клавиатуры
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

// ===== КОМАНДЫ =====

// help
void show_help() {
        print("Available commands:\n");
        print("  help     - show this message\n");
        print("  clear    - clear screen\n");
        print("  reboot   - restart system\n");
}

// Сами команды
void execute_command() {
        if (cmd_buffer[0] == 'h' && cmd_buffer[1] == 'e' && cmd_buffer[2] == 'l' && cmd_buffer[3] == 'p') {
                show_help();
        } else if (cmd_buffer[0] == 'c' && cmd_buffer[1] == 'l' && cmd_buffer[2] == 'e' && cmd_buffer[3] == 'a' && cmd_buffer[4] == 'r') {
                clearScreen();
        } else if (cmd_buffer[0] == 'r' && cmd_buffer[1] == 'e' && cmd_buffer[2] == 'b' && cmd_buffer[3] == 'o' && cmd_buffer[4] == 'o' && cmd_buffer[5] == 't') {
                print("Rebooting...\n");
                outb(0x64, 0xFE); 
                while(1);
        } else if (cmd_buffer[0] != '\0') {
                print("Unknown command: ");
                print(cmd_buffer);
                putchar('\n');
        }
}

void kmain() {
        clearScreen();
        print("TetoOS v1.0.3\n");
        print("Type 'help' for commands.\n");
        print("> ");

        while(1) {
                char ch = getchar();

                if (ch == '\n') {
                        putchar('\n');
                        cmd_buffer[cmd_index] = '\0';
                        execute_command();
                        print("> ");

                        cmd_index = 0;
                        for (unsigned int i = 0; i < MAX_CMD; i++) cmd_buffer[i] = '\0';
                }
                else if (ch == '\b') {
                        if (cmd_index > 0) {
                                cmd_index--;
                                putchar('\b');
                                // putchar(' ');
                                // putchar('\b');
                        }
                }
                else {
                        if (cmd_index < MAX_CMD - 1) {
                                cmd_buffer[cmd_index++] = ch;
                                putchar(ch);
                        }
                }
        }
}
