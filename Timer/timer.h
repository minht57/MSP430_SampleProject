/*
 * timer.h
 *
 *  Created on: Feb 17, 2019
 *      Author: minht
 */

#ifndef TIMER_TIMER_H_
#define TIMER_TIMER_H_

#include <stdint.h>

#define E_OK						1
#define E_NOT_OK					0
#define NULL						(void *) 0

typedef void (*TIMER_CALLBACK_FUNC)();

void Timer_InitAll (void);
uint8_t Timer_InitPWM (void);
uint8_t Timer_SetDuty (uint16_t u16DutySet);
uint8_t Timer_SetDeadtime (uint16_t u16DeadtimeSet);
uint8_t Timer_InitTimerEvent (void);
uint8_t Timer_InterruptCallbackFunctionRegister(TIMER_CALLBACK_FUNC tCallbackFunctionRegister);

#endif /* TIMER_TIMER_H_ */
