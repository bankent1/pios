/*
 * mm.c
 *
 * Author: Travis Banken
 *
 * Memory management code
 */

#include <kint.h>
#include <mm.h>

static int mem_initialized = 0;
// static u32 mem_size = 0;

int mem_init()
{
	if (mem_initialized) {
		return MEM_ALREADY_INIT;
	}

	// TODO

	mem_initialized = 1;
	return MEM_OK;
}