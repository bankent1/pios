#ifndef __KPSR_H
#define __KPSR_H

#include <kint.h>

#define PSR_USER_MODE 0b10000
#define PSR_FIQ_MODE 0b10001
#define PSR_IRQ_MODE 0b10010
#define PSR_SUPER_MODE 0b10011
#define PSR_ABORT_MODE 0b10111
#define PSR_UNDEFINED_MODE 0b11011
#define PSR_SYSTEM_MODE 0b11111

u8 psr_getmode();

#endif