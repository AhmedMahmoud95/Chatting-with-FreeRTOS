/**
 * \filename:   keypad.h
 * \project:    keypad&LCD_withOS
 * \Auther:     TAmoo7
 * \Date:       22/01/2020
 * \Version:    1.0
 */

/************************************************************************/
/*						      Includes                                  */
/************************************************************************/
#include "keypad.h"

/************************************************************************/
/*					    	 defines                                    */
/************************************************************************/
#define MAX_BOUNCE_CHECK        20

/************************************************************************/
/*                        Global variables                              */
/************************************************************************/
uint8 gu8_pressedKey = NO_KEY_PRESSED;

/************************************************************************/
/*                  Static functions declarations                       */
/************************************************************************/
/**
 * \Name:   updateKey
 * \IN:     NONE
 * \OUT:    NONE
 * \Return: ERROR_STATUS
 * \brief:  checks for the pressed Key
 */
static void updateKey (void);
/************************************************************************/
/*                      Functions definitions                           */
/************************************************************************/

/**
 * \Name:   keypad_init
 * \IN:     NONE
 * \OUT:    NONE
 * \Return: ERROR_STATUS
 * \brief:  Initiates the keypad pins
 */
ERROR_STATUS keypad_init ()
{
    DIO_Cfg_s DIO_Object1 = {KEYPAD_PORT, ROW1 | ROW2 | ROW3, OUTPUT};
    if (DIO_init( &DIO_Object1) == E_NOK)
    {
        return E_NOK;
    }
    else
    {/**< Do nothing */}

    DIO_Cfg_s DIO_Object2 = {KEYPAD_PORT, COLOMN1 | COLOMN2 | COLOMN3 , INPUT};
    if (DIO_init( &DIO_Object2) == E_NOK)
    {
        return E_NOK;
    }
    else
    {/**< Do nothing */}
    DIO_Write(KEYPAD_PORT, COLOMN1 | COLOMN2 | COLOMN3 , HIGH);

    return E_OK;
}
/**
 * \Name:   keypad_getPressedKey
 * \IN:     NONE
 * \OUT:    NONE
 * \Return: ERROR_STATUS
 * \brief:  Gets the pressed key and checks for bouncing
 */
ERROR_STATUS keypad_getPressedKey (uint8 *u8_pkey)
{
    updateKey();
    uint8 u8_prevPressedKey = gu8_pressedKey;
    updateKey();
    if (gu8_pressedKey != u8_prevPressedKey)
    {
        gu8_pressedKey = NO_KEY_PRESSED;
    }
    else
    { /**< Do nothing */ }
    *u8_pkey = gu8_pressedKey;

    return E_OK;
}

/************************************************************************/
/*                  Static functions definitions                        */
/************************************************************************/
/**
 * \Name:   updateKey
 * \IN:     NONE
 * \OUT:    NONE
 * \Return: ERROR_STATUS
 * \brief:  checks for the pressed Key
 */
static void updateKey (void)
{
    uint8 u8_currentState;


            /**< Check for columns with Row 1*/
    DIO_Write(KEYPAD_PORT, ROW1 | ROW2 | ROW3, HIGH);
    DIO_Write(KEYPAD_PORT, ROW1, LOW);

    /**< Check for button 1 */
    DIO_Read(KEYPAD_PORT, COLOMN1, &u8_currentState);
    if (u8_currentState == FALSE)
    {
        uint8 u8_counter = 0;
        /**< Check for de-bouncing */
        while (u8_counter < MAX_BOUNCE_CHECK )
        {
            DIO_Read(KEYPAD_PORT, COLOMN1, &u8_currentState);
            if (u8_currentState != FALSE)
            {
                gu8_pressedKey = NO_KEY_PRESSED;
                return;
            }
            else
            {
                DIO_Read(KEYPAD_PORT, COLOMN1, &u8_currentState);
                u8_counter ++;
            }
        }
        gu8_pressedKey = '1';
        return;
    }

    /**< Check for button 2 */
    DIO_Read(KEYPAD_PORT, COLOMN2, &u8_currentState);
    if (u8_currentState == FALSE)
    {
        uint8 u8_counter = 0;
        /**< Check for de-bouncing */
        while (u8_counter < MAX_BOUNCE_CHECK )
        {
            DIO_Read(KEYPAD_PORT, COLOMN2, &u8_currentState);
            if (u8_currentState != FALSE)
            {
                gu8_pressedKey = NO_KEY_PRESSED;
                return;
            }
            else
            {
                DIO_Read(KEYPAD_PORT, COLOMN2, &u8_currentState);
                u8_counter ++;
            }
        }
        gu8_pressedKey = '2';
        return;
    }

    /**< Check for button 3 */
    DIO_Read(KEYPAD_PORT, COLOMN3, &u8_currentState);
    if (u8_currentState == FALSE)
    {
        uint8 u8_counter = 0;
        /**< Check for de-bouncing */
        while (u8_counter < MAX_BOUNCE_CHECK )
        {
            DIO_Read(KEYPAD_PORT, COLOMN3, &u8_currentState);
            if (u8_currentState != FALSE)
            {
                gu8_pressedKey = NO_KEY_PRESSED;
                return;
            }
            else
            {
                DIO_Read(KEYPAD_PORT, COLOMN3, &u8_currentState);
                u8_counter ++;
            }
        }
        gu8_pressedKey = '3';
        return;
    }


            /**< Check for columns with Row 2*/

    DIO_Write(KEYPAD_PORT, ROW1 | ROW2 | ROW3, HIGH);
    DIO_Write(KEYPAD_PORT, ROW2, LOW);

    /**< Check for button 4 */
    DIO_Read(KEYPAD_PORT, COLOMN1, &u8_currentState);
    if (u8_currentState == FALSE)
    {
        uint8 u8_counter = 0;
        /**< Check for de-bouncing */
        while (u8_counter < MAX_BOUNCE_CHECK )
        {
            DIO_Read(KEYPAD_PORT, COLOMN1, &u8_currentState);
            if (u8_currentState != FALSE)
            {
                gu8_pressedKey = NO_KEY_PRESSED;
                return;
            }
            else
            {
                DIO_Read(KEYPAD_PORT, COLOMN1, &u8_currentState);
                u8_counter ++;
            }
        }
        gu8_pressedKey = '4';
        return;
    }

    /**< Check for button 5 */
    DIO_Read(KEYPAD_PORT, COLOMN2, &u8_currentState);
    if (u8_currentState == FALSE)
    {
        uint8 u8_counter = 0;
        /**< Check for de-bouncing */
        while (u8_counter < MAX_BOUNCE_CHECK )
        {
            DIO_Read(KEYPAD_PORT, COLOMN2, &u8_currentState);
            if (u8_currentState != FALSE)
            {
                gu8_pressedKey = NO_KEY_PRESSED;
                return;
            }
            else
            {
                DIO_Read(KEYPAD_PORT, COLOMN2, &u8_currentState);
                u8_counter ++;
            }
        }
        gu8_pressedKey = '5';
        return;
    }

    /**< Check for button 6 */
    DIO_Read(KEYPAD_PORT, COLOMN3, &u8_currentState);
    if (u8_currentState == FALSE)
    {
        uint8 u8_counter = 0;
        /**< Check for de-bouncing */
        while (u8_counter < MAX_BOUNCE_CHECK )
        {
            DIO_Read(KEYPAD_PORT, COLOMN3, &u8_currentState);
            if (u8_currentState != FALSE)
            {
                gu8_pressedKey = NO_KEY_PRESSED;
                return;
            }
            else
            {
                DIO_Read(KEYPAD_PORT, COLOMN3, &u8_currentState);
                u8_counter ++;
            }
        }
        gu8_pressedKey = '6';
        return;
    }



            /**< Check for columns with Row 3*/

    DIO_Write(KEYPAD_PORT, ROW1 | ROW2 | ROW3, HIGH);
    DIO_Write(KEYPAD_PORT, ROW3, LOW);

    /**< Check for button 7 */
    DIO_Read(KEYPAD_PORT, COLOMN1, &u8_currentState);
    if (u8_currentState == FALSE)
    {
        uint8 u8_counter = 0;
        /**< Check for de-bouncing */
        while (u8_counter < MAX_BOUNCE_CHECK )
        {
            DIO_Read(KEYPAD_PORT, COLOMN1, &u8_currentState);
            if (u8_currentState != FALSE)
            {
                gu8_pressedKey = NO_KEY_PRESSED;
                return;
            }
            else
            {
                DIO_Read(KEYPAD_PORT, COLOMN1, &u8_currentState);
                u8_counter ++;
            }
        }
        gu8_pressedKey = '7';
        return;
    }

    /**< Check for button 8 */
    DIO_Read(KEYPAD_PORT, COLOMN2, &u8_currentState);
    if (u8_currentState == FALSE)
    {
        uint8 u8_counter = 0;
        /**< Check for de-bouncing */
        while (u8_counter < MAX_BOUNCE_CHECK )
        {
            DIO_Read(KEYPAD_PORT, COLOMN2, &u8_currentState);
            if (u8_currentState != FALSE)
            {
                gu8_pressedKey = NO_KEY_PRESSED;
                return;
            }
            else
            {
                DIO_Read(KEYPAD_PORT, COLOMN2, &u8_currentState);
                u8_counter ++;
            }
        }
        gu8_pressedKey = '8';
        return;
    }

    /**< Check for button 9 */
    DIO_Read(KEYPAD_PORT, COLOMN3, &u8_currentState);
    if (u8_currentState == FALSE)
    {
        uint8 u8_counter = 0;
        /**< Check for de-bouncing */
        while (u8_counter < MAX_BOUNCE_CHECK )
        {
            DIO_Read(KEYPAD_PORT, COLOMN3, &u8_currentState);
            if (u8_currentState != FALSE)
            {
                gu8_pressedKey = NO_KEY_PRESSED;
                return;
            }
            else
            {
                DIO_Read(KEYPAD_PORT, COLOMN3, &u8_currentState);
                u8_counter ++;
            }
        }
        gu8_pressedKey = '9';
        return;
    }

    /**< Default case */
    gu8_pressedKey = NO_KEY_PRESSED;
}
