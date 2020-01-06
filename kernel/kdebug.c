/*
 *
 */
	
#include <kdebug.h>
#include <kint.h>

void kdebug_printmode()
{
	u8 mode = psr_getmode();
	switch (mode) {
	case PSR_USER_MODE:
		KLOG("MODE -- USER (0x%x)\n", mode);
		break;
	case PSR_FIQ_MODE:
		KLOG("MODE -- FIQ (0x%x)\n", mode);
		break;
	case PSR_IRQ_MODE:
		KLOG("MODE -- IRQ (0x%x)\n", mode);
		break;
	case PSR_SUPER_MODE:
		KLOG("MODE -- SUPERVISOR (0x%x)\n", mode);
		break;
	case PSR_ABORT_MODE:
		KLOG("MODE -- ABORT (0x%x)\n", mode);
		break;
	case PSR_UNDEFINED_MODE:
		KLOG("MODE -- UNDEFINED (0x%x)\n", mode);
		break;
	case PSR_SYSTEM_MODE:
		KLOG("MODE -- SYSTEM (0x%x)\n", mode);
		break;
	default:
		KLOG("MODE -- UNKNOWN (0x%x)\n", mode);
		break;
	}
}
