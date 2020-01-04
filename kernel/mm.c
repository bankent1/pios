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

typedef struct Frame {
	PTE page;
	u8 free;
} Frame;
Frame *frames;

static u8 mem_initialized = 0;
static u32 num_frames = 0;
static u32 page_size = 0;
static u32 mem_size = 0;

extern u8 __end;

int mem_init(u32 memsize, u32 pagesize)
{
	// TODO: checkmode
	KLOG("Initializing memory\n");
	if (mem_initialized) {
		KLOG("ERROR -- Already initialized!\n")
		return MEM_ALREADY_INIT;
	}

	mem_size = memsize;
	page_size = pagesize;
	num_frames = mem_size / page_size;

	// init frames data structure
	frames = (Frame *) &__end;
	for (u32 i = 0; i < num_frames; i++) {
		frames[i].free = 1;
	}

	mem_initialized = 1;
	KLOG("Initialized Memory with %d frames, sized %d\n", num_frames, page_size);
	return MEM_OK;
}

int mem_shutdown()
{
	// TODO: checkmode
	KLOG("Shutdown Called!\n");
	if (mem_initialized == 0) {
		return MEM_NOT_INIT;
	}

	// TODO
	// not sure this is necessary
	for (u32 i = 0; i < num_frames; i++) {
		frames[i].free = 1;
	}

	mem_initialized = 0;
	return MEM_OK;
}

u32 mem_get_pgsize()
{
	// TODO: checkmode
	return page_size;
}

u32 mem_get_msize()
{
	// TODO: checkmode
	return mem_size;
}

u32 mem_get_numframes()
{
	// TODO: checkmode
	return num_frames;
}

int mem_allocate_pt(int pid)
{
	// TODO: checkmode
	(void) pid;
	return MEM_OK;
}

int mem_free_pt(int pid)
{
	// TODO: checkmode
	(void) pid;
	return MEM_OK;
}

int mem_get_pt(int pid, PTE **table)
{
	// TODO: checkmode
	(void) pid;
	(void) table;
	return MEM_OK;
}