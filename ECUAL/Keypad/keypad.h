/**
 * \filename:   keypad.h
 * \project:    keypad&LCD_withOS
 * \Auther:     TAmoo7
 * \Date:       22/01/2020
 * \Version:    1.0
 */

/************************************************************************/
/*						         Includes                               */
/************************************************************************/
#ifndef __KEYPAD_H__
#define __KEYPAD_H__
#include "keypad_cfg.h"


/************************************************************************/
/*                        Extern variables                              */
/************************************************************************/

extern uint8 gu8_pressedKey;

/************************************************************************/
/*                      Functions declarations                          */
/************************************************************************/

/**
 * \Name:   keypad_init
 * \IN:     NONE
 * \OUT:    NONE
 * \Return: ERROR_STATUS
 * \brief:  Initiates the keypad pins
 */
ERROR_STATUS keypad_init ();


/**
 * \Name:   keypad_getPressedKey
 * \IN:     NONE
 * \OUT:    NONE
 * \Return: ERROR_STATUS
 * \brief:  gets the pressed key and checks for bouncing
 */
ERROR_STATUS keypad_getPressedKey (uint8 *u8_pkey);


#endif // __KEYPAD_H__
