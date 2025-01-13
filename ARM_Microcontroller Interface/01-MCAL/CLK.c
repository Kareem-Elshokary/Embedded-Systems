/*************************************************************************/
/* Author        : Kareem Abdelkader                                   			  	  	*/
/* Project       : STM32F103C8_Drivers  	                             			  	*/
/* File          : CLK.c        			                       				      	*/
/* Date          : 18/2/2024                                        				  	*/
/* Version       : V2                                                				    */
/* GitHub        : https://github.com/Kareem-Elshokary/Master_Embedded_systems          */
/*************************************************************************/

/*****************************
 * Includes
 ****************************/
#include "CLK.h"


//===========================================================================

/**=============================================
 * @Fn				- MCAL_RCC_SYSFREQ
 * @brief 			- Sets the clock source of the MCU
 * @param [in] 		- clock: Select the clock source from RCC_MODES_t
 * @param [out] 	- None
 * @retval 			- None
 * Note				- None
 */
void MCAL_RCC_SYSFREQ(RCC_MODES_t mode)
{
	switch(mode)
	{
	case HSI:
	{
		RCC->RCC_CR |= (1<<0);			//HSI ON
		RCC->RCC_CFGR &= ~(0b11<<0);	//HSI selected as system clock
	}
	break;
	case HSE:
	{
		RCC->RCC_CR |= (1<<16);				//HSE ON

		RCC->RCC_CFGR |= (1<<17);			//HSE divider for PLL entry

		RCC->RCC_CFGR |= (1<<16);			//PLL entry clock source, HSE oscillator clock selected as PLL input clock
		RCC->RCC_CFGR &= ~(0b1100<<18);

		RCC->RCC_CFGR |= (0b1100<<18);		//PLL multiplication factor, PLL input clock x 14

		RCC->RCC_CR |= (1<<24);				//PLL enable
		RCC->RCC_CFGR &=~ (0b11 << 0);		//PLL selected as system clock
		RCC->RCC_CFGR |=  (0b10 << 0);
	}
	break;
	case PLL:
	{
		RCC->RCC_CR |= (1<<0);				//HSI ON

		RCC->RCC_CFGR &= ~(1<<16);			//HSI oscillator clock / 2 selected as PLL input clock
		RCC->RCC_CFGR &= ~(0b1100<<18);

		RCC->RCC_CFGR |= (0b0111<<18);		//PLL multiplication factor, PLL input clock x 9

		RCC->RCC_CR |= (1<<24);				//PLL enable
		RCC->RCC_CFGR &=~ (0b11 << 0);		//PLL selected as system clock
		RCC->RCC_CFGR |=  (0b10 << 0);
	}
	break;
	}

}


/**=============================================
 * @Fn				- MCAL_RCC_GetHCLKFreq
 * @brief 			- Return the frequency value of AHB bus
 * @param [in] 		- none
 * @param [out] 	- none
 * @retval 			- frequency value of AHB bus
 * Note				- None
 */
uint32_t MCAL_RCC_GetHCLKFreq(void){

	/*
	0xxx: SYSCLK not divided
	1000: SYSCLK divided by 2
	1001: SYSCLK divided by 4
	1010: SYSCLK divided by 8
	1011: SYSCLK divided by 16
	1100: SYSCLK divided by 64
	1101: SYSCLK divided by 128
	1110: SYSCLK divided by 256
	1111: SYSCLK divided by 512
	 */

	return RCC->RCC_CFGR &= ~(0b1111 << 4);
}


/**=============================================
 * @Fn				- MCAL_RCC_GetPCLK1Freq
 * @brief 			- Return the frequency value of APB1 bus
 * @param [in] 		- none
 * @param [out] 	- none
 * @retval 			- frequency value of APB1 bus
 * Note				- None
 */
uint32_t MCAL_RCC_GetPCLK1Freq(RCC_MODES_t mode)
{

	/*
	Warning: the software has to set correctly these bits to not exceed 36 MHz on this domain.
	0xx: HCLK not divided
	100: HCLK divided by 2
	101: HCLK divided by 4
	110: HCLK divided by 8
	111: HCLK divided by 16
	 */

	switch(mode)
	{
	case HSI:
	{
		return RCC->RCC_CFGR &= ~(0b111 << 8);
	}
	break;
	case HSE:
	{
		return RCC->RCC_CFGR |= (0b100 << 8);
	}
	break;
	case PLL:
	{
		return RCC->RCC_CFGR &= ~(0b111 << 8);
	}
	break;
	}
}


/**=============================================
 * @Fn				- MCAL_RCC_GetPCLK2Freq
 * @brief 			- Return the frequency value of APB2 bus
 * @param [in] 		- none
 * @param [out] 	- none
 * @retval 			- frequency value of APB2 bus
 * Note				- None
 */
uint32_t MCAL_RCC_GetPCLK2Freq(void)
{
	/*
	0xx: HCLK not divided
	100: HCLK divided by 2
	101: HCLK divided by 4
	110: HCLK divided by 8
	111: HCLK divided by 16
	 */
	return RCC->RCC_CFGR &= ~(0b111 << 11);
}


/**=============================================
 * @Fn				- MCAL_RCC_GetPCLK2_ADCFreq
 * @brief 			- Return the frequency value of ADC
 * @param [in] 		- none
 * @param [out] 	- none
 * @retval 			- frequency value of ADC
 * Note				- None
 */
uint32_t MCAL_RCC_GetPCLK2_ADCFreq(void)
{

	/*
	00: PCLK2 divided by 2
	01: PCLK2 divided by 4
	10: PCLK2 divided by 6
	11: PCLK2 divided by 8
	 */

	return RCC->RCC_CFGR &= ~(0b01 << 14);
}


/**================================================================
 * @Fn			-MCAL_RCC_PERIPHERAL_EN
 * @brief 		-RCC enable the MCU Peripherals
 * @param[in] 	-bus:to select the bus
 * @param[in] 	-peripheral:to select which peripheral to enable
 * @param[out] 	-none
 * @retval		-none
 * Note			-none
 */
void MCAL_RCC_PERIPHERAL_EN(RCC_BUSES_t bus, uint16_t periphral)
{
	switch(bus)
	{
	case AHB:
	{
		RCC->RCC_AHBENR &= ~( Enable << periphral );
		RCC->RCC_AHBENR |= ( Enable << periphral );
	}
	break;
	case APB1:
	{
		RCC->RCC_APB1ENR &= ~( Enable << periphral );
		RCC->RCC_APB1ENR |= ( Enable << periphral );
	}
	break;
	case APB2:
	{
		RCC->RCC_APB2ENR &= ~( Enable << periphral );
		RCC->RCC_APB2ENR |= ( Enable << periphral );
	}
	break;
	}
}



/**================================================================
 * @Fn			-MCAL_RCC_PERIPHERAL_DIS
 * @brief 		-RCC enable the MCU Peripherals
 * @param[in] 	-bus:to select the bus
 * @param[in] 	-peripheral:to select which peripheral to enable
 * @param[out] 	-none
 * @retval		-none
 * Note			-none
 */
void MCAL_RCC_PERIPHERAL_DIS(RCC_BUSES_t bus, uint16_t periphral)
{
	switch(bus)
	{
	case AHB:
	{
		break;
	}
	break;
	case APB1:
	{
		RCC->RCC_APB1RSTR &= ~( Disable << periphral );
		RCC->RCC_APB1RSTR &= ~( Disable << periphral );
	}
	break;
	case APB2:
	{
		RCC->RCC_APB2RSTR &= ~( Disable << periphral );
		RCC->RCC_APB2RSTR &= ~( Disable << periphral );
	}
	break;
	}
}
