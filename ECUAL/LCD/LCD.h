/**
 * \filename:      LCD.h
 * \project_name:   keypad&LCD_withOS
 * \Owner:          Tamoo7
 * \Date:           23/01/2020
 * \Version:        1.0
 */
#ifndef _LCD_H__
#define _LCD_H__
/************************************************************************/
/*						         Includes                               */
/************************************************************************/
#include "LCD_cfg.h"


/************************************************************************/
/*                      Functions declarations                          */
/************************************************************************/

/**
 * \function name:     LCD_init
 * \IN:                 NONE
 * \OUT:                NONE
 * \return:             ERROR_STATUS
 * \brief:              Initiates the module and sets input and output pins
 */

ERROR_STATUS LCD_init (void);


/**
 * \function name:      LCD_sendCommand
 * \IN:                 NONE
 * \OUT:                NONE
 * \return:             ERROR_STATUS
 * \brief:              Sends a command to LCD
 */

ERROR_STATUS LCD_sendCommand(uint8 u8_command);

/**
 * \function name:      LCD_displayCharacter
 * \IN:                 s8_char
 * \OUT:                NONE
 * \return:             ERROR_STATUS
 * \brief:              Sends a char to LCD
 */

ERROR_STATUS LCD_displayCharacter(sint8 s8_char);

/**
 * \function name:      LCD_displayString
 * \IN:                 *s8_char
 * \OUT:                NONE
 * \return:             ERROR_STATUS
 * \brief:              Sends a string to LCD
 */

ERROR_STATUS LCD_displayString (sint8 *s8_char);



/**
 * \function name:      LCD_gotoRowColumn
 * \IN:                 u8_x, u8_y -> x and y co-ordinations
 * \OUT:                NONE
 * \return:             ERROR_STATUS
 */

ERROR_STATUS LCD_gotoRowColumn (uint8 u8_x, uint8 u8_y);


/**
 * \function name:      LCD_sendString_RowCol
 * \IN:                 u8_x, u8_y, *s8_char
 * \OUT:                NONE
 * \return:             ERROR_STATUS
 */

ERROR_STATUS LCD_sendString_RowCol (uint8 u8_x, uint8 u8_y, sint8 *s8_char);






#endif // _LCD_H__
