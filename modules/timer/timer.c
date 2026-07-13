#include "timer.h"
#include "../../common/common.h"

volatile unsigned int tick = 0;

void timer_handler() {
    tick++;
}

void init_timer() {
    outb(0x36, 0x43);
    outb(0x0C, 0x40);
    outb(0x00, 0x40);
}

unsigned int get_tick() {
    return tick;
}