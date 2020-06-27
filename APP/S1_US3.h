/**
 * \filename:       S1_US3.h
 * \Owner:          Tamoo7
 * \Date:           28/01/2020
 * \Version:        1.0
 */

#ifndef __S1_US3_H__
#define __S1_US3_H__
/************************************************************************/
/*						         Includes                               */
/************************************************************************/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "BTN.h"
#include "led.h"

/************************************************************************/
/*	       	            Functions declaration                           */
/************************************************************************/
/**
 * \function name:      S1_US3_init()
 * \IN:                 vptr
 * \OUT:                NONE
 * \return:             NONE
 * \Discription:        Initiates the push button, and the LED
 */
void S1_US3_init ( void *vptr);

/**
 * \function name:      S1_US3_getButton()
 * \IN:                 vptr
 * \OUT:                NONE
 * \return:             NONE
 * \Discription:        checks the button status and calculates the pressing time
 */
void S1_US3_getButton ( void *vptr);

/**
 * \function name:      S1_US3_updateLED()
 * \IN:                 vptr
 * \OUT:                NONE
 * \return:             NONE
 * \Discription:        Updates the toggling rate if needed
 */
void S1_US3_updateLED ( void *vptr);

/**
 * \function name:      S1_US3_MainFunction
 * \IN:                 vptr
 * \OUT:                NONE
 * \return:             NONE
 * \Discription:        Updates the toggling rate if needed
 */
void S1_US3_MainFunction (void);



#endif // __S1_US3_H__
