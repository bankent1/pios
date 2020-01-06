/*
 * proc.c
 *
 * Travis Banken
 * 1/6/2020
 * 
 * Framework for process management
 */

#include <kdebug.h>

static int cur_pid = -1;

void proc_kill()
{
	// TODO
	KLOG("Killing proc %d\n", cur_pid);
}