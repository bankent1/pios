/*
 * timer.c
 *
 * Travis Banken
 * 1/12/2020
 *
 * System timer functions
 */

#include <mmio.h>
#include <kint.h>
#include <interrupt.h>
#include <timer.h>
#include <kdebug.h>

enum TIMER_PERIPHS {
    TIMER_BASE     = (PERI_BASE + 0x3000),
    TIMER_CS       = (TIMER_BASE + 0x0),
    TIMER_CTR_LO32 = (TIMER_BASE + 0x4),
    TIMER_CTR_HI32 = (TIMER_BASE + 0x8),
    TIMER_CMP0     = (TIMER_BASE + 0xc),
    TIMER_CMP1     = (TIMER_BASE + 0x10),
    TIMER_CMP2     = (TIMER_BASE + 0x14),
    TIMER_CMP3     = (TIMER_BASE + 0x18),
};

// map out the timer control register
typedef struct {
    u8 match0: 1;
    u8 match1: 1;
    u8 match2: 1;
    u8 match3: 1;
    u32 reserved: 28;
} TimerCSReg;

typedef struct {
    TimerCSReg control;
    u32 ctr_lo32;
    u32 ctr_hi32;
    u32 cmp0;
    u32 cmp1;
    u32 cmp2;
    u32 cmp3;
} TimerRegisters;

static TimerRegisters *timer_regs;

#define MAGIC_TICK 5

// protos
static void handler();
static void clearer();

static kbool initialized = FALSE;
static int timer_tick = 0;

int timer_init()
{
    KLOG("Initializing timer\n");
    if (initialized) {
        KLOG("ERROR -- Already Initialized!\n");
        return TIMER_ALREADY_INIT;
    }

    int rc;
    rc = register_irq_handler(IRQ_SYSTIMER1, handler, clearer);
    if (rc != INT_OK) {
        KLOG("ERROR -- Failed to register irq, rc %d\n", rc);
        return TIMER_SETUP_FAILED;
    }

    timer_regs = (TimerRegisters *)TIMER_BASE;

    initialized = TRUE;
    return TIMER_OK;
}

int timer_shutdown()
{
    if (!initialized) {
        KLOG("ERROR -- Never Initialized!\n");
        return TIMER_NEVER_INIT;
    }

    int rc;
    rc = deregister_irq_handler(IRQ_SYSTIMER1);
    if (rc != INT_OK) {
        KLOG("ERROR -- Failed to deregister irq, rc %d\n", rc);
        return TIMER_SHUTDOWN_FAILED;
    }

    timer_regs = NULL;

    initialized = FALSE;
    return TIMER_OK;
}

static void handler()
{
    KLOG("Timer interrupt!\n");
    timer_tick++;
    if (timer_tick == MAGIC_TICK) {
        KLOG("MAGIC TICK\n");
        timer_tick = 0;
        // TODO something like call dispatcher or something
    }
}

static void clearer()
{
    KLOG("Clearing timer interrupt\n");
    timer_regs->control.match1 = 1;
}