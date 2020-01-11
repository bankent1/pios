#ifndef __PERIPHS_H
#define __PERIPHS_H

enum Peripherals {
#ifdef MODEL_1
    PERI_BASE = 0x20000000,
    // UART0_BASE = 0x20201000,
#else
    PERI_BASE = 0x3f000000,
    // UART0_BASE = 0x3F201000,
#endif
    PERI_SIZE = 0x01000000,

    // GPIO registers
    GPIO_BASE = (PERI_BASE + 0x200000),
    GPIOD     = (GPIO_BASE + 0x94),
    GPIODCLK0 = (GPIO_BASE + 0x98),

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

#endif