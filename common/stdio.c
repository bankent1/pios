#include <stdio.h>
#include <uart.h>
#include <stdlib.h>
#include <string.h>

#define PF_BUF_SIZE 32

char getc()
{
    return uart_getc();
}

void putc(char c)
{
    uart_putc(c);
}

void puts(char *s)
{
    for (int i = 0; s[i] != '\0'; i++) {
        putc(s[i]);
    }
}

void gets(char *buf, size_t len)
{
    (void) len;
    (void) buf;
    // TODO: handle newline
    // int i;
    // for (i = 0; i < (len - 1); i++) {
    //  buf[i] = getc();
    // }
}

// return num chars written on success, else -1
int vkprintf(const char *format, va_list args)
{
    char buf[PF_BUF_SIZE];
    char *str;


    int nprinted = 0;
    int fmtstart= 0;
    char *sp = (char *) format;
    while (*sp != '\0') {
        if (fmtstart) {
            switch(*sp) {
            case 'd':
                memset((void *) buf, '\0', PF_BUF_SIZE);
                int d = va_arg(args, int);
                char *dtoa = itoa(d, buf, 10);
                puts(dtoa);
                // nprinted += strlen(dtoa);
                break;
            case 'x':
                memset((void *) buf, '\0', PF_BUF_SIZE);
                int x = va_arg(args, int);
                char *xtoa = itoa(x, buf, 16);
                puts(xtoa);
                // nprinted += strlen(xtoa);
                break;
            case 's':
                str = va_arg(args, char *);
                puts(str);
                // nprinted += strlen(str);
                break;
            default:
                putc('%');
                // print % we didn't print earlier
                break;
            }
            fmtstart = 0;
        }
        else if ((sp == format && *sp == '%') 
            || (*sp == '%' && *(sp - 1) != '\\')) {
            fmtstart = 1;
            nprinted++;
        }
        else {
            putc(*sp);
        }
        sp++;
    }


    return nprinted;
}

int kprintf(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    int rc = vkprintf(format, args);
    va_end(args);
    return rc;
}
