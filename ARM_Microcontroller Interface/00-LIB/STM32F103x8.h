/*************************************************************************/
/* Author        : Kareem Abdelkader                                   			  	*/
/* Project       : STM32F103C8_Drivers  	                             			  	*/
/* File          : STM32F103c8.h     		                       				      	  */
/* Date          : 18/2/2024                                        				  	*/
/* Version       : V2                                                				    */
/* GitHub        : https://github.com/Kareem-Elshokary/Master_Embedded_systems  */
/*************************************************************************/


#ifndef INC_STM32F103X8_H_
#define INC_STM32F103X8_H_

/*****************************
 * Includes
 ****************************/
#include "stdint.h"
#include "stdio.h"


//===========================================================================

/**********************************************
 * Base Addresses for Memories and Peripherals
 *********************************************/

// Memory Mapping for MCU
#define FLASH_MEMORY_BASE						0x08000000
#define SYSTEM_MEMORY_BASE						0x1FFFF000
#define SRAM_MEMORY_BASE						0x20000000
#define PERIPHERALS_MEM_BASE					0x40000000
#define CortexM3_IN_PERIPHERALS_MEM_BASE		0xE0000000


//Memory Mapping for RCC Peripheral
#define RCC_BASE								0x40021000

//Memory Mapping for GPIO Peripheral
#define GPIOA_BASE								0x40010800
#define GPIOB_BASE								0x40010C00
#define GPIOC_BASE								0x40011000
#define GPIOD_BASE								0x40011400
#define GPIOE_BASE								0x40011800

//Memory Mapping for AFIO Peripheral
#define AFIO_BASE								0x40010000

//Memory Mapping for EXTI Peripheral
#define EXTI_BASE								0x40010400

//Memory Mapping for TIMER Peripheral
#define TIM1_BASE								0x40012C00
#define TIM2_BASE								0x40000000
#define TIM3_BASE								0x40000400
#define TIM4_BASE								0x40000800

//Memory Mapping for IWDG Peripheral
#define IWDG_BASE								0x40003000

//Memory Mapping for USART Peripheral
#define USART1_BASE								0x40013800
#define USART2_BASE								0x40004400
#define USART3_BASE								0x40004800

//Memory Mapping for SPI Peripheral
#define SPI1_BASE								0x40013000
#define SPI2_BASE								0x40003800

//Memory Mapping for NVIC
#define NVIC_BASE								0xE000E100


//===========================================================================

/*****************************
 * Peripheral Registers
 ****************************/

// RCC Registers
typedef struct {
	uint32_t RCC_CR;			  //Clock control register
	uint32_t RCC_CFGR;			//Clock configuration register
	uint32_t RCC_CIR;			  //Clock interrupt register
	uint32_t RCC_APB2RSTR;	//APB2 peripheral reset register
	uint32_t RCC_APB1RSTR;	//APB1 peripheral reset register
	uint32_t RCC_AHBENR;		//AHB peripheral clock enable register
	uint32_t RCC_APB2ENR;		//APB2 peripheral clock enable register
	uint32_t RCC_APB1ENR;		//APB1 peripheral clock enable register
	uint32_t RCC_BDCR;			//Backup domain control register
	uint32_t RCC_CSR;			  //Control/status register (RCC_CSR)
}RCC_REG_t;


// GPIO Registers
typedef struct {
	uint32_t GPIOx_CRL;			//Port configuration register low (GPIOx_CRL)
	uint32_t GPIOx_CRH;			//Port configuration register high (GPIOx_CRH)
	uint32_t GPIOx_IDR;			//Port input data register (GPIOx_IDR)
	uint32_t GPIOx_ODR;			//Port output data register (GPIOx_ODR)
	uint32_t GPIOx_BSRR;		//Port bit set/reset register (GPIOx_BSRR)
	uint32_t GPIOx_BRR;			//Port bit reset register (GPIOx_BRR)
	uint32_t GPIOx_LCKR;		//Port configuration lock register (GPIOx_LCKR)
}GPIO_REG_t;


// AFIO Registers
typedef struct {
	uint32_t AFIO_EVCR;			  //Event control register (AFIO_EVCR)
	uint32_t AFIO_MAPR;			  //AF remap and debug I/O configuration register (AFIO_MAPR)
	uint32_t AFIO_EXTICR1;		//External interrupt configuration register 1 (AFIO_EXTICR1)
	uint32_t AFIO_EXTICR2;		//External interrupt configuration register 2 (AFIO_EXTICR2)
	uint32_t AFIO_EXTICR3;		//External interrupt configuration register 3 (AFIO_EXTICR3)
	uint32_t AFIO_EXTICR4;		//External interrupt configuration register 4 (AFIO_EXTICR4)
	volatile uint32_t RESERVED;
	uint32_t AFIO_MAPR2;		  //AF remap and debug I/O configuration register2 (AFIO_MAPR2)
}AFIO_REG_t;



// EXTI Registers
typedef struct {
	uint32_t EXTI_IMR;			//Interrupt mask register (EXTI_IMR)
	uint32_t EXTI_EMR;			//Event mask register (EXTI_EMR)
	uint32_t EXTI_RTSR;			//Rising trigger selection register (EXTI_RTSR)
	uint32_t EXTI_FTSR;			//Falling trigger selection register (EXTI_FTSR)
	uint32_t EXTI_SWIER;		//Software interrupt event register (EXTI_SWIER)
	uint32_t EXTI_PR;			  //Pending register (EXTI_PR)
}EXTI_REG_t;

// NVIC Registers
typedef struct {
	uint32_t NVIC_ISER[2];              //Interrupt Set Enable Register
	uint32_t RESERVED0[30];
	uint32_t NVIC_ICER[2];              //Interrupt Clear Enable Register
	uint32_t RSERVED1[30];
	uint32_t NVIC_ISPR[2];              //Interrupt Set Pending Register
	uint32_t RESERVED2[30];
	uint32_t NVIC_ICPR[2];              //Interrupt Clear Pending Register
	uint32_t RESERVED3[30];
	uint32_t NVIC_IABR[2];              //Interrupt Active bit Register
	uint32_t RESERVED4[62];
	uint8_t  NVIC_IP[60];               //Interrupt Priority Register (8Bit wide)
	uint32_t RESERVED5[689];
	uint32_t NVIC_STIR;                 //Software trigger interrupt register (NVIC_STIR)
}NVIC_REG_t;

// TIMERs Registers
typedef struct {
	uint32_t TIMx_CR1;					//TIMx control register 1 (TIMx_CR1)
	uint32_t TIMx_CR2;					//TIMx control register 2 (TIMx_CR2)
	uint32_t TIMx_SMCR;					//TIMx slave mode control register (TIMx_SMCR)
	uint32_t TIMx_DIER;					//TIMx DMA/Interrupt enable register (TIMx_DIER)
	uint32_t TIMx_SR;					  //TIMx status register (TIMx_SR)
	uint32_t TIMx_EGR;					//TIMx event generation register (TIMx_EGR)
	uint32_t TIMx_CCMR1;				//TIMx capture/compare mode register 1 (TIMx_CCMR1)
	uint32_t TIMx_CCMR2;				//TIMx capture/compare mode register 2 (TIMx_CCMR2)
	uint32_t TIMx_CCER;					//TIMx capture/compare enable register (TIMx_CCER)
	uint32_t TIMx_CNT;					//TIMx counter (TIMx_CNT)
	uint32_t TIMx_PSC;					//TIMx prescaler (TIMx_PSC)
	uint32_t TIMx_ARR;					//TIMx auto-reload register (TIMx_ARR)
	uint32_t RESERVED_1;
	uint32_t TIMx_CCR1;					//TIMx capture/compare register 1 (TIMx_CCR1)
	uint32_t TIMx_CCR2;					//TIMx capture/compare register 2 (TIMx_CCR2)
	uint32_t TIMx_CCR3;					//TIMx capture/compare register 3 (TIMx_CCR3)
	uint32_t TIMx_CCR4;					//TIMx capture/compare register 4 (TIMx_CCR4)
	uint32_t RESERVED_2;
	uint32_t TIMx_DCR;					//TIMx DMA control register (TIMx_DCR)
	uint32_t TIMx_DMAR;					//TIMx DMA address for full transfer (TIMx_DMAR)
}TIMER_REG_t;

typedef struct {
	uint32_t TIMx_CR1;					//TIMx control register 1 (TIMx_CR1)
	uint32_t TIMx_CR2;					//TIMx control register 2 (TIMx_CR2)
	uint32_t TIMx_SMCR;					//TIMx slave mode control register (TIMx_SMCR)
	uint32_t TIMx_DIER;					//TIMx DMA/Interrupt enable register (TIMx_DIER)
	uint32_t TIMx_SR;					  //TIMx status register (TIMx_SR)
	uint32_t TIMx_EGR;					//TIMx event generation register (TIMx_EGR)
	uint32_t TIMx_CCMR1;				//TIMx capture/compare mode register 1 (TIMx_CCMR1)
	uint32_t TIMx_CCMR2;				//TIMx capture/compare mode register 2 (TIMx_CCMR2)
	uint32_t TIMx_CCER;					//TIMx capture/compare enable register (TIMx_CCER)
	uint32_t TIMx_CNT;					//TIMx counter (TIMx_CNT)
	uint32_t TIMx_PSC;					//TIMx prescaler (TIMx_PSC)
	uint32_t TIMx_ARR;					//TIMx auto-reload register (TIMx_ARR)
	uint32_t TIMx_CCR1;					//TIMx capture/compare register 1 (TIMx_CCR1)
	uint32_t TIMx_CCR2;					//TIMx capture/compare register 2 (TIMx_CCR2)
	uint32_t TIMx_CCR3;					//TIMx capture/compare register 3 (TIMx_CCR3)
	uint32_t TIMx_CCR4;					//TIMx capture/compare register 4 (TIMx_CCR4)
	uint32_t TIMx_DCR;					//TIMx DMA control register (TIMx_DCR)
	uint32_t TIMx_DMAR;					//TIMx DMA address for full transfer (TIMx_DMAR)
}TIMER1_REG_t;

// IWDG Registers
typedef struct {
	uint32_t IWDG_KR;					//Key register (IWDG_KR)
	uint32_t IWDG_PR;					//Prescaler register (IWDG_PR)
	uint32_t IWDG_RLR;				//Reload register (IWDG_RLR)
	uint32_t IWDG_SR;					//Status register (IWDG_SR)
}IWDG_REG_t;

// USART Registers
typedef struct {
	uint32_t USART_SR;					//Status register (USART_SR)
	uint32_t USART_DR;					//Data register (USART_DR)
	uint32_t USART_BRR;					//Baud rate register (USART_BRR)
	uint32_t USART_CR1;					//Control register 1 (USART_CR1)
	uint32_t USART_CR2;					//Control register 2 (USART_CR2)
	uint32_t USART_CR3;					//Control register 3 (USART_CR3)
	uint32_t USART_GTPR;				//Guard time and prescaler register (USART_GTPR)
}USART_REG_t;

// SPI Registers
typedef struct {
	uint32_t SPI_CR1;					//SPI control register 1 (SPI_CR1)
	uint32_t SPI_CR2;					//SPI control register 1 (SPI_CR2)
	uint32_t SPI_SR;					//SPI status register (SPI_SR)
	uint32_t SPI_DR;					//SPI data register (SPI_DR)
	uint32_t SPI_CRCPR;				//SPI CRC polynomial register (SPI_CRCPR)
	uint32_t SPI_RXCRCR;			//SPI RX CRC register (SPI_RXCRCR)
	uint32_t SPI_TXCRCR;			//SPI TX CRC register (SPI_TXCRCR)
	uint32_t SPI_I2SCFGR;			//SPI_I2S configuration register (SPI_I2SCFGR)
	uint32_t SPI_I2SPR;				//SPI_I2S prescaler register (SPI_I2SPR)
}SPI_REG_t;

//===========================================================================

/*****************************
 * Peripheral Instants
 ****************************/

//RCC Peripheral
#define RCC 		((RCC_REG_t *)RCC_BASE)

//GPIO Peripheral
#define GPIOA		((GPIO_REG_t *)GPIOA_BASE)
#define GPIOB		((GPIO_REG_t *)GPIOB_BASE)
#define GPIOC		((GPIO_REG_t *)GPIOC_BASE)
#define GPIOD		((GPIO_REG_t *)GPIOD_BASE)
#define GPIOE		((GPIO_REG_t *)GPIOE_BASE)

//AFIO Peripheral
#define AFIO		((AFIO_REG_t *)AFIO_BASE)

//EXTI Peripheral
#define EXTI		((EXTI_REG_t *)EXTI_BASE)

//NVIC
#define NVIC		((NVIC_REG_t *)NVIC_BASE)

//TIMERs
#define TIM1		((TIMER1_REG_t *)TIM1_BASE)
#define TIM2		((TIMER_REG_t *)TIM2_BASE)
#define TIM3		((TIMER_REG_t *)TIM3_BASE)
#define TIM4		((TIMER_REG_t *)TIM4_BASE)

// IWDG Peripheral
#define IWDG		((IWDG_REG_t *)IWDG_BASE)

// USART Peripheral
#define USART1	((USART_REG_t *)USART1_BASE)
#define USART2	((USART_REG_t *)USART2_BASE)
#define USART3	((USART_REG_t *)USART3_BASE)

// SPI Peripheral
#define SPI1		((SPI_REG_t *)SPI1_BASE)
#define SPI2		((SPI_REG_t *)SPI2_BASE)


//===========================================================================


#endif /* INC_STM32F103X8_H_ */
