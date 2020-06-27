/*
 * UART.c
 *
 *  Created on: Dec 28, 2019
 *      Author: Ghanem and Tamoh
 */
/************************************************************************/
/*		                        INCLUDES                 		        */
/************************************************************************/
#include "common_macros.h"
#include "interrupt.h"
#include "registers.h"
#include "UART.h"
#include "DIO.h"
/************************************************************************/
/*		                        DEFINES                 		        */
/************************************************************************/

#define GET_UBRR_VALUE(BAUD_RATE,SPEED) (((16000000UL / (BAUD_RATE * (16UL/(SPEED+1) ) ))) - 1)
#define TX_CBF                (0)
#define RX_CBF 	              (1)
#define UDRE_CBF 			  (2)
#define MAX_NUM_OF_INTERRUPTS (3)

#define PARITY_BITS_OFFSET 	   (4)
#define STOP_BITS_OFFSET  	   (3)
#define BITS_PER_FRAME_OFFSET  (1)
#define NUM_OF_BITS_MASK 0xFC
/************************************************************************/
/*		                          ISR                   		        */
/************************************************************************/

void (*gaptr_uartInterrupt_CBF[3])(void) = {NULL,NULL,NULL};

ISR(USART_TXC_vect)
{
	if(gaptr_uartInterrupt_CBF[TX_CBF] != NULL)
	{
		gaptr_uartInterrupt_CBF[TX_CBF]();
	}

}

ISR(USART_RXC_vect)
{
	if(gaptr_uartInterrupt_CBF[RX_CBF] != NULL)
	{
		gaptr_uartInterrupt_CBF[RX_CBF]();
	}
}

ISR(USART_UDRE_vect)
{
	if(gaptr_uartInterrupt_CBF[UDRE_CBF] != NULL)
	{
		gaptr_uartInterrupt_CBF[UDRE_CBF]();
	}
}

/************************************************************************/
/*		                 FUNCTIONS' IMPLMENTATION        		        */
/************************************************************************/

/**
 * \brief UART_Init :
 *
 * \param *pUART_cfg_s : A pointer to a struct that holds the desired UART configuration
 * \return ERROR_STATUS : Indication to the function execution
 *
 **/
ERROR_STATUS UART_Init(UART_cfg_s *pUART_cfg_s)
{
	/* Declaration of DIO configure structure for TX and RX */
	DIO_Cfg_s ST_txDio = {0};
	DIO_Cfg_s ST_rxDio = {0};
	uint8 u8_UCSRC_Buffer = UART_RSEL;
	switch(pUART_cfg_s->u8_DesiredOperation)
	{
		case TRANSMITTER:
			if(pUART_cfg_s->u8_InterruptMode)
			{
				/*Enable Interrupt if selected in cfg. structure*/
				SET_BIT(UART_CSRB,UART_TXCIE );
				/*assign the passed pointer to function to be called later in ISR*/
				gaptr_uartInterrupt_CBF[TX_CBF] = pUART_cfg_s->ptr_Transmit_CBK;
			}
			else
			{
				/*Polling selected in cfg. structure*/
				CLR_BIT(UART_CSRB,UART_TXCIE);
			}

			/* Enable the device to work as Transmitter*/
			SET_BIT(UART_CSRB,UART_TXEN);
			break;
		case RECEIVER:
						if(pUART_cfg_s->u8_InterruptMode)
			{
				/*Enable Interrupt if selected in cfg. structure*/
				SET_BIT(UART_CSRB,UART_RXCIE);
				/*assign the passed pointer to function to be called later in ISR*/
				gaptr_uartInterrupt_CBF[RX_CBF] = pUART_cfg_s->ptr_Resceive_CBK;
			}
			else
			{
				/*Polling selected in cfg. structure*/
				CLR_BIT(UART_CSRB,UART_RXCIE);
			}
			/* Enable the device to work as Receiver*/
			SET_BIT(UART_CSRB,UART_RXEN);
			break;
		case TRANSCEIVER:

			if(pUART_cfg_s->u8_InterruptMode)
			{
				/*Enable Interrupt if selected in cfg. structure*/
				SET_BIT(UART_CSRB,UART_TXCIE|UART_RXCIE);
				/*assign the passed pointer to function to be called later in ISR*/
				gaptr_uartInterrupt_CBF[RX_CBF] = pUART_cfg_s->ptr_Resceive_CBK;
				gaptr_uartInterrupt_CBF[TX_CBF] = pUART_cfg_s->ptr_Transmit_CBK;
			}
			else
			{
				/*Polling selected in cfg. structure*/
				CLR_BIT(UART_CSRB,UART_TXCIE|UART_RXCIE);
			}
			/* Enable the device to work as Receiver*/
			SET_BIT(UART_CSRB , UART_RXEN|UART_TXEN);
			break;

		default:
			return E_NOK;
	}

	/* U2X bit specify if UART work with double speed or not*/
	if(pUART_cfg_s->u8_DoubleSpeed == UART_DOUBLE_SPEED)
	{
		SET_BIT(UART_CSRA,UART_U2X);
	}
	else if (pUART_cfg_s->u8_DoubleSpeed == UART_NO_DOUBLE_SPEED)
	{
		CLR_BIT(UART_CSRA,UART_U2X);

	}
	else
	{
		return E_NOK;
	}
	/* Get Value to be set in UBBR register depending on baud-rate */
	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
	UART_BRRH = GET_UBRR_VALUE(pUART_cfg_s->u32_BaudRate,pUART_cfg_s->u8_DoubleSpeed)>>8;
	UART_BRRL = GET_UBRR_VALUE(pUART_cfg_s->u32_BaudRate,pUART_cfg_s->u8_DoubleSpeed);
	/*  StopBit   specify one or two bit
		ParityBit {even , odd , disable}
	    DataSize  {5,6,7,8,9 } */
	/*set value in UCSRC on buffer first because it share virtual address with UBRR*/
	u8_UCSRC_Buffer |= (pUART_cfg_s->u8_StopBit << STOP_BITS_OFFSET) | (pUART_cfg_s->u8_ParityBit<<PARITY_BITS_OFFSET);
	u8_UCSRC_Buffer |= ((NUM_OF_BITS_MASK & pUART_cfg_s->u8_DataSize)<<BITS_PER_FRAME_OFFSET);
	/* only at 9 bits frame the third bit should be set*/
	if(pUART_cfg_s->u8_DataSize == UART_9_BIT)
	{
		SET_BIT(UART_CSRB,UART_CSZ2);
	}
	else
	{
		CLR_BIT(UART_CSRB,UART_CSZ2);
	}

	/*Check if interrupt in Empty UDR register CBF is assigned to function address*/
	if(pUART_cfg_s->ptr_DataRegEmpty_CBk != NULL)
	{
		SET_BIT(UART_CSRB,UART_DRIE);
		gaptr_uartInterrupt_CBF[UDRE_CBF] = pUART_cfg_s->ptr_DataRegEmpty_CBk;
	}
	else
	{

	}
	/*DIO initialization*/
	/*TX pin -> O/P  */
	ST_txDio.pins = UART_TX_BIT;
	ST_txDio.GPIO = UART_TX_GPIO;
	ST_txDio.dir = OUTPUT;
	DIO_init(&ST_txDio);

	/*RX pin <- I/P*/
	ST_rxDio.pins = UART_RX_BIT;
	ST_rxDio.GPIO = UART_RX_GPIO;
	ST_rxDio.dir  = INPUT;
	DIO_init(&ST_rxDio);

return E_OK;

}

/**
 * \brief UART_Deinit : Deinitialize the UART module
 *
 * \param void
 * \return ERROR_STATUS : Indication to the function execution
 *
 **/
ERROR_STATUS UART_Deinit(void)
{
	/* Clear all the registers */
	UART_CSRA = LOW;
	UART_CSRB = LOW;
	UART_CSRC &= (UART_RSEL);	/*clear all bits unless URSEL to access the register*/
	UART_BRRH = LOW;
	UART_BRRL = LOW;
	UART_DR = LOW;
	gaptr_uartInterrupt_CBF[TX_CBF] = NULL;
	gaptr_uartInterrupt_CBF[RX_CBF] = NULL;
	gaptr_uartInterrupt_CBF[UDRE_CBF] = NULL;
	return E_OK;
}

/**
 * \brief  UART_SendByte : Sends a certain byte
 *
 * \param u8_Data : The byte the user wants to send
 * \return ERROR_STATUS : Indication to the function execution
 *
 **/
ERROR_STATUS UART_SendByte(uint8 u8_Data)
{
	if(gaptr_uartInterrupt_CBF[TX_CBF] == NULL)
	{
		/*	poll on the UDR register empty flag
		 *  wait until it available to write data on it */
		while(!GET_BIT(UART_CSRA,UART_DRE)){}

	}
	else
	{
		/* send function would be called at ISR of UDR it self*/
	}

	UART_DR = u8_Data;
	return E_OK;
}

/**
 * \brief  UART_ReceiveByte : Receives a certain byte
 *
 * \param pu8_ReceivedData : The sent byte will be stored in the passed pointer
 * \return ERROR_STATUS : Indication to the function execution
 *
 **/
ERROR_STATUS UART_ReceiveByte(uint8 *pu8_ReceivedData)
{
	if(gaptr_uartInterrupt_CBF[RX_CBF] == NULL)
	{
		/*	poll on the UDR register receive flag -> receive complete
		 *  wait until it available to read data from it */
		while(!GET_BIT(UART_CSRA,UART_RXC)){}

	}
	else
	{
		/* received function would be called at RX interrupt*/
	}
	*pu8_ReceivedData = UART_DR;
	return E_OK;
}
