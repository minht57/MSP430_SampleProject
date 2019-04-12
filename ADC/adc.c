/*
 * adc.c
 *
 *  Created on: Feb 20, 2019
 *      Author: minht
 */

#include <msp430g2553.h>
#include <stdint.h>
#include "adc.h"

uint16_t u16Buffer[ADC10_NUMBER_OF_CHANNEL];
ADC10_CALLBACK_FUNC pCallbackFunc = NULL;

void ADC10_Init (void)
{
	/*
	 * Reference: Vr+ = Vcc, Vr- = Vss
	 * Sample-and-hold time: 8 x ADC10CLKs
	 * ADC10 sampling rate: ~200 ksps
	 * Reference output off
	 * Reference buffer on continuously
	 * Reference off
	 * Multiple sample and conversion
	 * ADC10 on
	 * Interrupt enabled
	 */
	ADC10CTL0 |= ADC10SHT_1 |  ADC10ON | ADC10IE | MSC;

	/*
	 * Conversion sequence mode: Repeat-sequence-of-channels
	 * Clock source: SMCLK
	 * Clock divider: /2
	 * Input channel: A0 -> A3 (Repeat-sequence-of-channels mode)
	 */
	ADC10CTL1 |= ADC10_INPUT_CHANNEL | ADC10DIV_1 | ADC10SSEL_3 | CONSEQ_3;

	/*
	 * Analog enable: A0 (BIT0) and A3 (BIT3)
	 * Note: Pins for A1, A2 maybe use for UART
	 */
	ADC10AE0 |= ADC10_ANALOG_ENABLED;

	/* DTC configuration
	 * Mode: One-block transfer mode
	 * Data is transferred continuously
	 */
	ADC10DTC0 |= ADC10CT;

	/*
	 * DTC transfers: 3 transfers/block
	 */
	ADC10DTC1 = ADC10_NUMBER_OF_CHANNEL;

	/*
	 * Start address for Data transfer
	 */
	ADC10SA = (uint16_t)u16Buffer;
}

void ADC10_StartConversion (void)
{
	/*
	 * ADC10 enabled
	 * Start sample-and-conversion
	 */
	ADC10CTL0 |= ADC10SC | ENC;
}

uint8_t ADC10_GetAllBuffer (uint16_t * pu16Buffer)
{
	if (pu16Buffer != NULL)
	{
		int8_t i8Idx;

		for (i8Idx = ADC10_NUMBER_OF_CHANNEL - 1; i8Idx >= 0; i8Idx--)
		{
			pu16Buffer[ADC10_NUMBER_OF_CHANNEL - 1 - i8Idx] = u16Buffer[i8Idx];
		}

		return E_OK;
	}

	return E_NOT_OK;
}

uint16_t ADC10_GetChannelValue (uint8_t u8Channel)
{
	if (u8Channel < ADC10_NUMBER_OF_CHANNEL)
	{
		return u16Buffer[u8Channel];
	}

	return 0xFFFF;
}

void ADC10_CallbackFunctionRegister(ADC10_CALLBACK_FUNC pCallbakFunction)
{
	if (pCallbakFunction != NULL)
	{
		pCallbackFunc = pCallbakFunction;
	}
}

#pragma vector = ADC10_VECTOR
__interrupt void ADC10_Interrupt(void)
{
	if(pCallbackFunc != NULL)
	{
		pCallbackFunc();
	}

	// Clear interrupt flag
	ADC10CTL0 &= ~ADC10IFG;
}
