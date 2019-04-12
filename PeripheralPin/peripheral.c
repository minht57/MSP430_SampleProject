/*
 * peripheral.c
 *
 *  Created on: Feb 17, 2019
 *      Author: minht
 */

#include <msp430g2553.h>
#include "peripheral.h"

uint8_t Peripheral_InitSEL (PeripheralPort_t tPort, uint16_t u16Pin, PeripheralSEL_t tSEL)
{
	uint8_t u8Result = E_NOT_OK;

	if (tPort == PORT_1)
	{
		if (tSEL == SEL_0)
		{
			P1SEL &= ~u16Pin;
			P1SEL2 &= ~u16Pin;
			u8Result = E_OK;
		}
		else if (tSEL == SEL_1)
		{
			P1SEL |= u16Pin;
			P1SEL2 &= ~u16Pin;
			u8Result = E_OK;
		}
		else if (tSEL == SEL_2)
		{
			P1SEL &= ~u16Pin;
			P1SEL2 |= u16Pin;
			u8Result = E_OK;
		}
		else if (tSEL == SEL_3)
		{
			P1SEL |= u16Pin;
			P1SEL2 |= u16Pin;
			u8Result = E_OK;
		}
	}
	else if (tPort == PORT_2)
	{
		if (tSEL == SEL_0)
		{
			P2SEL &= ~u16Pin;
			P2SEL2 &= ~u16Pin;
			u8Result = E_OK;
		}
		else if (tSEL == SEL_1)
		{
			P2SEL |= u16Pin;
			P2SEL2 &= ~u16Pin;
			u8Result = E_OK;
		}
		else if (tSEL == SEL_2)
		{
			P2SEL &= ~u16Pin;
			P2SEL2 |= u16Pin;
			u8Result = E_OK;
		}
		else if (tSEL == SEL_3)
		{
			P2SEL |= u16Pin;
			P2SEL2 |= u16Pin;
			u8Result = E_OK;
		}
	}

	return u8Result;
}
