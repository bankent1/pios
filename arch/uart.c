/*
 * UART Framework
 *
 * Author: Travis Banken
 */

#include <stddef.h>
#include <stdint.h>

#include <uart.h>

static inline uint32_t mmio_read(uint32_t reg);
static inline void mmio_write(uint32_t reg, uint32_t data);
static inline void delay(uint32_t amount);


// set up the registers of uart for use
void uart_init()
{
    // disable all aspects of uart hardware using control reg
    mmio_write(UART0_CR, 0x0);

    // set up the GPIO
    mmio_write(GPIOD, 0x0);
    delay(150);
    mmio_write(GPIODCLK0, (0x1 << 14) | (0x1 << 15));
    delay(150);

    // clear all pending interrupts
    mmio_write(UART0_ICR, 0x7FF);

    // set 115200 baud rate
    mmio_write(UART0_IBRD, 1);
    mmio_write(UART0_FBRD, 40);

    // b4: set FIFO mode
    // b5-6: data size 8-bit words
    mmio_write(UART0_LCRH, (0x1 << 4) | (0x1 << 5) |  (0x1 << 6));

    // set masks for the UART interrupts
    mmio_write(UART0_IMSC, (0x1 << 1) | (0x1 << 4) | (0x1 << 5) | (0x1 << 6)
                        | (0x1 << 7) | (0x1 << 8) | (0x1 << 9) | (0x1 << 10));

    // enable transmit and receive and enable uart
    mmio_write(UART0_CR, (0x1 << 0) | (0x1 << 8) | (0x1 << 9));
}



char uart_getc()
{
    while ((mmio_read(UART0_FR) >> 4) & 0x1); // busy wait until uart rx full

    return (char) mmio_read(UART0_DR);
}

void uart_putc(char c)
{
    while ((mmio_read(UART0_FR) >> 5) & 0x1); // busy wait until uart tx empty

    mmio_write(UART0_DR, (uint32_t) c);
}

// NOTE temp until stdio is made
void uart_puts(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        uart_putc(str[i]);
    }
}

static inline uint32_t mmio_read(uint32_t reg)
{
    return *(volatile uint32_t *)reg;
}

static inline void mmio_write(uint32_t reg, uint32_t data)
{
    *(volatile uint32_t *)reg = data;
}

static inline void delay(uint32_t amount)
{
    // not too sure about this :/
    asm volatile(
        "__delay_%=:"
        "subs %[amount], %[amount], #1;"
        "bne __delay_%="
        : "=r" (amount)
        : [amount]"0"(amount)
        : "cc"
        );
}