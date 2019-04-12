/*
 * timer.c
 *
 *  Created on: Feb 17, 2019
 *      Author: minht
 */

#include <msp430g2553.h>
#include "timer.h"
#include "PeripheralPin/peripheral.h"

const uint16_t	u16PeriodicEvent = 1000;

uint16_t u16PeriodicPWM = 10000; // 10ms x 2 - f = 1MHz
uint16_t u16Duty = 0;
uint16_t u16Deadtime = 100;

TIMER_CALLBACK_FUNC tTimerCallbackFunction = NULL;

void Timer_InitAll (void)
{
	// Initialize timer for generating PWM
	Timer_InitPWM();
	Timer_InitTimerEvent();
}

uint8_t Timer_InitPWM (void)
{
	// Select SMCLK + choose up/down mode + clear timer
	TA1CTL |= (TASSEL_2 | MC_3 | TACLR);

	TA1CCTL1 = OUTMOD_6;
	TA1CCTL2 = OUTMOD_2;

	// Set function select register
	Peripheral_InitSEL(PORT_2, (BIT2 | BIT4), SEL_1);

	P2DIR |= (BIT2 | BIT4);

	TA1CCR0 = u16PeriodicPWM;
	TA1CCR1 = u16PeriodicPWM - u16Duty;
	TA1CCR2 = u16PeriodicPWM - u16Duty - u16Deadtime;

	return E_OK;
}

uint8_t Timer_ReInitPWM (void)
{
	TA1CCR0 = u16PeriodicPWM;
	TA1CCR1 = u16PeriodicPWM - u16Duty;
	TA1CCR2 = u16PeriodicPWM - u16Duty - u16Deadtime;

	return E_OK;
}

uint8_t Timer_InitTimerEvent (void)
{
	// Select SMCLK + choose up/down mode + clear timer
	TA0CTL |= (TASSEL_2 | MC_1 | TACLR | TAIE);

	TA0CCR0 = u16PeriodicEvent;

	return E_OK;
}

uint8_t Timer_SetDuty (uint16_t u16DutySet)
{
	if (u16DutySet < (u16PeriodicPWM - u16Deadtime))
	{
		u16Duty = u16DutySet;
		Timer_ReInitPWM();
		return E_OK;
	}

	return E_NOT_OK;
}

uint8_t Timer_SetDeadtime (uint16_t u16DeadtimeSet)
{
	if (u16DeadtimeSet < u16PeriodicPWM)
	{
		u16Deadtime = u16DeadtimeSet;
		//u16Duty = u16PeriodicPWM - u16Deadtime;
		Timer_ReInitPWM();
		return E_OK;
	}

	return E_NOT_OK;
}

uint16_t Timer_GetPeriodic (void)
{
	return u16PeriodicPWM;
}

uint16_t Timer_GetDeadtime (void)
{
	return u16Deadtime;
}

uint16_t Timer_GetDuty (void)
{
	return u16Duty;
}

uint8_t Timer_InterruptCallbackFunctionRegister(TIMER_CALLBACK_FUNC tCallbackFunctionRegister)
{
	if (tCallbackFunctionRegister != NULL)
	{
		tTimerCallbackFunction = tCallbackFunctionRegister;
		return E_OK;
	}

	return E_NOT_OK;
}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void TAIV_Interrupt (void)
{
	switch(TA0IV)
	{
	case 0x0A:
		if (tTimerCallbackFunction != NULL)
		{
			tTimerCallbackFunction();
		}
		break;
	}
}
