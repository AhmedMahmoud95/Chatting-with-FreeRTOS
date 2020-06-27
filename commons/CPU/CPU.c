/*
*	File name:	CPU.c
*	Owner:		Tamoo7
*	Date:		13/01/2020
*	Version:	1.0
*/


/************************************************************************/
/*				 		Included files  								*/
/************************************************************************/
#include "CPU.h"

/************************************************************************/
/*				 		functions definitions						    */
/************************************************************************/

/*
*/
ERROR_STATUS sleep_Disable()
{
    CLR_BIT(MCUCR, BIT7);
    return E_OK;
}

/*
*/
ERROR_STATUS sleep_init (uint8 sleepMode)
{
    MCUCR |= sleepMode;
    return E_OK;
}

/*
*/
void sleep_Enable ()
{
    SET_BIT(MCUCR, BIT7);
    __asm__ __volatile__  ("sleep" ::);
}
