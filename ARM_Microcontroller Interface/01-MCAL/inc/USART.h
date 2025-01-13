/*************************************************************************/
/* Author        : Kareem Abdelkader                                   			   	*/
/* Project       : STM32F103C8_Drivers  	                             			  	*/
/* File          : USART.h		     		                       				      	    */
/* Date          : 28/2/2024                                        				  	*/
/* Version       : V2                                                				    */
/* GitHub        : https://github.com/Kareem-Elshokary/Master_Embedded_systems  */
/*************************************************************************/

/*-----------------------------------------------------------------------------------------------------------
 * Universal Synchorous Asynchorous Reciever and Transmitter (USART), it is a standard serial communication
 * protocol that can be transmite and recive data between devices.
 *
 *  USART Features:
 *  1- Full/Half duplex
 *  2- Synchorous / Asynchorous
 *  3- Wire medium, peer to peer
 *  4- Optional flow control [CTS-RTS]
 *  5- Buad rate up to 4.5 MBites/s
 --------------------------------------------------------------------------------------------------------------*/

#ifndef INC_USART_H_
#define INC_USART_H_

/*****************************
 * Includes
 ****************************/
#include "STM32F103x8.h"
#include "GPIO.h"
#include "CLK.h"
#include "INTERRUPT.h"

//=====================================================================

/*****************************
 * User Configuration
 ****************************/

/*
 * To configure a pin, determine the following consideration:
 * 1- USART Mode (Transmit/Receive)
 * 2- USART Baudrate
 * 3- Data length (8/9 bits)
 * 4- Parity (even/odd)
 * 5- No. of stop bits (1/2 bits)
 * 6- HW Flow control (CTS/RTS)
 * 7- USART mechanism (Polling/EXTI/DMA)
 */

// USART Mode (Transmit/Receive)
#define USART_TR_MODE			  1
#define USART_RC_MODE			  2
#define USART_RC_TR_MODE		3

// USART Buadrate
#define BAUDRATE_2400			  2400
#define BAUDRATE_9600			  9600
#define BAUDRATE_19200			19200
#define BAUDRATE_57600			57600
#define BAUDRATE_115200			115200
#define BAUDRATE_230400			230400
#define BAUDRATE_460800			460800
#define BAUDRATE_921600			921600

// Data length (8/9 bits)
#define USART_DATA_LEN8			1
#define USART_DATA_LEN9			2

// Parity (even/odd)
#define USART_PC_DIS			  0
#define USART_PC_EN_EVEN		1
#define USART_PC_EN_ODD			2

// No. of stop bits (1/2 bits)
#define USART_1STB				0b00
#define USART_2STB				0b10

// HW Flow control (CTS/RTS)
#define USART_CTS_RTS_EN		1
#define USART_CTS_RTS_DIS		0

// USART mechanism
#define POLLING					1
#define INTERRUPT				2
#define DMA						  3

// USART IRQ EVENT
typedef enum {
	USART_IRQ_TXE,			//Transmit data register empty
	USART_IRQ_TC,			  //Transmission complete
	USART_IRQ_RXNE,			//Received data ready to read
	USART_IRQ_ORE,			//Overrun error
	USART_IRQ_PE			  //Parity error
}USART_IRQ_EVENT_t;


//=====================================================================

//BaudRate Calculation:

//USARTDIV = fclk / (16 * Baudrate)
#define USARTDIV(_PCLK_, _BAUD_)						(uint32_t) (_PCLK_/(16 * _BAUD_ ))

//To avoid loss fraction part multiply USARTDIV * 100 ,
//USARTDIV_MUL100 = uint32((100 *fclk ) / (16 * Baudrate) == (25 *fclk ) / (4* Baudrate) )
#define USARTDIV_MUL100(_PCLK_, _BAUD_)					(uint32_t) ( (25 * _PCLK_ ) / (4  * _BAUD_ ))

//DIV_Mantissa_MUL100 = Integer Part (USARTDIV)  * 100
#define Mantissa_MUL100(_PCLK_, _BAUD_)					(uint32_t) (USARTDIV(_PCLK_, _BAUD_) * 100)

//DIV_Mantissa = Integer Part (USARTDIV  )
#define Mantissa(_PCLK_, _BAUD_)						(uint32_t) (USARTDIV(_PCLK_, _BAUD_) )

//DIV_Fraction = (( USARTDIV_MUL100  - DIV_Mantissa_MUL100  ) * 16 ) / 100
#define DIV_Fraction(_PCLK_, _BAUD_)					(uint32_t) (((USARTDIV_MUL100(_PCLK_, _BAUD_) -  Mantissa_MUL100(_PCLK_, _BAUD_) ) * 16 ) / 100 )

//Value that write to BRR register
#define UART_BRR_Register(_PCLK_, _BAUD_)				(( Mantissa (_PCLK_, _BAUD_) ) <<4 )|( (DIV_Fraction(_PCLK_, _BAUD_)) & 0xF )


//=====================================================================

/**************************************
 * APIs Supported by MCAL USART Drive
 **************************************/

//USART init/deinit
void MCAL_USART_INIT(USART_REG_t* USARTx,uint32_t baud,uint8_t mode, uint8_t data_len, uint8_t parity, uint8_t stop, uint8_t HW_FC);
void MCAL_USART_DEINIT(USART_REG_t* USARTx);

//USART send data
void MCAL_USART_SEND(USART_REG_t* USARTx, uint16_t* buff, uint8_t mechanism);

//USART receive data
void MCAL_USART_RECEIVE(USART_REG_t* USARTx, uint16_t* buff, uint8_t mechanism);

//Wait
void MCAL_USART_WAIT_TC(USART_REG_t* USARTx);

#endif /* INC_USART_H_ */
