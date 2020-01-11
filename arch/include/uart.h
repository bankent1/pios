/*
 * uart.h
 *
 * Author: Travis Banken
 *
 * Header file for uart
 * https://www.raspberrypi.org/app/uploads/2012/02/BCM2835-ARM-Peripherals.pdf
 */

#ifndef __UART_H
#define __UART_H

void uart_init();
char uart_getc();
void uart_putc(char c);

#endif