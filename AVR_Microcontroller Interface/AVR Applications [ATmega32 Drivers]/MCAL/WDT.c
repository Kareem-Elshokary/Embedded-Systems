/*************************************************************************/
/* Author        : Kareem Abdelkader	                                   			  	*/
/* Project       : ATmega32_Drivers		  	                             			  	*/
/* File          : WDT.c			                       				      	        */
/* Date          : 20/4/2024                                        				  	*/
/* Version       : V1                                                				    */
/* GitHub        : 		  */
/*************************************************************************/ 


/************************************************************************/
/*                            Includes                                  */
/************************************************************************/
#include "ATmega32.h"
#include "WDT.h"

//=========================================================================

void WDT_EN(u8 prescaler)
{
	SET_BIT(WDTCR,WDE);
	
	switch(prescaler)
	{
		case WDT_16K_PRESCALER:
		{
			CLR_BIT(WDTCR,WDP0);
			CLR_BIT(WDTCR,WDP1);
			CLR_BIT(WDTCR,WDP2);
		}
		break;
		case WDT_32K_PRESCALER:
		{
			SET_BIT(WDTCR,WDP0);
			CLR_BIT(WDTCR,WDP1);
			CLR_BIT(WDTCR,WDP2);
		}
		break;
		case WDT_64K_PRESCALER:
		{
			CLR_BIT(WDTCR,WDP0);
			SET_BIT(WDTCR,WDP1);
			CLR_BIT(WDTCR,WDP2);
		}
		break;
		case WDT_128K_PRESCALER:
		{
			SET_BIT(WDTCR,WDP0);
			SET_BIT(WDTCR,WDP1);
			CLR_BIT(WDTCR,WDP2);
		}
		break;
		case WDT_256K_PRESCALER:
		{
			CLR_BIT(WDTCR,WDP0);
			CLR_BIT(WDTCR,WDP1);
			SET_BIT(WDTCR,WDP2);
		}
		break;
		case WDT_512K_PRESCALER:
		{
			SET_BIT(WDTCR,WDP0);
			CLR_BIT(WDTCR,WDP1);
			SET_BIT(WDTCR,WDP2);
		}
		break;
		case WDT_1024K_PRESCALER:
		{
			CLR_BIT(WDTCR,WDP0);
			SET_BIT(WDTCR,WDP1);
			SET_BIT(WDTCR,WDP2);
		}
		break;
		case WDT_2048K_PRESCALER:
		{
			SET_BIT(WDTCR,WDP0);
			SET_BIT(WDTCR,WDP1);
			SET_BIT(WDTCR,WDP2);
		}
		break;
	}
}


void WDT_DIS()
{
	SET_BIT(WDTCR,WDE);
	SET_BIT(WDTCR,WDTOE);
	
	//Disable WDT
	WDTCR = 0x00;
}