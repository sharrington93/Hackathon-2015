/*
 * uart.c
 *
 *  Created on: Nov 14, 2015
 *      Author: Sean
 */


#include <msp430.h>

int index;
extern char output[6];

int Configure_BlueSMiRF()
{
	index = 0;
	UCA0CTL1 |= UCSSEL_2;			// SMCLK as source
	UCA0BR0 = 104;					// 9600 Baudrate with 1Mhz clock
	UCA0BR1 = 0;

	UCA0MCTL = UCBRS0;				// Modulation UCBRSx = 1
									// CHECK ME
	UCA0CTL1 &= ~UCSWRST;			// Initialize USCI
	IE2 |= UCA0TXIE;
}

void Send_Data()
{
	IE2 |= UCA0TXIE;				// Enable USCI_A0 TX interrupt
}

#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void)
{
	if((IFG2&UCA0TXIFG) && (IE2&UCA0TXIE))
	{
		UCA0TXBUF = output[index];
		index ++;
		if(index == 6)
		{
			index = 0;
			IE2 &= ~UCA0TXIE;
		}
	}
}

#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
	// Received character. Do something?
}




