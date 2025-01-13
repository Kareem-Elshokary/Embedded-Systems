/*************************************************************************/
/* Author        : Kareem Abdelkader                                   			  	*/
/* Project       : STM32F103C8_Drivers  	                             			  	*/
/* File          : INTERRUPT.h		     		                     				          */
/* Date          : 22/2/2024                                        				  	*/
/* Version       : V2                                                				    */
/* GitHub        : https://github.com/Kareem-Elshokary/Master_Embedded_systems  */
/*************************************************************************/


#ifndef INC_INTERRUPT_H_
#define INC_INTERRUPT_H_

/*****************************
 * Includes
 ****************************/
#include "STM32F103x8.h"
#include "GPIO.h"


//===================================================================================

/*****************************
 * EXTI Configuration
 ****************************/

/*
 * To use a pin as EXTI pin you should configure the following:
 * 1- Port
 * 2- Pin Number
 * 3- Trigger case
 * 4- Pointer to function
 */


// EXTI pin
#define EXTI0			0
#define EXTI1			1
#define EXTI2			2
#define EXTI3			3
#define EXTI4			4
#define EXTI5			5
#define EXTI6			6
#define EXTI7			7
#define EXTI8			8
#define EXTI9			9
#define EXTI10		10
#define EXTI11		11
#define EXTI12		12
#define EXTI13		13
#define EXTI14		14
#define EXTI15		15


// Trigger case
#define RISING_EDGE				    1
#define FALLING_EDGE			    2
#define RISING_FALLING_EDGE		3


//===================================================================================

/*****************************
 * NVIC Configuration
 ****************************/

/*
 * Vector table ( IRQ_NUM )
 */

#define WWDG					    0
#define PVD						    1
#define TAMPER					  2
#define RTC						    3
#define FLASH					    4
#define RCC_					    5
#define EXTI0_					  6
#define EXTI1_				  	7
#define EXTI2_					  8
#define EXTI3_					  9
#define EXTI4_					  10
#define DMA1_Channel1			11
#define DMA1_Channel2			12
#define DMA1_Channel3			13
#define DMA1_Channel4			14
#define DMA1_Channel5			15
#define DMA1_Channel6			16
#define DMA1_Channel7			17
#define ADC1_2					  18
#define USB_HP_CAN_TX			19
#define USB_LP_CAN_RX0		20
#define CAN_RX1					  21
#define CAN_SCE					  22
#define EXTI9_5					  23
#define TIM1_BRK				  24
#define TIM_UP					  25
#define TIM1_TRG_COM		 	26
#define TIM1_CC					  27
#define TIM2_					    28
#define TIM3_					    29
#define TIM4_					    30
#define NVIC_I2C1_EV			31
#define NVIC_I2C1_ER			32
#define NVIC_I2C2_EV			33
#define NVIC_I2C2_ER			34
#define NVIC_SPI1			  	35
#define NVIC_SPI2			  	36
#define NVIC_USART1				37
#define NVIC_USART2				38
#define NVIC_USART3				39
#define EXTI10_15				  40
#define RTCAlarm				  41
#define USBWakeup				  42



/*
 * Enable and Disable IRQ Macros
 */
// Numbers above 32, (IRQ_NUM - 32)
#define NVIC_IRQ_EN(REG, IRQ_NUM)			REG |= (1 << IRQ_NUM)		// Enable IRQ. 0->31 ISER[0], 32->42 ISER[1]
#define NVIC_IRQ_DIS(REG, IRQ_NUM)			REG &= ~(1 << IRQ_NUM)		// Disable IRQ. 0->31 ICER[0], 32->42 ICER[1]



/*
 * Set and Reset IRQ Pending Flag Macros
 */
// Numbers above 32, (IRQ_NUM - 32)
#define NVIC_IRQ_SETPENDING(REG, IRQ_NUM)		REG |= (1 << IRQ_NUM)		// Set IRQ Pending Flag. 0->31 ISPR[0], 32->42 ISPR[1]
#define NVIC_IRQ_RESETPENDING(REG, IRQ_NUM)		REG &= ~(1 << IRQ_NUM)		// Reset IRQ Pending Flag. 0->31 ICPR[0], 32->42 ICPR[1]


//===================================================================================

/**************************************
 * APIs Supported by MCAL EXTI Drive
 **************************************/

//EXTI INIT
void MCAL_EXTI_INIT(GPIO_REG_t* GPIOxx, uint16_t pin, uint32_t trigger_case, void(* func_add) (void));

//EXTI DEINIT
void MCAL_EXTI_DEINIT(AFIO_REG_t* AFIOx);




#endif /* INC_INTERRUPT_H_ */
