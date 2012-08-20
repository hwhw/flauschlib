#ifndef _FLAUSCH_PLATFORM_CONFIG_H
#define _FLAUSCH_PLATFORM_CONFIG_H

#include <xc.h>

#define GetSystemClock()              (40000000ul)
#define GetPeripheralClock()          (GetSystemClock())
#define GetInstructionClock()         (GetSystemClock())

/* library feature config */
#define UART_TX_INTERRUPTS

/* Pin configuration */

/* we use UART2 */
#define mPin_Config_UART_RX()	U2RXR = 6; /* RPC8, Pinguino: D0 */
#define mPin_Config_UART_TX()	RPC9R = 2; /* RPC9, Pinguino: D1 */

/* SPI: */
#define SD_CS_TRIS		TRISAbits.TRISA7
#define SD_CS			LATAbits.LATA7
#define mPin_Config_SPI1_RX()	SDI1R = 5; // MISO / RX
#define mPin_Config_SPI1_TX()	RPA9R = 3; // MOSI / TX
#define SD_SPI_BRG		SPI1BRG
#define SD_SPI_CON		SPI1CON
#define SD_SPI_BUF		SPI1BUF
#define SD_SPI_STATbits		SPI1STATbits

/* Peripheral devices config */
/* UART: we use UART2 */
#define U_BRG		U2BRG
#define U_STA		U2STA
#define U_MODE		U2MODE
#define U_STASET	U2STASET
#define U_STAbits	U2STAbits
#define U_TXREG		U2TXREG
#define U_RXREG		U2RXREG

#ifdef UART_TX_INTERRUPTS
#define U_TXBUF		256

#define U_IF_TX		IFS1bits.U2TXIF
#define U_IF_RX		IFS1bits.U2RXIF
#define U_IF_ERR	IFS1bits.U2EIF
#define U_IE_TX		IEC1bits.U2TXIE
#define U_IP		IPC9bits.U2IP
#define U_ISP		IPC9bits.U2IS
#define U_VECTOR	_UART_2_VECTOR
#endif

/* convenience / board features */

#define mInitAllLEDs()      LATAbits.LATA10=0;TRISAbits.TRISA10=0;LATBbits.LATB15=0;TRISBbits.TRISB15=0;
#define mInitAllSwitches()  TRISBbits.TRISB7=1;
#define sw2                 PORTBbits.RB7

#define mLED_1              LATBbits.LATB15
#define mLED_2              LATAbits.LATA10

#define mGetLED_1()         mLED_1
#define mGetLED_2()         mLED_2

#define mLED_1_On()         mLED_1 = 1;
#define mLED_2_On()         mLED_2 = 1;

#define mLED_1_Off()        mLED_1 = 0;
#define mLED_2_Off()        mLED_2 = 0;

#define mLED_1_Toggle()     mLED_1 = !mLED_1;
#define mLED_2_Toggle()     mLED_2 = !mLED_2;


#endif // _FLAUSCH_PLATFORM_CONFIG_H
