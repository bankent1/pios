/*
 * interrupts.c
 *
 * Author: Travis Banken
 *
 * Deal with interrupts
 */

#include <kint.h>
#include <interrupts.h>

inline int int_enabled()
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

inline void disable_int()
{
	asm volatile (
		"cpsie i"
	);
}

inline int enable_int()
{
	u8 prev_on = 0;
	if (int_enabled()) {
		prev_on = 1;
	}

	asm volatile (
		"cpsid i"
	);
	return prev_on;
}