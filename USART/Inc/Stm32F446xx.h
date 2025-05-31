/*
 * Stm32F446xx.h
 *
 *  Created on: Dec 18, 2024
 *      Author: Mai El Shahed
 */

#ifndef STM32F446XX_H_
#define STM32F446XX_H_


/*******************memories base addresses**********/
#define FLASH_BASE_ADDRESS 0x08000000UL
#define SRAM_BASE_ADDRESS 0x02000000UL
#define ROM_BASE_ADDRESS 0x1FFF0000UL



/*******AHB1 peripheral base addresses **************/
#define GPIOA_BASE_ADDRESS 0x40020000U
#define GPIOB_BASE_ADDRESS 0x40020400U
#define GPIOC_BASE_ADDRESS 0x40020800U
#define GPIOD_BASE_ADDRESS 0x40020C00U
#define GPIOE_BASE_ADDRESS 0x40021000U
#define GPIOF_BASE_ADDRESS 0x40021400U
#define GPIOG_BASE_ADDRESS 0x40021800U
#define GPIOH_BASE_ADDRESS 0x40021C00U


#define RCC_BASE_ADDRESS 0x40023800U

#define SysTick_BASE_ADDRESS 0xE000E010U   /*System Timer, see The system timer, SysTick*/


#define NVIC_BASE_ADDRESS 0xE000E100U


#define SCB_BASE_ADDRESS 0xE000E008U /*!<  System control block Base Address */

#define  SYSCFG_BASE_ADDRESS 0x40013800U






#define USART1_BASE_ADDRESS 0x40011000U
#define USART2_BASE_ADDRESS 0x40004400U
#define USART3_BASE_ADDRESS 0x40004800U
#define USART4_BASE_ADDRESS 0x40004C00U
#define USART5_BASE_ADDRESS 0x40005000U
#define USART6_BASE_ADDRESS 0x40011400U

/*******AHB2 peripheral base addresses **************/

/*******AHB3 peripheral base addresses **************/

/*******APB1 peripheral base addresses **************/

/*******APB2 peripheral base addresses **************/

/*******GPIO registers Definition Structure *****GPIO register map*********/
typedef struct{
	volatile uint32_t MODER;          /* mode register (00: Input (reset state)  01: General purpose output mode---10: Alternate function mode---11: Analog mode*/
	volatile uint32_t OTYPER;         /*output type register  0: Output push-pull -1: Output open-drain Address offset: 0x04*/
	volatile uint32_t OSPEEDER;        /*Address offset: 0x08 output speed register*/
	volatile uint32_t PUPDR;   /*Address offset: 0x0C  pull-up/pull-down register*/
	volatile uint32_t IDR;   /*Address offset: 0x10  input data register*/
	volatile uint32_t ODR;    /*Address offset: 0x014  output data register*/
	volatile uint32_t BSRR;   /*Address offset: 0x18   bit set/reset register*/
	volatile uint32_t LCKR;   /*configuration lock register*/
    volatile uint32_t AFR[2];   /*alternate function low&high register*/


	//volatile uint32_t AFRL; /*alternate function low register*/
	//volatile uint32_t AFRH; /*alternate function high register*/

}GPIO_Reg_t;


/*******RCC registers Definition Structure **************/

typedef struct{
	volatile uint32_t CR;          // Clock control register address Offset
	volatile uint32_t PLLCFGR;
	volatile uint32_t CFGR;       // Clock configuration register (RCC_CFGR)Address offset: 0x08
	volatile uint32_t CIR;        //Address offset: 0x0c
	volatile uint32_t AHB1RSTR;   //Address offset: 0x010
	volatile uint32_t AHB2RSTR;   //Address offset: 0x014
	volatile uint32_t AHB3RSTR;   //Address offset: 0x018

	volatile uint32_t Reserved;   //Address offset: Reserved Reset value

	volatile uint32_t APB1RSTR;    //
	volatile uint32_t APB2RSTR;

	volatile uint32_t Reserved2[2];   //Address offset: Reserved Reset value

	volatile uint32_t AHB1ENR; //write add 0x30
	volatile uint32_t AHB2ENR;   //Address offset: 0x34
	volatile uint32_t AHB3ENR;   //Address offset: 0x38


	volatile uint32_t Reserved3;   //Address offset: Reserved Reset value

	volatile uint32_t APB1ENR;  //Address offset: 0x40
	volatile uint32_t APB2ENR; //Address offset: 0x44

        volatile uint32_t Reserved4[2];

        volatile uint32_t AHB1LPENR;
	volatile uint32_t AHB2LPENR;
	volatile uint32_t AHB3LPENR;

        volatile uint32_t Reserved5;

	volatile uint32_t APB1LPENR;
	volatile uint32_t APB2LPENR;

	volatile uint32_t Reserved6[2];   //Address offset: Reserved Reset value-8 byte unsigned integer

	volatile uint32_t BDCR;
	volatile uint32_t CSR;

	volatile uint32_t Reserved7[2];   //Address offset: Reserved Reset value-8 byte unsigned integer

	volatile uint32_t SSCGR;
	volatile uint32_t PLLI2SCFG;
	volatile uint32_t PLLSAICFGR;
	volatile uint32_t DCKCFGR;
	volatile uint32_t CKGATENR;
	volatile uint32_t DCKCFGR2;

}RCC_Reg_t;

/*******RCC peripheral Definition  **************/
#define RCC  ((RCC_Reg_t*) RCC_BASE_ADDRESS)


/*******GPIO peripheral Definition  **************/

#define GPIOA  ((GPIO_Reg_t*) GPIOA_BASE_ADDRESS)
#define GPIOB  ((GPIO_Reg_t*) GPIOB_BASE_ADDRESS)
#define GPIOC  ((GPIO_Reg_t*) GPIOC_BASE_ADDRESS)
#define GPIOD  ((GPIO_Reg_t*) GPIOD_BASE_ADDRESS)
#define GPIOE  ((GPIO_Reg_t*) GPIOE_BASE_ADDRESS)
#define GPIOF  ((GPIO_Reg_t*) GPIOF_BASE_ADDRESS)
#define GPIOG  ((GPIO_Reg_t*) GPIOG_BASE_ADDRESS)
#define GPIOH  ((GPIO_Reg_t*) GPIOH_BASE_ADDRESS)


/*******SysTick registers Definition Structure **************/

typedef struct{
	volatile uint32_t CTRL;   /*!< Offset: 0x000 (R/W) Controls the SysTick timer Register */
	volatile uint32_t LOAD;   /*!< Offset: 0x004 (R/W) Sets the reload value for the timer. Register */
	volatile uint32_t VAL;    /*!< Offset: 0x008 (R/W) Shows the current timer value Register */
	volatile const  uint32_t CALIB;  /*!< Offset: 0x00C (R/ ) Provides calibration information for the SysTick time Register */
}SysTick_Type;

/*******RCC peripheral Definition  **************/
#define SysTick  ((SysTick_Type*) SysTick_BASE_ADDRESS)


/****************Nested Vectored Interrupt Controller****************************************************/

typedef struct{
	volatile uint32_t ISER[8];   /*  0xE000E100 - 0xE000E11C  Set-enable Registers*/
	volatile uint32_t Reserved0[24];
	volatile uint32_t ICER[8];  /*Interrupt Clear-Enable Register*/
	volatile uint32_t Reserved1[24];
	volatile uint32_t ISPR[8];     /*Interrupt Set-Pending Register*/

	volatile uint32_t Reserved2[24];

	volatile uint32_t ICPR[8];  /* Interrupt Clear-pending Registers*/
	volatile uint32_t Reserved3[24];
	volatile uint32_t IABR[8];  /*    Interrupt Active Bit Registers*/
	volatile uint32_t Reserved4[56];

	volatile uint8_t IPR[240];    /* Interrupt Priority Registers*/

	volatile uint32_t Reserved5[644];
	volatile uint32_t STIR;  /* Software Trigger Interrupt Register*/

}NVIC_Reg_t;



#define NVIC ((NVIC_Reg_t*)  NVIC_BASE_ADDRESS)

/***********************The System Control Block (SCB)*******************************/


typedef struct{
	volatile uint32_t ACTLR;
	volatile uint32_t CPUID;
	volatile uint32_t ICSR;
	volatile uint32_t VTOR;
	volatile uint32_t AIRCR;    // Application Interrupt and Reset Control Register

	volatile uint32_t SCR;
	volatile uint32_t CCR;

}SCB_Reg_t;

#define SCB ((SCB_Reg_t*) SCB_BASE_ADDRESS)

/**********************SYSCFG register map and reset values**********************88*/


typedef struct
{
  volatile uint32_t MEMRMP;        // Memory remap register
  volatile uint32_t PMC;           // Peripheral mode configuration register
  volatile uint32_t EXTICR[4];     // External interrupt configuration registers (EXTICR1 to EXTICR4)
  uint32_t RESERVED1[2];           // Reserved
  volatile uint32_t CMPCR;         // Compensation cell control register
  uint32_t RESERVED2[2];           // Reserved
  volatile uint32_t CFGR;

}SYSCFG_TypeDef;

#define SYSCFG ((SYSCFG_TypeDef*) SYSCFG_BASE_ADDRESS)

/********************External interrupt/event controller register map and reset values**********************************/


typedef struct
{
  volatile uint32_t IMR;     // Interrupt mask register
  volatile uint32_t EMR;     // Event mask register
  volatile uint32_t RTSR;    // Rising trigger selection register
  volatile uint32_t FTSR;    // Falling trigger selection register
  volatile uint32_t SWIER;   // Software interrupt event register
  volatile uint32_t PR;      // Pending register
}EXTI_TypeDef;

#define EXTI ((EXTI_TypeDef *)0x40013C00)





/*****************USART register map**********************************************************/

typedef struct {
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t BRR;
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t CR3;
    volatile uint32_t GTPR;
} USART_RegDef_t;




/******************************GPIO peripheral Definition  **********************************************************/
#define USART1 ((USART_RegDef_t *)USART1_BASE_ADDRESS)
#define USART2 ((USART_RegDef_t *)USART2_BASE_ADDRESS)
#define USART3 ((USART_RegDef_t *)USART3_BASE_ADDRESS)
#define USART4 ((USART_RegDef_t *)USART4_BASE_ADDRESS)
#define USART5 ((USART_RegDef_t *)USART5_BASE_ADDRESS)
#define USART6 ((USART_RegDef_t *)USART6_BASE_ADDRESS)


/*************************Direct memory access controller (DMA)****************************/
typedef struct {

  volatile uint32_t CR;     // Stream x configuration register
  volatile uint32_t NDTR;   // Stream x number of data register
  volatile uint32_t PAR;    // Stream x peripheral address register
  volatile uint32_t M0AR;   // Stream x memory 0 address register
  volatile uint32_t M1AR;   // Stream x memory 1 address register
  volatile uint32_t FCR;    // Stream x FIFO control register

} DMA_Stream_RegDef_t;

typedef struct {


  volatile uint32_t LISR;    // Low interrupt status register
  volatile uint32_t HISR;    // High interrupt status register
  volatile uint32_t LIFCR;   // Low interrupt flag clear register
  volatile uint32_t HIFCR;   // High interrupt flag clear register
  volatile DMA_Stream_RegDef_t DMA_Stream[8];

} DMA_RegDef;


#define DMA1_BASE 0x40026000U
#define DMA2_BASE 0x40026400U

#define MY_DMA1 ((DMA_RegDef *)DMA1_BASE)
#define MY_DMA2 ((DMA_RegDef *)DMA2_BASE)


#endif /* STM32F446XX_H_ */
