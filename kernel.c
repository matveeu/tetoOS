#define VIDMEM 0xB8000
#define WOB 0x0F

void kmain() {
        char* video = (char*) VIDMEM;
        const char* msg = "Hello, tetoOS!";
        for (int i = 0; msg[i] != '\0'; i++) {
                video[i * 2] = msg[i];
                video[i * 2 + 1] = WOB;
        }
        while(1);
}
