#include "DIO.h"
#include "registers.h"
/*
*Input: DIO_Cfg_s -> to get PORT name, pins to be initiated and the required direction
*Output: No output
*In/Out:
*Description: This function can set the direction of a full port, a nibble
* 			  or even one pin.
*/
ERROR_STATUS DIO_init (DIO_Cfg_s *DIO_info)
{
	switch (DIO_info->GPIO)
	{
		case GPIOA:
		if (DIO_info->dir == HIGH)
		{
			PORTA_DIR |= DIO_info->pins;
		}
		else
		{
			DIO_info->pins ^= 0xFF;
			PORTA_DIR &= DIO_info->pins;
		}
		return E_OK;

		case GPIOB:
		if (DIO_info->dir == HIGH)
		{
			PORTB_DIR |= DIO_info->pins;
		}
		else
		{
			DIO_info->pins ^= 0xFF;
			PORTB_DIR &= DIO_info->pins;
		}
		return E_OK;

		case GPIOC:
		if (DIO_info->dir == HIGH)
		{
			PORTC_DIR |= DIO_info->pins;
		}
		else
		{
			DIO_info->pins ^= 0xFF;
			PORTC_DIR &= DIO_info->pins;
		}
		return E_OK;

		case GPIOD:
		if (DIO_info->dir== HIGH)
		{
			PORTD_DIR |= DIO_info->pins;
		}
		else
		{
			DIO_info->pins ^= 0xFF;
			PORTD_DIR &= DIO_info->pins;
		}
		return E_OK;

		default:
		return E_NOK;
	}
}

/*
*Input: GPIO -> to get PORT name
*					- GPIOA
*					- GPIOB
*					- GPIOC
*					- GPIOD
*		pins -> pins to be written at.
*					- PIN0
*					- PIN1
*					- PIN2
*					- PIN3
*					- PIN4
*					- PIN5
*					- PIN6
*					- PIN7
*					- UPPER_NIBBLE
*					- LOWER_NIBBLE
*					- FULL_PORT
*		value -> The desired value.
*Output: No output
*In/Out: No In/Out
*Description: This function can set the value of a full port, a nibble
* 			  or even one pin.
*/
ERROR_STATUS DIO_Write (uint8 GPIO, uint8 pins, uint8 value)
{
	switch (GPIO)
	{
		case GPIOA:
		if (value == HIGH)
		{
			PORTA_DATA |= pins;
		}
		else
		{
			pins ^= 0xFF;
			PORTA_DATA &= pins;
		}
		return E_OK;

		case GPIOB:
		if (value == HIGH)
		{
			PORTB_DATA |= pins;
		}
		else
		{
			pins ^= 0xFF;
			PORTB_DATA &= pins;
		}
		return E_OK;

		case GPIOC:
		if (value == HIGH)
		{
			PORTC_DATA |= pins;
		}
		else
		{
			pins ^= 0xFF;
			PORTC_DATA &= pins;
		}
		return E_OK;

		case GPIOD:
		if (value == HIGH)
		{
			PORTD_DATA |= pins;
		}
		else
		{
			pins ^= 0xFF;
			PORTD_DATA &= pins;
		}
		return E_OK;

		default:
		return E_NOK;
	}
}
/*
*Input: GPIO -> to get PORT name
*					- GPIOA
*					- GPIOB
*					- GPIOC
*					- GPIOD
*		pins -> pins to be written at.
*					- PIN0
*					- PIN1
*					- PIN2
*					- PIN3
*					- PIN4
*					- PIN5
*					- PIN6
*					- PIN7
*					- UPPER_NIBBLE
*					- LOWER_NIBBLE
*					- FULL_PORT
*Output: data -> the acquired data wether it was PORT data or pins data
*In/Out:
*Description: This function gets the value of a full port, a nibble
* 			  or even one pin.
*/
ERROR_STATUS DIO_Read (uint8 GPIO,uint8 pins, uint8 *data)
{
    if (pins == 0)
    {
        return E_NOK;
    }
	switch (GPIO)
	{
		case GPIOA:
		*data = (PORTA_PIN & pins) / pins;
		return E_OK;
		break;

		case GPIOB:
		*data = (PORTB_PIN & pins) / pins;
		return E_OK;
		break;

		case GPIOC:
		*data = (PORTC_PIN & pins) / pins;
		return E_OK;
		break;

		case GPIOD:
		*data = (PORTD_PIN & pins) / pins;
		return E_OK;
		break;

		default:
		return E_NOK;
		break;
	}
}
/*
*Input: GPIO -> to get PORT name
*					- GPIOA
*					- GPIOB
*					- GPIOC
*					- GPIOD
*		pins -> pins to be written at.
*					- PIN0
*					- PIN1
*					- PIN2
*					- PIN3
*					- PIN4
*					- PIN5
*					- PIN6
*					- PIN7
*					- UPPER_NIBBLE
*					- LOWER_NIBBLE
*					- FULL_PORT
*Output: data -> No output
*In/Out:
*Description: This function toggles the value of a full port, a nibble
* 			  or even one pin.
*/
ERROR_STATUS DIO_Toggle (uint8 GPIO, uint8 pins)
{
	switch (GPIO)
	{
		case GPIOA:
            PORTA_DATA ^= pins;
            return E_OK;

		case GPIOB:
            PORTB_DATA ^= pins;
            return E_OK;

		case GPIOC:
            PORTC_DATA ^= pins;
            return E_OK;

		case GPIOD:
            PORTD_DATA ^= pins;
            return E_OK;
		default:
            return E_NOK;
	}
}
