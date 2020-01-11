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
#include <interrupts.h>
#include <kdebug.h>

#ifdef VIRTUALIZED
#define QEMU_MEM_SIZE_MB 256
#endif

#define ATAGS_CORE 0x54410001
#define ATAGS_MEM 0x54410002
#define ATAGS_CMDLINE 0x54410009
#define ATAGS_NONE 0x0

#define PAGE_SIZE (4 * 1080) // 4KB

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

	// grab atags info
	u32 *atag = (u32 *) atags;
	struct atag_mem *memtag = NULL;
	while (*atag != ATAGS_NONE) {
		switch (*atag) {
		case ATAGS_CORE:
			// TODO
			break;
		case ATAGS_MEM:
			memtag = (struct atag_mem *)ATAGS_MEM;
			break;
		case ATAGS_CMDLINE:
			// TODO
			break;
		}
		// incr by size of atag
		atag += *(atag + 1);
	}

	// qmeu does not provide atag info
#ifdef VIRTUALIZED
	memtag->size = QEMU_MEM_SIZE_MB * 1028 * 1028;
#endif

	MEM_SIZE = memtag->size;
	// init everything
	uart_init();
	init_all();

    // kprintf("*** Testing memcpy ***\n");
    // int arr1[] = {0, 1, 2, 3, 4};
    // int arr2[5];
    // kprintf("&arr1 = %x\n", arr1);
    // kprintf("&arr2 = %x\n", arr2);
    // memcpy(arr2, arr1, 5);


	kprintf("Hello, kernel world!\n");
	kprintf("MEM Size: %d B or %d MB\n", memtag->size, memtag->size / (1028*1028));

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
	if (mem_init(MEM_SIZE, PAGE_SIZE) != MEM_OK) {
		KLOG("ERROR -- Mem init failed!\n");
		panic();
	}
}

static void shutdown_all()
{
	if (mem_shutdown() != MEM_OK) {
		KLOG("ERROR -- Mem Shutdown failed\n");
		panic();
	}
}

static void panic()
{
	KLOG("Kernel PANIC!!\n");
	// TODO any important stuff
}