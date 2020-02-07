/*
 * timer.h
 *
 * Travis Banken
 * 2/6/2020
 *
 * Header file for the system timer
 */

#ifndef __TIMER_H__
#define __TIMER_H__

// return codes
#define TIMER_OK 0
#define TIMER_ALREADY_INIT 1
#define TIMER_NEVER_INIT 2
#define TIMER_SETUP_FAILED 3
#define TIMER_SHUTDOWN_FAILED 4

// functions
int timer_init();
int timer_shutdown();

#endif