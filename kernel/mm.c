/*
 * mm.c
 *
 * Author: Travis Banken
 *
 * Memory management code
 */

#include <kint.h>
#include <mm.h>
#include <kdebug.h>

static int mem_initialized = 0;
// static u32 mem_size = 0;

int mem_init()
{
	KLOG("Initializing memory\n");
	if (mem_initialized) {
		KLOG("ERROR -- Already initialized!\n")
		return MEM_ALREADY_INIT;
	}

	// TODO

	mem_initialized = 1;
	return MEM_OK;
}

int mem_shutdown()
{
	KLOG("Shutdown Called!\n");
	if (mem_initialized == 0) {
		return MEM_NOT_INIT;
	}
	// TODO

	return MEM_OK;
}

int mem_allocate_pt(int pid)
{
	(void) pid;
	return MEM_OK;
}

int mem_free_pt(int pid)
{
	(void) pid;
	return MEM_OK;
}

int mem_get_pt(int pid, PTE **table)
{
	(void) pid;
	(void) table;
	return MEM_OK;
}