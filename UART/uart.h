/*
 * uart.h
 *
 *  Created on: Feb 17, 2019
 *      Author: minht
 */

#ifndef UART_UART_H_
#define UART_UART_H_

#include <stdint.h>

#define CLOCKRATE				1000000		// 1 MHz
#define BAUDRATE				9600
#define BUFFER_TX_SIZE			(50)
#define BUFFER_RX_SIZE			(50)

uint8_t UART_Init(void);
uint8_t UART_ReadTxBufferAvailable (void);
uint8_t UART_ReadRxBufferAvailable (void);
uint8_t UART_Read (char* aBuffer, uint16_t ui16Length);
uint8_t UART_Write (char* aBuffer, uint16_t ui16Length);

#endif /* UART_UART_H_ */
