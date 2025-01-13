/*************************************************************************/
/* Author        : Kareem Abdelkader                                   			  	  	*/
/* Project       : STM32F103C8_Drivers  	                             			  	*/
/* File          : USART.c		     		                       				      	*/
/* Date          : 28/2/2024                                        				  	*/
/* Version       : V2                                                				    */
/* GitHub        : https://github.com/Kareem-Elshokary/Master_Embedded_systems          */
/*************************************************************************/


/*****************************
 * Includes
 ****************************/
#include "USART.h"

//=====================================================================

/*****************************
 * Generic Variables
 ****************************/

void(* P_IRQ_CallBack1)(void) ;
void(* P_IRQ_CallBack2)(void) ;
void(* P_IRQ_CallBack3)(void) ;



/*****************************
 * Generic Function
 ****************************/

void SET_PINS(USART_REG_t* USARTx, uint8_t HW_FC)
{
	if(USARTx == USART1)
	{
		MCAL_RCC_PERIPHERAL_EN(APB2, RCC_USART1);
		/*PA9		TX
		 *PA10		RX
		 *PA11		CTS
		 *PA12		RTS
		 */
		MCAL_GPIO_INIT(GPIOA, PIN9, OUTPUT_AF_PP, SPEED_10MHz);
		MCAL_GPIO_INIT(GPIOA, PIN10, INPUT_AF, 0);
		if(HW_FC == USART_CTS_RTS_EN)
		{
			MCAL_GPIO_INIT(GPIOA, PIN11, INPUT_AF, 0);
			MCAL_GPIO_INIT(GPIOA, PIN12, OUTPUT_AF_PP, SPEED_10MHz);
		}
	}
	else if(USARTx == USART2)
	{
		MCAL_RCC_PERIPHERAL_EN(APB1, RCC_USART2);
		/*PA2		TX
		 *PA3		RX
		 *PA0		CTS
		 *PA1		RTS
		 */
		MCAL_GPIO_INIT(GPIOA, PIN2, OUTPUT_AF_PP, SPEED_10MHz);
		MCAL_GPIO_INIT(GPIOA, PIN3, INPUT_AF, 0);
		if(HW_FC == USART_CTS_RTS_EN)
		{
			MCAL_GPIO_INIT(GPIOA, PIN0, INPUT_AF, 0);
			MCAL_GPIO_INIT(GPIOA, PIN1, OUTPUT_AF_PP, SPEED_10MHz);
		}
	}
	else
	{
		MCAL_RCC_PERIPHERAL_EN(APB1, RCC_USART3);
		/*PB10		TX
		 *PB11		RX
		 *PB13		CTS
		 *PB14		RTS
		 */
		MCAL_GPIO_INIT(GPIOB, PIN10, OUTPUT_AF_PP, SPEED_10MHz);
		MCAL_GPIO_INIT(GPIOB, PIN11, INPUT_AF, 0);
		if(HW_FC == USART_CTS_RTS_EN)
		{
			MCAL_GPIO_INIT(GPIOB, PIN13, INPUT_AF, 0);
			MCAL_GPIO_INIT(GPIOB, PIN14, OUTPUT_AF_PP, SPEED_10MHz);
		}
	}
}


void USART_IRQ_EN(NVIC_REG_t* NVICx, USART_REG_t* USARTx)
{
	if( USARTx == USART1)
	{
		NVIC_IRQ_EN(NVICx->NVIC_ISER[1], (NVIC_USART1 - 32));
	}
	else if( USARTx == USART2)
	{
		NVIC_IRQ_EN(NVICx->NVIC_ISER[1], (NVIC_USART2 - 32));
	}
	else if( USARTx == USART3)
	{
		NVIC_IRQ_EN(NVICx->NVIC_ISER[1], (NVIC_USART3 - 32));
	}
}


void USART_IRQ_DIS(NVIC_REG_t* NVICx, USART_REG_t* USARTx)
{
	if( USARTx == USART1)
	{
		NVIC_IRQ_DIS(NVICx->NVIC_ICER[1], (NVIC_USART1 - 32));
	}
	else if( USARTx == USART2)
	{
		NVIC_IRQ_DIS(NVICx->NVIC_ICER[1], (NVIC_USART2 - 32));
	}
	else if( USARTx == USART3)
	{
		NVIC_IRQ_DIS(NVICx->NVIC_ICER[1], (NVIC_USART3 - 32));
	}
}

//=====================================================================

/**================================================================
 * @Fn			- MCAL_USART_INIT
 * @brief 		- Initializes the USARTx according to a specific parameters
 * @param [in] 	- USARTx: x can be (1/2/3 depend on the device used) to select the USART peripheral
 * @param [in] 	- baud: buad rate value
 * @param [in] 	- mode: transmite / receive
 * @param [in] 	- data_len: 8/9 bits data
 * @param [in] 	- parity: enable/disable parity
 * @param [in] 	- stop: no. of stop bits
 * @param [in] 	- HW_FC: CTS/RTS enable/disable
 * @retval 		- none
 * Note			- none
 */
void MCAL_USART_INIT(USART_REG_t* USARTx,uint32_t baud,uint8_t mode, uint8_t data_len, uint8_t parity, uint8_t stop, uint8_t HW_FC)
{
	//Enable USART
	USARTx->USART_CR1 |= (1 << 13) ;
	SET_PINS(USARTx, HW_FC);

	//Select mode
	switch(mode)
	{
	case USART_TR_MODE:
	{
		USARTx->USART_CR1 |= (1<<3);
	}
	break;
	case USART_RC_MODE:
	{
		USARTx->USART_CR1 |= (1<<2);
	}
	break;
	case USART_RC_TR_MODE:
	{
		USARTx->USART_CR1 |= (1<<2);
		USARTx->USART_CR1 |= (1<<3);
	}
	break;
	}

	//Select data_len
	switch(data_len)
	{
	case USART_DATA_LEN8:
	{
		USARTx->USART_CR1 &= ~(1<<12);
	}
	break;
	case USART_DATA_LEN9:
	{
		USARTx->USART_CR1 |= (1<<12);
	}
	break;
	}

	//Select parity
	if (parity == USART_PC_DIS) {
		USARTx->USART_CR1 &= ~(1<<10);
	}
	else
	{
		if(parity == USART_PC_EN_EVEN){
			USARTx->USART_CR1 &= ~(1<<9);
		}
		else{
			USARTx->USART_CR1 |= (1<<9);
		}
	}

	//Select no. of stop bits
	switch(stop)
	{
	case USART_1STB:
	{
		USARTx->USART_CR2 = (USART_1STB << 12);
	}
	break;
	case USART_2STB:
	{
		USARTx->USART_CR2 = (USART_2STB << 12);
	}
	break;
	}

	//Select HW flow control
	switch(HW_FC)
	{
	case USART_CTS_RTS_EN:
	{
		USARTx->USART_CR3 |= (1<<9);
		USARTx->USART_CR3 |= (1<<8);
	}
	break;
	case USART_CTS_RTS_DIS:
	{
		USARTx->USART_CR3 &= ~(1<<9);
		USARTx->USART_CR3 &= ~(1<<8);
	}
	break;
	}

	//Select baudrate
	uint32_t pclk, brr;
	if(USARTx == USART1)
	{
		pclk = MCAL_RCC_GetPCLK2Freq();
	}
	else
	{
		pclk = MCAL_RCC_GetPCLK1Freq(HSI);
	}
	brr = UART_BRR_Register(pclk, baud);
	USARTx->USART_BRR = brr;


	//Enable USART NVIC
	USART_IRQ_EN(NVIC, USARTx);
}


/**================================================================
 * @Fn			- MCAL_USART_DEINIT
 * @brief 		- Reset the USARTx
 * @param [in] 	- USARTx: x can be (1/2/3 depend on the device used) to select the USARTx peripheral
 * @retval 		- none
 * Note			- none
 */
void MCAL_USART_DEINIT(USART_REG_t* USARTx)
{
	if ( USARTx == USART1 )
	{
		MCAL_RCC_PERIPHERAL_DIS(APB2, RCC_USART1);
		USART_IRQ_DIS(NVIC, USARTx);
	}

	else if ( USARTx == USART2 )
	{
		MCAL_RCC_PERIPHERAL_DIS(APB1, RCC_USART2);
		USART_IRQ_DIS(NVIC, USARTx);
	}

	else if ( USARTx == USART3 )
	{
		MCAL_RCC_PERIPHERAL_DIS(APB1, RCC_USART3);
		USART_IRQ_DIS(NVIC, USARTx);
	}
}


/*********************************************************************
 * @fn      		  -MCAL_USART_SEND
 * @brief             -Send Buffer on UART
 * @param [in] 		  -USARTx: where x can be (1..3 depending on device used)
 * @param[in]         -buff: Buffer
 * @param[in]         -mechanism: Enable pooling or disable it
 * @return            -none
 * @Note              -Should initialize UART First
 */
void MCAL_USART_SEND(USART_REG_t* USARTx, uint16_t* buff, uint8_t mechanism)
{
	if(mechanism == POLLING)
	{
		while(! (USARTx->USART_SR & 1<<7) );
	}

	//Check if the data 9bit or 8bit
	if( ((USARTx->USART_CR1 >> 12) & 1) == 1)
	{
		//access all register bits (0:8)
		USARTx->USART_DR = (*buff & (uint16_t)0x01FF);
	}
	else
	{
		//access register bits (0:7)
		USARTx->USART_DR = (*buff & (uint8_t)0xFF);
	}

}


/*********************************************************************
 * @fn      		  -MCAL_USART_RECEIVE
 * @brief             -Read Buffer from USART
 * @param [in] 		  -USARTx: where x can be (1..3 depending on device used)
 * @param[in]         -buff: Buffer
 * @param[in]         -mechanism: Enable pooling or disable it
 * @return            -none
 * @Note              -Should initialize UART First
 */
void MCAL_USART_RECEIVE(USART_REG_t* USARTx, uint16_t* buff, uint8_t mechanism)
{
	if(mechanism == POLLING)
	{
		while(! (USARTx->USART_SR & 1<<5) );
	}

	//Check if the data 9bit or 8bit
	if( ((USARTx->USART_CR1 >> 12) & 1) == 1)
	{
		//Check for parity
		if( ((USARTx->USART_CR1 >> 10) & 1) == 1 )
		{
			//Parity is used, data will be 8bits
			*((uint16_t*) buff) = (USARTx->USART_DR & (uint8_t)0xFF);
		}
		else
		{
			*((uint16_t*) buff) = USARTx->USART_DR;
		}
	}
	else
	{
		//Check for parity
		if( ((USARTx->USART_CR1 >> 10) & 1) == 1 )
		{
			//Parity is used, data will be 7bits
			*((uint16_t*) buff) = (USARTx->USART_DR & (uint8_t)0x7F);
		}
		else
		{
			*((uint16_t*) buff) = (USARTx->USART_DR & (uint8_t)0xFF);
		}
	}

}


/**================================================================
 * @Fn				-MCAL_USART_WAIT_TC
 * @brief 			-Wait till TC flag is set in the SR
 * @param [in] 		-USARTx: where x can be (1..3 depending on device used)
 * @retval 			-none
 * Note				-none
 */
void MCAL_USART_WAIT_TC(USART_REG_t* USARTx)
{
	while( ! (USARTx->USART_SR & 1<<6 ));
}



/*
 * ISR
 */
//void USART1_IRQHandler (void)
//{
//
//}
//
//void USART2_IRQHandler (void)
//{
//
//}
//void USART3_IRQHandler (void)
//{
//
//}
