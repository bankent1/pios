#ifndef __KTOOLS_H
#define __KTOOLS_H

#include <kdebug.h>
#include <kpsr.h>
#include <proc.h>

// TODO dump core and shutdown
#define PANIC KLOG("PANIC!!!\n");

static inline void kcheckmode()
{
	u8 mode = psr_getmode();
	if (mode == PSR_USER_MODE) {
		// TODO switch to supervisor mode
		proc_kill();
	}
}

#endif