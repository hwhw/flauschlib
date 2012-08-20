#include "uart.h"

#ifdef UART_TX_INTERRUPTS
#include "fifo.h"
fifo_t uart_out_buffer;
#endif

void uart_init_highspeed() {
	/* pin configuration */
	mPin_Config_UART_TX();
	mPin_Config_UART_RX();

#ifdef UART_TX_INTERRUPTS
	fifo_init(&uart_out_buffer, U_TXBUF);

	U_STA = 0x8080; // TX interrupt when hardware FIFO empty, RX interrupt when buffer 3/4 full (we don't need this here)
#else
	U_STA = 0;
#endif

	/* set up UART peripheral: */
	U_BRG = 10; // @40MHz PCLK, with BRGH=1: ~910k Baud, set CP210x to 921600 Baud
	U_MODE = 0x8008; // ON, otherwise 8N1, high-speed mode (4x divider)
	U_STASET = 0x1400; // RXEN, TXEN

#ifdef UART_TX_INTERRUPTS
	U_IP = 2; /* interrupt priority, must match specification in handler signature */
	//U_ISP = 0; /* interrupt subpriority */
	//U_IE_TX = 1;
#endif
}

void uart_putc(const char txbyte) {
#ifdef UART_TX_INTERRUPTS
	if(U_STAbits.UTXBF || fifo_has_data(&uart_out_buffer)) {
		// buffer full or data in FIFO pending, push to FIFO
		fifo_push(&uart_out_buffer, txbyte);
		U_IE_TX = 1; // enable interrupt for when there's space in TX buffer
	} else {
		U_TXREG = txbyte;
	}
#else
	while(U_STAbits.UTXBF); // wait when buffer is full
	U_TXREG = txbyte;
#endif
}

#ifdef UART_TX_INTERRUPTS
void __attribute__ ((nomips16,interrupt(ipl2),vector(U_VECTOR))) uart_interrupt(void) {
	if(U_IF_TX) {
check_loop:
		if(!fifo_has_data(&uart_out_buffer)) {
			// FIFO empty
			U_IE_TX = 0; // disable interrupt
		} else {
			if(!U_STAbits.UTXBF) {
				U_TXREG = fifo_pop(&uart_out_buffer);
			} else {
				goto quit_loop;
			}
			goto check_loop;
		}
quit_loop:
		U_IF_TX = 0;
	} else if(U_IF_RX) {
		/* should not happen. we drop a byte from the receive buffer */
		volatile register char dummy = U_RXREG;
		U_IF_RX = 0;
	} else if(U_IF_ERR) {
		U_IF_ERR = 0;
	}
}
#endif

void uart_puts(const char *buffer) {
	while(*buffer) {
		uart_putc(*buffer);
		buffer++;
	}
}

void uart_puthexchar(const int val) {
	if(val > 9) {
		uart_putc(('A'-10) + val);
	} else {
		uart_putc('0' + val);
	}
}
void uart_puthex(unsigned int val) {
	register unsigned int i;
	for(i=0; i<8; i++) {
		uart_puthexchar((val & 0xF0000000) >> 28);
		val <<= 4;
	}
}

char uart_getc() {
	while(!uart_have_data());
	return U_RXREG;
}
