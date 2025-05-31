/*
 * DMA_interface.h
 *
 *  Created on: May 21, 2025
 *      Author: Mai El Shahed
 */

#ifndef DMA_INTERFACE_H_
#define DMA_INTERFACE_H_



#include "Stm32F446xx.h"




/**************************Data trend****************************************************/
typedef enum {
    DMA_DIR_PERIPH_TO_MEM = (0x0 << 6),
    DMA_DIR_MEM_TO_PERIPH = (0x1 << 6),
    DMA_DIR_MEM_TO_MEM    = (0x2 << 6)
} DMA_Direction_t;



/********************DMA Priority********************************************************/


typedef enum {
    DMA_PRIORITY_LOW       = (0x0 << 16),
    DMA_PRIORITY_MEDIUM    = (0x1 << 16),
    DMA_PRIORITY_HIGH      = (0x2 << 16),
    DMA_PRIORITY_VERY_HIGH = (0x3 << 16)
} DMA_Priority_t;


/********************DMA Data Size********************************************************/
typedef enum {
    DMA_DATA_SIZE_8BIT  = 0x0,
    DMA_DATA_SIZE_16BIT = 0x1,
    DMA_DATA_SIZE_32BIT = 0x2
} DMA_DataSize_t;

/**********************FIFO settings: enable/disable + threshold level*********************************************************/

typedef enum {
    DMA_FIFO_DISABLE = 0,
    DMA_FIFO_ENABLE  = 1
} DMA_FIFOState_t;

typedef enum {
    DMA_FIFO_THRESHOLD_1_4 = (0x0 << 0),
    DMA_FIFO_THRESHOLD_1_2 = (0x1 << 0),
    DMA_FIFO_THRESHOLD_3_4 = (0x2 << 0),
    DMA_FIFO_THRESHOLD_FULL = (0x3 << 0)
} DMA_FIFOThreshold_t;


/**************************DMA Peripheral Stream*************************************************/
typedef enum {
    DMA1_STREAM0 = 0,
    DMA1_STREAM1,
    DMA1_STREAM2,
    DMA1_STREAM3,
    DMA1_STREAM4,
    DMA1_STREAM5,
    DMA1_STREAM6,
    DMA1_STREAM7,
    DMA2_STREAM0,
    DMA2_STREAM1,
    DMA2_STREAM2,
    DMA2_STREAM3,
    DMA2_STREAM4,
    DMA2_STREAM5,
    DMA2_STREAM6,
    DMA2_STREAM7
}DMA_StreamID_t;


/*********************Mood************************************************/
typedef enum {
    DMA_MODE_NORMAL = 0,
    DMA_MODE_CIRCULAR = 1
} DMA_Mode_t;




/**********************  DMA_CHANNEL************************************/

typedef enum {
    DMA_CHANNEL_0 = 0x0 << 25,
    DMA_CHANNEL_1 = 0x1 << 25,
    DMA_CHANNEL_2 = 0x2 << 25,
    DMA_CHANNEL_3 = 0x3 << 25,
    DMA_CHANNEL_4 = 0x4 << 25,
    DMA_CHANNEL_5 = 0x5 << 25,
    DMA_CHANNEL_6 = 0x6 << 25,
    DMA_CHANNEL_7 = 0x7 << 25
} DMA_Channel_t;




#define DMA_EN                (1U << 0)   // Enable bit -- CR
#define DMA_MINC_ENABLE       (1U << 10)  // Memory increment enable
#define DMA_TCIE_ENABLE       (1U << 4)   // Transfer complete interrupt enable
#define DMA_CIRC_ENABLE       (1U << 8)   // Circular mode enable

#define DMA_FIFO_ENABLE       1
#define DMA_FIFO_DISABLE      0

#define DMA_FIFO_THRESHOLD_FULL     (3U << 0) // Full FIFO threshold (مثلاً 0x3)







// ==============================
// DMA Low Interrupt Status Flags (LISR) – Streams 0 to 3
// ==============================
#define DMA_LISR_FEIF0    (1U << 0)
#define DMA_LISR_DMEIF0   (1U << 2)
#define DMA_LISR_TEIF0    (1U << 3)
#define DMA_LISR_HTIF0    (1U << 4)
#define DMA_LISR_TCIF0    (1U << 5)

#define DMA_LISR_FEIF1    (1U << 6)
#define DMA_LISR_DMEIF1   (1U << 8)
#define DMA_LISR_TEIF1    (1U << 9)
#define DMA_LISR_HTIF1    (1U << 10)
#define DMA_LISR_TCIF1    (1U << 11)

#define DMA_LISR_FEIF2    (1U << 16)
#define DMA_LISR_DMEIF2   (1U << 18)
#define DMA_LISR_TEIF2    (1U << 19)
#define DMA_LISR_HTIF2    (1U << 20)
#define DMA_LISR_TCIF2    (1U << 21)

#define DMA_LISR_FEIF3    (1U << 22)
#define DMA_LISR_DMEIF3   (1U << 24)
#define DMA_LISR_TEIF3    (1U << 25)
#define DMA_LISR_HTIF3    (1U << 26)
#define DMA_LISR_TCIF3    (1U << 27)


// ==============================
// DMA High Interrupt Status Flags (HISR) – Streams 4 to 7
// ==============================
#define DMA_HISR_FEIF4    (1U << 0)
#define DMA_HISR_DMEIF4   (1U << 2)
#define DMA_HISR_TEIF4    (1U << 3)
#define DMA_HISR_HTIF4    (1U << 4)
#define DMA_HISR_TCIF4    (1U << 5)

#define DMA_HISR_FEIF5    (1U << 6)
#define DMA_HISR_DMEIF5   (1U << 8)
#define DMA_HISR_TEIF5    (1U << 9)
#define DMA_HISR_HTIF5    (1U << 10)
#define DMA_HISR_TCIF5    (1U << 11)

#define DMA_HISR_FEIF6    (1U << 16)
#define DMA_HISR_DMEIF6   (1U << 18)
#define DMA_HISR_TEIF6    (1U << 19)
#define DMA_HISR_HTIF6    (1U << 20)
#define DMA_HISR_TCIF6    (1U << 21)

#define DMA_HISR_FEIF7    (1U << 22)
#define DMA_HISR_DMEIF7   (1U << 24)
#define DMA_HISR_TEIF7    (1U << 25)
#define DMA_HISR_HTIF7    (1U << 26)
#define DMA_HISR_TCIF7    (1U << 27)


// ==============================
// DMA Low Interrupt Flag Clear (LIFCR)
// ==============================
#define DMA_LIFCR_CFEIF0   (1U << 0)
#define DMA_LIFCR_CDMEIF0  (1U << 2)
#define DMA_LIFCR_CTEIF0   (1U << 3)
#define DMA_LIFCR_CHTIF0   (1U << 4)
#define DMA_LIFCR_CTCIF0   (1U << 5)

#define DMA_LIFCR_CFEIF1   (1U << 6)
#define DMA_LIFCR_CDMEIF1  (1U << 8)
#define DMA_LIFCR_CTEIF1   (1U << 9)
#define DMA_LIFCR_CHTIF1   (1U << 10)
#define DMA_LIFCR_CTCIF1   (1U << 11)

#define DMA_LIFCR_CFEIF2   (1U << 16)
#define DMA_LIFCR_CDMEIF2  (1U << 18)
#define DMA_LIFCR_CTEIF2   (1U << 19)
#define DMA_LIFCR_CHTIF2   (1U << 20)
#define DMA_LIFCR_CTCIF2   (1U << 21)

#define DMA_LIFCR_CFEIF3   (1U << 22)
#define DMA_LIFCR_CDMEIF3  (1U << 24)
#define DMA_LIFCR_CTEIF3   (1U << 25)
#define DMA_LIFCR_CHTIF3   (1U << 26)
#define DMA_LIFCR_CTCIF3   (1U << 27)


// ==============================
// DMA High Interrupt Flag Clear (HIFCR)
// ==============================
#define DMA_HIFCR_CFEIF4   (1U << 0)
#define DMA_HIFCR_CDMEIF4  (1U << 2)
#define DMA_HIFCR_CTEIF4   (1U << 3)
#define DMA_HIFCR_CHTIF4   (1U << 4)
#define DMA_HIFCR_CTCIF4   (1U << 5)

#define DMA_HIFCR_CFEIF5   (1U << 6)
#define DMA_HIFCR_CDMEIF5  (1U << 8)
#define DMA_HIFCR_CTEIF5   (1U << 9)
#define DMA_HIFCR_CHTIF5   (1U << 10)
#define DMA_HIFCR_CTCIF5   (1U << 11)

#define DMA_HIFCR_CFEIF6   (1U << 16)
#define DMA_HIFCR_CDMEIF6  (1U << 18)
#define DMA_HIFCR_CTEIF6   (1U << 19)
#define DMA_HIFCR_CHTIF6   (1U << 20)
#define DMA_HIFCR_CTCIF6   (1U << 21)

#define DMA_HIFCR_CFEIF7   (1U << 22)
#define DMA_HIFCR_CDMEIF7  (1U << 24)
#define DMA_HIFCR_CTEIF7   (1U << 25)
#define DMA_HIFCR_CHTIF7   (1U << 26)
#define DMA_HIFCR_CTCIF7   (1U << 27)




typedef struct {
    DMA_StreamID_t streamID;
    volatile DMA_Stream_RegDef_t* stream;

    uint32_t periphAddr;
    uint32_t memAddr;
    uint32_t mem1Addr;
    uint32_t dataLength;

    DMA_Direction_t direction;
    DMA_Priority_t priority;
    DMA_DataSize_t msize;
    DMA_DataSize_t psize;

    DMA_Channel_t channel;

    uint8_t enableDoubleBuffer;
    DMA_FIFOState_t fifoEnable;
    DMA_FIFOThreshold_t fifoThreshold;

    DMA_Mode_t mode;
} DMA_Config_t;








void DMA_TRANSFER(DMA_Config_t *config);
void DMA_Init(DMA_Config_t* config);
void Enable_DMA_IRQ(DMA_StreamID_t streamID);
void DMA_CLEARFLAGS(DMA_StreamID_t streamID);
uint32_t DMA_GETSTATUS(DMA_StreamID_t streamID);
void DMA_START_IT(DMA_Config_t *config);
void DMA_START(DMA_Config_t *config);

volatile DMA_Stream_RegDef_t* DMA_GetStreamPtr(DMA_StreamID_t id);
void USART_DMA_WaitTxComplete(void);

void DMA_EnableStream(DMA_StreamID_t streamID);


#endif /* DMA_INTERFACE_H_ */
