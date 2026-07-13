#include "idt.h"
#include "../../common/common.h"

struct idt_entry {
    unsigned short base_low;
    unsigned short selector;
    unsigned char zero;
    unsigned char flags;
    unsigned short base_high;
} __attribute__((packed));

struct idt_ptr {
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

struct idt_entry idt_entries[256];
struct idt_ptr idt_ptr;

void idt_set_gate(int num, unsigned int base, unsigned short selector, unsigned char flags) {
    idt_entries[num].base_low = base & 0xFFFF;
    idt_entries[num].base_high = (base >> 16) & 0xFFFF;
    idt_entries[num].selector = selector;
    idt_entries[num].zero = 0;
    idt_entries[num].flags = flags;
}

void idt_init() {
    idt_ptr.limit = sizeof(idt_entries) - 1;
    idt_ptr.base = (unsigned int) &idt_entries;
    __asm__ volatile ("lidt (%0)" : : "r" (&idt_ptr));
}