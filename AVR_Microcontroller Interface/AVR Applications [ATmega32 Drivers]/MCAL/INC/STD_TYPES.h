/*************************************************************************/
/* Author        : Kareem Abdelkader                                   			  	  	*/
/* Project       : ATmega32_Drivers		  	                             			  	*/
/* File          : STD_TYPES.h					                     			      	*/
/* Date          : 21/3/2024                                        				  	*/
/* Version       : V1                                                				    */
/* GitHub        : 		        */
/*************************************************************************/

#ifndef _STD_TYPES_H_
#define _STD_TYPES_H_


/*********************************
 * 	Includes
 ********************************/
#include "stdint.h"
#include "stdio.h"


//===========================================================================


/*
 * unSigned Data Types
 */
typedef unsigned char           u8;
typedef unsigned short int      u16;
typedef unsigned long int       u32;
typedef unsigned long long int  u64;

/*
 * signed Data Types
 */
typedef signed char             s8;
typedef signed short int        s16;
typedef signed long int         s32;
typedef signed long long int    s64;

/*
 * Floating point Types
 */
typedef float                   f32;
typedef double                  f64;

/*
 * Address NULL
 */

#define NULL ( (void *) 0x00)

#endif /* _STD_TYPES_H */
