#ifndef __STRING_H
#define __STRING_H

void* memcpy(void *dest, const void *src, size_t n);
void* memset(void *s, int c, size_t n);
char* strcpy(char *dest, char *src);
char* strncpy(char *dest, char *src, size_t n);
size_t strlen(const char *str);
int strcmp(char *str1, char *str2);

#endif