/*
 * stm32g491xx.h
 *
 * Created on: 12-Jan-2026
 * Author: Dhanush
 */


#ifndef INC_STM32G491XX_H_
#define INC_STM32G491XX_H_

#include<stdint.h>

/************************************Processror Specific Details******************************************************/
/*
 * ARM Cortex M4 Processor NVIC ISERx register addresses (interrupt set register)
*/
#define NVIC_ISER0			( (__vo uint32_t*)0xE000E100 )
#define NVIC_ISER1			( (__vo uint32_t*)0xE000E104 )
#define NVIC_ISER2			( (__vo uint32_t*)0xE000E108 )
#define NVIC_ISER3			( (__vo uint32_t*)0xE000E10C )

/*
 * ARM Cortex M4 Processor NVIC ICERx register addresses (interrupt clear register)
*/
#define NVIC_ICER0			( (__vo uint32_t*)0XE000E180 )
#define NVIC_ICER1			( (__vo uint32_t*)0XE000E184 )
#define NVIC_ICER2			( (__vo uint32_t*)0XE000E188 )
#define NVIC_ICER3			( (__vo uint32_t*)0XE000E18C )

/*
 * ARM Cortex M4 Processor NVIC IPRx register addresses  (interrupt priority register)
*/

#define NVIC_IPR					( (__vo uint32_t*)0xE000E400)
#define no_of_PR_bits_implemented	4			// Depends on the processor for stm32G4 series it is 4

#define __vo volatile
/*
 * Base addresses of SRAM and FLASH
 */
#define FLASH_BASEADDR     0x08000000U
#define SRAM1_BASEADDR     0x20000000U
#define SRAM2_BASEADDR     0x20014000U
#define ROM_BASEADDR       0x1FFF0000U   // System memory (bootloader)
#define SRAM               SRAM1_BASEADDR



/*
 * Base Address of various BUS Domains
 */
#define APB1PER_BASEADDR   0x40000000U 		// APB1 peripheral base address = 0x40000000U ( U - unsigned int, ecause address are not signed)
#define APB2PER_BASEADDR   0x40010000U		// APB2 peripheral base address
#define AHB1PER_BASEADDR   0x40020000U		// AHB1 peripheral base address
#define AHB2PER_BASEADDR   0x48000000U		// AHB2 peripheral base address

// RCC Base address:
#define RCC_BASEADDR	   (AHB1PER_BASEADDR + 0x1000U) 		// Reset Clock Control (RCC) perppheral base address. This is connected to the AHB1 Peripheral so use the base address and add the offset 

/*
 * EXTI and SYSCGF Base Addresses
*/

#define EXTI_BASEADDR		(APB2PER_BASEADDR + 0x0400U)		
#define SYSCFG_BASEADDR 	(APB2PER_BASEADDR + 0x0000U)

/*
 * Base Address of GPIO peripherals
 */
#define GPIOA_BASEADDR     (AHB2PER_BASEADDR + 0x0000U)
#define GPIOB_BASEADDR     (AHB2PER_BASEADDR + 0x0400U)
#define GPIOC_BASEADDR     (AHB2PER_BASEADDR + 0x0800U)
#define GPIOD_BASEADDR     (AHB2PER_BASEADDR + 0x0C00U)
#define GPIOE_BASEADDR     (AHB2PER_BASEADDR + 0x1000U)
#define GPIOF_BASEADDR     (AHB2PER_BASEADDR + 0x1400U)
#define GPIOG_BASEADDR     (AHB2PER_BASEADDR + 0x1800U)

/*
 * Base address of I2C peripherals
 */
#define I2C1_BASEADDR      (APB1PER_BASEADDR + 0x5400U)
#define I2C2_BASEADDR      (APB1PER_BASEADDR + 0x5800U)
#define I2C3_BASEADDR      (APB1PER_BASEADDR + 0x7800U)
#define I2C4_BASEADDR      (APB1PER_BASEADDR + 0x8400U)  // Reserved on STM32G491xx

/*
 * Base address of SPI peripherals
 */
#define SPI1_BASEADDR      (APB2PER_BASEADDR + 0x3000U)
#define SPI2_BASEADDR      (APB1PER_BASEADDR + 0x3800U)
#define SPI3_BASEADDR      (APB1PER_BASEADDR + 0x3C00U)
#define SPI4_BASEADDR	   (APB2PER_BASEADDR + 0x3C00U)

/*
 * Base address of USART/UART
 */
#define USART1_BASEADDR    (APB2PER_BASEADDR + 0x3800U)
#define USART2_BASEADDR    (APB1PER_BASEADDR + 0x4400U)
#define USART3_BASEADDR    (APB1PER_BASEADDR + 0x4800U)
#define UART4_BASEADDR     (APB1PER_BASEADDR + 0x4C00U)
#define UART5_BASEADDR     (APB1PER_BASEADDR + 0x5000U)



/************************************Peripheral Register Structure Definitions******************************************************/
/*
 * GPIO registers
*/

typedef struct {

	__vo uint32_t MODER; 		/* GPIO Pin mode register 				Offset: 0x00   */
	__vo uint32_t OTYPER;		/* GPIO Output type register 			Offset: 0x04   */
	__vo uint32_t OSPEEDR;		/* GPIO Output speed register 			Offset: 0x08   */
	__vo uint32_t PUPDR;		/* GPIO Pull-up/Pull-down register 		Offset: 0x0C   */
	__vo uint32_t IDR;			/* Input Data Register 		 			Offset: 0x10   */
	__vo uint32_t ODR;			/* Output Data Register 	 			Offset: 0x14   */
	__vo uint32_t BSRR;			/* Register Definition 		 			Offset: 0x18   */
	__vo uint32_t LCKR;			/* Register Definition 		 			Offset: 0x1C   */
	__vo uint32_t AFRL;			/* Alternate function register-1 		Offset: 0x20   */
	__vo uint32_t AFRH;			/* Alternate function register-2 		Offset: 0x24   */
	__vo uint32_t BRR;			/* Register Definition 		 			Offset: 0x28   */

}GPIO_RegDef_t;

/*
 * RCC registers
*/


typedef struct{

	__vo uint32_t CR;				/*Address Offset: 0x00*/
	__vo uint32_t ICSCR;			/*Address Offset: 0x04*/
	__vo uint32_t CFGR;				/*Address Offset: 0x08*/
	__vo uint32_t PLLCFGR;			/*Address Offset: 0x0C*/
	uint32_t RESERVED0[2];			/*Address Offset: 0x10*/

	__vo uint32_t CIER;				/*Address Offset: 0x18*/
	__vo uint32_t CIFR;				/*Address Offset: 0x1C*/
	__vo uint32_t CICR;				/*Address Offset: 0x20*/
	uint32_t RESERVED1;				/*Address Offset: 0x24*/

	__vo uint32_t AHB1RSTR;			/*Address Offset: 0x28*/
	__vo uint32_t AHB2RSTR;			/*Address Offset: 0x2C*/
	__vo uint32_t AHB3RSTR;			/*Address Offset: 0x30*/
	uint32_t RESERVED2;				/*Address Offset: 0x34*/

	__vo uint32_t APB1RSTR1;		/*Address Offset: 0x38*/
	__vo uint32_t APB1RSTR2;		/*Address Offset: 0x3C*/
	__vo uint32_t APB2RSTR;			/*Address Offset: 0x40*/
	uint32_t RESERVED3;				/*Address Offset: 0x44*/

	__vo uint32_t AHB1ENR;			/*Address Offset: 0x48*/
	__vo uint32_t AHB2ENR;			/*Address Offset: 0x4C*/
	__vo uint32_t AHB3ENR;			/*Address Offset: 0x50*/
	uint32_t RESERVED4;				/*Address Offset: 0x54*/

	__vo uint32_t APB1ENR1;			/*Address Offset: 0x58*/
	__vo uint32_t APB1ENR2;			/*Address Offset: 0x5C*/
	__vo uint32_t APB2ENR;			/*Address Offset: 0x60*/
	uint32_t RESERVED5;				/*Address Offset: 0x64*/

	__vo uint32_t AHB1SMENR;		/*Address Offset: 0x68*/
	__vo uint32_t AHB2SMENR;		/*Address Offset: 0x6C*/
	__vo uint32_t AHB3SMENR;		/*Address Offset: 0x70*/
	uint32_t RESERVED6;				/*Address Offset: 0x74*/

	__vo uint32_t APB1SMENR1;		/*Address Offset: 0x78*/
	__vo uint32_t APB1SMENR2;		/*Address Offset: 0x7C*/
	__vo uint32_t APB2SMENR;		/*Address Offset: 0x80*/
	uint32_t RESERVED7;				/*Address Offset: 0x84*/

	__vo uint32_t CCIPR;			/*Address Offset: 0x88*/
	uint32_t RESERVED8;				/*Address Offset: 0x8C*/

	__vo uint32_t BDCR;				/*Address Offset: 0x90*/
	__vo uint32_t CSR;				/*Address Offset: 0x94*/
	__vo uint32_t CRRCR;			/*Address Offset: 0x98*/
	__vo uint32_t CCIPR2;			/*Address Offset: 0x9C*/

}RCC_RegDef_t;


/*
 * SYSCFG Regester Structure Definition
*/

typedef struct 
{
	__vo uint32_t MEMRMP;			/* 		Offset: 0x00		*/
	__vo uint32_t CFGR1;			/* 		Offset: 0x04		*/
	__vo uint32_t EXTICR[3];		/* 		Offset: 0x08 - 0x14		*/
	__vo uint32_t SCSR;				/* 		Offset: 0x18		*/
	__vo uint32_t CFGR2;			/*		Offset: 0x1C		*/
	__vo uint32_t SWPR;				/* 		Offset: 0x20		*/
	__vo uint32_t SKR;				/* 		Offset: 0x24		*/

}SYSCFG_RegDef_t;


/*
 * EXTI Regester Structure Definition
*/

typedef struct 
{
	__vo uint32_t IMR1;				/* 		Offset: 0x00		*/
	__vo uint32_t EMR1;				/* 		Offset: 0x04		*/
	__vo uint32_t RTSR1;			/* 		Offset: 0x08		*/
	__vo uint32_t FTSR1;			/* 		Offset: 0x0C		*/
	__vo uint32_t SWIER1;			/* 		Offset: 0x10		*/
	__vo uint32_t PR1;				/* 		Offset: 0x14		*/
	__vo uint32_t RESERVED[2];		/* 		Offset: 0x18 and 0x1C*/
	__vo uint32_t IMR2;				/* 		Offset: 0x20		*/
	__vo uint32_t EMR2;				/*		Offset: 0x24		*/
	__vo uint32_t RTSR2;			/* 		Offset: 0x28		*/
	__vo uint32_t FTSR2;			/* 		Offset: 0x2C		*/
	__vo uint32_t SWIER2;			/* 		Offset: 0x30		*/
	__vo uint32_t PR2;				/* 		Offset: 0x34		*/

}EXTI_RegDef_t;



/*
 * ESPI Regester Structure Definition
*/

typedef struct 
{
	__vo uint32_t SPIx_CR1;				/* 		Offset: 0x00		*/
	__vo uint32_t SPIx_CR2;				/* 		Offset: 0x04		*/
	__vo uint32_t SPIx_SR;				/* 		Offset: 0x08		*/
	__vo uint32_t SPIx_DR;				/* 		Offset: 0x0C		*/
	__vo uint32_t SPIx_CRCPR;			/* 		Offset: 0x10		*/
	__vo uint32_t SPIx_RXCRCR;			/* 		Offset: 0x14		*/
	__vo uint32_t SPIx_TXCRCR;			/* 		Offset: 0x18		*/
	__vo uint32_t SPIx_I2SCFGR;			/* 		Offset: 0x1C		*/
	__vo uint32_t SPIx_I2SPR;			/* 		Offset: 0x20		*/
}SPI_RegDef_t;



/************************************Peripheral Definitions******************************************************/

// GPIO Peripherals: There are 8 gpio perhipherals (GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF and GPIOG) I have defined only 7 because GPIOH is not present in STM32G491xx series

#define GPIOA 		( (GPIO_RegDef_t*)GPIOA_BASEADDR )
#define GPIOB 		( (GPIO_RegDef_t*)GPIOB_BASEADDR )
#define GPIOC 		( (GPIO_RegDef_t*)GPIOC_BASEADDR )
#define GPIOD 		( (GPIO_RegDef_t*)GPIOD_BASEADDR )
#define GPIOE 		( (GPIO_RegDef_t*)GPIOE_BASEADDR )
#define GPIOF 		( (GPIO_RegDef_t*)GPIOF_BASEADDR )
#define GPIOG 		( (GPIO_RegDef_t*)GPIOG_BASEADDR )


// RCC Peripherals:
#define	RCC 		( (RCC_RegDef_t*) RCC_BASEADDR )

// SCFG peripherals 
#define SYSCFG 		( (SYSCFG_RegDef_t*)SYSCFG_BASEADDR)


// EXTI peripheral
#define EXTI		( (EXTI_RegDef_t*)EXTI_BASEADDR)

/*
 * SPI Peripherals
*/
#define SPI1		( (SPI_RegDef_t*)SPI1_BASEADDR )
#define SPI2		( (SPI_RegDef_t*)SPI2_BASEADDR )
#define SPI3		( (SPI_RegDef_t*)SPI3_BASEADDR )	
#define SPI4 		( (SPI_RegDef_t*)SPI4_BASEADDR )

/*
 * Clock Enable macro for GPIOx(x = A, B,....,G) peripherals
*/

#define GPIOA_PCLK_EN()		( RCC->AHB2ENR |= (1 << 0) ) 	//  First bit of the AHB2ENR register is for GPIOA peripheral, so we need to set that bit to enable the clock for GPIOA peripheral
#define GPIOB_PCLK_EN()		( RCC->AHB2ENR |= (1 << 1) )	// Second bit of the AHB2ENR register is for GPIOB peripheral, so we need to set that bit to enable the clock for GPIOB peripheral
#define GPIOC_PCLK_EN()		( RCC->AHB2ENR |= (1 << 2) )
#define GPIOD_PCLK_EN()		( RCC->AHB2ENR |= (1 << 3) )
#define GPIOE_PCLK_EN()		( RCC->AHB2ENR |= (1 << 4) )
#define GPIOF_PCLK_EN()		( RCC->AHB2ENR |= (1 << 5) )
#define GPIOG_PCLK_EN()		( RCC->AHB2ENR |= (1 << 6) )

/*
 * Clock enable macro for I2Cx(x = 1, 2, 3, 4) peripherals
*/

#define I2C1_PCLK_EN() 		( RCC->APB1ENR1 |= (1 << 21) )
#define I2C2_PCLK_EN() 		( RCC->APB1ENR1 |= (1 << 22) )
#define I2C3_PCLK_EN() 		( RCC->APB1ENR1 |= (1 << 30) )
#define I2C4_PCLK_EN() 		( RCC->APB1ENR2 |= (1 << 1 ) )

/*
 *Clock Enable macro for SPIx(x = 1, 2 and 3) peripherals
*/

#define SPI1_PCLK_EN() 		( RCC->APB2ENR |= (1 << 12))
#define SPI2_PCLK_EN() 		( RCC->APB1ENR1 |= (1 << 14))
#define SPI3_PCLK_EN() 		( RCC->APB1ENR1 |= (1 << 15))
#define SPI4_PCLK_EN() 		( RCC->APB2ENR |= (1 << 15))

/*
 *Clock Enable Macro for UART and USART peripherals
*/

#define USART1_PCLK_EN()		( RCC->APB2ENR |= (1 << 14))
#define USART2_PCLK_EN()		( RCC->APB1ENR1 |= (1 << 17))
#define USART3_PCLK_EN()		( RCC->APB1ENR1 |= (1 << 18))
#define UART4_PCLK_EN()			( RCC->APB1ENR1 |= (1 << 19))
#define UART5_PCLK_EN()			( RCC->APB1ENR1 |= (1 << 20))

/*
 * Clock Enable macro for SysConfig peripheral
*/

#define SYSCONFIG_PCLK_EN() 	( RCC->APB2ENR |= (1 << 0))



/*
 * Clock Disable macro for GPIOx(x = A, B,....,G) peripherals
*/

#define GPIOA_PCLK_DI()		( RCC->AHB2ENR &= ~(1 << 0) )
#define GPIOB_PCLK_DI()		( RCC->AHB2ENR &= ~(1 << 1) )
#define GPIOC_PCLK_DI()		( RCC->AHB2ENR &= ~(1 << 2) )
#define GPIOD_PCLK_DI()		( RCC->AHB2ENR &= ~(1 << 3) )
#define GPIOE_PCLK_DI()		( RCC->AHB2ENR &= ~(1 << 4) )
#define GPIOF_PCLK_DI()		( RCC->AHB2ENR &= ~(1 << 5) )
#define GPIOG_PCLK_DI()		( RCC->AHB2ENR &= ~(1 << 6) )

/*
 * Clock Disable macro for I2Cx(x = 1, 2, 3, 4) peripherals
*/

#define I2C1_PCLK_DI() 		( RCC->APB1ENR1 &= ~(1 << 21) )
#define I2C2_PCLK_DI() 		( RCC->APB1ENR1 &= ~(1 << 22) )
#define I2C3_PCLK_DI() 		( RCC->APB1ENR1 &= ~(1 << 30) )
#define I2C4_PCLK_DI() 		( RCC->APB1ENR2 &= ~(1 << 1 ) )

/*
 *Clock Disable macro for SPIx(x = 1, 2 and 3) peripherals
*/

#define SPI1_PCLK_DI() 		( RCC->APB2ENR &= ~(1 << 12))
#define SPI2_PCLK_DI() 		( RCC->APB1ENR1 &= ~(1 << 14))
#define SPI3_PCLK_DI() 		( RCC->APB1ENR1 &= ~(1 << 15))
#define SPI4_PCLK_DI() 		( RCC->APB2ENR &= ~(1 << 15))

/*
 *Clock Disable Macro for UART and USART peripherals
*/

#define USART1_PCLK_DI()		( RCC->APB2ENR &= ~(1 << 14))
#define USART2_PCLK_DI()		( RCC->APB1ENR1 &= ~(1 << 17))
#define USART3_PCLK_DI()		( RCC->APB1ENR1 &= ~(1 << 18))
#define UART4_PCLK_DI()			( RCC->APB1ENR1 &= ~(1 << 19))
#define UART5_PCLK_DI()			( RCC->APB1ENR1 &= ~(1 << 20))

/*
* Reset GPIO registers
*/
								/* 				SET					then 			RESET					*/
#define GPIOA_REG_RESET()		do{  ( RCC->AHB2RSTR |= (1UL << 0));	( RCC->AHB2RSTR &= ~(1UL << 0)); } while(0)
#define GPIOB_REG_RESET()		do{  ( RCC->AHB2RSTR |= (1UL << 1));	( RCC->AHB2RSTR &= ~(1UL << 1)); } while(0)
#define GPIOC_REG_RESET()		do{  ( RCC->AHB2RSTR |= (1UL << 2));	( RCC->AHB2RSTR &= ~(1UL << 2)); } while(0)
#define GPIOD_REG_RESET()		do{  ( RCC->AHB2RSTR |= (1UL << 3));	( RCC->AHB2RSTR &= ~(1UL << 3)); } while(0)
#define GPIOE_REG_RESET()		do{  ( RCC->AHB2RSTR |= (1UL << 4));	( RCC->AHB2RSTR &= ~(1UL << 4)); } while(0)
#define GPIOF_REG_RESET()		do{  ( RCC->AHB2RSTR |= (1UL << 5));	( RCC->AHB2RSTR &= ~(1UL << 5)); } while(0)
#define GPIOG_REG_RESET()		do{  ( RCC->AHB2RSTR |= (1UL << 6));	( RCC->AHB2RSTR &= ~(1UL << 6)); } while(0)


#define GPIOB_BASEADDR_TO_CODE(x) 	(	(x == GPIOA) ? 0 :\
										(x == GPIOB) ? 1 :\
										(x == GPIOC) ? 2 :\
										(x == GPIOD) ? 3 :\
										(x == GPIOE) ? 4 :\
										(x == GPIOF) ? 5 :\
										(x == GPIOG) ? 6 : 0)

/*
 * Interrupt request numbers (IRQn) for STM32G491xx series MCUs
 * (using POSITION numbers from the vector table)
 */

#define IRQ_NO_WWDG                  0      // Window Watchdog interrupt
#define IRQ_NO_PVD_PVM               1      // PVD/PVM1/PVM2/PVM3/PVM4 through EXTI line 16
#define IRQ_NO_RTC_TAMP_CSS_LSE      2      // RTC tamper / CSS on LSE / LSECSS through EXTI line 19
#define IRQ_NO_RTC_WKUP              3      // RTC wakeup timer through EXTI line 20
#define IRQ_NO_FLASH                 4      // Flash global interrupt
#define IRQ_NO_RCC                   5      // RCC global interrupt
#define IRQ_NO_EXTI0                 6      // EXTI Line 0 interrupt
#define IRQ_NO_EXTI1                 7      // EXTI Line 1 interrupt
#define IRQ_NO_EXTI2                 8      // EXTI Line 2 interrupt
#define IRQ_NO_EXTI3                 9      // EXTI Line 3 interrupt
#define IRQ_NO_EXTI4                 10     // EXTI Line 4 interrupt
#define IRQ_NO_EXTI9_5               23     // EXTI Line [9:5] interrupts
#define IRQ_NO_EXTI15_10             40     // EXTI Line [15:10] interrupts


/*
 * Generic Macros
*/

#define ENABLE 				1
#define DISABLE 			0
#define SET 				ENABLE
#define RESET 				DISABLE
#define GPIO_PIN_SET 		SET
#define GPIO_PIN_RESET		RESET
#define FLAG_SET			SET
#define FLAG_RESET			RESET

/*
 * Bit position definitions for SPI peripheral
 Macros tell the bit position of the corresponding configuration bits in the SPI_CR1, SPI_CR2 and SPI_SR  registers. These macros will be used in the SPI driver source file to configure the SPI peripheral based on the user configurations in the SPI handle structure.
*/
#define SPI_CR1_CPHA			0
#define SPI_CR1_CPOL			1
#define SPI_CR1_MSTR			2
#define SPI_CR1_BR				3
#define SPI_CR1_SPE				6
#define SPI_CR1_LSBFIRST		7
#define SPI_CR1_SSI				8
#define SPI_CR1_SSM				9
#define SPI_CR1_RXONLY			10
#define SPI_CR1_DFF				11
#define SPI_CR1_CRCNEXT			12
#define SPI_CR1_CRCEN			13
#define SPI_CR1_BIDIOE			14	
#define SPI_CR1_BIDIMODE		15

#define SPI_CR2_RXDMAEN			0
#define SPI_CR2_TXDMAEN			1
#define SPI_CR2_SSOE			2
#define SPI_CR2_ERRIE			5
#define SPI_CR2_RXNEIE			6
#define SPI_CR2_TXEIE			7	
#define SPI_CR2_DS				8
#define SPI_CR2_FRXTH			12
#define SPI_CR2_LDMARX			13
#define SPI_CR2_LDMATX			14

// Bit position definitions for SPI_SR register
#define SPI_SR_RXNE				0
#define SPI_SR_TXE				1
#define SPI_SR_CHSIDE			2
#define SPI_SR_UDR				3
#define SPI_SR_CRCERR			4
#define SPI_SR_MODF				5
#define SPI_SR_OVR				6
#define SPI_SR_BSY				7
#define SPI_SR_FRE				8
#define SPI_SR_FRLVL			9
#define SPI_SR_FTLVL			11



/*
* Reset SPI registers
*/
								/* 				SET					then 			RESET					*/
#define SPI1_REG_RESET()		do{  ( RCC->APB2RSTR |= (1UL << 12));	( RCC->APB2RSTR &= ~(1UL << 12)); } while(0)
#define SPI2_REG_RESET()		do{  ( RCC->APB1RSTR1 |= (1UL << 14));	( RCC->APB1RSTR1 &= ~(1UL << 14)); } while(0)
#define SPI3_REG_RESET()		do{  ( RCC->APB1RSTR1 |= (1UL << 15));	( RCC->APB1RSTR1 &= ~(1UL << 15)); } while(0)
#define SPI4_REG_RESET()		do{  ( RCC->APB2RSTR |= (1UL << 15));	( RCC->APB2RSTR &= ~(1UL << 15)); } while(0)





#include "stm32G491xx_gpio_driver.h"
#include "stm32G491xx_spi_driver.h"

#endif
