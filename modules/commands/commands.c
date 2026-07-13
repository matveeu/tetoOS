#include "commands.h"
#include "../../common/common.h"
#include "../bundle.h"
// help
void show_help() {
        print("Available commands:\n");
        print("  help     - show this message\n");
        print("  clear    - clear screen\n");
        print("  reboot   - restart system\n");
        print("  poweroff - shutdown PC\n");
}

void execute_command() {
        if (cmd_buffer[0] == 'h' && cmd_buffer[1] == 'e' && cmd_buffer[2] == 'l' && cmd_buffer[3] == 'p') {
                show_help();
        } else if (cmd_buffer[0] == 'c' && cmd_buffer[1] == 'l' && cmd_buffer[2] == 'e' && cmd_buffer[3] == 'a' && cmd_buffer[4] == 'r') {
                clear_screen();
        } else if (cmd_buffer[0] == 'r' && cmd_buffer[1] == 'e' && cmd_buffer[2] == 'b' && cmd_buffer[3] == 'o' && cmd_buffer[4] == 'o' && cmd_buffer[5] == 't') {
                print("Rebooting...\n");
                outb(0x64, 0xFE); 
                while(1);
        } else if (cmd_buffer[0] == 'p' && cmd_buffer[1] == 'o' && cmd_buffer[2] == 'w' && cmd_buffer[3] == 'e' && cmd_buffer[4] == 'r' && cmd_buffer[5] == 'o' && cmd_buffer[6] == 'f' && cmd_buffer[7] == 'f') {
                print("Shutting down...\n");
                outw(0x604, 0x2000);
                outw(0x4004, 0x3400);
                while(1);
        } else if (cmd_buffer[0] != '\0') {
                print("Unknown command: ");
                print(cmd_buffer);
                putchar('\n');
        }
}