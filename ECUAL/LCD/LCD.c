/**
 * \filename:       LCD.c
 * \project_name:   keypad&LCD_withOS
 * \Owner:          Tamoo7 (Updated version from Osama)
 * \Date:           23/01/2020
 * \Version:        1.0
 */

/************************************************************************/
/*						         Includes                               */
/************************************************************************/
#include "LCD.h"
#include <string.h>
/************************************************************************/
/*                      Static functions                                */
/************************************************************************/
void LCD_sendNibble(uint8 u8_command)
{
    uint8 u8_mask;
    /**< Shifts the command into the lower nibble */
    u8_command = u8_command >> 4;

    /**< Sets the 4 LCD bits with the command */
    u8_mask = 0b0001;
    if(u8_command&u8_mask)
        DIO_Write(LCD_D4_PORT, LCD_D4_PIN, HIGH);
    else
        DIO_Write(LCD_D4_PORT, LCD_D4_PIN, LOW);

    u8_mask = 0b0010;
    if(u8_command&u8_mask)
        DIO_Write(LCD_D5_PORT, LCD_D5_PIN, HIGH);
    else
        DIO_Write(LCD_D5_PORT, LCD_D5_PIN, LOW);

    u8_mask = 0b0100;
    if(u8_command&u8_mask)
        DIO_Write(LCD_D6_PORT, LCD_D6_PIN, HIGH);
    else
        DIO_Write(LCD_D6_PORT, LCD_D6_PIN, LOW);

    u8_mask = 0b1000;
    if(u8_command&u8_mask)
        DIO_Write(LCD_D7_PORT, LCD_D7_PIN, HIGH);
    else
        DIO_Write(LCD_D7_PORT, LCD_D7_PIN, LOW);
}

void LCD_EN_pulse(void)
{
    DIO_Write(LCD_EN_PORT, LCD_EN_PIN, HIGH);
    SwDelay_us(1);
    DIO_Write(LCD_EN_PORT, LCD_EN_PIN, LOW);
}
/************************************************************************/
/*                      Functions definitions                           */
/************************************************************************/

/**
 * \function name:     	LCD_init
 * \IN:                 NONE
 * \OUT:                NONE
 * \return:             ERROR_STATUS
 * \brief:              Initiates the module and sets input and output pins
 */
ERROR_STATUS LCD_init (void)
{
    DIO_Cfg_s ST_dio = {0};
    ST_dio.GPIO = LCD_RS_PORT;
    ST_dio.dir = OUTPUT;
    ST_dio.pins = LCD_RS_PIN;
    DIO_init(&ST_dio);

    ST_dio.GPIO = LCD_RW_PORT;
    ST_dio.pins = LCD_RW_PIN;
    DIO_init(&ST_dio);

    ST_dio.GPIO = LCD_EN_PORT;
    ST_dio.pins = LCD_EN_PIN;
    DIO_init(&ST_dio);

    ST_dio.GPIO = LCD_D4_PORT;
    ST_dio.pins = LCD_D4_PIN;
    DIO_init(&ST_dio);

    ST_dio.GPIO = LCD_D5_PORT;
    ST_dio.pins = LCD_D5_PIN;
    DIO_init(&ST_dio);

    ST_dio.GPIO = LCD_D6_PORT;
    ST_dio.pins = LCD_D6_PIN;
    DIO_init(&ST_dio);

    ST_dio.GPIO = LCD_D7_PORT;
    ST_dio.pins = LCD_D7_PIN;
    DIO_init(&ST_dio);

    SwDelay_ms(20);

    LCD_sendCommand(0x33);
    SwDelay_ms(1);
    LCD_sendCommand(0x32);
    SwDelay_ms(1);
    LCD_sendCommand(FOUR_BIT); // 4-bit
    SwDelay_ms(1);
    LCD_sendCommand(CURSOR_ON);
    SwDelay_ms(1);
    LCD_sendCommand(LCD_CLEAR);
    SwDelay_ms(2);
    LCD_sendCommand(INCREMENT_CURSOR);
    SwDelay_ms(1);
    LCD_sendCommand(CURSOR_OFF); // Cursor off
    SwDelay_ms(2);

    return E_OK;
}

/**
 * \function name:      LCD_sendCommand
 * \IN:                 u8_command
 * \OUT:                NONE
 * \return:             ERROR_STATUS
 * \brief:              Sends a command to LCD
 */

ERROR_STATUS LCD_sendCommand(uint8 u8_command)
{
    DIO_Write(LCD_RS_PORT, LCD_RS_PIN, LOW);

    LCD_sendNibble(u8_command); // Higher nibble first
    LCD_EN_pulse();
    /**< The valuable data should saturate in the upper nibble  */
    /**< as we shift it again in the opposite direction inside LCD_sendNibble() */
    LCD_sendNibble(u8_command << 4);
    LCD_EN_pulse();
    return E_OK;
}

/**
 * \function name:      LCD_displayCharacter
 * \IN:                 s8_char
 * \OUT:                NONE
 * \return:             ERROR_STATUS
 * \brief:              Sends a char to LCD
 */

ERROR_STATUS LCD_displayCharacter(sint8 s8_char)
{
    DIO_Write(LCD_RS_PORT, LCD_RS_PIN, HIGH);

    LCD_sendNibble(s8_char); // Higher nibble first
    LCD_EN_pulse();

    /**< The valuable data should saturate in the upper nibble  */
    /**< as we shift it again in the opposite direction inside LCD_sendNibble() */
    LCD_sendNibble(s8_char << 4);
    LCD_EN_pulse();
    return E_OK;
}

/**
 * \function name:      LCD_displayString
 * \IN:                 *s8_char
 * \OUT:                NONE
 * \return:             ERROR_STATUS
 * \brief:              Sends a string to LCD
 */

ERROR_STATUS LCD_displayString (sint8 *s8_char)
{
	while(*s8_char)
    {
		LCD_displayCharacter(*s8_char++);
	}
    return E_OK;
/*
    static uint16 u16_BufferIndex =0;
    if (u16_BufferIndex <= strlen((char *)s8_char))
    {
        LCD_displayCharacter(s8_char[u16_BufferIndex]);
        u16_BufferIndex ++;
        return E_OK;
    }
    else
    {
        return E_OK;
    }
*/
}

/**
 * \function name:      LCD_gotoRowColumn
 * \IN:                 u8_x, u8_y -> x and y co-ordinations
 * \OUT:                NONE
 * \return:             ERROR_STATUS
 */

ERROR_STATUS LCD_gotoRowColumn (uint8 u8_x, uint8 u8_y)
{
    uint8 u8_DDRAMAddr;
    // remap lines into proper order
    switch(u8_y)
    {
    case 0:
        u8_DDRAMAddr = LCD_LINE0_DDRAMADDR+u8_x;
        break;
    case 1:
        u8_DDRAMAddr = LCD_LINE1_DDRAMADDR+u8_x;
        break;
    case 2:
        u8_DDRAMAddr = LCD_LINE2_DDRAMADDR+u8_x;
        break;
    case 3:
        u8_DDRAMAddr = LCD_LINE3_DDRAMADDR+u8_x;
        break;
    default:
        u8_DDRAMAddr = LCD_LINE0_DDRAMADDR+u8_x;
    }

    /**< set data address */
    LCD_sendCommand(1 <<LCD_DDRAM | u8_DDRAMAddr);
    return E_OK;
}
/**
 * \function name:      LCD_sendString_RowCol
 * \IN:                 u8_x, u8_y, *s8_char
 * \OUT:                NONE
 * \return:             ERROR_STATUS
 */

ERROR_STATUS LCD_sendString_RowCol (uint8 u8_x, uint8 u8_y, sint8 *s8_char)
{
    LCD_gotoRowColumn(u8_x, u8_y);
    LCD_displayString(s8_char);
}

