/*************************************************************************/
/* Author        : Kareem Abdelkader                                   			  	  	*/
/* Project       : STM32F103C8_Drivers  	                             			  	*/
/* File          : SPI.h     				                       				      	      */
/* Date          : 29/2/2024                                        				  	*/
/* Version       : V1                                                				    */
/* GitHub        : https://github.com/Kareem-Elshokary/Master_Embedded_systems          */
/*************************************************************************/

#ifndef INC_SPI_H_
#define INC_SPI_H_

/*****************************
 * Includes
 ****************************/
#include "STM32F103x8.h"
#include "CLK.h"
#include "GPIO.h"
#include "INTERRUPT.h"


//===========================================================

/*****************************
 * User Configuration
 ****************************/

struct S_IRQ_SRC {
	uint8_t TXE:1;					//TX buffer empty
	uint8_t RXNE:1;					//RX buffer not empty
	uint8_t ERRI:1;					//Error
	uint8_t reserved:5;
};

typedef struct {
	uint16_t Device_Mode;			    //Device is master or slave
	uint16_t Communication_Mode;	//Fullduplix or halfduplix
	uint16_t Frame_Format;			  //Specifies LSB or MSB
	uint16_t Data_Size;				    //Data lengh 8B or 16B
	uint16_t CLK_Polarity;			  //CLK idle is high or low
	uint16_t CLK_Phase;				    //Sampling done with 1st or 2nd edge
	uint16_t NSS;					        //Slave Select, specifies if it control by the HW or SW
	uint16_t Buadrate;				    //Select buadrate prescaler, take care you should configure clock to buses
	uint16_t IRQ_EN;				      //Enable or Disable interrupt
	void (* P_IRQ_SPI_CallBack)(struct S_IRQ_SRC irq_src);
}SPI_CFG_t;


/*****************************
 * User Macros
 ****************************/

//Device_Mode
//Bit 2 MSTR: Master selection		CR1_Reg
#define SPI_MASTER_MODE				~(1<<2)
#define SPI_SLAVE_MODE				(uint32_t)(1<<2)

//Communication_Mode				CR1_Reg
//Bit 15 BIDIMODE: Bidirectional data mode enable
//Bit 14 BIDIOE: Output enable in bidirectional mode
#define SPI_BI_DIR_OUTPUT_DIS		  ~(1<<14)
#define SPI_BI_DIR_OUTPUT_EN		  (uint32_t)(1<<14)
#define SPI_UNI_2LINE_DIR_MODE		~(1<<15)
#define SPI_BI_1LINE_DIR_MODE		  (uint32_t)(1<<15)

//Frame_Format
//Bit 7 LSBFIRST: Frame format		CR1_Reg
#define SPI_MSB_FORMAT				~(1<<7)
#define SPI_LSB_FORMAT				(uint32_t)(1<<7)

//Data_Size
//Bit 11 DFF: Data frame format		CR1_Reg
#define SPI_DATA_SIZE_8B			~((uint32_t)(1<<11))
#define SPI_DATA_SIZE_16B			(uint32_t)(1<<11)

//CLK_Polarity
//Bit1 CPOL: Clock polarity			CR1_Reg
#define SPI_CLK_IDLE_LOW			~(1<<1)
#define SPI_CLK_IDLE_HIGH			(uint32_t)(1<<1)

//CLK_Phase
//Bit 0 CPHA: Clock phase			CR1_Reg
#define SPI_CLK_PHASE_1ST_EDGE		~(1<<0)
#define SPI_CLK_PHASE_2ST_EDGE		(uint32_t)(1<<0)

//NSS
//Bit 8 SSI: Internal slave select		CR1_Reg
//Bit 9 SSM: Software slave management  CR1_Reg
//Bit 2 SSOE: SS output enable			CR2_Reg
#define SPI_NSS_Hard_Slave  						        (uint32_t)(0)   		//CR1 >> Bit 9 SSM: Software slave management (Reset)
#define SPI_NSS_Hard_Master_SS_Output_Enable		(uint32_t)(1<<2)		//CR2 >>Bit 2 SSOE: SS output enable
#define SPI_NSS_Hard_Master_SS_Output_Disable		~((uint32_t)(1<<2))		//CR2 >>Bit 2 SSOE: SS output enable

//NSS is Driven by SW (Master or Slave)
#define SPI_NSS_SW_NSSInternalSoft_Reset			(uint32_t)(1<<9)		//CR1 >> Bit 9 SSM: Software slave management (Reset)
#define SPI_NSS_SW_NSSInternalSoft_Set				(uint32_t)(1<<9 | 1<<8) // for Slave & Master

//Buadrate
//Bits 5:3 BR[2:0]: Baud rate control	CR1_Reg
#define SPI_BUADRATE_DIV2			  (uint32_t)(0b000 <<3)
#define SPI_BUADRATE_DIV4			  (uint32_t)(0b001 <<3)
#define SPI_BUADRATE_DIV8			  (uint32_t)(0b010 <<3)
#define SPI_BUADRATE_DIV16			(uint32_t)(0b011 <<3)
#define SPI_BUADRATE_DIV32			(uint32_t)(0b100 <<3)
#define SPI_BUADRATE_DIV64			(uint32_t)(0b101 <<3)
#define SPI_BUADRATE_DIV128			(uint32_t)(0b110 <<3)
#define SPI_BUADRATE_DIV256			(uint32_t)(0b111 <<3)

//IRQ_EN
//CR2_Reg
#define SPI_IRQ_Enable_NONE				(uint32_t)(0)
#define SPI_IRQ_Enable_TXEIE			(uint32_t)(1<<7)
#define SPI_IRQ_Enable_RXNEIE			(uint32_t)(1<<5)
#define SPI_IRQ_Enable_ERRIE			(uint32_t)(1<<6)


enum PollingMechanism
{
	PollingEnable ,
	PollingDisable
};


//=====================================================================

/**************************************
 * APIs Supported by MCAL SPI Drive
 **************************************/

//SPI init and deinit
void MCAL_SPI_Init(SPI_REG_t *SPIx,SPI_CFG_t *SPI_Config);
void MCAL_SPI_DeInit(SPI_REG_t *SPIx);

//Send and receive data APIs
void MCAL_SPI_SendData(SPI_REG_t *SPIx, uint16_t* buff, enum PollingMechanism PollingEn );
void MCAL_SPI_ReceiveData(SPI_REG_t *SPIx, uint16_t* buff, enum PollingMechanism PollingEn );
void MCAL_SPI_TX_RX(SPI_REG_t *SPIx, uint16_t* buff, enum PollingMechanism PollingEn);




#endif /* INC_SPI_H_ */
