#include <test.h>
#include <kint.h>
#include <uart.h>

void test_main(u32 r0, u32 r1, u32 atags)
{
    (void) r0;
    (void) r1;
    (void) atags;

    uart_init();

    test_common();
}