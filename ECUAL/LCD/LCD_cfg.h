/**
 * \file name:      LCD_cfg.h
 * \project name:   keypad&LCD_withOS
 * \Owner:          Tamoo7
 * \Date:           23/01/2020
 * \Version:        1.0
 */
#ifndef _LCD_CFG_H__
#define _LCD_CFG_H__
/************************************************************************/
/*						         Includes                               */
/************************************************************************/
#include "DIO.h"
#include "std_types.h"
#include "common_macros.h"
#include "softwareDelay.h"

#define LCD_RS_PIN	BIT1 	//define MCU pin connected to LCD RS
#define LCD_RS_PORT	GPIOA

#define LCD_RW_PIN	BIT2 	//define MCU pin connected to LCD R/W
#define LCD_RW_PORT	GPIOA

#define LCD_EN_PIN	BIT3	//define MCU pin connected to LCD E
#define LCD_EN_PORT	GPIOA

#define LCD_D4_PIN	BIT4	//define MCU pin connected to LCD D4
#define LCD_D4_PORT	GPIOA

#define LCD_D5_PIN	BIT5	//define MCU pin connected to LCD D5
#define LCD_D5_PORT	GPIOA

#define LCD_D6_PIN	BIT6	//define MCU pin connected to LCD D6
#define LCD_D6_PORT	GPIOA

#define LCD_D7_PIN	BIT7	//define MCU pin connected to LCD D7
#define LCD_D7_PORT	GPIOA

/* LCD Commands definition */
#define LCD_CLEAR           0x01
#define RETURN_HOME         0x02
#define DECREMENT_CURSOR    0x04
#define SHIFT_DISPLAY_RIGHT 0x05
#define INCREMENT_CURSOR    0x06
#define SHIFT_DISPLAY_LEFT  0x07
#define SHIFT_CURSOR_LEFT   0x10
#define SHIFT_CURSOR_RIGHT  0x14
#define FOUR_BIT            0x28
#define EIGHT_BIT           0x38
#define CURSOR_OFF          0x0C
#define CURSOR_ON           0x0E

// cursor position to DDRAM mapping
#define LCD_DDRAM           7	//DB7: set DD RAM address
#define LCD_LINE0_DDRAMADDR		0x00
#define LCD_LINE1_DDRAMADDR		0x40
#define LCD_LINE2_DDRAMADDR		0x14
#define LCD_LINE3_DDRAMADDR		0x54

#endif // _LCD_CFG_H__
