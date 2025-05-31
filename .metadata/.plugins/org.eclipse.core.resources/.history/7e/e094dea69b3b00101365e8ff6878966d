/*
 * NVIC_interface.h
 *
 *  Created on: Apr 19, 2025
 *      Author: Mai El Shahed
 */




#ifndef NVIC_INTERFACE_H_
#define NVIC_INTERFACE_H_

/*****************External interrupt/event controller (EXTI)************************************/
enum{WWDG,PVD,TAMP_STAMP,RTC_WKUP,FLASH,RCCC,EXTI0,EXTI1,EXTI2,EXTI3,EXTI04,
	DMA0,DMA1,DMA2,DMA3,DMA4,DMA5,DMA6,ADC,CAN1_TX,CAN1_RX0,
	CAN1_RX1,CAN1_SCE,I2C1_EV=31,I2C1_ER,I2C2_EV,I2C2_ER,SPI1,
	SPI2,USART1,USART2,USART3,SPI3=51,USART4,USART5};


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
