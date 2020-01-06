/*
 * kpsr.c
 *
 * Author: Travis Banken
 *
 * Functions related to PSR
 * ARM manual A2.5
 */

#include <kint.h>

u8 psr_getmode()
{
	u32 psr;
	asm volatile (
		"mrs %[psr], CPSR"
		: [psr] "=r" (psr)
		::
	);

	// want bits 0-4
	return psr & 0b11111;
}
