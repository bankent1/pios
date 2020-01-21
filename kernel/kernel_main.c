/*
 * Entry point for the kernel
 *
 * Travis Banken
 *
 * ATAGS information can be found here
 * http://www.simtec.co.uk/products/SWLINUX/files/booting_article.html#appendix_tag_reference
 */

#include <stddef.h>

#include <kint.h>
#include <uart.h>
#include <stdio.h>
#include <mm.h>
#include <interrupt.h>
#include <kdebug.h>
#include <proc.h>

#ifdef VIRTUALIZED
#define QEMU_MEM_SIZE_MB 256
#endif

#define ATAGS_CORE 0x54410001
#define ATAGS_MEM 0x54410002
#define ATAGS_CMDLINE 0x54410009
#define ATAGS_NONE 0x0

#define PAGE_SIZE (4 * 1024) // 4KB

static u32 MEM_SIZE;


// prototypes
static void init_all();
static void shutdown_all();
static void panic();

struct atag_mem {
	u32 size;
	u32 start; // physical start addr
};

void kernel_main(u32 r0, u32 r1, u32 atags)
{
	// deal with these later
	(void) r0;
	(void) r1;
	(void) atags;

	// TODO this is borked :/
	// grab atags info
	// u32 *atag = (u32 *) atags;
	// struct atag_mem *memtag = NULL;
	// while (*atag != ATAGS_NONE) {
	// 	switch (*atag) {
	// 	case ATAGS_CORE:
	// 		// TODO
	// 		break;
	// 	case ATAGS_MEM:
	// 		memtag = (struct atag_mem *)ATAGS_MEM;
	// 		break;
	// 	case ATAGS_CMDLINE:
	// 		// TODO
	// 		break;
	// 	}
	// 	// incr by size of atag
	// 	atag += *(atag + 1);
	// }

	// qmeu does not provide atag info
#ifdef VIRTUALIZED
	// TODO
	// memtag->size = QEMU_MEM_SIZE_MB * 1024 * 1024;
	MEM_SIZE = QEMU_MEM_SIZE_MB * 1024 * 1024;
#endif

	// MEM_SIZE = memtag->size;
	// init everything
	uart_init();
	init_all();

	kprintf("Hello, kernel world!\n");
	// kprintf("MEM Size: %d B or %d MB\n", memtag->size, memtag->size / (1024*1024));
	kprintf("MEM Size: %d B or %d MB\n", MEM_SIZE, MEM_SIZE / (1024*1024));

	// TODO not this
	disable_int();
	enable_int();

	if (int_enabled())
		kprintf("Interrupts enabled!\n");
	else
		kprintf("Interrupts disabled!\n");

	kdebug_printmode();

	while (1) {
		putc(getc());
	}

	// shutdown everything
	shutdown_all();
}

static void init_all()
{
	int rc = 0;

	rc = interrupt_init();
	if (rc != INT_OK) {
		KLOG("ERROR -- Interrupt init FAILED: rc %d\n", rc);
		panic();
	}

	rc = mem_init(MEM_SIZE, PAGE_SIZE);
	if (rc != MEM_OK) {
		KLOG("ERROR -- Mem init FAILED: rc %d\n", rc);
		panic();
	}

	rc = proc_init();
	if (rc != PROC_OK) {
		KLOG("ERROR -- Proc init FAILED: rc %d\n", rc);
		panic();
	}
}

static void shutdown_all()
{
	int rc;

	rc = mem_shutdown();
	if (rc != MEM_OK) {
		KLOG("ERROR -- Mem Shutdown failed: rc %d\n", rc);
		panic();
	}

	rc = proc_shutdown();
	if (rc != PROC_OK) {
		KLOG("ERROR -- Proc shutdown FAILED: rc %d\n", rc);
		panic();
	}

	rc = interrupt_shutdown();
	if (rc != INT_OK) {
		KLOG("ERROR -- Interrupt Shutdown failed: rc %d\n", rc);
		panic();
	}
}

static void panic()
{
	KLOG("Kernel PANIC!!\n");
	// TODO any important stuff
}