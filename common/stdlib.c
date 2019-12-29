#include <stddef.h>

void* memcpy(void *dest, const void *src, size_t n)
{
    unsigned char *dp = (unsigned char *)dest;
    unsigned char *sp = (unsigned char *)src;
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

char* itoa(int value, char *str, int base)
{
    char *sp = str;

    // check negative on base 10
    int neg = value < 0;
    unsigned int uval = value;
    if (base == 10 && neg) {
        uval = -value;
        *sp = '-';
        sp++;
    }

    int offset;
    while (uval != 0) {
        offset = uval % base;
        if (offset >= 10) {
            *sp = (char) ((offset - 10) + 'A');
        } else {
            *sp = (char) (offset + '0');
        }
        uval = uval / base;
        sp++;
    }
    *sp = '\0';

    // reverse string
    char *end = sp - 1;
    char *start = neg && base == 10 ? str + 1 : str;
    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
    return str;
}
