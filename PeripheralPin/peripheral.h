/*
 * peripheral.h
 *
 *  Created on: Feb 17, 2019
 *      Author: minht
 */

#ifndef PERIPHERALPIN_PERIPHERAL_H_
#define PERIPHERALPIN_PERIPHERAL_H_

#include <stdint.h>

#define E_OK						1
#define E_NOT_OK					0
#define NULL						(void *) 0

typedef enum
{
	PORT_1 = 0,
	PORT_2
}PeripheralPort_t;

typedef enum
{
	SEL_0 = 0,
	SEL_1,
	SEL_2,
	SEL_3,
}PeripheralSEL_t;

uint8_t Peripheral_InitSEL (PeripheralPort_t tPort, uint16_t u16Pin, PeripheralSEL_t tSEL);

#endif /* PERIPHERALPIN_PERIPHERAL_H_ */
