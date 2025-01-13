/*************************************************************************/
/* Author        : Kareem Abdelkader                                   			  */
/* Project       : ATmega32_Drivers		  	                             	  */
/* File          : ATmega32.h				                     		  */
/* Date          : 21/3/2024                                        			  */
/* Version       : V1                                                			  */
/* GitHub        : 		  */
/*************************************************************************/


#ifndef ATMEGA32_H_
#define ATMEGA32_H_

/************************************************************************/
/*                            Includes                                  */
/************************************************************************/
#include "STD_TYPES.H"
#include "BIT_MATH.h"

//========================================================================

/************************************************************************/
/*                          Register Macros                             */
/************************************************************************/

/*
		DIO
*/
/*************** Group A Registers *************/
#define PORTA_REG	*((volatile u8*)0x3B)
#define DDRA_REG	*((volatile u8*)0x3A)
#define PINA_REG	*((volatile u8*)0x39)


/*************** Group B Registers *************/
#define PORTB_REG  *((volatile u8*)0x38)
#define DDRB_REG   *((volatile u8*)0x37)
#define PINB_REG   *((volatile u8*)0x36)


/*************** Group C Registers *************/
#define PORTC_REG  *((volatile u8*)0x35)
#define DDRC_REG   *((volatile u8*)0x34)
#define PINC_REG   *((volatile u8*)0x33)


/*************** Group D Registers ************/
#define PORTD_REG  *((volatile u8*)0x32)
#define DDRD_REG   *((volatile u8*)0x31)
#define PIND_REG   *((volatile u8*)0x30)


/*
		GIE
*/
#define GIE_SREG  *((volatile u8*) 0x5F)
#define I_bit     7


/*
		EXTI
*/
#define EXTINT_DIS_EN   0
#define EXTINT_EN       1

#define MCUCR_REG  *((volatile u8 *)0x55)
#define MCUCR_ISC00 0
#define MCUCR_ISC01 1
#define MCUCR_ISC10 2
#define MCUCR_ISC11 3

#define MCUCSR_REG *((volatile u8 *)0x54)
#define MCUCSR_ISC2 6

#define GICR_REG   *((volatile u8 *)0x5B)
#define GICR_INT1 7
#define GICR_INT0 6
#define GICR_INT2 5

#define GIFR_REG   *((volatile u8 *)0x5A)
#define GIFR_INTF1 7
#define GIFR_INTF0 6
#define GIFR_INTF2 5


/*
	TIM0
*/
#define     TIM0_u8_TCCR0_REG		      *((volatile u8 *)(0x53))		// Timer/Counter0 Control Register
#define     TIM0_u8_TCCR0_FOC0            7								// Force On Compare
#define     TIM0_u8_TCCR0_WGM00           6                             // Wave Generation Mode 0
#define     TIM0_u8_TCCR0_COM01           5                             // Compare match output mode 1
#define     TIM0_u8_TCCR0_COM00           4                             // Compare match output mode 0
#define     TIM0_u8_TCCR0_WGM01           3                             // Wave Generation Mode 1
#define     TIM0_u8_TCCR0_CS02            2                             // Clock Select 02
#define     TIM0_u8_TCCR0_CS01            1                             // Clock Select 01
#define     TIM0_u8_TCCR0_CS00            0                             // Clock Select 00

#define     TIM0_u8_TCNT0_REG		      *((volatile u8 *)(0x52))		// Timer/Counter0 Register

#define     TIM0_u8_OCR0_REG		      *((volatile u8 *)(0x5C))		// Output Compare0 Register

#define     TIM0_u8_TIMSK_REG		      *((volatile u8 *)(0x59))		// Timer0 Mask Register
#define     TIM0_u8_TIMSK_TOIE0           0								// Timer Overflow Interrupt Enable
#define     TIM0_u8_TIMSK_OCIE0           1                             // Timer On Compare Interrupt Enable
#define		TIM0_u8_TIMSK_TOIE1		      2								// Timer/Counter1 Overflow Interrupt Enable
#define		TIM0_u8_TIMSK_OCIE1B	      3								// Timer/Counter1 Output Compare B Interrupt Enable
#define		TIM0_u8_TIMSK_OCIE1A	      4								// Timer/Counter1 Output Compare A Interrupt Enable
#define		TIM0_u8_TIMSK_TICIE1	      5								// Timer/Counter1 Input Capture Interrupt Enable
#define     TIM0_u8_TIMSK_TOIE2           6								// Timer/Counter2 Overflow Interrupt Enable
#define     TIM0_u8_TIMSK_OCIE2           7								// Timer/Counter2 Output Compare Interrupt Enable

#define     TIM0_u8_TIFR_REG              *((volatile u8 *)(0x58))		// Timer/Counter0 Interrupt Flag Register
#define     TIM0_u8_TIFR_TOV0             0								// Timer/Counter0 Overflow flag
#define     TIM0_u8_TIFR_OCF0             1                             // Timer/Counter0 Output Compare flag
#define		TIM0_u8_TIFR_TOV1		      2								// Timer/Counter1 Overflow Flag
#define		TIM0_u8_TIFR_OCF1B		      3								// Timer/Counter1 Output Compare B Flag
#define		TIM0_u8_TIFR_OCF1A		      4								// Timer/Counter1 Output Compare A Flag
#define		TIM0_u8_TIFR_ICF1		      5								// Timer/Counter1 Input Capture Flag
#define     TIM0_u8_TIFR_TOV2             6								// Timer/Counter2 Overflow flag
#define     TIM0_u8_TIFR_OCF2             7                             // Timer/Counter2 Output Compare flag


/*
	TIM1
*/
#define		TIM1_u8_TCCR1A_REG			  *((volatile u8 *)(0x4F))		// Timer/Counter 1 Control Register A
#define     TIM1_u8_TCCR1A_WGM10	      0								// Wave Generation Mode 0 Bit
#define     TIM1_u8_TCCR1A_WGM11	      1								// Wave Generation Mode 1 Bit
#define     TIM1_u8_TCCR1A_FOC1B	      2								// Force Output Compare B Bit
#define     TIM1_u8_TCCR1A_FOC1A	      3								// Force Output Compare A Bit
#define     TIM1_u8_TCCR1A_COM1B0	      4								// Compare Output Mode Channel B 0 Bit
#define     TIM1_u8_TCCR1A_COM1B1	      5								// Compare Output Mode Channel B 1 Bit
#define     TIM1_u8_TCCR1A_COM1A0	      6								// Compare Output Mode Channel A 0 Bit
#define     TIM1_u8_TCCR1A_COM1A1	      7								// Compare Output Mode Channel A 1 Bit

#define		TIM1_u8_TCCR1B_REG			  *((volatile u8 *)(0x4E))		// Timer/Counter 1 Control Register B
#define     TIM1_u8_TCCR1B_CS10			  0								// Clock Selection 0 Bit
#define     TIM1_u8_TCCR1B_CS11			  1								// Clock Selection 1 Bit
#define     TIM1_u8_TCCR1B_CS12			  2								// Clock Selection 2 Bit
#define     TIM1_u8_TCCR1B_WGM12 		  3								// Wave Generation Mode 2 Bit
#define     TIM1_u8_TCCR1B_WGM13		  4								// Wave Generation Mode 3 Bit
#define     TIM1_u8_TCCR1B_ICES1		  6								// Input Capture Edge Select
#define     TIM1_u8_TCCR1B_ICNC1		  7								// Input Capture Noise Canceler

#define		TIM1_u8_TCNT1L_REG			  *((volatile u8 *)(0x4C))		// Timer/Counter 1 Low Register
#define		TIM1_u8_TCNT1H_REG			  *((volatile u8 *)(0x4D))		// Timer/Counter 1 High Register
#define		TIM1_u16_TCNT1_REG			  *((volatile u16 *)(0x4C))		// Timer/Counter 1 Register

#define		TIM1_u8_OCR1AL_REG			  *((volatile u8 *)(0x4A))		// Output Compare 1 Channel A Low Register
#define		TIM1_u8_OCR1AH_REG			  *((volatile u8 *)(0x4B))		// Output Compare 1 Channel A High Register
#define     TIM1_u16_OCR1A_REG			  *((volatile u16 *)(0x4A))		// Output Compare 1 Channel A Register

#define		TIM1_u8_OCR1BL_REG			  *((volatile u8 *)(0x48))		// Output Compare 1 Channel B Low Register
#define		TIM1_u8_OCR1BH_REG			  *((volatile u8 *)(0x49))		// Output Compare 1 Channel B High Register
#define     TIM1_u16_OCR1B_REG			  *((volatile u16 *)(0x48))		// Output Compare 1 Channel B Register

#define		TIM1_u8_ICR1L_REG			  *((volatile u8 *)(0x46))		// Input Capture 1 Low Register
#define		TIM1_u8_ICR1H_REG			  *((volatile u8 *)(0x47))		// Input Capture 1 High Register
#define     TIM1_u16_ICR1_REG			  *((volatile u16 *)(0x46))		// Input Capture 1 Register


/*
	WDT
*/
#define		WDTCR			*((volatile u8 *)(0x41))			// Watchdog Timer Control Register




#endif /* ATMEGA32_H_ */