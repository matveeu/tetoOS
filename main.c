#include "common/common.h"
#include "modules/bundle.h"

// История команд (на стадии разработки)
/*#define HISTORY_SIZE 8
char history[HISTORY_SIZE][MAX_CMD];
int history_count = 0;
int history_pos = -1;

void add_history(const char* cmd) {
        if (cmd[0] == '\0') return;
        for (int i = HISTORY_SIZE - 1; i > 0; i--) {
                for (int j = 0; j < MAX_CMD; j++) {
                        history[i][j] = history[i-1][j];
                }
        }

        for (int i = 0; i < MAX_CMD && cmd[i] != '\0'; i++) {
                history[0][i] = cmd[i];
                history[0][i+1] = '\0';
        }
        if (history_count < HISTORY_SIZE) history_count++;
        history_pos = -1;
}

void load_history(int offset) {
        int new_pos = history_pos + offset;
        if (new_pos < -1 || new_pos >= history_count) return;
        history_pos = new_pos;

        while (cmd_index > 0) {
                putchar('\b');
                cmd_index--;
        }

        if (history_pos == -1) {
                for (int i = 0; i < MAX_CMD; i++) cmd_buffer[i] = '\0';
                return;
        }

        for (int i = 0; i < MAX_CMD; i ++) {
                cmd_buffer[i] = history[history_pos][i];
                if (cmd_buffer[i] == '\0') break;
                putchar(cmd_buffer[i]);
                cmd_index = i+1;
        }
}*/

void kmain() {
        clear_screen();
        print("TetoOS v1.0.6\n");
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
                        }
                } /*
                else if (ch == 0x80) {
                        load_history(-1);
                }
                else if (ch == 0x81) {
                        load_history(1);
                } */ 
                else {
                        if (cmd_index < MAX_CMD - 1) {
                                cmd_buffer[cmd_index++] = ch;
                                putchar(ch);
                        }
                }
                //putchar(ch); // Для отладки
        }

}