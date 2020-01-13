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

#ifdef VIRTUALIZED
#define QEMU_MEM_SIZE_MB 256
#endif

#define ATAGS_CORE 0x54410001
#define ATAGS_MEM 0x54410002
#define ATAGS_CMDLINE 0x54410009
#define ATAGS_NONE 0x0

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

	// init everything
	uart_init();

	kprintf("Hello, kernel world!\n");
	kprintf("MEM Size: %d B or %d MB", memtag->size, memtag->size / (1028*1028));
	// kprintf("MEM starts at addr 0x%x", memtag->size);

	while (1) {
		putc(getc());
	}
}