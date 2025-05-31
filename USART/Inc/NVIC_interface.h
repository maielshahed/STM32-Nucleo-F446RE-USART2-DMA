/*
 * NVIC_interface.h
 *
 *  Created on: Apr 19, 2025
 *      Author: Mai El Shahed
 */




#ifndef NVIC_INTERFACE_H_
#define NVIC_INTERFACE_H_

/*****************External interrupt/event controller (EXTI)************************************/
/*enum{WWDG,PVD,TAMP_STAMP,RTC_WKUP,FLASH,RCC,EXTI0,EXTI1,EXTI2,EXTI3,EXTI4,
	DMA0,DMA1,DMA2,DMA3,DMA4,DMA5,DMA6,ADC,CAN1_TX,CAN1_RX0,
	CAN1_RX1,CAN1_SCE,I2C1_EV=31,I2C1_ER,I2C2_EV,I2C2_ER,SPI1,
	SPI2,USART1,USART2,USART3,SPI3=51,USART4,USART5};*/
  enum{
	 WWDG_IRQn = 0,
	 PVD_IRQn,
    TAMP_STAMP_IRQn,
    RTC_WKUP_IRQn,
    FLASH_IRQn,
    RCC_IRQn,
    EXTI0_IRQn,
    EXTI1_IRQn,
    EXTI2_IRQn,
    EXTI3_IRQn,
    EXTI4_IRQn,
    DMA1_Stream0_IRQn,
    DMA1_Stream1_IRQn,
    DMA1_Stream2_IRQn,
    DMA1_Stream3_IRQn,
    DMA1_Stream4_IRQn,
    DMA1_Stream5_IRQn,
    DMA1_Stream6_IRQn,
    ADC_IRQn,
    CAN1_TX_IRQn,
    CAN1_RX0_IRQn,
    CAN1_RX1_IRQn,
    CAN1_SCE_IRQn,
    EXTI9_5_IRQn,
    TIM1_BRK_TIM9_IRQn,
    TIM1_UP_TIM10_IRQn,
    TIM1_TRG_COM_TIM11_IRQn,
    TIM1_CC_IRQn,
    TIM2_IRQn,
    TIM3_IRQn,
    TIM4_IRQn,
    I2C1_EV_IRQn,
    I2C1_ER_IRQn,
    I2C2_EV_IRQn,
    I2C2_ER_IRQn,
    SPI1_IRQn,
    SPI2_IRQn,
    USART1_IRQn,
    USART2_IRQn,
    USART3_IRQn,
    EXTI15_10_IRQn = 40,
    RTC_Alarm_IRQn,
    OTG_FS_WKUP_IRQn,
    TIM8_BRK_TIM12_IRQn = 43,
    TIM8_UP_TIM13_IRQn,
    TIM8_TRG_COM_TIM14_IRQn,
    TIM8_CC_IRQn,
    DMA1_Stream7_IRQn,
    FMC_IRQn,
    SDIO_IRQn,
    TIM5_IRQn,
    SPI3_IRQn,
    UART4_IRQn,
    UART5_IRQn};


/**************************Interrupt priority level value, PRI_N[7:0]********************************/
// When you write to the AIRCR register, you must put a specific security value called 0x5FA in this place. 16 bit
#define SCB_AIRCR_VECTKEY_Pos  (16U)

#define SCB_AIRCR_PRIGROUP_Pos (8U)   //The PRIGROUP field starts at bit 8 of AIRCR.


#define PRIGROUP3 0b011
#define PRIGROUP4 0b100
#define PRIGROUP5 0b101
#define PRIGROUP6 0b110
#define PRIGROUP7 0b111


/***************Interrupt Set-enable Registers  NVIC_ISER0-NVIC_ISER7 ***********************/

uint8_t ENABLE_interrupt(uint8_t IRQNUM);

/***************Interrupt Clear-enable Registers The NVIC_ICER0-NVIC_ICER7**************************************/
uint8_t DISABLED_interrupt(uint8_t IRQNUM);

/***************Interrupt Clear-pending Registers The NVIC_ICPR0-NCVIC_ICPR7******************/
/*read 0=not pen  1=enable   &  Write:0 = no effect-----   1 = removes pending state an interrupt.  ****/

uint8_t Clear_PendingFlag(uint8_t IRQNUM);

/*************** Interrupt Active Bit Registers The NVIC_IABR0-NVIC_IABR7****************/
/***************  0=not   1=active interrupt  ****************/

uint8_t Active_PendingFlag(uint8_t IRQNUM);

/***************Interrupt Set-pending Registers The NVIC_ISPR0-NVIC_ISPR7 r
0 = no effect
1 = changes interrupt state to pending***********************************************/
uint8_t SET_PendingFlag(uint8_t IRQNUM);



void SetInterruptPriority(uint8_t IRQNUM, uint32_t priority);


void NVIC_ConfigurePriorityGrouping(uint8_t priorityGroup);


#endif /* NVIC_INTERFACE_H_ */
