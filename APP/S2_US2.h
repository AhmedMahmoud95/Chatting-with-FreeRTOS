
#ifndef __S2_US2_H__
#define __S2_US2_H__

/************************************************************************/
/*	       	                   Includes                                 */
/************************************************************************/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "BTN.h"
#include "led.h"
#include "LCD.h"
/**
 * \function name:      S2_US2_init()
 * \IN:                 vptr
 * \OUT:                NONE
 * \return:             NONE
 * \Discription:        Initiates the push button, and the LED
 */
void S2_US2_init ( void *vptr);


/**
 * \function name:      S2_US2_getButtons()
 * \IN:                 vptr
 * \OUT:                NONE
 * \return:             NONE
 * \Discription:        checks the button status and calculates the pressing time
 */
void S2_US2_getButtons ( void *vptr);
/**
 * \function name:      S2_US2_updateLED()
 * \IN:                 vptr
 * \OUT:                NONE
 * \return:             NONE
 * \Discription:        Updates the toggling rate if needed
 */
void S2_US2_updateLED ( void *vptr);

/**
 * \function name:      S1_US3_updateLED()
 * \IN:                 vptr
 * \OUT:                NONE
 * \return:             NONE
 * \Discription:        Updates the toggling rate if needed
 */
void S1_US3_updateLCD ( void *vptr);

/**
 * \function name:      S2_US2_MainFunction
 * \IN:                 vptr
 * \OUT:                NONE
 * \return:             NONE
 * \Discription:        Runs the full system
 */
void S2_US2_MainFunction (void);


#endif // __S2_US2_H__
