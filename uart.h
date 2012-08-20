#ifndef _FLAUSCH_UART_H
#define _FLAUSCH_UART_H

#include "platform_config.h"

/* this initializes the UART and put it to 921600 Baud (approx.) */
void uart_init_highspeed();

void uart_putc(const char txbyte);
void uart_puts(const char *buffer);
void uart_puthexchar(const int val);
void uart_puthex(unsigned int val);

#define uart_have_data() U_STAbits.URXDA

char uart_getc();

#endif // _FLAUSCH_UART_H
