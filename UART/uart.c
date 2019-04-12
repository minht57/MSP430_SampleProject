/*
 * uart.c
 *
 *  Created on: Feb 17, 2019
 *      Author: minht
 */

#include <msp430g2553.h>
#include "uart.h"
#include "PeripheralPin/peripheral.h"

#define NFACTOR					(uint16_t) (CLOCKRATE/BAUDRATE)

char aTxBuffer[BUFFER_TX_SIZE];
char aRxBuffer[BUFFER_RX_SIZE];

uint8_t i8ReadIndexTxBuffer = 0;
uint8_t i8WriteIndexTxBuffer = 0;
uint8_t i8AvailableTxBuffer = BUFFER_TX_SIZE;

uint8_t i8ReadIndexRxBuffer = 0;
uint8_t i8WriteIndexRxBuffer = 0;
uint8_t i8AvailableRxBuffer = 0;

uint8_t UART_Init (void)
{
	Peripheral_InitSEL(PORT_1, (BIT1 | BIT2), SEL_3);

	// UART mode, no parity, 8-bit data, 1 stop bit
	UCA0CTL0 |= UCMODE_0;

	// Choose SMCLK source clock, hold in reset state
	UCA0CTL1 |= UCSSEL_2 | UCSWRST;

	// Set baud-rate
	UCA0BR0 = (uint8_t) NFACTOR;
	UCA0BR1 = (uint8_t) (NFACTOR >> 8);

	// Released for operation
	UCA0CTL1 &= ~UCSWRST;

	// Enable transmit/receive interrupt
	IE2 = (UCA0TXIE | UCA0RXIE);

	return E_OK;
}

uint8_t UART_ReadTxBufferAvailable (void)
{
	return i8AvailableTxBuffer;
}

uint8_t UART_ReadRxBufferAvailable (void)
{
	return i8AvailableRxBuffer;
}

uint8_t UART_Write (char* aBuffer, uint16_t ui16Length)
{
    if (ui16Length <= i8AvailableTxBuffer)
    {
    	uint16_t ui16Idx = 0;

        for (ui16Idx = 0; ui16Idx < ui16Length; ui16Idx++)
        {
        	if (i8WriteIndexTxBuffer >= BUFFER_TX_SIZE)
        	{
        		i8WriteIndexTxBuffer = 0;
        	}
        	aTxBuffer[i8WriteIndexTxBuffer++] = aBuffer[ui16Idx];
        }
        i8AvailableTxBuffer -= (ui16Length - 1);
        UCA0TXBUF = aTxBuffer[i8ReadIndexTxBuffer++];

        return E_OK;
    }
    return E_NOT_OK;
}

uint8_t UART_Read (char* aBuffer, uint16_t ui16Length)
{
	if (ui16Length <= i8AvailableRxBuffer)
	{
    	uint16_t ui16Idx = 0;

        for (ui16Idx = 0; ui16Idx < ui16Length; ui16Idx++)
        {
        	if (i8ReadIndexRxBuffer >= BUFFER_RX_SIZE)
        	{
        		i8ReadIndexRxBuffer = 0;
        	}
        	aBuffer[ui16Idx] = aRxBuffer[i8ReadIndexRxBuffer++];
        }
        i8AvailableRxBuffer -= ui16Length;

        return E_OK;
	}
	return E_NOT_OK;
}

#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIA0TX_ISR(void)
{
	if (IFG2 & UCA0TXIFG)
	{
		if (i8AvailableTxBuffer < BUFFER_TX_SIZE)
		{
			UCA0TXBUF = aTxBuffer[i8ReadIndexTxBuffer++];

			if (i8ReadIndexTxBuffer >= BUFFER_TX_SIZE)
			{
				i8ReadIndexTxBuffer = 0;
			}

			i8AvailableTxBuffer++;
		}

		IFG2 &= ~UCA0TXIFG;
	}
}

#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCIA0RX_ISR(void)
{
	if (IFG2 & UCA0RXIFG)
	{
		if (i8AvailableRxBuffer < BUFFER_RX_SIZE)
		{
			aRxBuffer[i8WriteIndexRxBuffer++] = UCA0RXBUF;

			if (i8WriteIndexRxBuffer >= BUFFER_RX_SIZE)
			{
				i8WriteIndexRxBuffer = 0;
			}

			i8AvailableRxBuffer++;
		}

		IFG2 &= ~UCA0RXIFG;
	}
}
