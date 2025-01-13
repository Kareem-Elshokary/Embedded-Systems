/*************************************************************************/
/* Author        : Kareem Abdelkader                                   			  	  	*/
/* Project       : STM32F103C8_Drivers  	                             			  	*/
/* File          : SPI.c        			                       				      	*/
/* Date          : 29/2/2024                                        				  	*/
/* Version       : V2                                                				    */
/* GitHub        : https://github.com/Kareem-Elshokary/Master_Embedded_systems          */
/*************************************************************************/

/*****************************
 * Includes
 ****************************/
#include "SPI.h"


//===========================================================================

//=====================================================================

/*****************************
 * Generic Variables
 ****************************/
SPI_CFG_t* Global_SPI_Config[2] = {NULL,NULL};

#define SPI1_INDEX    	  0
#define SPI2_INDEX  	  1

#define SPI_SR_TXE		((uint8_t)(0x02)) // Transmit Buffer is empty
#define SPI_SR_RXNE		((uint8_t)(0x01)) // Receive Buffer is not empty



/*****************************
 * Generic Function
 ****************************/

void MCAL_SPI_GPIO_Set_Pins(SPI_REG_t *SPIx)
{
	if(SPIx == SPI1){
		// PA4 : NSS
		if(Global_SPI_Config[SPI1_INDEX]->Device_Mode == SPI_MASTER_MODE)
		{

			if(Global_SPI_Config[SPI1_INDEX]->NSS == SPI_NSS_Hard_Master_SS_Output_Disable)
			{
				// Hardware master /slave Input floating
				MCAL_GPIO_INIT(GPIOA, PIN4, INPUT_FLOATING, 0);
			}
			else if(Global_SPI_Config[SPI1_INDEX]->NSS == SPI_NSS_Hard_Master_SS_Output_Disable)
			{
				// Hardware master/ NSS output enabled Alternate function push-pull
				MCAL_GPIO_INIT(GPIOA, PIN4, OUTPUT_AF_PP, SPEED_10MHz);
			}


			// PA5 : SCK
			// Master Alternate function push-pull
			MCAL_GPIO_INIT(GPIOA, PIN5, OUTPUT_AF_PP, SPEED_10MHz);


			// PA6 : MISO
			// Full duplex / master Input floating
			MCAL_GPIO_INIT(GPIOA, PIN6, INPUT_FLOATING, 0);

			// PA7 : MOSI
			// Full duplex / master Alternate function push-pull
			MCAL_GPIO_INIT(GPIOA, PIN7, OUTPUT_AF_PP, SPEED_10MHz);
		}
		else
		{
			// Slave

			// PA4 : NSS
			// Just use NSS in case of it is configured as hardware
			if(Global_SPI_Config[SPI1_INDEX]->NSS == SPI_SLAVE_MODE)
			{
				// Slave Input floating
				MCAL_GPIO_INIT(GPIOA, PIN4, INPUT_FLOATING, 0);
			}


			// PA5 : SCK
			// Slave Input floating
			MCAL_GPIO_INIT(GPIOA, PIN5, INPUT_FLOATING, 0);


			// PA6 : MISO
			// Full duplex / slave (point to point) Alternate function push-pull
			MCAL_GPIO_INIT(GPIOA, PIN6, OUTPUT_AF_PP, SPEED_10MHz);


			// PA7 : MOSI
			// Full duplex / slave Input floating
			MCAL_GPIO_INIT(GPIOA, PIN7, INPUT_FLOATING, 0);
		}
	}
	else if(SPIx == SPI2)
	{
		// PB12 : NSS
		if(Global_SPI_Config[SPI2_INDEX]->Device_Mode == SPI_MASTER_MODE)
		{
			if(Global_SPI_Config[SPI2_INDEX]->NSS == SPI_NSS_Hard_Master_SS_Output_Disable)
			{
				// Hardware master /slave Input floating
				MCAL_GPIO_INIT(GPIOB, PIN12, INPUT_FLOATING, 0);
			}
			else if(Global_SPI_Config[SPI2_INDEX]->NSS == SPI_NSS_Hard_Master_SS_Output_Disable)
			{
				// Hardware master/ NSS output enabled Alternate function push-pull
				MCAL_GPIO_INIT(GPIOB, PIN12, OUTPUT_AF_PP, SPEED_10MHz);
			}


			// PB13 : SCK
			// Master Alternate function push-pull
			MCAL_GPIO_INIT(GPIOB, PIN13, OUTPUT_AF_PP, SPEED_10MHz);


			// PB14 : MISO
			// Full duplex / master Input floating
			MCAL_GPIO_INIT(GPIOB, PIN14, INPUT_FLOATING, 0);

			// PB15 : MOSI
			// Full duplex / master Alternate function push-pull
			MCAL_GPIO_INIT(GPIOB, PIN15, OUTPUT_AF_PP, SPEED_10MHz);
		}
		else
		{
			// Slave

			// PB12 : NSS
			// Just use NSS in case of it is configured as hardware
			if(Global_SPI_Config[SPI2_INDEX]->NSS == SPI_SLAVE_MODE)
			{
				// Slave Input floating
				MCAL_GPIO_INIT(GPIOB, PIN12, INPUT_FLOATING, 0);
			}


			// PB13 : SCK
			// Slave Input floating
			MCAL_GPIO_INIT(GPIOB, PIN13, INPUT_FLOATING, 0);


			// PB14 : MISO
			// Full duplex / slave (point to point) Alternate function push-pull
			MCAL_GPIO_INIT(GPIOB, PIN14, OUTPUT_AF_PP, SPEED_10MHz);


			// PB15 : MOSI
			// Full duplex / slave Input floating
			MCAL_GPIO_INIT(GPIOB, PIN15, INPUT_FLOATING, 0);
		}
	}
}

void SPI_IRQ_EN(NVIC_REG_t* NVICx, SPI_REG_t* SPIx)
{
	if( SPIx == SPI1)
	{
		NVIC_IRQ_EN(NVICx->NVIC_ISER[1], (NVIC_SPI1 - 32));
	}
	else if( SPIx == SPI2)
	{
		NVIC_IRQ_EN(NVICx->NVIC_ISER[1], (NVIC_SPI2 - 32));
	}
}


void SPI_IRQ_DIS(NVIC_REG_t* NVICx, SPI_REG_t* SPIx)
{
	if( SPIx == SPI1)
	{
		NVIC_IRQ_DIS(NVICx->NVIC_ICER[1], (NVIC_SPI1 - 32));
	}
	else if( SPIx == SPI2)
	{
		NVIC_IRQ_DIS(NVICx->NVIC_ICER[1], (NVIC_SPI2 - 32));
	}
}


//=====================================================================

/**================================================================
 * @Fn			 -MCAL_SPI_Init
 * @brief 		 -Initialize SPI according to the specified parameters in SPI_Config
 * @param [in]   -SPIx :  were x can be (1,2 depending on device used)to select the SPI Peripheral
 * @param [in]   -PinConfig : pointer to SPI_Config Structure that Contains the configuration information for All SPI.
 * @retval		 -none
 * Note			 -Support for SPI Full Duplex Master/Slave & NSS HW/SW
 * 				 -In Case of Master you have to Configure pin and drive it.
 */
void MCAL_SPI_Init(SPI_REG_t *SPIx,SPI_CFG_t *SPI_Config)
{
	//Safety for registers
	uint16_t tmpreg_CR1 = 0 ;
	uint16_t tmpreg_CR2 = 0 ;

	if (SPIx == SPI1)
	{
		Global_SPI_Config[SPI1_INDEX] = SPI_Config ;
		MCAL_RCC_PERIPHERAL_EN(APB2, RCC_SPI1);
	}
	else if (SPIx == SPI2)
	{
		Global_SPI_Config[SPI2_INDEX] = SPI_Config ;
		MCAL_RCC_PERIPHERAL_EN(APB1, RCC_SPI2);
	}

	//SPI_CR1. Bit 6 SPE: SPI enable
	tmpreg_CR1 = (1<<6) ;

	// Master or Slave
	tmpreg_CR1 |= SPI_Config->Device_Mode ;

	//SPI_Communication_Mode
	tmpreg_CR1 |= SPI_Config->Communication_Mode ;

	//SPI_Frame_Format
	tmpreg_CR1 |= SPI_Config->Frame_Format ;

	//SPI_Data_Size
	tmpreg_CR1 |= SPI_Config->Data_Size ;

	//SPI_Clock_Polarity
	tmpreg_CR1 |= SPI_Config->CLK_Polarity ;

	//SPI_Clock_Phase
	tmpreg_CR1 |= SPI_Config->CLK_Phase ;

	//=======================NSS=====================
	//SPI_NSS SPI Slave Select Management

	if (SPI_Config->NSS == SPI_NSS_Hard_Master_SS_Output_Enable)
	{
		tmpreg_CR2 |= SPI_Config->NSS ;
	}
	else if (SPI_Config->NSS == SPI_NSS_Hard_Master_SS_Output_Disable)
	{
		tmpreg_CR2 &= SPI_Config->NSS ;
	}
	else
	{
		tmpreg_CR1 |= SPI_Config->NSS ;
	}

	//===============================================
	//SPI_BaudRatePrescaler
	tmpreg_CR1 |= SPI_Config->Buadrate ;

	if(SPI_Config->IRQ_EN != SPI_IRQ_Enable_NONE )
	{
		// SPI_IRQ_Enable_define
		tmpreg_CR2 |= SPI_Config->IRQ_EN ;
		if (SPIx == SPI1)
		{
			SPI_IRQ_EN(NVIC, SPI1);
		}
		else if (SPIx == SPI2)
		{
			SPI_IRQ_EN(NVIC, SPI2);
		}
	}

	SPIx->SPI_CR1 = tmpreg_CR1 ;
	SPIx->SPI_CR2 = tmpreg_CR2 ;

}


/**================================================================
 * @Fn			 -MCAL_SPI_DeInit
 * @brief 		 -Reset SPI Registers and NVIC corresponding to IRQ Mask
 * @param [in]   -SPIx :  were x can be (1,2 depending on device used)to select the SPI Peripheral
 * @retval		 -none
 * Note			 -none
 */
void MCAL_SPI_DeInit(SPI_REG_t *SPIx)
{
	if (SPIx == SPI1)
	{
		SPI_IRQ_DIS(NVIC, SPI1);
		MCAL_RCC_PERIPHERAL_DIS(APB2, RCC_SPI1);
	}
	else if (SPIx == SPI2)
	{
		SPI_IRQ_DIS(NVIC, SPI2);
		MCAL_RCC_PERIPHERAL_DIS(APB1, RCC_SPI2);
	}
}


/**================================================================
 * @Fn			- MCAL_SPI_SendData
 * @brief 		- Send data via SPI
 * @param [in] 	- SPIx :  were x can be (1,2 depending on device used)to select the SPI Peripheral
 * @param [in] 	- pTxBuffer: the data
 * @param [in] 	- PollingEn: Whether you're using polling or interrupt
 * @retval 		- None
 * Note			- None
 */
void MCAL_SPI_SendData(SPI_REG_t *SPIx, uint16_t* buff, enum PollingMechanism PollingEn )
{
	if(PollingEn == PollingEnable)
		while(!((SPIx)->SPI_SR & SPI_SR_TXE)) ;

	SPIx->SPI_DR = *buff;
}


/**================================================================
 * @Fn			- MCAL_SPI_ReceiveData
 * @brief 		- Receive data via SPI
 * @param [in] 	- SPIx :  were x can be (1,2 depending on device used)to select the SPI Peripheral
 * @param [in] 	- pTxBuffer: the data
 * @param [in] 	- PollingEn: Whether you're using polling or interrupt
 * @retval 		- None
 * Note			- None
 */
void MCAL_SPI_ReceiveData(SPI_REG_t *SPIx, uint16_t* buff, enum PollingMechanism PollingEn )
{
	if(PollingEn == PollingEnable)
		while(!((SPIx)->SPI_SR & SPI_SR_RXNE)) ;

	*buff = SPIx->SPI_DR ;
}


/**================================================================
 * @Fn			- MCAL_SPI_TX_RX
 * @brief 		- To transmit and receive data via SPI
 * @param [in] 	- SPIx :  were x can be (1,2 depending on device used)to select the SPI Peripheral
 * @param [in]  - pTxBuffer: the data
 * @param [in] 	- PollingEn: Whether you're using polling or interrupt
 * @retval 		- None
 * Note			- None
 */
void MCAL_SPI_TX_RX(SPI_REG_t *SPIx, uint16_t* buff, enum PollingMechanism PollingEn)
{
	if(PollingEn == PollingEnable)
		while(!((SPIx)->SPI_SR & SPI_SR_TXE)) ;

	SPIx->SPI_DR = *buff ;


	if(PollingEn == PollingEnable)
		while(!((SPIx)->SPI_SR & SPI_SR_RXNE)) ;

	*buff = SPIx->SPI_DR ;
}



//===============================================================================================

/*
 * ISR
 */

void SPI1_IRQHandler(void)
{
	struct S_IRQ_SRC irq_src ;

	irq_src.TXE  = ( ( SPI1->SPI_SR  & (1<<1)) >> 1 ) ;
	irq_src.RXNE = ( ( SPI1->SPI_SR  & (1<<0)) >> 0 ) ;
	irq_src.ERRI = ( ( SPI1->SPI_SR  & (1<<4)) >> 4 ) ;

	Global_SPI_Config[SPI1_INDEX]->P_IRQ_SPI_CallBack(irq_src);
}

void SPI2_IRQHandler(void)
{
	struct S_IRQ_SRC irq_src ;

	irq_src.TXE  = ( ( SPI1->SPI_SR  & (1<<1)) >> 1 ) ;
	irq_src.RXNE = ( ( SPI1->SPI_SR  & (1<<0)) >> 0 ) ;
	irq_src.ERRI = ( ( SPI1->SPI_SR  & (1<<4)) >> 4 ) ;

	Global_SPI_Config[SPI2_INDEX]->P_IRQ_SPI_CallBack(irq_src);
}
