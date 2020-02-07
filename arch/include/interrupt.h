#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H

#include <kint.h>

// TODO fill out
enum IRQ_NUM {
    IRQ_SYSTIMER1 = 1,
    IRQ_USB       = 9,
    IRQ_ARM_TIMER = 64, 
};


static inline int int_enabled()
{
    // read CPRS reg into res
    u32 res;
    asm volatile (
        "mrs %[res], CPSR"
        : [res] "=r" (res)
        ::
    );

    return (res >> 7) & 0x1;
}

static inline void disable_int()
{
    // CPS Interrupt Enable IRQ
    asm volatile (
        "cpsie i"
    );
}

static inline int enable_int()
{
    u8 prev_on = 0;
    if (int_enabled()) {
        prev_on = 1;
    }

    // CPS Interrupt Disable IRQ
    asm volatile (
        "cpsid i"
    );
    return prev_on;
}


int interrupt_init();
int interrupt_shutdown();
int register_irq_handler(enum IRQ_NUM irq_num, void (*handler)(void), void (*clearer)(void));
int deregister_irq_handler(enum IRQ_NUM irq_num);
void irq_handler();
void __attribute__ ((interrupt ("SWI"))) reset_handler();
void __attribute__ ((interrupt ("ABORT"))) prefetch_abort_handler();
void __attribute__ ((interrupt ("ABORT"))) data_abort_handler();
void __attribute__ ((interrupt ("UNDEF"))) undefined_instruction_handler();
void __attribute__ ((interrupt ("SWI"))) software_interrupt_handler();
void __attribute__ ((interrupt ("FIQ"))) fast_irq_handler();

// error codes
#define INT_OK 0
#define INT_ALREADY_INIT 1
#define INT_NEVER_INIT 2
#define INT_INVALID_IRQ 3
#define INT_NULL_HANDLER 4
#define INT_NULL_CLEARER 5

#endif