/*
 * HandleEvent.h
 *
 *  Created on: Feb 17, 2019
 *      Author: minht
 */

#ifndef HANDLEEVENT_HANDLEEVENT_H_
#define HANDLEEVENT_HANDLEEVENT_H_

#include <stdint.h>

#define E_OK						1
#define E_NOT_OK					0
#define NULL						(void *) 0
#define INVALID_EVENT				0xFF

#define MAX_No_EVENT 				10

typedef void (*HE_CALLBACK_FUNC)();
typedef int8_t EVENT_ID;

uint8_t HandleEvent_Init (void);
EVENT_ID HandleEvent_RegisterEvent (HE_CALLBACK_FUNC tCallbackFunction, uint32_t u32PeriodicMs);
uint8_t HandleEvent_UnRegisterEvent (EVENT_ID tEventId);

#endif /* HANDLEEVENT_HANDLEEVENT_H_ */
