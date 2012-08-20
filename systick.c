#include "systick.h"
#include "uart.h"

/* high priority interrupt as a 100 usec systick counter */
void __attribute__ ((nomips16,interrupt(ipl5),vector(_TIMER_3_VECTOR))) systick_interrupt(void) {
	systick++;
	IFS0bits.T3IF = 0; /* reset interrupt flag */
}

void systick_init() {
	/* set up timer 2 for life indicator */
	PR3 = 500;
	T3CON = 0x8030; // enable, prescaler=1/8 -> 5 MHz
	IPC3bits.T3IP = 5;
	IEC0bits.T3IE = 1;
}

void delay100usec(const unsigned int times) {
	systick = 0;
	while(systick < times) {}
}

