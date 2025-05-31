/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Mai El Shahed
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include <string.h>

#include "Stm32F446xx.h"
#include "NVIC_interface.h"
#include "USART_interface.h"
#include "DMA_interface.h"
#include "RCC_interface.h"
#include "errtype.h"
#include "GPIO_interface.h"
#include "SysTick_interface.h"



#define RX_BUFFER_SIZE 64
char rx_buffer[RX_BUFFER_SIZE];

int main(void)
{



	char msg[] = "Hello from Nucleo-F446RE USART2!\r\nSend '1' to turn LED ON, '0' to turn LED OFF.\r\n";


	 RCC_SETCLK(HSI,RCC_ON);
	    RCC_SETSYSCLK(SW_HSI);  /* Switch system clock to PLL*/
	    SystemCoreClockUpdate();   /* Update core clock variable*/
	 	SysTick_Init(ProcessorAHB); /* Initialize SysTick with new frequency*/

		RCC_AHB1_enable(GPIOAEN);   /* Enable GPIOA لـ USART2*/
		RCC_AHB1_enable(DMA1EN);      /* DMA1 for USART2 */
		RCC_APB1_enable(USART2EN);  /*     USART2*/


		    pin_configer_t USART2_PA2_TX={
		    .port=PORTA,
		    .pinNum=2,
		    .mode=ALTERNATE_FUNCTION,
			.altfunc=AF7,   //USART2---> AF7
		    .speed=LOW,
		    .outputtype=PUSH_PULL,
		    .pulltype=NOPULL
		    };

		    GPIO_u8pininit(&USART2_PA2_TX);

		    pin_configer_t LED_PA5={
		 		    .port=PORTA,
		 		    .pinNum=5,
		 		    .mode=OUTPUT,

		 		    .speed=LOW,
		 		    .outputtype=PUSH_PULL,
		 		    .pulltype=NOPULL
		 		    };

		 		   GPIO_u8pininit(&LED_PA5);


		    pin_configer_t USART2_PA3_RX={
		    .port=PORTA,
		    .pinNum=3,
			 .mode=ALTERNATE_FUNCTION,
			.altfunc=AF7,
		    .pulltype=PULLUP
		    };

		    GPIO_u8pininit(&USART2_PA3_RX);


		    USART_Init(USART2, 9600, 16000000, 16);
		  // USART_ConfigMode(USART2, TX_ONLY);
		    USART_ConfigMode(USART2, RX_TX);
		   USART_SendString(USART2, msg);



  			USART_SendString(USART2, "Testing TX UART2 RX DMA\r\n");


  			char rx_buffer[64];

  			// DMA Config
  			DMA_Config_t usart2_rx_dma = {
  			    .streamID = DMA1_STREAM5,
  			    .stream = &MY_DMA1->DMA_Stream[5],
  			    .channel = DMA_CHANNEL_4,
  			    .periphAddr = (uint32_t)&USART2->DR,
  			    .memAddr = (uint32_t)rx_buffer,
  			    .dataLength = 64,
  			    .direction = DMA_DIR_PERIPH_TO_MEM,
  			    .priority = DMA_PRIORITY_MEDIUM,
  			    .msize = DMA_DATA_SIZE_8BIT,
  			    .psize = DMA_DATA_SIZE_8BIT,
  			    .enableDoubleBuffer = 0,
  			    .fifoEnable = DMA_FIFO_DISABLE,
  			    .mode = DMA_MODE_CIRCULAR



  			};

  			DMA_Init(&usart2_rx_dma);


  			DMA_EnableStream(DMA1_STREAM5);
  			// Enable USART2 DMA receiver
  			//USART2->CR3 |= (1 <<  DMAR);
  			USART_DMA_StartRx(USART2);



  			int old_pos = 0;

  			while (1)
  			{
  			    int current_pos = RX_BUFFER_SIZE - MY_DMA1->DMA_Stream[5].NDTR;

  			    if (current_pos != old_pos)
  			    {
  			        for (int i = old_pos; i != current_pos; i = (i + 1) % RX_BUFFER_SIZE)
  			        {
  			            char received = rx_buffer[i];

  			            if (received == '1') {
  			                GPIO_u8setpinvalue(PORTA, PIN5, PIN_HIGH);
  			                USART_SendString(USART2, "LED ON\r\n");
  			            } else if (received == '0') {
  			                GPIO_u8setpinvalue(PORTA, PIN5, PIN_LOW);
  			                USART_SendString(USART2, "LED OFF\r\n");
  			            }
  			        }

  			        old_pos = current_pos;
  			    }
  			}






}






