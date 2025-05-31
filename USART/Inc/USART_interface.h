/*
 * USART_interface.h
 *
 *  Created on: May 26, 2025
 *      Author: Mai El Shahed
 */

#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_










/**********************Status register (USART_SR)****************************/

typedef enum{
	PE,    /*PARITY ERROR*/
	FE,    /*Framing error*/
	NF,     /*Noise detected flag*/
	ORE,   /* Overrun error*/
	IDLE,  /* IDLE line detected	*/
	RXNE,  /* Read data register not empty*/
	TC,  /* Transmission complete  */
	TXE,    /* Transmit data register empty   */
	LBD,    /* LIN break detection flag   */
	CTS,    /*CTS flag  */

}USART_SR;


/*********************Data register (USART_DR)***************************************/

typedef enum{
	DR ,   /* Data value   */

}USART_DR;


/********************Baud rate register (USART_BR****************************************/

typedef enum{
	DIV_Fraction,    /* fraction of USARTDIV  */
	DIV_Mantissa=4,  /* mantissa of USARTDIV   */

}USART_BR;


/***********************Control register 1 (USART_CR1)*************************************/


typedef enum {
    SBK     = 0,   /* Send break */
    RWU     = 1,   /* Receiver wakeup */
    RE      = 2,   /* Receiver enable */
    TE      = 3,   /* Transmitter enable */
    IDLEIE  = 4,   /* IDLE interrupt enable */
    RXNEIE  = 5,   /* RXNE interrupt enable */
    TCIE    = 6,   /* Transmission complete interrupt enable */
    TXEIE   = 7,   /* TXE interrupt enable */
    PEIE    = 8,   /* PE interrupt enable */
    PS      = 9,   /* Parity selection */
    PCE     = 10,  /* Parity control enable */
    WAKE    = 11,  /* Wakeup method */
    M       = 12,  /* Word length */
    UE      = 13,  /* USART enable */
    /* Bit 14 is Reserved */
    OVER8   = 15,  /* Oversampling mode */
    /* Bits 31:16 Reserved */
} USART_CR1;






/********************Control register 2 (USART_CR2)****************************************/

typedef enum {
    ADD      = 0,   /* [3:0] Address of the USART node */
    LBDL     = 5,   /* LIN break detection length */
    LBDIE    = 6,   /* LIN break detection interrupt enable */
    /* Bit 7 reserved */
    LBCL     = 8,   /* Last bit clock pulse */
    CPHA     = 9,   /* Clock phase */
    CPOL     = 10,  /* Clock polarity */
    CLKEN    = 11,  /* Clock enable */
    STOP     = 12,  /* [13:12] STOP bits (2 bits) */
    LINEN    = 14   /* LIN mode enable */
    /* Bits 15: Reserved */
} USART_CR2;


/********************Control register 3 (USART_CR3)****************************************/

typedef enum {
    EIE      = 0,   /* Error interrupt enable */
    IREN     = 1,   /* IrDA mode enable */
    IRLP     = 2,   /* IrDA low-power */
    HDSEL    = 3,   /* Half-duplex selection */
    NACK     = 4,   /* Smartcard NACK enable */
    SCEN     = 5,   /* Smartcard mode enable */
    DMAR     = 6,   /* DMA enable receiver */
    DMAT     = 7,   /* DMA enable transmitter */
    RTSE     = 8,   /* RTS enable */
    CTSE     = 9,   /* CTS enable */
    CTSIE    = 10,  /* CTS interrupt enable */
    ONEBIT   = 11   /* One sample bit method enable */
    /* Bits 15:12 Reserved */
} USART_CR3;

/*****************USART_Mode*******************************************/

typedef enum {
    RX_ONLY,
    TX_ONLY,
    RX_TX
} USART_Mode;


/*************************************stop bit******************************************************/

#define USART_STOP_1      (0x0 << STOP)  // 1 stop bit
#define USART_STOP_0_5    (0x1 << STOP)  // 0.5 stop bit
#define USART_STOP_2      (0x2 << STOP)  // 2 stop bits
#define USART_STOP_1_5    (0x3 << STOP)  // 1.5 stop bit


/*****************************************************************************************/

typedef struct {
    USART_SR   Status_reg;     // USART (ثل TXE, RXNE, ORE...)
    USART_DR   Data_reg;       // Data register (  Received or Transmitted data character)
    USART_BR   Baud_rate_reg;     //Baud rate registerد
    USART_CR1  Control1_reg;   // اControl register 1
    USART_CR2  Control2_reg;   // اControl register 2
    USART_CR3  Control3_reg;   // اControl register 3
} USART_TypeDef;

/****************************************DMA_HIFCR**********************************************************/



void USART1_IRQHandler(void);
void USART_SendString(USART_RegDef_t *USARTx, const char *str);
uint8_t USART_ReceiveChar(USART_RegDef_t *USARTx);

void USART_SendChar(USART_RegDef_t *USARTx, uint8_t data);
void USART_Init(USART_RegDef_t *USARTx, uint32_t baud_rate, uint32_t PCLKx, uint8_t over);
void USART_ConfigMode(USART_RegDef_t *USARTx, USART_Mode mode);

uint8_t USART_GetFlagStatus(USART_RegDef_t *USARTx, USART_SR Flag);

void USART_DMA_StartTx(USART_RegDef_t *USARTx);
void USART_DMA_StartRx(USART_RegDef_t *USARTx);


void USART2_IRQHandler(void);















#endif /* USART_INTERFACE_H_ */
