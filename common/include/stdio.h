#ifndef __STDIO_H
#define __STDIO_H

#include <stdarg.h>

char getc();
void putc(char c);
void puts(char *s);
void gets(char *buf, size_t len);
int kprintf(const char *format, ...);
int vkprintf(const char *format, va_list args);

#endif
