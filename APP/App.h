#define asm __asm__

#ifndef __App_H__
#define __App_H__

/************************************************************************/
/*	       	                   Includes                                 */
/************************************************************************/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "BTN.h"
#include "led.h"
#include "LCD.h"
#include "UART.h"
#include "keypad.h"


/**
 * \function name:      App_init()
 * \IN:                 vptr
 * \OUT:                NONE
 * \return:             NONE
 * \Discription:        Initiates the push button, the LED, the LCD, and the UART
 */
void App_init ( void *vptr);

/**
 * \function name:      App_getKeypad()
 * \IN:                 vptr
 * \OUT:                NONE
 * \return:             NONE
 * \Discription:        get pressed button from keypad and send them to sendToUArt
 */
void App_getKeypad ( void *vptr);

/**
 * \function name:      App_getButton()
 * \IN:                 vptr
 * \OUT:                NONE
 * \return:             NONE
 * \Discription:        Checks the button status and send notification to sendToUART
 */
void App_getButton ( void *vptr);

/**
 * \function name:      App_sendToUart()
 * \IN:                 vptr
 * \OUT:                NONE
 * \return:             NONE
 * \Discription:        Gets the msg char by char and sends it, then initiates LCD & LED
 */
void App_sendToUart ( void *vptr);

/**
 * \function name:      App_updateLED0()
 * \IN:                 vptr
 * \OUT:                NONE
 * \return:             NONE
 * \Discription:        Updates the sending led status
 */
void App_updateLED0 ( void *vptr);

/**
 * \function name:      App_updateLED1()
 * \IN:                 vptr
 * \OUT:                NONE
 * \return:             NONE
 * \Discription:        Updates the receiving led status
 */
void App_updateLED1 ( void *vptr);

/**
 * \function name:      App_updateLCD()
 * \IN:                 vptr
 * \OUT:                NONE
 * \return:             NONE
 * \Discription:        Updates the LCD
 */
void App_updateLCD ( void *vptr);

/*******************************************************************************
 * 	Task name: 			toggleLED0_task
 *
 * 	Brief: 				toggle led 0
 *
 * 	Details: 			task to toggle led by pins
 *
 * 	Arguments:
 * 		-				pvParameters
 *
 * 	Return:
 * 		-				void
 *******************************************************************************/
 /**
 * \function name:      UART_Receive_task
 * \IN:                 vptr
 * \OUT:                NONE
 * \return:             NONE
 * \Discription:        Receive string from ISR and display it on LCD
 */
void App_UART_Receive_task( void * pvParameters );

/**
 * \function name:      App_MainFunction
 * \IN:                 vptr
 * \OUT:                NONE
 * \return:             NONE
 * \Discription:        Runs the full system
 */
void App_MainFunction (void);


#endif // __App_H__
