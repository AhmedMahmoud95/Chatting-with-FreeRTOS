#ifndef __KEYPAD_CFG_H__
#define __KEYPAD_CFG_H__
/**
 * \filename:   keypad_cfg.h
 * \project:    keypad&LCD_withOS
 * \Auther:     TAmoo7
 * \Date:       22/01/2020
 * \Version:    1.0
 */

/************************************************************************/
/*						         Includes                               */
/************************************************************************/
#include "common_macros.h"
#include "std_types.h"
#include "DIO.h"

/************************************************************************/
/*						 Pins definitions                               */
/************************************************************************/

#define KEYPAD_PORT             GPIOC
#define ROW1                    BIT2
#define ROW2                    BIT3
#define ROW3                    BIT4
#define COLOMN1                 BIT5
#define COLOMN2                 BIT6
#define COLOMN3                 BIT7

#define NO_KEY_PRESSED          (0xAF)


#endif // __KEYPAD_CFG_H__
