/*
 * interrupts.c
 *
 * Author: Travis Banken
 *
 * Deal with interrupts
 */

#include <kint.h>
#include <interrupt.h>
#include <kdebug.h>
#include <mmio.h>
#include <string.h>

#define NUM_IRQ 72
#define NUM_HANDLERS NUM_IRQ
#define NUM_CLEARERS NUM_IRQ

enum IRQ_PERIPH {
    IRQ_BASE            = (PERI_BASE + 0xb000 + 0x200),
    ARM_SPEC_PENDING    = (IRQ_BASE + 0x00),
    GPU_SHARED_PENDING1 = (IRQ_BASE + 0x04),
    GPU_SHARED_PENDING2 = (IRQ_BASE + 0x08),
    FAST_IRQ_CONTROL    = (IRQ_BASE + 0x0c),
    GPU_SHARED_ENABLE1  = (IRQ_BASE + 0x10),
    GPU_SHARED_ENABLE2  = (IRQ_BASE + 0x14),
    ARM_SPEC_ENABLE     = (IRQ_BASE + 0x18),
    GPU_SHARED_DISABLE1 = (IRQ_BASE + 0x1c),
    GPU_SHARED_DISABLE2 = (IRQ_BASE + 0x20),
    ARM_SPEC_DISABLE    = (IRQ_BASE + 0x24),
};

#define GPU_SHARED_IRQ1(irq_num) ((irq_num) <= 31)
#define GPU_SHARED_IRQ2(irq_num) ((irq_num) >= 32 && (irq_num) <= 63)
#define ARM_SPECIFIC_IRQ(irq_num) ((irq_num) >= 64 && (irq_num) <= 71)


typedef struct IrqRegs {
    u32 arm_spec_pending;
    u32 gpu_shared_pending1;
    u32 gpu_shared_pending2;
    u32 fast_irq_control;
    u32 gpu_shared_enable1;
    u32 gpu_shared_enable2;
    u32 arm_spec_enable;
    u32 gpu_shared_disable1;
    u32 gpu_shared_disable2;
    u32 arm_spec_disable;
} IrqRegs;
static IrqRegs *irq_regs;

// helper prototypes
static inline kbool irq_pending(u32 irq_num);

// defined in int_vec.s
void move_exception_vector();

typedef void (*interrupt_handlers_f)(void);
typedef void (*interrupt_clearers_f)(void);

static interrupt_handlers_f handlers[NUM_HANDLERS];
static interrupt_clearers_f clearers[NUM_CLEARERS];


static kbool int_intitialized = FALSE;

int interrupt_init()
{
    KLOG("Initializing interrupts\n");
    if (int_intitialized) {
        KLOG("ERROR -- Already Initialized\n");
        return INT_ALREADY_INIT;
    }

    irq_regs = (IrqRegs *)IRQ_BASE;

    bzero((void*)handlers, sizeof(interrupt_handlers_f) * NUM_HANDLERS);
    bzero((void*)clearers, sizeof(interrupt_clearers_f) * NUM_CLEARERS);
    bzero((void*)&irq_regs, sizeof(IrqRegs));
    // TODO disable all interrupts
    move_exception_vector();

    int_intitialized = TRUE;

    enable_int();
    return INT_OK;
}

int interrupt_shutdown()
{
    KLOG("Shutting down interrupt\n");
    if (!int_intitialized) {
        KLOG("ERROR -- Not Initialized\n");
        return INT_NEVER_INIT;
    }

    int_intitialized = FALSE;
    disable_int();
    return INT_OK;
}

int register_irq_handler(enum IRQ_NUM irq_num, void (*handler)(void), void (*clearer)(void))
{
    if (!int_intitialized) {
        KLOG("ERROR -- Not Initialized\n");
        return INT_NEVER_INIT;
    }

    if (irq_num >= NUM_IRQ) {
        KLOG("ERROR -- Invalid irq num %d\n", irq_num);
        return INT_INVALID_IRQ;
    }

    if (handler == NULL) {
        KLOG("ERROR -- Handler is NULL\n");
        return INT_NULL_HANDLER;
    }

    if (clearer == NULL) {
        KLOG("ERROR -- Clearer is NULL\n");
        return INT_NULL_CLEARER;
    }

    handlers[irq_num] = handler;
    clearers[irq_num] = clearer;
    u32 irq_bit;
    if (GPU_SHARED_IRQ1(irq_num)) {
        irq_bit = irq_num - 0;
        irq_regs->gpu_shared_enable1 |= (1 << irq_bit);
    } else if (GPU_SHARED_IRQ2(irq_num)) {
        irq_bit = irq_num - 32;
        irq_regs->gpu_shared_enable2 |= (1 << irq_bit);
    } else if (ARM_SPECIFIC_IRQ(irq_num)) {
        irq_bit = irq_num - 64;
        irq_regs->arm_spec_enable |= (1 << irq_bit);
    }
    return INT_OK;
}

int deregister_irq_handler(enum IRQ_NUM irq_num)
{
    if (!int_intitialized) {
        KLOG("ERROR -- Not Initialized\n");
        return INT_NEVER_INIT;
    }

    if (irq_num >= NUM_IRQ) {
        KLOG("ERROR -- Invalid irq num %d\n", irq_num);
        return INT_INVALID_IRQ;
    }

    handlers[irq_num] = NULL;
    clearers[irq_num] = NULL;
    u32 irq_bit;
    if (GPU_SHARED_IRQ1(irq_num)) {
        irq_bit = irq_num - 0;
        irq_regs->gpu_shared_disable1 |= (1 << irq_bit);
    } else if (GPU_SHARED_IRQ2(irq_num)) {
        irq_bit = irq_num - 32;
        irq_regs->gpu_shared_disable2 |= (1 << irq_bit);
    } else if (ARM_SPECIFIC_IRQ(irq_num)) {
        irq_bit = irq_num - 64;
        irq_regs->arm_spec_disable |= (1 << irq_bit);
    }
    return INT_OK;
}

// *** interrupt handlers ***

// called from asm wrapper for some special instructions which __attribute__
// will not cover. See int_vec.s for impl
void irq_handler()
{
    KLOG("IRQ HANDLER\n");
    // find out what triggered irq and handle
    for (u32 i = 0; i < NUM_IRQ; i++) {
        if (irq_pending(i) && handlers[i] != NULL) {
            clearers[i]();
            // enable interrupts to allow nested interrupts
            enable_int();
            handlers[i]();
            disable_int();
        }
    }
    while (1);
}

void __attribute__ ((interrupt ("ABORT"))) reset_handler()
{
    KLOG("RESET HANDLER\n");
    // TODO reset kernel
    while (1);
}

void __attribute__ ((interrupt ("ABORT"))) prefetch_abort_handler()
{
    KLOG("PREFETCH ABORT HANDLER\n");
    // TODO kill offending process
    while (1);
}

void __attribute__ ((interrupt ("ABORT"))) data_abort_handler()
{
    KLOG("DATA ABORT HANDLER\n");
    // TODO kill offending process
    while (1);
}

void __attribute__ ((interrupt ("UNDEF"))) undefined_instruction_handler()
{
    KLOG("UNDEFINED INSTRUCTION HANDLER\n");
    // TODO kill offending process
    while (1);
}

void __attribute__ ((interrupt ("SWI"))) software_interrupt_handler()
{
    KLOG("SOFTWARE INTERRUPT HANDLER\n");
    // TODO perform previleged operation and return to caller
    while (1);
}

void __attribute__ ((interrupt ("FIQ"))) fast_irq_handler()
{
    KLOG("FAST IRQ HANDLER\n");
    while (1);
}

// *** helper functions ***
static inline kbool irq_pending(u32 irq_num)
{
    if (irq_num < 32) {
        return (irq_regs->gpu_shared_pending1 >> irq_num) & 0x1;
    } else if (irq_num < 64) {
        return (irq_regs->gpu_shared_pending2 >> irq_num) & 0x1;
    } else {
        return (irq_regs->arm_spec_pending >> irq_num) & 0x1;
    }
}