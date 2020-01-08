#include <stddef.h>

char* strcpy(char *dest, char *src)
{
    char *destp = dest;
    char *srcp = src;

    while (*srcp != '\0') {
        *destp = *srcp;
        destp++;
        srcp++;
    }
    return dest;
}

char* strncpy(char *dest, char *src, size_t n)
{
    size_t i;
    for (i = 0; i < n && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    for (; i < n; i++) {
        dest[i] = '\0';
    }
    return dest;
}

size_t strlen(const char *str)
{
    int len;
    for (len = 0; str[len] != '\0'; len++); // empty loop
    return len;
}

int strcmp(char *str1, char *str2)
{
    (void) str1;
    (void) str2;
    return -1;
}