/*
 * USART_Prog.c
 *
 *  Created on: May 26, 2025
 *      Author: Mai El Shahed
 */


#include <stdint.h>


#include "Stm32F446xx.h"
#include "NVIC_interface.h"
#include "USART_interface.h"





/*  USART_ConfigMode(USART1, RX_TX);    */


void USART_ConfigMode(USART_RegDef_t *USARTx, USART_Mode mode)
{
    // RE و TE
    USARTx->CR1 &= ~((1 << RE) | (1 << TE));

    switch (mode)
    {
        case RX_ONLY:
            USARTx->CR1 |= (1 << RE);
            break;
        case TX_ONLY:
            USARTx->CR1 |= (1 << TE);
            break;
        case RX_TX:
            USARTx->CR1 |= (1 << RE) | (1 << TE);
            break;
    }
}

void USART_DMA_StartTx(USART_RegDef_t *USARTx)
{

    USARTx->CR3 |= (1 <<  DMAT);             //DMAT: DMA Transmit (bit 7)

}

void USART_DMA_StartRx(USART_RegDef_t *USARTx)
{
    USARTx->CR3 |= (1 <<  DMAR);             //  DMAR: DMA Receive (bit 6)
}



/*USART_Init(USART1, 9600, 16000000, 16); //  USART1 ---9600--------- MHz16    oversampling    8&16*/


void USART_Init(USART_RegDef_t *USARTx, uint32_t baud_rate, uint32_t PCLKx, uint8_t over)
{
    // ـ oversampling (8-----أ16)
    if (over == 8)
    {
        USARTx->CR1 |= (1 << OVER8);  // oversampling 8
    }
    else
    {
        USARTx->CR1 &= ~(1 << OVER8); // oversampling  16
        over = 16;
    }

    // USARTDIV
    // over = 8 => divisor = PCLKx / (8 * baud_rate)
    // over = 16 => divisor = PCLKx / (16 * baud_rate)
    uint32_t usartdiv_multiplied = (PCLKx * 100) / (baud_rate * over);  // *100
    uint32_t mantissa = usartdiv_multiplied / 100;
    uint32_t fraction = (((usartdiv_multiplied - (mantissa * 100)) * over + 50) / 100);

    // fraction :
    if (fraction > (over - 1))
    {
        fraction = 0;
        mantissa += 1;
    }

    // BRR
    USARTx->BRR = (mantissa << 4) | (fraction & 0x0F);

    // USART
    USARTx->CR1 |= (1 << UE);


}



/**/

void USART_SendChar(USART_RegDef_t *USARTx, uint8_t data)
{
// Wait until the send register is empty (TXE = 1)
 while (!(USARTx->SR & (1 << TXE))); // TXE bit

 USARTx->DR = data; // Send data

// Wait until the send is complete (TC = 1)
 while (!(USARTx->SR & (1 << TC))); // TC bit
}


uint8_t USART_ReceiveChar(USART_RegDef_t *USARTx)
{
// Wait for data to arrive (RXNE = 1)
while (!(USARTx->SR & (1 << RXNE))); // RXNE bit

return (uint8_t)(USARTx->DR & 0xFF); // Read the received data
}


void USART_SendString(USART_RegDef_t *USARTx, const char *str)
{
    while (*str)
    {
        USART_SendChar(USARTx, (uint8_t)*str);
        str++;
    }
}
void USART1_IRQHandler(void)
{
    // Read data register not empty  RXNE
    if (USART1->SR & (1 << RXNE))  // RXNE
    {
        uint8_t received = USART1->DR & 0xFF;

        //resend the letter directly (echo)
        USART1->DR = received;
    }

    // End transmission (optional)
    if (USART1->SR & (1 << TC)) // TC
    {
    // Transmission can be stopped or the application notified
    USART1->SR &= ~(1 << TC); // Clear the flag by reading SR then DR
    }
}



uint8_t USART_GetFlagStatus(USART_RegDef_t *USARTx, USART_SR Flag)
{
    if ((USARTx->SR & Flag) != 0)
    {
        return 1; // Flag is set
    }
    else
    {
        return 0; // Flag is not set
    }
}

/*
 * USART1->CR1 |= (1 << RXNEIE); // تفعيل مقاطعة الاستقبال
NVIC_EnableIRQ(USART1_IRQn); // إذا كنت تستخدم CMSIS
 *
 *
 *
 *
 *
 *
 *
  USART_Init(USART1, 9600, 16000000, 16);
USART_ConfigMode(USART1, RX_TX);

USART_SendString(USART1, "Hello STM32!\r\n");

uint8_t received = USART_ReceiveChar(USART1);
USART_SendChar(USART1, received); // إعادة إرسال الحرف المستلم
 *
 *
 *
 * */











