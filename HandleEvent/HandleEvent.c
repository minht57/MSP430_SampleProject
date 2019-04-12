/*
 * HandleEvent.c
 *
 *  Created on: Feb 17, 2019
 *      Author: minht
 */

#include "HandleEvent.h"
#include "Timer/timer.h"

typedef struct
{
	HE_CALLBACK_FUNC tCallbackFunc;
	uint32_t u32Periodic;
} HandleEvent_t;

HandleEvent_t tHandleEvent[MAX_No_EVENT];

void HandleEvent_ISR (void);

uint8_t HandleEvent_Init (void)
{
	Timer_InitTimerEvent();
	Timer_InterruptCallbackFunctionRegister(&HandleEvent_ISR);

	return E_OK;
}

EVENT_ID HandleEvent_RegisterEvent (HE_CALLBACK_FUNC tCallbackFunction, uint32_t u32PeriodicMs)
{
	if (tCallbackFunction != NULL)
	{
		EVENT_ID tIdx = 0;
		for (tIdx = 0; tIdx < MAX_No_EVENT; tIdx++)
		{
			if (tHandleEvent[tIdx].tCallbackFunc == NULL)
			{
				tHandleEvent[tIdx].tCallbackFunc = tCallbackFunction;
				tHandleEvent[tIdx].u32Periodic = u32PeriodicMs;
				return tIdx;
			}
		}
	}

	return INVALID_EVENT;
}

uint8_t HandleEvent_UnRegisterEvent (EVENT_ID tEventId)
{
	if (tEventId < MAX_No_EVENT)
	{
		tHandleEvent[tEventId].tCallbackFunc = NULL;
		tHandleEvent[tEventId].u32Periodic = 0;

		return E_OK;
	}
	return E_NOT_OK;
}

void HandleEvent_ISR (void)
{
	EVENT_ID tIdx = 0;
	for (tIdx = 0; tIdx < MAX_No_EVENT; tIdx++)
	{
		if ((tHandleEvent[tIdx].tCallbackFunc != NULL) && (tHandleEvent[tIdx].u32Periodic != 0))
		{
			tHandleEvent[tIdx].u32Periodic--;

			if (tHandleEvent[tIdx].u32Periodic == 0)
			{
				tHandleEvent[tIdx].tCallbackFunc();

				tHandleEvent[tIdx].tCallbackFunc = NULL;
			}
		}
		else
		{
			tHandleEvent[tIdx].u32Periodic = 0;
			tHandleEvent[tIdx].tCallbackFunc = NULL;
		}
	}
}
