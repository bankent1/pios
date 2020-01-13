/*
 * UART Framework
 *
 * Author: Travis Banken
 */

#include <stddef.h>

#include <kint.h>
#include <uart.h>
#include <mmio.h>

enum UART_PERIPHS {
    // UART0 registers
    UART0_BASE  = (GPIO_BASE + 0x1000),
    UART0_DR    = (UART0_BASE + 0x0),
    UART0_FR    = (UART0_BASE + 0x18),
    UART0_IBRD  = (UART0_BASE + 0x24),
    UART0_FBRD  = (UART0_BASE + 0x28),
    UART0_LCRH  = (UART0_BASE + 0x2c),
    UART0_CR    = (UART0_BASE + 0x30),
    UART0_IFLS  = (UART0_BASE + 0x34),
    UART0_IMSC  = (UART0_BASE + 0x38),
    UART0_RIS   = (UART0_BASE + 0x3c),
    UART0_MIS   = (UART0_BASE + 0x40),
    UART0_ICR   = (UART0_BASE + 0x44),
    UART0_DMACR = (UART0_BASE + 0x48),
    UART0_ITCR  = (UART0_BASE + 0x80),
    UART0_ITIP  = (UART0_BASE + 0x84),
    UART0_ITOP  = (UART0_BASE + 0x88),
    UART0_TDR   = (UART0_BASE + 0x8c),
};

// set up the registers of uart for use
void uart_init()
{
    // disable all aspects of uart hardware using control reg
    mmio_write(UART0_CR, 0x0);

    // set up the GPIO
    mmio_write(GPIOD, 0x0);
    mmio_delay(150);
    mmio_write(GPIODCLK0, (0x1 << 14) | (0x1 << 15));
    mmio_delay(150);

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

    mmio_write(UART0_DR, (u32) c);
}
