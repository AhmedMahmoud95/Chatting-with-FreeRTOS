/*
 * pushButton.c
 *
 *  Created on: Dec 29, 2019
 *      Author: Ghanem & Tamoh
 */
/************************************************************************/
/*		                        INCLUDES                 		        */
/************************************************************************/
#include "Dio.h"
#include "BTN.h"
/************************************************************************/
/*		                        DEFINES                 		        */
/************************************************************************/

#define MAX_COUNTS 10
/************************************************************************/
/*		             STATIC and GLOBAL VATIABLES          		        */
/************************************************************************/

static uint8 gsau8_btnStatus[NUM_OF_BTN] = {0};
/************************************************************************/
/*		                FUNCTIONS' IMPLEMENTATION         		        */
/***************************************************************************
 *
 *
 * @Function: BTN_Init
 * @Inputs:	u8_buttonId -> indicate the push button index to be initialized.
 * @Outputs:
 * @In Out:
 * @Return: ERROR_STATUS -> check if there any error occurs, would return E_NOK else it would return E_OK.
 * @Description: Initiate the pin of button as input.
 *	event of interrupt.
 ****************************************************************************/
ERROR_STATUS BTN_Init(uint8 u8_buttonId)
{
	DIO_Cfg_s ST_btnDio = {0};
	ST_btnDio.GPIO = BTN_GPIO(u8_buttonId);
	ST_btnDio.pins = BTN_BIT(u8_buttonId);
	ST_btnDio.dir = INPUT;
	return DIO_init(&ST_btnDio);
}
/*
 * Function: BTN_GetStatus
 * Inputs: u8_buttonId ->indicate the push button index to read it's status.
 * Outputs:*ptru8_status -> set by PRESSED or RELEASED.
 * In Out:
 * Return: ERROR_STATUS -> check if there any error occurs, would return E_NOK else it would return E_OK.
 * Description: read ten stable status of the button and then return that status to avoid bouncing.
 */
ERROR_STATUS BTN_GetStatus(uint8 u8_buttonId,bool *ptru8_status)
{
    if (ptru8_status == NULL)
    {
        return E_NOK;
    }
	 // The function reads the button continuously until it reads 10 similar readings in a row
	    uint8  u8_counts = 0;
	    bool bool_stableReading = FALSE;
	    uint8 u8_initialStatus = RELEASED, u8_currentStatus = RELEASED;

	    /* read the button pin	*/
	    if( E_OK == DIO_Read(BTN_GPIO(u8_buttonId), BTN_BIT(u8_buttonId),  &u8_initialStatus))
	    {
	    	while (bool_stableReading == FALSE)
	    	{
	    		/* check for ten reads that are the same*/
	    		if(E_OK ==DIO_Read(BTN_GPIO(u8_buttonId), BTN_BIT(u8_buttonId),  &u8_currentStatus))
	    		{

	    			if (u8_initialStatus == u8_currentStatus)
	    			{
	    				u8_counts++;
	    				if (u8_counts >= MAX_COUNTS)
	    				{
	    					gsau8_btnStatus[u8_buttonId] = u8_currentStatus;
	    					*ptru8_status = u8_currentStatus * PRESSED;
	    					bool_stableReading = TRUE;
	    				}
	    				else
	    				{

	    				}
	    			}
	    			else
	    			{
	    				/*if they not equal to each other just start the ten reads again*/
	    				u8_initialStatus = u8_currentStatus;
	    				u8_counts = 0;
	    			}
	    		}
	    		else
	    		{

	    		}
	    	}
	    }
	    else
	    {
	    	return E_NOK;
	    }

	    return E_OK;
}
