# MSP430_SampleProject
## Over view
This project has some basic code algorithms related to Timer, UART, PWM, ADC, for training students after Cx course.

## Dependencies
- IDE: Code Composer Studio (TI)
- MCU: MSP430G2553

## Feature
- Module:
	- Event handler:
		- Calling a function with a given time and the timer can manage multiple events simultaneously.
		- Unit: millisecond
- PWM: generate pwm based on OUTMODE in timer and generate PWM complementary signals with dead time for all half-bridge topology PWM power outputs.
- UART: use fifo buffer for transmission and reception data.
- ADC: A sequence of channels is converted and using Data Transfer Controller (DTC) to automatically transfer conversion results from ADC10MEM to other on-chip memory locations.

## Docs
Document for training:
- About CPU
- About MCU
- IDE and coding style
- C/C++ optimization
