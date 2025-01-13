/*************************************************************************/
/* Author        : Kareem Abdelkader                                   			  	  	*/
/* Project       : STM32F103C8_Drivers  	                             			  	*/
/* File          : WDG.c		     		                       				      	*/
/* Date          : 20/2/2024                                        				  	*/
/* Version       : V1                                                				    */
/* GitHub        : https://github.com/Kareem-Elshokary/Master_Embedded_systems          */
/*************************************************************************/

/*****************************
 * Includes
 ****************************/
#include "WDG.h"


//=====================================================================

/*****************************
 * Generic Functions
 ****************************/

//LSI Clock Enable
void LSI_CLK_EN()
{
	RCC->RCC_CSR |= (1<<0);
}


//=====================================================================

/**================================================================
 * @Fn			- MCAL_WDG_INIT
 * @brief 		- Get IWDG ready
 * @retval 		- none
 * Note			- none
 */
void MCAL_WDG_INIT()
{
	LSI_CLK_EN();

	IWDG->IWDG_KR &= ~(0xFFFF << 0);
	IWDG->IWDG_KR = 0xCCCC;
}


/**================================================================
 * @Fn			- MCAL_WDG_SET
 * @brief 		- Set IWDG prescaler and the time
 * param[in]	- prescaler: the value of prescaler divider
 * param[in]	- value: time value
 * @retval 		- none
 * Note			- none
 */
void MCAL_WDG_SET(uint32_t prescaler, uint32_t value)
{
	IWDG->IWDG_KR &= ~(0xFFFF << 0);
	IWDG->IWDG_KR = 0x5555;

	/*
	000: divider /4
	001: divider /8
	010: divider /16
	011: divider /32
	100: divider /64
	101: divider /128
	110: divider /256
	 */
	switch(prescaler)
	{
	case IWDG_PRESCALER_4:
	{
		IWDG->IWDG_PR = 0b000;
	}
	break;
	case IWDG_PRESCALER_8:
	{
		IWDG->IWDG_PR = 0b001;
	}
	break;
	case IWDG_PRESCALER_16:
	{
		IWDG->IWDG_PR = 0b010;
	}
	break;
	case IWDG_PRESCALER_32:
	{
		IWDG->IWDG_PR = 0b011;
	}
	break;
	case IWDG_PRESCALER_64:
	{
		IWDG->IWDG_PR = 0b100;
	}
	break;
	case IWDG_PRESCALER_128:
	{
		IWDG->IWDG_PR = 0b101;
	}
	break;
	case IWDG_PRESCALER_256:
	{
		IWDG->IWDG_PR = 0b110;
	}
	break;
	}

//	uint32_t rlr ;
//
//	switch(prescaler)
//	{
//	case IWDG_PRESCALER_4 :
//	{
//		rlr = ((time / 0.1)-1);
//	}
//	break;
//	case IWDG_PRESCALER_8 :
//	{
//		rlr = ((time / 0.2)-1);
//	}
//	break;
//	case IWDG_PRESCALER_16 :
//	{
//		rlr = ((time / 0.4)-1);
//	}
//	break;
//	case IWDG_PRESCALER_32 :
//	{
//		rlr = ((time / 0.8)-1);
//	}
//	break;
//	case IWDG_PRESCALER_64 :
//	{
//		rlr = ((time / 1.6)-1);
//	}
//	break;
//	case IWDG_PRESCALER_128 :
//	{
//		rlr = ((time / 3.2)-1);
//	}
//	break;
//	case IWDG_PRESCALER_256 :
//	{
//		rlr = ((time / 6.4)-1);
//	}
//	break;
//	}
//
//	IWDG->IWDG_RLR = rlr ;

}


/**================================================================
 * @Fn			- MCAL_WDG_RELOAD
 * @brief 		- Reset IWDG
 * @retval 		- none
 * Note			- none
 */
void MCAL_WDG_RELOAD()
{
	IWDG->IWDG_KR &= ~(0xFFFF << 0);
	IWDG->IWDG_KR = 0xAAAA;
}
