/*************************************************************************/
/* Author        : Kareem Abdelkader                                   			  */
/* Project       : ATmega32_Drivers			  	                             	  */
/* File          : TIMERS.h							                     		  */
/* Date          : 21/3/2024                                        			  */
/* Version       : V2                                                			  */
/* GitHub        : 		  */
/*************************************************************************/ 


#ifndef TIMERS_H_
#define TIMERS_H_

/* 
 *	Public Macros
 */
#define    NORMAL_MODE      			                            0
#define    PWM_OR_PHASE_COTROL                                      1
#define    CTC_MODE                                                 2
#define    FAST_PWM_MODE                                            3

#define    NON_PWM_NORMAL_PORT_OPRETATION                           0
#define    NON_PWM_TOGGLE_OC0_ON_COMPARE_MATCH                      1
#define    NON_PWM_CLEAR_OC0_ON_COMPARE_MATCH                       2
#define    NON_PWM_SET_OC0_ON_COMPARE_MATCH						    3


#define    FAST_PWM_NORMAL_PORT_OPRETATION                          0
#define    FAST_PWM_CLEAR_OC0_ON_COMPARE_MATCH__SET_OC0_ON_TOP      1
#define    FAST_PWM_SET_OC0_ON_COMPARE_MATCH__CLEAR_OC0_ON_TOP	  	2


#define    CLK_DIV_BY_0										 	    1
#define    CLK_DIV_BY_8										 	    2
#define    CLK_DIV_BY_64                                            3
#define    CLK_DIV_BY_256                                           4
#define    CLK_DIV_BY_1024                                          5
#define    ECS_ON_T0_FALLING_EDGE      								6
#define    ECS_ON_T0_RISING_EDGE       								7

#define	   RISING_EDGE												0
#define	   FALLING_EDGE												1

//==================================================================================

/**************************************************************************************************/
/**********************************WAVEFORM_GEN_MODE options***************************************/
/* 			  	                    0  NORMAL_MODE                                                */
/*                                  1  PWM_OR_PHASE_COTROL                                        */
/*                                  2  CTC_MODE                                                   */
/*                                  3  FAST_PWM_MODE                                              */
/**************************************************************************************************/
/**************************************************************************************************/
#define 	  WAVEFORM_GEN_MODE          FAST_PWM_MODE

/*********************************Control action on OC0 pin****************************************/
/**********************************for Non-PWM Mode options****************************************/
/* 			  	                    0  NORMAL_MODE                                                */
/*                                  1  PWM_OR_PHASE_COTROL                                        */
/*                                  2  CTC_MODE                                                   */
/*                                  3  FAST_PWM_MODE                                              */
/**************************************************************************************************/
/***********************************FAST_PWM_MODE options******************************************/
/*  0  FAST_PWM_NORMAL_PORT_OPRETATION                                                            */
/*  1  FAST_PWM_CLEAR_OC0_ON_COMPARE_MATCH__SET_OC0_ON_TOP    (non inverted mode)                 */
/*  2  FAST_PWM_SET_OC0_ON_COMPARE_MATCH__CLEAR_OC0_ON_TOP	   (inverted mode)                    */
/**************************************************************************************************/
/**************************************************************************************************/
#define 	 OC0_ACTION                 FAST_PWM_CLEAR_OC0_ON_COMPARE_MATCH__SET_OC0_ON_TOP

/**************************************************************************************************/
/**********************************PRESCALER_TYPE options******************************************/
/* 	TIMER_COUNTER_DISABLED              No clock source (Timer/Counter stopped).                  */
/*  CLK_DIV_BY_0				        (No   prescaling)                                         */
/*  CLK_DIV_BY_8				        (From prescaler)                                          */
/*  CLK_DIV_BY_64                       (From prescaler)                                          */
/* 	CLK_DIV_BY_256                      (From prescaler)                                          */
/*  CLK_DIV_BY_1024                     (From prescaler)                                          */
/*  ECS_ON_T0_FALLING_EDGE              External clock source on T0 pin. Clock on falling edge.   */
/*  ECS_ON_T0_RISING_EDGE               External clock source on T0 pin. Clock on rising edge     */
/* 	ECS_ON_T1_FALLING_EDGE              External clock source on T1 pin. Clock on falling edge.   */
/*  ECS_ON_T1_RISING_EDGE               External clock source on T1 pin. Clock on rising edge     */
/**************************************************************************************************/
/**************************************************************************************************/
#define 	 PRESCALER_TYPE     CLK_DIV_BY_8

#define 	 PRESCALER_MASK     0b11111000

//==================================================================================


/************************************************************************/
/*                            APIs                                      */
/************************************************************************/

void TIMER_voidTimer0Init(void);

void TIMER_voidTimer1Init(void);

void TIMER_voidTimer0SetCompareValue(u8 Copy_u8CompareValue);

void TIMER_voidTimer0SetCallBack(void (*Copy_pvNotificationFunction)(void));

void TIMER_voidTimer1ASetCompareValue(u16 Copy_u16CompareValue);

void TIMER_voidTimer1BSetCompareValue(u16 Copy_u16CompareValue);

void TIMER_voidTimer1SetInputCaptureValue(u16 Copy_u16CaptureValue);

void ICU_voidInit(void);

void ICU_voidSetTrigger(u8 Copy_u8TriggerSource);

u16 ICU_u16ReadInputCapture(void);

void ICU_voidInterruptDisbale(void);

void ICU_voidSetCallBack(void (*Copy_pvNotificationFunction)(void));



#endif /* TIMERS_H_ */