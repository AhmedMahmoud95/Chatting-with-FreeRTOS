/************************************************************************/
/*	       	                   Includes                                 */
/************************************************************************/
#include "S2_US2.h"


/************************************************************************/
/*	       	            Global defines                                  */
/************************************************************************/
#define BTN_0_PRESSED       1
#define BTN_1_PRESSED       2
#define NO_BTN_PRESSED      3

/************************************************************************/
/*	       	            Global variables                                */
/************************************************************************/
QueueHandle_t gQH_BTN_status;

/************************************************************************/
/*	       	            Functions declaration                           */
/************************************************************************/
/**
 * \function name:      S2_US2_init()
 * \IN:                 vptr
 * \OUT:                NONE
 * \return:             NONE
 * \Discription:        Initiates the push button, and the LED
 */
void S2_US2_init ( void *vptr)
{
    for (;;)
    {
        Led_Init(LED_0);
        BTN_Init(BTN_0);
        BTN_Init(BTN_1);
        LCD_init();
        gQH_BTN_status = xQueueCreate(1, sizeof(uint8));
        vTaskSuspend(NULL);
    }
}

/**
 * \function name:      S2_US2_getButtons()
 * \IN:                 vptr
 * \OUT:                NONE
 * \return:             NONE
 * \Discription:        checks the button status and calculates the pressing time
 */
void S2_US2_getButtons ( void *vptr)
{
    bool b_pin0Status, b_pin1Status;
    uint8 u8_btnStatus = 0;
    for (;;)
    {
        BTN_GetStatus(BTN_0, &b_pin0Status);
        BTN_GetStatus(BTN_1, &b_pin1Status);
        if (b_pin0Status == PRESSED)
        {
            u8_btnStatus = BTN_0_PRESSED;
            xQueueReset(gQH_BTN_status);
            xQueueOverwrite(gQH_BTN_status, &u8_btnStatus);
        }
        else if (b_pin1Status == PRESSED)
        {
            u8_btnStatus = BTN_1_PRESSED;
            xQueueReset(gQH_BTN_status);
            xQueueOverwrite(gQH_BTN_status, &u8_btnStatus);
        }
        else
        {
            u8_btnStatus = NO_BTN_PRESSED;
            xQueueReset(gQH_BTN_status);
            xQueueOverwrite(gQH_BTN_status, &u8_btnStatus);
        }
        vTaskDelay(portTICK_PERIOD_MS * 100);
    }
}

/**
 * \function name:      S2_US2_updateLED()
 * \IN:                 vptr
 * \OUT:                NONE
 * \return:             NONE
 * \Discription:        Updates the toggling rate if needed
 */
void S2_US2_updateLED ( void *vptr)
{
    for(;;)
    {
        uint8 u8_pressedBTN = 0;
        xQueueReceive(gQH_BTN_status, (void *)&u8_pressedBTN, 0);
        if (u8_pressedBTN == BTN_0_PRESSED)
        {
            Led_On(LED_0);
        }
        else if (u8_pressedBTN == BTN_1_PRESSED)
        {
            Led_On(LED_0);
        }
        else
        {
            Led_Off(LED_0);
        }
        xQueueOverwrite(gQH_BTN_status, &u8_pressedBTN);
        vTaskDelay(portTICK_PERIOD_MS * 100);
    }
}

/**
 * \function name:      S2_US2_updateLCD()
 * \IN:                 vptr
 * \OUT:                NONE
 * \return:             NONE
 * \Discription:        Updates the toggling rate if needed
 */
void S2_US2_updateLCD ( void *vptr)
{
    static uint8 su8_prevLedStatus = 0;
    uint8 u8_LedStatus;
    for (;;)
    {
        xQueueReceive(gQH_BTN_status, &u8_LedStatus, 0);
        if (su8_prevLedStatus != u8_LedStatus)
        {
            su8_prevLedStatus = u8_LedStatus;
            if (u8_LedStatus == BTN_0_PRESSED)
            {
                LCD_sendCommand(LCD_CLEAR);
                vTaskDelay(5 * portTICK_PERIOD_MS);
                LCD_sendString_RowCol(0, 0, "LED is ON");
                LCD_sendString_RowCol(0, 1, "BTN 0 pressed");
            }
            else if (u8_LedStatus == BTN_1_PRESSED)
            {
                LCD_sendCommand(LCD_CLEAR);
                vTaskDelay(5 * portTICK_PERIOD_MS);
                LCD_sendString_RowCol(0, 0, "LED is ON");
                LCD_sendString_RowCol(0, 1, "BTN 1 pressed");
            }
            else
            {
                LCD_sendString_RowCol(0, 0, "LED is OFF");
                LCD_sendString_RowCol(0, 1, "NO pressed BTN");
            }
        }
        else
        {/**< Do nothing */}
        vTaskDelay(portTICK_PERIOD_MS * 100);
    }
}
/**
 * \function name:      S2_US2_MainFunction
 * \IN:                 vptr
 * \OUT:                NONE
 * \return:             NONE
 * \Discription:        Runs the full system
 */
void S2_US2_MainFunction (void)
{
    xTaskCreate(S2_US2_init, "Init", configMINIMAL_STACK_SIZE, (void *)0, 4, NULL);
    xTaskCreate(S2_US2_getButtons, "Button",configMINIMAL_STACK_SIZE, (void *)0, 3, NULL );
    xTaskCreate(S2_US2_updateLED, "Led", configMINIMAL_STACK_SIZE, (void *)0, 2, NULL);
    xTaskCreate(S2_US2_updateLCD, "LCD", configMINIMAL_STACK_SIZE, (void *)0, 1, NULL);
    vTaskStartScheduler();

}

