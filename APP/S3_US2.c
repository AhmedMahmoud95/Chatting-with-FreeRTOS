/************************************************************************/
/*	       	                   Includes                                 */
/************************************************************************/
#include "S3_US2.h"

/************************************************************************/
/*                          Global variables                            */
/************************************************************************/
QueueHandle_t GQ_keypadCh, GQ_SendToISR, GQ_ReceiveFromUart,  GQ_BTN;
xTaskHandle GH_UART, GH_LED_0, GH_LED_1, GH_UART_R, GH_KEYPAD;

typedef char LCD_Buffer[17];

typedef enum en_sendToUartStates
{
    RECEIVING_FROM_KEYPAD,
    SENDING_DATA
} en_sendToUartStates;



/************************************************************************/
/*                          Callback functions                          */
/************************************************************************/
void cbk_SendUART ()
{
    static uint8 su8_counter = 0;
    static LCD_Buffer s_Buffer;
    sint8 s8_currentChar;

    /**< Checks if there is new data to be sent */
    xQueueReceiveFromISR(GQ_SendToISR, s_Buffer, NULL);
    s8_currentChar = s_Buffer[su8_counter++];
    if ( s8_currentChar == '\0')
    {
        su8_counter = 0;
        vTaskResume(GH_UART);
    }
    else
    {
        UART_SendByte(s_Buffer[su8_counter]);
    }
}

void cbk_receiveUart()
{
    static uint8 su8_counter = 0;
    static LCD_Buffer s_Buffer;
    uint8 u8_currentChar;
    UART_ReceiveByte( &u8_currentChar);
    s_Buffer[su8_counter++] = u8_currentChar;
    if ( u8_currentChar == '\0')
    {
        xQueueOverwriteFromISR(GQ_ReceiveFromUart, s_Buffer, NULL);
        su8_counter = 0;
        vTaskResume(GH_UART_R);
    }

}
/************************************************************************/
/*                          Functions definition                        */
/************************************************************************/

/**
 * \function name:      S3_US2_init()
 * \IN:                 vptr
 * \OUT:                NONE
 * \return:             NONE
 * \Discription:        Initiates the push button, the LED, the LCD, and the UART
 */
void S3_US2_init ( void *vptr)
{
    for (;;)
    {
        LCD_init();
        Led_Init(LED_0);
        Led_Init(LED_1);
        keypad_init();
        BTN_Init(BTN_1);
        UART_cfg_s strUartObject = {UART_INTERRUPT,
                                    TRANSCEIVER,
                                    UART_NO_DOUBLE_SPEED,
                                    UART_ONE_STOP_BIT,
                                    UART_NO_PARITY,
                                    UART_8_BIT,
                                    9600,
                                    cbk_SendUART,
                                    cbk_receiveUart,
                                    NULL
                                   };
        UART_Init( &strUartObject);

        GQ_keypadCh = xQueueCreate( 1, sizeof(uint8));

        /**< This queue holds the full msg to be sent through UART */
        GQ_SendToISR = xQueueCreate(1, sizeof(LCD_Buffer));
        GQ_ReceiveFromUart = xQueueCreate(1, sizeof(LCD_Buffer));
        GQ_BTN = xQueueCreate(1, sizeof(uint8));

        /**< Stop leds until a msg is received or sent */
        vTaskSuspend(GH_LED_0);
        vTaskSuspend(GH_LED_1);
        vTaskSuspend(GH_UART_R);

        /**< Call initialization once */
        vTaskSuspend(NULL);
    }
}

/**
 * \function name:      S3_US2_getKeypad()
 * \IN:                 vptr
 * \OUT:                NONE
 * \return:             NONE
 * \Discription:        get pressed button from keypad and send them to sendToUArt
 */
void S3_US2_getKeypad ( void *vptr)
{
    for (;;)
    {
        uint8 u8_pressedKey;
        keypad_getPressedKey(&u8_pressedKey);
        if (u8_pressedKey != NO_KEY_PRESSED)
        {
            xQueueOverwrite(GQ_keypadCh, &u8_pressedKey);
        }
        /**< Wait 100ms after each character reading to prevent reading */
        /**< the same press twice */
        vTaskDelay( 150 / portTICK_PERIOD_MS);
    }
}

/**
 * \function name:      S3_US2_getButton()
 * \IN:                 vptr
 * \OUT:                NONE
 * \return:             NONE
 * \Discription:        Checks the button status and send notification to sendToUART
 */
void S3_US2_getButton ( void *vptr)
{
    for (;;)
    {

        bool b_buttonState;
        BTN_GetStatus(BTN_1, &b_buttonState);
        if (b_buttonState == PRESSED)
        {
            xQueueOverwrite(GQ_BTN, &b_buttonState);

            /**< Wait for data sending */
            vTaskDelay( 200 / portTICK_PERIOD_MS);
        }
        else
        {
            vTaskDelay( 5 / portTICK_PERIOD_MS);
        }
    }
}

/**
 * \function name:      S3_US2_sendToUart()
 * \IN:                 vptr
 * \OUT:                NONE
 * \return:             NONE
 * \Discription:        Gets the msg char by char and sends it, then initiates LCD & LED
 */
void S3_US2_sendToUart ( void *vptr)
{
    for (;;)
    {
        static en_sendToUartStates en_funState = RECEIVING_FROM_KEYPAD;
        static LCD_Buffer str_DataToSend = {'\0'};
        static uint8 u8_chCounter = 0;
        uint8 u8_tempBuffer = 0;

        switch (en_funState)
        {
        case RECEIVING_FROM_KEYPAD:
            if (xQueueReceive(GQ_keypadCh, &u8_tempBuffer, 0 ) == pdTRUE)
            {
                /**< Check for overflow */
                /**< Max line size for the LCD */
                if (u8_chCounter >= 16)
                {
                    u8_chCounter --;
                }
                LCD_gotoRowColumn(u8_chCounter, 0);
                LCD_displayCharacter(u8_tempBuffer);
                str_DataToSend[u8_chCounter++] = u8_tempBuffer;
            }
            else
            {
                /**< Do nothing */
            }
            if (xQueueReceive(GQ_BTN, &u8_tempBuffer, 0) == pdTRUE)
            {
                /**< Now, we have the msg and the button is pressed  */
                str_DataToSend[u8_chCounter] = '\0';
                en_funState = SENDING_DATA;
            }
            else
            {
                vTaskDelay( 10 / portTICK_PERIOD_MS);
            }
            break;
        case SENDING_DATA:

            xQueueOverwrite(GQ_SendToISR, str_DataToSend);
            UART_SendByte(str_DataToSend[0]);
            vTaskResume(GH_LED_0);
            /**< Wait until data is sent */
            /**< Prevent extra data to be displayed after data is submitted */
            /**< If not suspended, data cannot  */
            vTaskSuspend(NULL);
            vTaskSuspend(GH_KEYPAD);
            vTaskDelay(2000 / portTICK_PERIOD_MS);
            LCD_sendString_RowCol(0, 0, (sint8*)"                ");
            u8_chCounter = 0;
            en_funState = RECEIVING_FROM_KEYPAD;

        }
    }
}

/**
 * \function name:      S3_US2_updateLED0()
 * \IN:                 vptr
 * \OUT:                NONE
 * \return:             NONE
 * \Discription:        Updates the sending led status
 */
void S3_US2_updateLED0 ( void *vptr)
{
    for (;;)
    {

        Led_On(LED_0);
        vTaskDelay(200 / portTICK_PERIOD_MS );
        Led_Off(LED_0);
        vTaskResume(GH_KEYPAD);
        /**< SendToUart will resume it again when new data is sent */
        vTaskSuspend(NULL);
    }
}

/**
 * \function name:      S3_US2_updateLED1()
 * \IN:                 vptr
 * \OUT:                NONE
 * \return:             NONE
 * \Discription:        Updates the receiving led status
 */
void S3_US2_updateLED1 ( void *vptr)
{
    for (;;)
    {

        Led_On(LED_1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        Led_Off(LED_1);
        vTaskResume(GH_UART);
        /**< ReceiveFromUArt will resume it again when new data is received */
        vTaskSuspend(NULL);
    }
}

void UART_Recieve_task( void * pvParameters )
{
    LCD_Buffer Receive_string;
    for( ;; )
    {
        if (xQueueReceive(GQ_ReceiveFromUart,Receive_string, 0) ==pdTRUE)
        {
            /*led task*/
            vTaskResume(GH_LED_1);
            /*lcd_goto(1, 0)    */
            /*LCD _send string*/
            LCD_sendString_RowCol(0, 1, (sint8*)Receive_string);
            vTaskDelay(2000 / portTICK_PERIOD_MS);
            /**< Spaces with the size of the line to clear it without affecting upper line */
            LCD_sendString_RowCol(0, 1, (sint8*)"               ");
            vTaskSuspend(NULL);
        }
    }
}

/**
 * \function name:      S3_US2_MainFunction
 * \IN:                 vptr
 * \OUT:                NONE
 * \return:             NONE
 * \Discription:        Runs the full system
 */
void S3_US2_MainFunction (void)
{
    xTaskCreate(S3_US2_init, "Init", configMINIMAL_STACK_SIZE, NULL, 10, NULL);
    xTaskCreate(S3_US2_sendToUart, "UART_S", configMINIMAL_STACK_SIZE, NULL, 2, &GH_UART);
    xTaskCreate(S3_US2_updateLED0, "LED_0", configMINIMAL_STACK_SIZE, NULL, 4, &GH_LED_0);
    xTaskCreate(S3_US2_updateLED1, "LED_1", configMINIMAL_STACK_SIZE, NULL, 4, &GH_LED_1);
    xTaskCreate(UART_Recieve_task, "UART_R", configMINIMAL_STACK_SIZE, NULL, 5, &GH_UART_R);
    xTaskCreate(S3_US2_getButton, "BTN", configMINIMAL_STACK_SIZE, NULL, 7, NULL);
    xTaskCreate(S3_US2_getKeypad, "keypad", configMINIMAL_STACK_SIZE, NULL, 1, &GH_KEYPAD);
    vTaskStartScheduler();
}
