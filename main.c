#include <msp430.h> 
#include <stdio.h>
#include <string.h>
#include "HandleEvent/HandleEvent.h"
#include "PeripheralPin/peripheral.h"
#include "UART/uart.h"
#include "ADC/adc.h"
#include "Timer/timer.h"

/*
 * main.c
 */

void A(void)
{
	P1OUT ^= BIT0;
	HandleEvent_RegisterEvent(&A, 500);
}

void B(void)
{
	P1OUT ^= BIT6;
	HandleEvent_RegisterEvent(&B, 2000);
}

void Config_Clocks(void)
{
	if (CALBC1_1MHZ ==0xFF || CALDCO_1MHZ == 0xFF) // Check if constants cleared
	{
	  while(1);            			// If cal constants erased, trap CPU!!
	}

	BCSCTL1 = CALBC1_1MHZ; 			// Set DCO range & ACLK prescaler
	// BCSCTL1 - Basic Clock System Control Register 1
		// XT2OFF   = XT2 off. This bit turns off the XT2 oscillator
		// XTS      = LFXT1 mode select. 1: High-frequency mode
		// DIVAx    = Divider for ACLK
		// RSELx    = Range select
	DCOCTL = CALDCO_1MHZ;  			// Set DCO step + modulation
	// DCOCTL - DCO Control Register
		// DCOx     = DCO frequency select
		// MODx     = Modulator selection
	BCSCTL3 |= LFXT1S_2 + XCAP_3; // configure ACLK Source
	// BCSCTL3 - Basic Clock System Control Register 3
		// XT2Sx    = XT2 range select
		// LFXT1Sx  = Low-frequency clock select and LFXT1 range select
			// When XTS=0: 00 32768-Hz crystal on LFXT1
						//10 VLOCLK 12 KHz
			// When XTS=1: 01 1-to 3-MHz crystal or resonator
						//10 3-to 16-MHz crystal or resonator
		// XCAPx    = Oscillator capacitor selection. 11 ~12.5pF
		// XT2OF    = XT2 oscillator fault
		// LFXT1OF  = LFXT1 oscillator fault
	while(IFG1 & OFIFG)				// wait for OSCFault to clear
	{
	  IFG1 &= ~OFIFG;
	  __delay_cycles(100000);
	}
	// IFG1 - Interrupt Flag Register 1
		// OFIFG    = Oscillator fault interrupt flag

	//	_bis_SR_register(SCG1 + SCG0);	// Stop DCO

	BCSCTL2 |= SELM_0 + DIVM_0;		// select MCLK, SMCLK clock and prescaler
	// BCSCTL2 - Basic Clock System Control Register 2
		// SELMx   = Select MCLK. These bits select the MCLK source.
			//00 DCOCLK
			//01 DCOCLK
			//10 XT2CLK when XT2 present. LFXT1CLK or VLOCLK when XT2 not present
			//11 LFXT1CLK or VLOCLK
		// DIVMx   = Divider for MCLK
		// SELS    = Select SMCLK.This bit selects the SMCLK source.
			//0 DCOCLK
			//1 LFXT1CLK or VLOCLK when XT2 not present. XT2CLK when XT2 present.
		// DIVSx   = Divider for SMCLK
		// DCOR    = DCO resistor select
}

char TxBuff[30] = "PIF Lab\r\n";
char RxBuff[30];
uint16_t u16ADCBuffer[ADC10_NUMBER_OF_CHANNEL];

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    Config_Clocks();

    P1DIR |= (BIT0 + BIT6);
    P1SEL &= ~(BIT0 + BIT6);
    P1SEL2 &= ~(BIT0 + BIT6);

    HandleEvent_Init();
    HandleEvent_RegisterEvent(&A, 500);
    HandleEvent_RegisterEvent(&B, 2000);

    UART_Init();
    UART_Write(TxBuff, 9);

//    ADC10_Init();
//    ADC10_StartConversion();

//    Timer_InitPWM();
//    Timer_SetDuty(1000);
//    Timer_SetDeadtime(500);

    _BIS_SR(GIE);

    while (1)
    {
//    	ADC10_GetAllBuffer(u16ADCBuffer);
//    	sprintf(TxBuff, "%d %d %d %d\r\n", u16ADCBuffer[0], u16ADCBuffer[1], u16ADCBuffer[2], u16ADCBuffer[3]);
//    	UART_Write(TxBuff, 30);
//    	__delay_cycles(1000000);

//    	uint8_t u8NumberOfTx = UART_ReadRxBufferAvailable();
//
//    	if (u8NumberOfTx)
//    	{
//    		UART_Read(RxBuff, u8NumberOfTx);
//    		UART_Write(RxBuff, u8NumberOfTx);
//    	}
//    	__delay_cycles(1000000);
    }

	return 0;
}
