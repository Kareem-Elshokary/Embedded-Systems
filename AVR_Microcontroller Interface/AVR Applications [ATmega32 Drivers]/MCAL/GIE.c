/*************************************************************************/
/* Author        : Kareem Abdelkader                                   			  	  	*/
/* Project       : ATmega32_Drivers		  	                             			  	*/
/* File          : GIE.c					                       				      	*/
/* Date          : 22/3/2024                                        				  	*/
/* Version       : V1                                                				    */
/* GitHub        : https://github.com/Kareem-Elshokary/AVR_ATmega32_DRIVERS		        */
/*************************************************************************/


/************************************************************************/
/*                            Includes                                  */
/************************************************************************/
#include "ATmega32.h"
#include "GIE.h"


//========================================================================



void GIE_Enable(void)
{
     SET_BIT(GIE_SREG,I_bit);

}

void GIE_Disable(void)
{
 CLR_BIT(GIE_SREG,I_bit);

}


