/*************************************************************************/
/* Author        : Kareem Abdelkader                                   			  	  	*/
/* Project       : ATmega32_Drivers		  	                             			  	*/
/* File          : EXTINT.h						                   				      	*/
/* Date          : 22/3/2024                                        				  	*/
/* Version       : V1                                                				    */
/* GitHub        : 		        */
/*************************************************************************/

#ifndef EXTINT_INTERFACE_H_
#define EXTINT_INTERFACE_H_

/*
EXT_Init_DIR
EXT_Init_NORMAL
*/
#define EXT_Init_NORMAL
#ifdef EXT_Init_DIR

/*
 * EXTINT_EN
 * EXTINT_DIS_EN
 */
#define EXT0  EXTINT_DIS_EN
#define EXT1  EXTINT_EN
#define EXT2  EXTINT_DIS_EN

/*
 * RISING_EDGE
 * FALLING_EDGE
 */
#if EXT0 == EXTINT_EN
#define EXT0_ControlSens  FALLING_EDGE
#endif

#if EXT1 == EXTINT_EN
#define EXT1_ControlSens  FALLING_EDGE
#endif

#if EXT2 == EXTINT_EN
#define EXT1_ControlSens  FALLING_EDGE
#endif


#endif
/* End of----->   #ifdef EXT_Init_DIR*/

/*******************************************************************************************/
#define EXT0_ID (u8)(0)
#define EXT1_ID (u8)(1)
#define EXT2_ID (u8)(2)

#define FALLING_EDGE 0
#define RISING_EDGE  1

/*******************************************************************************************/

/************************************************************************/
/*                            APIs                                      */
/************************************************************************/

void EXTINT_voidInitDir(void);

//FOR Example:  EXTINT_voidInit(EXT0_ID,FALLING_EDGE)
void EXTINT_voidInit(u8 copy_u8ExtNum,u8 copy_u8ControlSens) ;

void EXTINT_voidSetCallBack(  void (*ptr_ext)(void) ,u8 copy_u8ExtNum );

/*******************************************************************************************/

#endif /* EXTINT_INTERFACE_H_ */
