/*
 * stm32g491xx.h
 *
 * Created on: 12-Jan-2026
 * Author: Dhanush
 */


#ifndef INC_STM32G491XX_H_
#define INC_STM32G491XX_H_

#include<stdint.h>

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
#define APB1PER_BASEADDR   0x40000000U
#define APB2PER_BASEADDR   0x40010000U
#define AHB1PER_BASEADDR   0x40020000U
#define AHB2PER_BASEADDR   0x48000000U

// RCC Base address:
#define RCC_BASEADDR	   (AHB1PER_BASEADDR + 0x1000U)

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

/*
 * Base Address of EXTI and SYSCFG
 */
#define SYSCFG_BASEADDR    (APB2PER_BASEADDR + 0x3800U)  // 0x40013800
#define EXTI_BASEADDR      (APB2PER_BASEADDR + 0x3C00U)  // 0x40013C00

/************************************Peripheral Register Structure Definitions******************************************************/
/*
 * GPIO registers
*/

typedef struct {

	__vo uint32_t MODER; 		/* Register Definition 		 Offset: 0x00   */
	__vo uint32_t OTYPER;		/* Register Definition 		 Offset: 0x04   */
	__vo uint32_t OSPEEDR;		/* Register Definition 		 Offset: 0x08   */
	__vo uint32_t PUPDR;		/* Register Definition 		 Offset: 0x0C   */
	__vo uint32_t IDR;			/* Register Definition 		 Offset: 0x10   */
	__vo uint32_t ODR;			/* Register Definition 		 Offset: 0x14   */
	__vo uint32_t BSRR;			/* Register Definition 		 Offset: 0x18   */
	__vo uint32_t LCKR;			/* Register Definition 		 Offset: 0x1C   */
	__vo uint32_t AFRL;			/* Register Definition 		 Offset: 0x20   */
	__vo uint32_t AFRH;			/* Register Definition 		 Offset: 0x24   */
	__vo uint32_t BRR;			/* Register Definition 		 Offset: 0x28   */

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


/************************************Peripheral Definitions******************************************************/

// GPIO Peripherals:

#define GPIOA 		( (GPIO_RegDef_t*)GPIOA_BASEADDR )
#define GPIOB 		( (GPIO_RegDef_t*)GPIOB_BASEADDR )
#define GPIOC 		( (GPIO_RegDef_t*)GPIOC_BASEADDR )
#define GPIOD 		( (GPIO_RegDef_t*)GPIOD_BASEADDR )
#define GPIOE 		( (GPIO_RegDef_t*)GPIOE_BASEADDR )
#define GPIOF 		( (GPIO_RegDef_t*)GPIOF_BASEADDR )
#define GPIOG 		( (GPIO_RegDef_t*)GPIOG_BASEADDR )


// RCC Peripherals:
#define	RCC 		( (RCC_RegDef_t*) RCC_BASEADDR )


/*
 * Clock Enable macro for GPIOx(x = A, B,....,G) peripherals
*/

#define GPIOA_PCLK_EN()		( RCC->AHB2ENR |= (1 << 0) )
#define GPIOB_PCLK_EN()		( RCC->AHB2ENR |= (1 << 1) )
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

/*
 * Generic Macros
*/

#define ENABLE 				1
#define DISABLE 			0
#define SET 				ENABLE
#define RESET 				DISABLE
#define GPIO_PIN_SET 		SET
#define GPIO_PIN_RESET		RESET





#endif /* INC_STM32G491XX_H_ */
