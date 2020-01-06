#ifndef __KDEBUG_H
#define __KDEBUG_H

#include <stdio.h>
#include <kpsr.h>

static void kdebug_printf(char *fmt, ...)
{
#ifdef DEBUG
	va_list args;
	va_start(args, fmt);
	vkprintf(fmt, args);
	va_end(args);
#endif
	return;
}

#define KLOG(fmt, ...) kdebug_printf("%s: ", __FUNCTION__);\
	kdebug_printf(fmt, ##__VA_ARGS__);

void kdebug_printmode();

#endif