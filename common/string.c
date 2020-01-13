#include <stddef.h>
#include <stdio.h>


void* memcpy(void *dest, void *src, size_t n)
{
    char *dp = (char *)dest;
    char *sp = (char *)src;
    for (size_t i = 0; i < n; i++) {
        dp[i] = sp[i];
    }
    return dest;
}

void* memset(void *s, int c, size_t n)
{
    unsigned char *sp = (unsigned char *)s;
    for (size_t i = 0; i < n; i++) {
        sp[i] = (unsigned char) c;
    }
    return s;
}

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
    int i;
    for (i = 0; str1[i] != '\0' && str2[i] != '\0'; i++) {
        if (str1[i] != str2[i])
            return str1[i] - str2[i];
    }
    if (str1[i] != str2[i]) {
        return str1[i] - str2[i];
    }
    return 0;
}

void bzero(void *s, size_t n)
{
    char *p = (char *)s;
    for (size_t i = 0; i < n; i++) {
        p[i] = 0;
    }
}