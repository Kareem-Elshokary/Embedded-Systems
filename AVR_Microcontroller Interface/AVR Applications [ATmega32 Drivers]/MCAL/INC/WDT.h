/*************************************************************************/
/* Author        : Kareem Abdelkader	                                   			  	*/
/* Project       : ATmega32_Drivers		  	                             			  	*/
/* File          : WDT.h			                       				      	        */
/* Date          : 20/4/2024                                        				  	*/
/* Version       : V1                                                				    */
/* GitHub        : 		  */
/*************************************************************************/


#ifndef WDT_H_
#define WDT_H_

/************************************************************************/
/*                        User Configuration                            */
/************************************************************************/

#define WDTOE	  4	//WDTOE: Watchdog Turn-off Enable
#define WDE		  3	//WDE: Watchdog Enable
#define WDP2	  2	//Watchdog Timer Prescaler 2, 1, and 0
#define WDP1	  1
#define WDP0	  0

//Prescaler (Number of WDT Oscillator Cycles)
#define WDT_16K_PRESCALER		  0	//16.3 ms	at VCC = 5.0V
#define WDT_32K_PRESCALER		  1	//32.5 ms
#define WDT_64K_PRESCALER		  2	//65 ms
#define WDT_128K_PRESCALER		3	//0.13 s
#define WDT_256K_PRESCALER		4	//0.26 s
#define WDT_512K_PRESCALER		5	//0.52 s
#define WDT_1024K_PRESCALER		6	//1.0 s
#define WDT_2048K_PRESCALER		7	//2.1 s



//===============================================================

/************************************************************************/
/*                            APIs                                      */
/************************************************************************/

void WDT_EN(u8 prescaler);
void WDT_DIS();



#endif /* WDT_H_ */