#include <stddef.h>


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
