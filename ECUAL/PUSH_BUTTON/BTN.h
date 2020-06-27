/*
 * pushButton.h
 *
 *  Created on: Dec 29, 2019
 *      Author: eng-m
 */

#ifndef ECUAL_BTN_BTN_H_
#define ECUAL_BTN_BTN_H_

#include "std_types.h"

#define BTN_0 0
#define BTN_1 1
#define PRESSED   0xFF
#define RELEASED  0x00
#define NUM_OF_BTN 2


#define BTN_GPIO(BTN_ID)	((BTN_ID)? GPIOB:GPIOC)
#define BTN_BIT(BTN_ID)	    ((BTN_ID)? BIT2:BIT4)


extern ERROR_STATUS BTN_Init(uint8 u8_buttonId);

extern ERROR_STATUS BTN_GetStatus(uint8 u8_buttonId,bool *ptru8_status);

#endif /* ECUAL_BTN_BTN_H_ */
