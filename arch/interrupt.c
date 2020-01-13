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


static kbool int_intitialized = FALSE;

int interrupt_init()
{
	if (int_intitialized) {
		return INT_ALREADY_INIT;
	}

	int_intitialized = TRUE;

	return INT_OK;
}

int interrupt_shutdown()
{
	if (!int_intitialized) {
		return INT_NEVER_INIT;
	}

	int_intitialized = FALSE;
	return INT_OK;
}

// *** interrupt handlers ***

// called from asm wrapper for some special instructions which __attribute__
// will not cover. See int_vec.s for impl
void irq_handler()
{
	KLOG("IRQ HANDLER\n");
	while (1);
}

void __attribute__ ((interrupt ("SWI"))) reset_handler()
{
	KLOG("RESET HANDLER\n");
	while (1);
}

void __attribute__ ((interrupt ("ABORT"))) prefetch_abort_handler()
{
	KLOG("PREFETCH ABORT HANDLER\n");
	while (1);
}

void __attribute__ ((interrupt ("ABORT"))) data_abort_handler()
{
	KLOG("DATA ABORT HANDLER\n");
	while (1);
}

void __attribute__ ((interrupt ("UNDEF"))) undefined_instruction_handler()
{
	KLOG("UNDEFINED INSTRUCTION HANDLER\n");
	while (1);
}

void __attribute__ ((interrupt ("SWI"))) software_interrupt_handler()
{
	KLOG("SOFTWARE INTERRUPT HANDLER\n");
	while (1);
}

void __attribute__ ((interrupt ("FIQ"))) fast_irq_handler()
{
	KLOG("FAST IRQ HANDLER\n");
	while (1);
}
