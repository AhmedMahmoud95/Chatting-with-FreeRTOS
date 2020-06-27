/************************************************************************/
/*	       	                   Includes                                 */
/************************************************************************/
#include "S1_US3.h"

/************************************************************************/
/*	       	            Global variables                                */
/************************************************************************/
QueueHandle_t gQH_updateLED;

/************************************************************************/
/*	       	            Functions declaration                           */
/************************************************************************/
/**
 * \function name:      S1_US3_init()
 * \IN:                 vptr
 * \OUT:                NONE
 * \return:             NONE
 * \Discription:        Initiates the push button, and the LED
 */
void S1_US3_init ( void *vptr)
{
    for (;;)
    {
        Led_Init(LED_0);
        BTN_Init(BTN_0);
        gQH_updateLED = xQueueCreate(1, sizeof(unsigned long));
        vTaskSuspend(NULL);
    }
}

/**
 * \function name:      S1_US3_getButton()
 * \IN:                 vptr
 * \OUT:                NONE
 * \return:             NONE
 * \Discription:        checks the button status and calculates the pressing time
 */
void S1_US3_getButton ( void *vptr)
{
    static uint16 su16_pressCount = 0;
    bool sb_justReleased = FALSE;
    bool b_pinStatus;
    for (;;)
    {
        BTN_GetStatus(BTN_0, &b_pinStatus);
        if (b_pinStatus == PRESSED)
        {
            /**< To avoid overflow */
            if (su16_pressCount < 4001)
            {
                su16_pressCount ++;
            }
            else
            {/**< Do nothing */}

            /**< Keep the flag always true until the button is released */
            sb_justReleased = TRUE;
        }
        else
        {
            if (sb_justReleased == TRUE)
            {
                xQueueReset(gQH_updateLED);
                xQueueOverwrite(gQH_updateLED, &su16_pressCount);
                sb_justReleased = FALSE;
            }
            su16_pressCount = 0;
        }
        vTaskDelay(1);
    }
}

/**
 * \function name:      S1_US3_updateLED()
 * \IN:                 vptr
 * \OUT:                NONE
 * \return:             NONE
 * \Discription:        Updates the toggling rate if needed
 */
void S1_US3_updateLED ( void *vptr)
{
    for(;;)
    {
        static uint16 su16_pressTime = 0;
        xQueueReceive(gQH_updateLED, (void *)&su16_pressTime, 0);
        if (su16_pressTime < 2000)
        {
            Led_Off(LED_0);
            vTaskDelay(1);
        }
        else if (su16_pressTime >= 2000 && su16_pressTime <4000)
        {
            Led_Toggle(LED_0);
            vTaskDelay(400);
        }
        else
            /**< More than 4 seconds */
        {
            Led_Toggle(LED_0);
            vTaskDelay(100);
        }
    }
}
/**
 * \function name:      S1_US3_MainFunction
 * \IN:                 vptr
 * \OUT:                NONE
 * \return:             NONE
 * \Discription:        Updates the toggling rate if needed
 */
void S1_US3_MainFunction (void)
{
    xTaskCreate(S1_US3_init, "Init", configMINIMAL_STACK_SIZE, (void *)0, 4, NULL);
    xTaskCreate(S1_US3_getButton, "Button",configMINIMAL_STACK_SIZE, (void *)0, 2, NULL );
    xTaskCreate(S1_US3_updateLED, "Led", configMINIMAL_STACK_SIZE, (void *)gQH_updateLED, 1, NULL);

    vTaskStartScheduler();

}

