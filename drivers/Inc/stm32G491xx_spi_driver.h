/*
 * stm32G491xx_spi_driver.h
 *
 *  Created on: 18-Feb-2026
 *      Author: dhanush
 */

#ifndef INC_STM32G491XX_SPI_DRIVER_H_
#define INC_STM32G491XX_SPI_DRIVER_H_

#include "stm32G491xx.h"
/*
 * Configuration structure for the SPI Peripheral
*/
typedef struct{
	uint8_t SPI_DeviceMode;		/* Master or Slave mode 					*/
	uint8_t SPI_BusConfig;		/* Full-Duplex or Half-Duplex or Simplex 	*/
	uint8_t SPI_SclkSpeed;		/* Serial Clock Speed 						*/
	uint8_t SPI_DS;				/* Data Frame Format						*/
	uint8_t SPI_CPHA;			/* Clock Phase 	(default set to 0)			*/
	uint8_t SPI_CPOL;			/* Clock Polarity (default set to 0)		*/
	uint8_t SPI_SSM;			/* Slave Select Management					*/

}SPI_Config_t;


typedef struct{
	SPI_RegDef_t 		*pSPIx;
	SPI_Config_t 		SPIConfig;
}SPI_Handle_t;


/*
* @SPI_DeviceMode
* Possible SPI Device Modes
*/
#define SPI_DEVICE_MODE_MASTER		1
#define SPI_DEVICE_MODE_SLAVE		0  // (default)

/*
* @SPI_BusConfig
* Possible SPI Bus Configurations
*/
#define SPI_BUS_CONFIG_FD				1	// Full-Duplex
#define SPI_BUS_CONFIG_HD				2	// Half-Duplex
#define SPI_BUS_CONFIG_SIMPLEX_RXONLY	3	// Simplex receive-only
#define SPI_BUS_CONFIG_SIMPLEX_TXONLY	4	// Simplex transmit-only

/*
* @SPI_SclkSpeed
* Possible SPI Serial Clock Speeds (baud rate)
* APB_Clock = fpclk/2^(n+1) where n is the value of the SPI_SCLK_SPEED macro
* For example, if the APB clock is 16 MHz and we want the SPI clock to be 1 MHz, we can use the formula to calculate the value of n:
* 1 MHz = 16 MHz / 2^(n+1)
* 2^(n+1) = 16
* n + 1 = log2(16)
* n + 1 = 4
* n = 3
* So we can use the SPI_SCLK_SPEED_DIV16 macro to set the SPI clock speed to 1 MHz when the APB clock is 16 MHz.
*/
#define SPI_SCLK_SPEED_DIV2				0		// SPI clock speed = APB clock speed / 2  	 (DEFULT - Baude rate))
#define SPI_SCLK_SPEED_DIV4				1		// SPI clock speed = APB clock speed / 4
#define SPI_SCLK_SPEED_DIV8				2		// SPI clock speed = APB clock speed / 8
#define SPI_SCLK_SPEED_DIV16			3		// SPI clock speed = APB clock speed / 16
#define SPI_SCLK_SPEED_DIV32			4		// SPI clock speed = APB clock speed / 32
#define SPI_SCLK_SPEED_DIV64			5		// SPI clock speed = APB clock speed / 64
#define SPI_SCLK_SPEED_DIV128			6		// SPI clock speed = APB clock speed / 128
#define SPI_SCLK_SPEED_DIV256			7		// SPI clock speed = APB clock speed / 256

/*
* @SPI_DFF
* Possible SPI Data Frame Formats
*/
// If software attempts to write one of the “Not used” values, they are forced to the value “0111”  (8-bit)

#define SPI_DS_4BITS					3		// SPI data size is 4 bits
#define SPI_DS_5BITS					4		// SPI data size is 5 bits
#define SPI_DS_6BITS					5		// SPI data size is 6 bits
#define SPI_DS_7BITS					6		// SPI data size is 7 bits
#define SPI_DS_8BITS					7		// SPI data size is 8 bits (default)
#define SPI_DS_9BITS					8		// SPI data size is 9 bits
#define SPI_DS_10BITS					9		// SPI data size is 10 bits
#define SPI_DS_11BITS					10		// SPI data size is 11 bits
#define SPI_DS_12BITS					11		// SPI data size is 12 bits	
#define SPI_DS_13BITS					12		// SPI data size is 13 bits
#define SPI_DS_14BITS					13		// SPI data size is 14 bits
#define SPI_DS_15BITS					14		// SPI data size is 15 bits
#define SPI_DS_16BITS					15		// SPI data size is 16 bits


/*
* @SPI_CPHA
* Possible SPI Clock Phase settings
*/
#define SPI_CPHA_LOW					0		// Clock phase is low(first clock transition is the first data capture edge)
#define SPI_CPHA_HIGH					1		// Clock phase is high(second clock transition is the first data capture edge)	

/*
* @SPI_CPOL
* Possible SPI Clock Polarity settings 
*/
#define SPI_CPOL_LOW					0		// Clock polarity is low(Idle state of the clock is low)
#define SPI_CPOL_HIGH					1		// Clock polarity is high(Idle state of the clock is high)

/*
* @SPI_SSM
* Possible SPI Software Slave Management settings
*/
#define SPI_SSM_EN						1		// Software slave management enabled (when SSM is enabled, the NSS pin is not used for slave select management and we can control the slave select using software by setting and clearing the SSI bit in the SPI_CR1 register`)
#define SPI_SSM_DI						0		// (Default) Software slave management disabled (when SSM is disabled, the NSS pin is used for slave select management)

#define SPI_TXE_FLAG					(1 << SPI_SR_TXE) // Transmit buffer empty flag
#define SPI_RXNE_FLAG					(1 << SPI_SR_RXNE) // Receive buffer not empty flag
#define SPI_BUSY_FLAG					(1 << SPI_SR_BSY)  // Busy flag

/*
* API Supported by this driver (prototypes)	
*/

// Peripheral Clock Setup
void SPI_PCLK_CTRL(SPI_RegDef_t *pSPIx, uint8_t EnORDi);



// SPI initialization and de-initialization
void SPI_Init(SPI_Handle_t *pSPIHandle);

void SPI_DeInit(SPI_RegDef_t *pSPIx);

/* 
* Data Send and Receive  
* There are three ways of data transmission in SPI: Blocking, Non-Blocking(Interrupt based) and Non-Blocking with DMA.
*/ 

void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len); // Arguments: Base address of the SPI peripheral, pointer to the Tx buffer(data to be sent), length of the data to be sent(standard practivce to declare the length as uint32_t even if the data to be sent is less than 255 bytes because in future we might want to send more data and we don't want to change the function prototype again and again)
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len); // Arguments: Base address of the SPI peripheral, pointer to the Rx buffer(where the received data will be stored), length of the data to be received

// IRQ Configuration and ISR handling
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnORDi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);
void SPI_IRQHandling(SPI_Handle_t *pHandle); // we need to pass the SPI handle structure because in the interrupt handler we need to know which SPI peripheral is generating the interrupt and also we might need to access the SPI configuration settings in the interrupt handler

// Other Peripheral Control APIs

#endif /* INC_STM32G491XX_SPI_DRIVER_H_ */
