#include "led.h"

/**
 * Description: Initialize the LED_x (where x 0, 1, 2, 3) as output
 * @param led_id: The led to be initialized and it takes
 * 				  one of the enum (En_LedNumber_t) parameters
 *
 */
void Led_Init(En_LedNumber_t  led_id)
{
	DIO_Cfg_s str_ledCfg ;
	switch (led_id){
	case (LED_0):
		str_ledCfg.GPIO = LED_0_GPIO;
		str_ledCfg.pins = LED_0_BIT;

		break;
	case (LED_1):
		str_ledCfg.GPIO = LED_1_GPIO;
		str_ledCfg.pins = LED_1_BIT;
			break;
	case LED_2:
		str_ledCfg.GPIO = LED_2_GPIO;
		str_ledCfg.pins = LED_2_BIT;
			break;
	case LED_3:
		str_ledCfg.GPIO = LED_3_GPIO;
		str_ledCfg.pins = LED_3_BIT;
			break;
	default:
		break;

	}

	str_ledCfg.dir = OUTPUT;
	DIO_init(&str_ledCfg);
}
/**
 * Description: Change the LED_x state (where x 0, 1, 2, 3) to be on
 * @param led_id: The led to be initialized and it takes
 * 				  one of the enum (En_LedNumber_t) parameters
 *
 */
void Led_On(En_LedNumber_t led_id){

	switch(led_id){

	case LED_0:
		DIO_Write(LED_0_GPIO,LED_0_BIT,HIGH);
		break;
	case LED_1:
		DIO_Write(LED_1_GPIO,LED_1_BIT,HIGH);
			break;
	case LED_2:
		DIO_Write(LED_2_GPIO,LED_2_BIT,HIGH);
			break;
	case LED_3:
		DIO_Write(LED_3_GPIO,LED_3_BIT,HIGH);
			break;
	default:
		break;
	}

}
/**
 * Description: Change the LED_x state (where x 0, 1, 2, 3) to be off
 * @param led_id: The led to be initialized and it takes
 * 				  one of the enum (En_LedNumber_t) parameters
 *
 */
void Led_Off(En_LedNumber_t led_id){
	switch(led_id){
	case LED_0:
		DIO_Write(LED_0_GPIO,LED_0_BIT,LOW);
		break;
	case LED_1:
		DIO_Write(LED_1_GPIO,LED_1_BIT,LOW);
			break;
	case LED_2:
		DIO_Write(LED_2_GPIO,LED_2_BIT,LOW);
			break;
	case LED_3:
		DIO_Write(LED_3_GPIO,LED_3_BIT,LOW);
			break;
	default:
		break;
	}

}
/**
 * Description: Toggle the LED_x state (where x 0, 1, 2, 3)
 * @param led_id: The led to be initialized and it takes
 * 				  one of the enum (En_LedNumber_t) parameters
 *
 */
void Led_Toggle(En_LedNumber_t led_id){
	switch(led_id){
	case LED_0:
		DIO_Toggle(LED_0_GPIO,LED_0_BIT);
		break;
	case LED_1:
		DIO_Toggle(LED_1_GPIO,LED_1_BIT);
			break;
	case LED_2:
		DIO_Toggle(LED_2_GPIO,LED_2_BIT);
			break;
	case LED_3:
		DIO_Toggle(LED_3_GPIO,LED_3_BIT);
			break;
	default:
		break;
	}

}
