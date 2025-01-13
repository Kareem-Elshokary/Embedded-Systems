/*************************************************************************/
/* Author        : Kareem Abdelkader                                   			  	*/
/* Project       : STM32F103C8_Drivers  	                             			  	*/
/* File          : TIMER.h		     		                       				      	    */
/* Date          : 24/2/2024                                        				  	*/
/* Version       : V1                                                				    */
/* GitHub        : https://github.com/Kareem-Elshokary/Master_Embedded_systems  */
/*************************************************************************/


#ifndef INC_TIMER_H_
#define INC_TIMER_H_

/*****************************
 * Includes
 ****************************/
#include "STM32F103x8.h"
#include "CLK.h"
#include "GPIO.h"
#include "INTERRUPT.h"


//===========================================================

/*****************************
 * User Configuration
 ****************************/

// Timers
#define TIMER_1			1
#define TIMER_2			2
#define TIMER_3			3
#define TIMER_4			4

// Channels
#define CH1				1
#define CH2				2
#define CH3				3
#define CH4				4


// Timer State
#define TIMER_START		1
#define TIMER_STOP		0


// Delay
#define ms				0
#define us				1


// Count direction
#define TIM_COUNT_UP	0
#define TIM_COUNT_DOWN	1

// PWM modes
typedef enum{
	PWM_MODE1,
	PWM_MODE2
}PWM_Modes_t;


//=====================================================================

/****************************************
 * APIs Supported by MCAL TIMER Drive
 ****************************************/

//Timer init
void MCAL_TIMER_INIT(TIMER_REG_t* TIMx, uint16_t reload);
void setTimerClockSource(uint32_t clockSource);

//Timer Start/Stop
void MCAL_TIMER_START(TIMER_REG_t* TIMx);
void MCAL_TIMER_STOP(TIMER_REG_t* TIMx);

//Timer counter
uint32_t MCAL_TIMER_GETCOUNT(TIMER_REG_t* TIMx, uint32_t clk, uint16_t reload);
void MCAL_TIMER_CLRCOUNT(TIMER_REG_t* TIMx);

//PWM
void MCAL_TIMER_PWM_SET(PWM_Modes_t mode, uint8_t channel, double duty_cycle, uint32_t freq, uint32_t prescaler);

//Delay
void MCAL_TIMER_Delay(uint16_t time,uint8_t U,uint32_t clk);

/*
 * To do
 */
//Capture Mode
void MCAL_TIMER_CAPTMODE_SET(TIMER_REG_t* TIMx, uint8_t channel, uint32_t captureEdge);
uint32_t MCAL_TIMER_CAPTIP_GETVALUE(uint8_t channel);


#endif /* INC_TIMER_H_ */
