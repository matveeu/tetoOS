#ifndef TERMINAL_H
#define TERMINAL_H

// Обновление аппаратного курсора
void update_cursor();

// Очистка экрана
void clear_screen();

// Размещение символа в видеопамять
void putchar(char c);

// Печать строки
void print(const char* str);

#endif