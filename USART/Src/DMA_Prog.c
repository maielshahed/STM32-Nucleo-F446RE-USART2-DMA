/*
 * DMA_Prog.c
 *
 *  Created on: May 21, 2025
 *      Author: Mai El Shahed
 */

#include <stdint.h>

#include "Stm32F446xx.h"
#include "DMA_interface.h"
#include "errtype.h"







/**
 * @brief  Enables the interrupt for the specified DMA stream using NVIC registers.
 * @param  streamID: The DMA stream identifier (DMA1_STREAM0 to DMA2_STREAM7).
 * @retval None
 */







void DMA_Init(DMA_Config_t* config) {
    // Enable clock
    if (config->streamID < DMA2_STREAM0)
        RCC->AHB1ENR |= (1 << 21); // DMA1EN
    else
        RCC->AHB1ENR |= (1 << 22); // DMA2EN

    // Disable stream
    config->stream->CR &= ~DMA_EN;
    while (config->stream->CR & DMA_EN);

    // Set addresses
    config->stream->PAR  = config->periphAddr;
    config->stream->M0AR = config->memAddr;
    config->stream->NDTR = config->dataLength;

    if (config->enableDoubleBuffer) {
        config->stream->M1AR = config->mem1Addr;
        config->stream->CR |= (1 << 18); // DBM
    }

    // FIFO config
    if (config->fifoEnable == DMA_FIFO_ENABLE) {
        config->stream->FCR = (1 << 2) | config->fifoThreshold;
    } else {
        config->stream->FCR = 0;
    }


    // Mode bits
    uint32_t mode_bits = (config->mode == DMA_MODE_CIRCULAR) ? DMA_CIRC_ENABLE : 0;

    // Clear old channel bits first, then set channel
    config->stream->CR &= ~(0x7 << 25);
    config->stream->CR |= config->channel;

    // Final CR config
    config->stream->CR |=
        config->direction |
        (config->msize << 13) |
        (config->psize << 11) |
        config->priority |
        DMA_MINC_ENABLE |
        DMA_TCIE_ENABLE |
        mode_bits;

    // Enable interrupt
    Enable_DMA_IRQ(config->streamID);

    // Enable stream
    config->stream->CR |= DMA_EN;
}









void DMA_START(DMA_Config_t *config)
{
    if (config == NULL || config->stream == NULL) return;
    config->stream->CR &= ~(1U << 0);
    while (config->stream->CR & (1U << 0)) {}
    config->stream->CR = (config->channel | config->direction | config->priority |
                          (config->msize << 13) | (config->psize << 11) |
                          (config->mode << 8) | (config->enableDoubleBuffer << 18) |
                          (config->fifoEnable << 2));
    if (config->fifoEnable == DMA_FIFO_ENABLE)
    {
        config->stream->FCR = (config->fifoThreshold | (1U << 2));
    }
    else
    {
        config->stream->FCR = 0;
    }
    config->stream->PAR = config->periphAddr;
    config->stream->M0AR = config->memAddr;
    config->stream->M1AR = config->mem1Addr;
    config->stream->NDTR = config->dataLength;
    config->stream->CR |= (1U << 0);
}

/**
 * @brief  Performs a DMA transfer using the provided configuration structure.
 * @param  config: Pointer to DMA configuration structure.
 * @retval None
 */
void DMA_TRANSFER(DMA_Config_t *config)
{
    if (config == NULL || config->stream == NULL || config->dataLength == 0) return; /* Basic error checking */

    /* Disable the stream before configuration */
    config->stream->CR &= ~(1U << 0); /* Clear EN bit */
    while (config->stream->CR & (1U << 0)) {} /* Wait until stream is disabled */

    /* Configure DMA stream registers */
    config->stream->CR = (config->channel | config->direction | config->priority |
                         (config->msize << 13) | (config->psize << 11) |
                         (config->mode << 8) | (config->enableDoubleBuffer << 18) |
                         (config->fifoEnable << 2));

    /* Configure FIFO if enabled */
    if (config->fifoEnable == DMA_FIFO_ENABLE)
    {
        config->stream->FCR = (config->fifoThreshold | (1U << 2)); /* Enable FIFO */
    }
    else
    {
        config->stream->FCR = 0; /* Disable FIFO */
    }

    /* Set peripheral, memory addresses, and data length */
    config->stream->PAR = config->periphAddr;
    config->stream->M0AR = config->memAddr;
    config->stream->M1AR = config->mem1Addr; /* Used in double buffer mode */
    config->stream->NDTR = config->dataLength;

    /* Enable the DMA stream */
    config->stream->CR |= (1U << 0);
}

/**
 * @brief  Clears the status flags for a DMA stream.
 * @param  streamID: The DMA stream identifier (DMA1_STREAM0 to DMA2_STREAM7).
 * @retval None
 */
void DMA_CLEARFLAGS(DMA_StreamID_t streamID)
{
    /* Base addresses for DMA1 and DMA2 */
    static const uint32_t DMA_BASE[] = {0x40026000, 0x40026400};
    volatile uint32_t *clearReg = (streamID < 4) ? (uint32_t *)(DMA_BASE[streamID / 8] + 0x04) : /* LIFCR */
                                          (uint32_t *)(DMA_BASE[streamID / 8] + 0x0C); /* HIFCR */
    uint32_t offset = (streamID % 4) * 6;

    /* Clear FEIF, TEIF, TCIF flags by writing 1 */
    *clearReg |= (1U << (offset + 5)) | /* CFEIF */
                 (1U << (offset + 3)) | /* CTEIF */
                 (1U << (offset + 1));  /* CTCIF */
}

void DMA_START_IT(DMA_Config_t *config)
{
    if (config == NULL || config->stream == NULL) return;
    config->stream->CR &= ~(1U << 0);
    while (config->stream->CR & (1U << 0)) {}
    config->stream->CR = (config->channel | config->direction | config->priority |
                          (config->msize << 13) | (config->psize << 11) |
                          (config->mode << 8) | (config->enableDoubleBuffer << 18) |
                          (config->fifoEnable << 2));
    if (config->fifoEnable == DMA_FIFO_ENABLE)
    {
        config->stream->FCR = (config->fifoThreshold | (1U << 2));
    }
    else
    {
        config->stream->FCR = 0;
    }
    config->stream->PAR = config->periphAddr;
    config->stream->M0AR = config->memAddr;
    config->stream->M1AR = config->mem1Addr;
    config->stream->NDTR = config->dataLength;
    config->stream->CR |= (1U << 4) | (1U << 2);
    config->stream->FCR |= (1U << 7);
    Enable_DMA_IRQ(config->streamID);
    config->stream->CR |= (1U << 0);
}

uint32_t DMA_GETSTATUS(DMA_StreamID_t streamID)
{
    static const uint32_t DMA_BASE[] = {0x40026000, 0x40026400};
    volatile uint32_t *statusReg = (streamID < 4) ? (uint32_t *)(DMA_BASE[streamID / 8] + 0x08) : (uint32_t *)(DMA_BASE[streamID / 8] + 0x0C);
    uint32_t offset = (streamID % 4) * 6;
    uint32_t status = 0;
    if (*statusReg & (1U << (offset + 5))) status |= (1U << 0); /* FEIF */
    if (*statusReg & (1U << (offset + 3))) status |= (1U << 1); /* TEIF */
    if (*statusReg & (1U << (offset + 1))) status |= (1U << 2); /* TCIF */
    return status;
}






void Enable_DMA_IRQ(DMA_StreamID_t streamID)
{
    /* DMA IRQn numbers for STM32F446xx (based on vector table in reference manual) */
    static const uint8_t DMA_IRQn[] = {
        11, 12, 13, 14, 15, 16, 17, 47, /* DMA1 Stream 0 to 7 */
        56, 57, 58, 59, 60, 68, 69, 70  /* DMA2 Stream 0 to 7 */
    };

    /* Check if streamID is valid */
    if (streamID >= DMA1_STREAM0 && streamID <= DMA2_STREAM7)
    {
        /* Calculate the ISER register index (each ISER handles 32 interrupts) */
        uint32_t reg_index = DMA_IRQn[streamID] / 32;
        uint32_t bit_offset = DMA_IRQn[streamID] % 32;

        /* Set the corresponding bit in ISER to enable the interrupt */
        NVIC->ISER[reg_index] |= (1U << bit_offset);
    }
    /* Optional: Handle invalid streamID */
    /* else {
        // Error handling (e.g., assert or debug print)
    } */
}



volatile DMA_Stream_RegDef_t* DMA_GetStreamPtr(DMA_StreamID_t id) {
    if (id <= DMA1_STREAM7) {
        return &(MY_DMA1->DMA_Stream[id]);
    } else if (id <= DMA2_STREAM7) {
        return &(MY_DMA2->DMA_Stream[id - DMA2_STREAM0]);
    } else {
        return NULL;
    }
}



void DMA_EnableStream(DMA_StreamID_t streamID)
{
    DMA_RegDef *DMAx;
    uint8_t stream_number;

    if (streamID <= DMA1_STREAM7) {
        DMAx = MY_DMA1;
        stream_number = streamID;
    } else {
        DMAx = MY_DMA2;
        stream_number = streamID - DMA2_STREAM0;
    }

    // Clear interrupt flags (you can adjust the mask)
    DMAx->HIFCR = 0x3D << ((stream_number % 4) * 6);

    // Enable the stream
    DMAx->DMA_Stream[stream_number].CR |= (1 << 0); // Bit 0 = EN
}


// (Optional) Wait for transfer to complete

void USART_DMA_WaitTxComplete(void)
{
    while (!(MY_DMA1->HISR & DMA_HISR_TCIF6));
    MY_DMA1->HIFCR |= DMA_HIFCR_CTCIF6;
}
