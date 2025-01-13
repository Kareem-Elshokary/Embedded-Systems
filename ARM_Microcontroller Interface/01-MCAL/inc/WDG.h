/*************************************************************************/
/* Author        : Kareem Abdelkader                                   			  	*/
/* Project       : STM32F103C8_Drivers  	                             			  	*/
/* File          : WDG.h     		         		              				      	      */
/* Date          : 20/2/2024                                        				  	*/
/* Version       : V1                                                				    */
/* GitHub        : https://github.com/Kareem-Elshokary/Master_Embedded_systems  */
/*************************************************************************/

#ifndef INC_WDG_H_
#define INC_WDG_H_

/*****************************
 * Includes
 ****************************/
#include "STM32F103x8.h"
#include "CLK.h"

//=====================================================================

/*****************************
 * User Configuration
 ****************************/

/*
The IWDG is a hardware timer that helps detect and recover from software malfunctions in your microcontroller.
It acts as a safety mechanism by resetting the MCU if the core program gets stuck or encounters an infinite loop.
*/


/*
 * Prescaler
	0: divider /4   : tick_time : 0.1ms  max_time : 409.6ms
	1: divider /8   : tick_time : 0.2ms  max_time : 819.2ms
	2: divider /16  : tick_time : 0.4ms  max_time : 1638.4ms
	3: divider /32  : tick_time : 0.8ms  max_time : 3276.8ms
	4: divider /64  : tick_time : 1.6ms  max_time : 6553.6ms
	5: divider /128 : tick_time : 3.2ms  max_time : 13107.2ms
	6: divider /256 : tick_time : 6.4ms  max_time : 26214.4ms
*/
#define IWDG_PRESCALER_4		  000
#define IWDG_PRESCALER_8		  001
#define IWDG_PRESCALER_16		  010
#define IWDG_PRESCALER_32		  011
#define IWDG_PRESCALER_64		  100
#define IWDG_PRESCALER_128		101
#define IWDG_PRESCALER_256		110



//=====================================================================

/**************************************
 * APIs Supported by MCAL WDG Drive
 **************************************/

//IWDG INIT
void MCAL_WDG_INIT();

//IWDG Set
void MCAL_WDG_SET(uint32_t prescaler, uint32_t value);

//IWDG Reload
void MCAL_WDG_RELOAD();



#endif /* INC_WDG_H_ */
