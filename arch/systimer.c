/*
 * systimer.c
 *
 * Travis Banken
 * 1/12/2020
 *
 * System timer functions
 */

#include <mmio.h>

enum TIMER_PERIPHS {
    TIMER_BASE     = (PERI_BASE + 0x3000),
    TIMER_CTR_LO32 = (TIMER_BASE + 0x4),
    TIMER_CTR_HI32 = (TIMER_BASE + 0x8),
    TIMER_CMP0     = (TIMER_BASE + 0xc),
    TIMER_CMP1     = (TIMER_BASE + 0x10),
    TIMER_CMP2     = (TIMER_BASE + 0x14),
    TIMER_CMP3     = (TIMER_BASE + 0x18),
};

int systimer_init()
{
    return 0;
}

int systimer_shutdown()
{
    return 0;
}