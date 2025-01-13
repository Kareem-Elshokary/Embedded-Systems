/*************************************************************************/
/* Author        : Kareem Abdelkader                                   			      */
/* Project       : STM32F103C8_Drivers  	                             			      */
/* File          : CLK.h        			                       				              */
/* Date          : 18/2/2024                                        				      */
/* Version       : V2                                                				      */
/* GitHub        : https://github.com/Kareem-Elshokary/Master_Embedded_systems    */
/*************************************************************************/


#ifndef INC_CLK_H_
#define INC_CLK_H_

/*****************************
 * Includes
 ****************************/
#include "STM32F103x8.h"


//===========================================================

/*****************************
 * User Configuration
 ****************************/

//Modes
typedef enum{
	HSI,	// 8 MHz
	HSE,	// 56 MHz
	PLL		// 36 MHz
}RCC_MODES_t;

//Buses
typedef enum{
	AHB,
	APB1,
	APB2
}RCC_BUSES_t;


//AHB Peripherals
#define RCC_DMA1		0
#define RCC_DMA2		1
#define RCC_SRAM		2
#define RCC_FLITF		4
#define RCC_CRC			6
#define RCC_FSMC		8
#define RCC_SDIO		10

//APB1 Peripherals
#define RCC_TIM2		0
#define RCC_TIM3		1
#define RCC_TIM4		2
#define RCC_WWD			11
#define RCC_SPI2		14
#define RCC_USART2		17
#define RCC_USART3		18
#define RCC_I2C1		21
#define RCC_I2C2		22
#define RCC_USB			23
#define RCC_CAN			25
#define RCC_BKP			27
#define RCC_PWR			28

//APB2 Peripherals
#define RCC_AFIO		0
#define RCC_GPIOA		2
#define RCC_GPIOB		3
#define RCC_GPIOC		4
#define RCC_GPIOD		5
#define RCC_GPIOE		6
#define RCC_ADC1		9
#define RCC_ADC2		10
#define RCC_TIM1		11
#define RCC_SPI1		12
#define RCC_USART1		14



//RCC Peripherals state
#define Enable			1
#define Disable 		0

//RCC Peripherals Reset state
#define RCC_Reset			1
#define RCC_Rereset 		0

//=====================================================================

/*************************************
 * APIs Supported by MCAL RCC Drive
 ************************************/

//System Clock Frequency
void MCAL_RCC_SYSFREQ(RCC_MODES_t mode);

//this function is to set AHB bus frequency
uint32_t MCAL_RCC_GetHCLKFreq(void);

//this function is to set ABP1 bus frequency
uint32_t MCAL_RCC_GetPCLK1Freq(RCC_MODES_t mode);

//this function is to set ABP2 bus frequency
uint32_t MCAL_RCC_GetPCLK2Freq(void);

//this function is to set ADC frequency
uint32_t MCAL_RCC_GetPCLK2_ADCFreq(void);

//Enable Peripherals Frequency
void MCAL_RCC_PERIPHERAL_EN(RCC_BUSES_t bus, uint16_t periphral);

//Disable Peripherals Frequency
void MCAL_RCC_PERIPHERAL_DIS(RCC_BUSES_t bus, uint16_t periphral);





#endif /* INC_CLK_H_ */
