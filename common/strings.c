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