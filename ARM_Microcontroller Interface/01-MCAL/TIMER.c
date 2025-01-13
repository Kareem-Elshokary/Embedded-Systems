/*************************************************************************/
/* Author        : Kareem Abdelkader                                   			  	  	*/
/* Project       : STM32F103C8_Drivers  	                             			  	*/
/* File          : TIMER.c		     		                       				      	*/
/* Date          : 24/2/2024                                        				  	*/
/* Version       : V1                                                				    */
/* GitHub        : https://github.com/Kareem-Elshokary/Master_Embedded_systems          */
/*************************************************************************/

/*****************************
 * Includes
 ****************************/
#include "TIMER.h"


//===========================================================================

/*****************************
 * Generic Variables
 ****************************/
uint16_t Timer_ticks;
uint16_t No_of_overflow;
uint8_t Delay_Flag = 1;


/*****************************
 * Generic Function
 ****************************/

void TIMER_IRQ_EN(NVIC_REG_t* NVICx, TIMER_REG_t* TIMx)
{
	if( TIMx == TIM2)
	{
		NVIC_IRQ_EN(NVICx->NVIC_ISER[0], TIM2_);
	}
	else if( TIMx == TIM3)
	{
		NVIC_IRQ_EN(NVICx->NVIC_ISER[0], TIM3_);
	}
	else if( TIMx == TIM4)
	{
		NVIC_IRQ_EN(NVICx->NVIC_ISER[0], TIM4_);
	}
}


void TIMER_IRQ_DIS(NVIC_REG_t* NVICx, TIMER_REG_t* TIMx)
{
	if( TIMx == TIM2)
	{
		NVIC_IRQ_EN(NVICx->NVIC_ICER[0], TIM2_);
	}
	else if( TIMx == TIM3)
	{
		NVIC_IRQ_EN(NVICx->NVIC_ICER[0], TIM3_);
	}
	else if( TIMx == TIM4)
	{
		NVIC_IRQ_EN(NVICx->NVIC_ICER[0], TIM4_);
	}
}


void (*ptrF_Timer2) (void);
void (*ptrF_Timer3) (void);
void (*ptrF_Timer4) (void);


//===========================================================================

/**================================================================
 * @Fn			- MCAL_TIMER_INIT
 * @brief 		- Initializes the TIMx
 * @param [in] 	- TIMx: x can be (2:5 depend on the device used) to select the TIM peripheral
 * @param [in] 	- reload: reload value
 * @retval 		- none
 * Note			- none
 */
void MCAL_TIMER_INIT(TIMER_REG_t* TIMx, uint16_t reload)
{
	// RCC enable for TIMx
	if(TIMx == TIM2)
	{
		MCAL_RCC_PERIPHERAL_EN(APB1, RCC_TIM2);
	}
	else if(TIMx == TIM3)
	{
		MCAL_RCC_PERIPHERAL_EN(APB1, RCC_TIM3);
	}
	else if(TIMx == TIM4)
	{
		MCAL_RCC_PERIPHERAL_EN(APB1, RCC_TIM4);
	}

	// Disable timer
	MCAL_TIMER_STOP(TIMx);

	// Relaod value
	// Bits 15:0 ARR[15:0]: Prescaler value
	TIMx->TIMx_ARR = reload;

	// Set prescaler
	// Bits 15:0 PSC[15:0]: Prescaler value
	TIMx->TIMx_PSC = (uint16_t)0;

	// Bit 0 UG: Update generation
	TIMx->TIMx_EGR |= (1<<0);

	// Enable timer
	MCAL_TIMER_START(TIMx);

	// Enable NVIC
	TIMER_IRQ_EN(NVIC,TIMx);
}


void setTimerClockSource(uint32_t clockSource)
{

}


/**================================================================
 * @Fn			- MCAL_TIMER_START
 * @brief 		- Enable TIMx counter
 * @param [in] 	- TIMx: x can be (2:5 depend on the device used) to select the TIM peripheral
 * @retval 		- none
 * Note			- none
 */
void MCAL_TIMER_START(TIMER_REG_t* TIMx)
{
	/*
	 * Bit 0 CEN: Counter enable
		0: Counter disabled
		1: Counter enabled
	 */
	if(TIMx == TIM2)
	{
		TIMx->TIMx_CR1 |= (1<<0);
	}
	else if(TIMx == TIM3)
	{
		TIMx->TIMx_CR1 |= (1<<0);
	}
	else if(TIMx == TIM4)
	{
		TIMx->TIMx_CR1 |= (1<<0);
	}
}


/**================================================================
 * @Fn			- MCAL_TIMER_STOP
 * @brief 		- Disable TIMx counter
 * @param [in] 	- TIMx: x can be (2:5 depend on the device used) to select the TIM peripheral
 * @retval 		- none
 * Note			- none
 */
void MCAL_TIMER_STOP(TIMER_REG_t* TIMx)
{
	/*
	 * Bit 0 CEN: Counter enable
			0: Counter disabled
			1: Counter enabled
	 */
	if(TIMx == TIM2)
	{
		TIMx->TIMx_CR1 &= ~(1<<0);
	}
	else if(TIMx == TIM3)
	{
		TIMx->TIMx_CR1 &= ~(1<<0);
	}
	else if(TIMx == TIM4)
	{
		TIMx->TIMx_CR1 &= ~(1<<0);
	}
}


/**================================================================
 * @Fn			- MCAL_TIMER_GETCOUNT
 * @brief 		- Return current timer count
 * @param [in] 	- TIMx: x can be (2:5 depend on the device used) to select the TIM peripheral
 * @param [in] 	- clk: clk frequency
 * @param [in] 	- reload: reload value
 * @retval 		- none
 * Note			- none
 */
uint32_t MCAL_TIMER_GETCOUNT(TIMER_REG_t* TIMx, uint32_t clk, uint16_t reload)
{
	MCAL_TIMER_STOP(TIMx);
	Timer_ticks = TIMx->TIMx_CNT;
	uint32_t x;
	x = ( (Timer_ticks + (No_of_overflow*reload)) / (clk/1000000));
	No_of_overflow = 0;
	Timer_ticks = 0;
	return x;
}


/**================================================================
 * @Fn			- MCAL_TIMER_CLRCOUNT
 * @brief 		- Reset timer count
 * @param [in] 	- TIMx: x can be (2:5 depend on the device used) to select the TIM peripheral
 * @retval 		- none
 * Note			- none
 */
void MCAL_TIMER_CLRCOUNT(TIMER_REG_t* TIMx)
{
	TIMx->TIMx_CNT = 0;
}


/**================================================================
 * @Fn			- MCAL_TIMER_CAPTMODE_SET
 * @brief 		- Configure TIMx for capture mode
 * @param [in] 	- TIMx: x can be (2:5 depend on the device used) to select the TIM peripheral
 * @param [in] 	- channel: selected channel (1:4)
 * @param [in] 	- captureEdge: capture Edge
 * @retval 		- none
 * Note			- none
 */
void MCAL_TIMER_CAPTMODE_SET(TIMER_REG_t* TIMx, uint8_t channel, uint32_t captureEdge)
{

}


/**================================================================
 * @Fn			- MCAL_TIMER_CAPTIP_GETVALUE
 * @brief 		- Read and return captured value
 * @param [in] 	- channel: selected channel (1:4)
 * @retval 		- captured value
 * Note			- none
 */
//uint32_t MCAL_TIMER_CAPTIP_GETVALUE(uint8_t channel)
//{
//
//}


/**================================================================
 * @Fn			- MCAL_TIMER_INIT
 * @brief 		- Configure TIMx for PWM mode
 * @param [in] 	- TIMx: x can be (2:5 depend on the device used) to select the TIM peripheral
 * @param [in] 	- prescaler: prescaler number
 * @param [in] 	- count: count value
 * @retval 		- none
 * Note			- none
 */
void MCAL_TIMER_PWM_SET(PWM_Modes_t mode, uint8_t channel, double duty_cycle, uint32_t freq, uint32_t prescaler)
{
	// RCC enable
	MCAL_RCC_PERIPHERAL_EN(APB1, RCC_TIM3);
	MCAL_RCC_PERIPHERAL_EN(APB2, RCC_GPIOA);
	MCAL_RCC_PERIPHERAL_EN(APB2, RCC_GPIOB);
	MCAL_RCC_PERIPHERAL_EN(APB2, RCC_AFIO);

	// Disable timer3
	MCAL_TIMER_STOP(TIM3);

	uint32_t TIM_ARR, TIM_CRR;
	TIM_ARR = (1000000 / freq );
	TIM_CRR = ((duty_cycle /100) * (float)TIM_ARR );

	// Timer3 ch_1 --> A6  <> timer3 ch_2 --> A7 <> timer3 ch_3 --> B0 <> timer3 ch_4 --> B1
	switch(channel)
	{
	case CH1:
	{
		MCAL_GPIO_INIT(GPIOA, PIN6, OUTPUT_AF_PP, SPEED_50MHz);
		TIM3->TIMx_CCMR1 &=~ (0b11 << 0);
		TIM3->TIMx_CCMR1 |= (1 << 3);
		TIM3->TIMx_CCER |= (1 << 0);
		if(mode == PWM_MODE1)
		{
			TIM3->TIMx_CCMR1 |= (0b110<<4);
		}
		else if(mode == PWM_MODE2)
		{
			TIM3->TIMx_CCMR1 |= (0b111<<4);
		}
		TIM3->TIMx_CCR1 =  TIM_CRR ;
		TIM3->TIMx_DIER |= (0b11 << 0);
		TIM3->TIMx_EGR |= (1 << 1);
		TIM3->TIMx_CCER &=~ (1 << 1);
	}
	break;
	case CH2:
	{
		MCAL_GPIO_INIT(GPIOA, PIN7, OUTPUT_AF_PP, SPEED_50MHz);
		TIM3->TIMx_CCMR1 &=~ (0b11 << 8);
		TIM3->TIMx_CCMR1 |= (1 << 11);
		TIM3->TIMx_CCER |= (1 << 4);
		if(mode == PWM_MODE1)
		{
			TIM3->TIMx_CCMR1 |= (0b110<<12);
		}
		else if(mode == PWM_MODE2)
		{
			TIM3->TIMx_CCMR1 |= (0b111<<12);
		}
		TIM3->TIMx_CCR2 = TIM_CRR ;
		TIM3->TIMx_DIER |= (0b101 << 0);
		TIM3->TIMx_EGR |= (1 << 2);
		TIM3->TIMx_CCER &=~ (1 << 5);
	}
	break;
	case CH3:
	{
		MCAL_GPIO_INIT(GPIOB, PIN0, OUTPUT_AF_PP, SPEED_50MHz);
		TIM3->TIMx_CCMR2 &=~ (0b11 << 0);
		TIM3->TIMx_CCMR2 |= (1 << 3);
		TIM3->TIMx_CCER |= (1 << 8);
		if(mode == PWM_MODE1)
		{
			TIM3->TIMx_CCMR2 |= (0b110<<4);
		}
		else if(mode == PWM_MODE2)
		{
			TIM3->TIMx_CCMR2 |= (0b111<<4);
		}
		TIM3->TIMx_CCR3 = TIM_CRR ;
		TIM3->TIMx_DIER |= (0b1001 << 0);
		TIM3->TIMx_EGR |= (1 << 3);
		TIM3->TIMx_CCER &=~ (1 << 9);
	}
	break;
	case CH4:
	{
		MCAL_GPIO_INIT(GPIOB, PIN1, OUTPUT_AF_PP, SPEED_50MHz);
		TIM3->TIMx_CCMR2 &=~ (0b11 << 8);
		TIM3->TIMx_CCMR2 |= (1 << 11);
		TIM3->TIMx_CCER |= (1 << 12);
		if(mode == PWM_MODE1)
		{
			TIM3->TIMx_CCMR2 |= (0b110<<12);
		}
		else if(mode == PWM_MODE2)
		{
			TIM3->TIMx_CCMR2 |= (0b111<<12);
		}
		TIM3->TIMx_CCR4 = TIM_CRR ;
		TIM3->TIMx_DIER |= (0b10001 << 0);
		TIM3->TIMx_EGR |= (1 << 4);
		TIM3->TIMx_CCER &=~ (1 << 13);
	}
	break;
	}

	TIM3->TIMx_CR1 |= (1 << 7);
	TIM3->TIMx_ARR = TIM_ARR ;
	TIM3->TIMx_PSC = prescaler ;
	TIM3->TIMx_EGR |= (1 << 0);
	// Enable TIM3
	MCAL_TIMER_START(TIM3);

}


/**================================================================
 * @Fn			- MCAL_TIMER_Delay
 * @brief 		- Configure TIMx for delay mode
 * @param [in] 	- time: hold value
 * @param [in] 	- U: hold millisecond / microsecond
 * @param [in] 	- clk: clk freq
 * @retval 		- none
 * Note			- none
 */
void MCAL_TIMER_Delay(uint16_t time,uint8_t U,uint32_t clk)
{
	MCAL_RCC_PERIPHERAL_EN(APB1, RCC_TIM2);

	// Disable timer
	MCAL_TIMER_STOP(TIM2);

	char user_flage=1;
	uint32_t user_top=0;
	uint32_t user_pre=1;
	uint32_t unit =1000;
	uint8_t  increase=2;

	if (U == ms){
		unit = 1000;
		if (time > 3000)increase = 100;
		else increase = 10;
	}
	else {
		unit = 1000000;
		if (time > 3000)increase = 10;
		else increase = 5;
	}

	while(user_flage==1){
		user_top = (clk/unit*time)/( user_pre );
		if(user_top>=32000){

			if(user_pre>65530){
				user_pre=65530;
				user_flage=0;
			}
			else user_pre+=increase;

		}
		else{
			user_flage=0;
		}
	}


	// Disable timer
	MCAL_TIMER_STOP(TIM2);

	// Only counter overflow/underflow generates an update
	TIM2->TIMx_CR1 |= (1<<2);

	// Update interrupt enabled
	TIM2->TIMx_DIER |= (1<<0);

	// frec peak value
	TIM2->TIMx_ARR = user_top;

	// Prescaller
	TIM2->TIMx_PSC = (user_pre - 1);

	// Re-initialize the counter and generates an update of the registers
	TIM2->TIMx_EGR |= (1<<0);

	// Enable the timer
	MCAL_TIMER_START(TIM2);

	Delay_Flag = 1;

	TIMER_IRQ_EN(NVIC,TIM2);

	while(Delay_Flag){

	}
}


//==========================================================================================

void TIM2_IRQHandler()
{
	//Bit 0 UIF: Update interrupt flag
	TIM2->TIMx_SR &= ~(1<<0);

	Delay_Flag = 0;

	// Disable timer
	MCAL_TIMER_STOP(TIM2);
}


void TIM3_IRQHandler()
{
	ptrF_Timer3();
}


void TIM4_IRQHandler()
{
	TIM4->TIMx_SR &= ~(1<<0);
	No_of_overflow++;
}


