/*
 * adc.h
 *
 *  Created on: Feb 20, 2019
 *      Author: minht
 */

#ifndef ADC_ADC_H_
#define ADC_ADC_H_

#define ADC10_NUMBER_OF_CHANNEL			4
#define ADC10_INPUT_CHANNEL				INCH_3
#define ADC10_ANALOG_ENABLED			(BIT0 | BIT3)

typedef void (* ADC10_CALLBACK_FUNC)();
#define NULL							(void *) 0
#define E_OK							1
#define E_NOT_OK						0

void ADC10_Init (void);
void ADC10_StartConversion (void);
uint8_t ADC10_GetAllBuffer (uint16_t * pu16Buffer);
uint16_t ADC10_GetChannelValue (uint8_t u8Channel);
void ADC10_CallbackFunctionRegister(ADC10_CALLBACK_FUNC pCallbakFunction);


#endif /* ADC_ADC_H_ */
