/*************************************************************************/
/* Author        : Kareem Abdelkader                                   			  	  	*/
/* Project       : ATmega32_Drivers		  	                             			  	*/
/* File          : BIT_MATH.h					                     			      	*/
/* Date          : 21/3/2024                                        				  	*/
/* Version       : V1                                                				    */
/* GitHub        : 		        */
/*************************************************************************/


#ifndef _BIT_MATH_H_
#define _BIT_MATH_H_


/*********************************
 * 	Bit Math
 ********************************/

// Set Specific Bit
#define SET_BIT(REG,BIT)			(REG |= (1<<BIT))

// Clear Specific Bit
#define CLR_BIT(REG,BIT)			(REG &= ~(1<<BIT))

// Toggle Specific Bit
#define TOG_BIT(REG,BIT)			(REG ^= (1<<BIT))

// Get Specific Bit Value
#define GET_BIT(REG,BIT)			((REG>>BIT) & 0x01)

// Assign Value to a Specific Bit
#define ASS_BIT(REG,BIT,VAL)		(VAL==0)? CLR_BIT(REG,BIT) : SET_BIT(REG,BIT)

// Set All Bits
#define SET_PORT(VAR,PORT)			((VAR) =  (PORT))


#define ZERO     (u8)0
#define	ONE      (u8)1
#define	TWO      (u8)2
#define	THREE    (u8)3
#define	FOUR     (u8)4
#define	FIVE     (u8)5
#define	SIX      (u8)6
#define	SEVEN    (u8)7
#define	EIGHT    (u8)8
#define	NINE     (u8)9




#endif
