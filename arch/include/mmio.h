#ifndef __MMIO_H
#define __MMIO_H

#include <kint.h>

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

};

static inline u32 mmio_read(u32 reg)
{
    return *(volatile u32 *)reg;
}

static inline void mmio_write(u32 reg, u32 data)
{
    *(volatile u32 *)reg = data;
}

static inline void mmio_delay(u32 amount)
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

#endif