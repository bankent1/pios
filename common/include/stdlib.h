#ifndef __STDLIB_H
#define __STDLIB_H

void* memcpy(void *dest, const void *src, size_t n);
void* memset(void *s, int c, size_t n);
char* itoa(int value, char *str, int base);

#endif