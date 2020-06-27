/*
*	File name:	CPU.h
*	Owner:		Tamoo7
*	Date:		13/01/2020
*	Version:	1.0
*/

#ifndef __CPU_H__
#define __CPU_H__

/************************************************************************/
/*				 		Included files  								*/
/************************************************************************/
#include "registers.h"
#include "std_types.h"
#include "common_macros.h"
#include "interrupt.h"


/************************************************************************/
/*				 		Global definitions								*/
/************************************************************************/

#define IDLE				0x00
#define ADC_NOISE_REDUCTION	0x10
#define POWER_DOWN			0x20
#define POWER_SAVE			0x30
#define STANDBY				0x60
#define EXTENDED_STANDBY	0x70

#define BIT0	0x01
#define BIT1	0x02
#define BIT2	0x04
#define BIT3	0x08
#define BIT4	0x10
#define BIT5	0x20
#define BIT6	0x40
#define BIT7	0x80

/************************************************************************/
/*				 		Global declarations								*/
/************************************************************************/
/*
*/
ERROR_STATUS sleep_Disable();


/*
*/
ERROR_STATUS sleep_init (uint8 sleepMode);

/*
*/
void sleep_Enable ();


#endif // __CPU_H__
