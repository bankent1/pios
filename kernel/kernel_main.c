/*
 * Entry point for the kernel
 *
 * Travis Banken
 */

#include <stddef.h>
#include <stdint.h>

#include <uart.h>


void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags)
{
	// deal with these later
	(void) r0;
	(void) r1;
	(void) atags;
	
	uart_init();

	// TODO: print out stuff
	uart_puts("Hello, kernel world!\n");

	while (1) {
		uart_putc(uart_getc());
	}
}