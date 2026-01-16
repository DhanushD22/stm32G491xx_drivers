/*
 * stm32G491xx_gpio_driver.h
 *
 *  Created on: 15 Jan 2026
 *      Author: dhanushd
 */

#ifndef INC_STM32G491XX_GPIO_DRIVER_H_
#define INC_STM32G491XX_GPIO_DRIVER_H_

#include<stdint.h>

// Driver header file should always contain the driver specific header file
#include "stm32G491xx.h"
/*
 * GPIO Pin Configuration Structure
*/
typedef struct{

	uint8_t GPIO_PinNumber;			/* Possible Values: @GPIO_PIN_NUMBERS 			*/
	uint8_t GPIO_PinMode;			/* Possible Values: @GPIO_PIN_MODES 			*/
	uint8_t GPIO_PinSpeed;			/* Possible values: @GPIO_OUTPUT_SPEED_MODES 	*/
	uint8_t GPIO_PinPuPdControl;	/* Possible values: @GPIO_PUPD_MODES 			*/
	uint8_t GPIO_PinOType;			/* Possible values: @GPIO_PIN_OUTPUT_MODES 		*/
	uint8_t GPIO_AltFuncMode;		/* Possible values: @GPIO_ALT_FUNC_MODES 		*/

}GPIO_PinConfig;


/*
 * Driver handler structure for GPIO
*/

typedef struct{

	GPIO_RegDef_t *pGPIOx; /* this holds the base address of the GPIO port to which the pin belongs */
	GPIO_PinConfig GPIO_PinConfig;
}GPIO_Handle_t;


/*
 * @GPIO_PIN_NUMBERS
 * GPIO Pin numbers
 */

#define GPIO_PIN_0				0
#define GPIO_PIN_1				1
#define GPIO_PIN_2				2
#define GPIO_PIN_3				3
#define GPIO_PIN_4				4
#define GPIO_PIN_5				5
#define GPIO_PIN_6				6
#define GPIO_PIN_7				7
#define GPIO_PIN_8				8
#define GPIO_PIN_9				9
#define GPIO_PIN_10				10
#define GPIO_PIN_11				11
#define GPIO_PIN_12				12
#define GPIO_PIN_13				13
#define GPIO_PIN_14				14
#define GPIO_PIN_15				15


/*
 * @GPIO_PIN_MODES
 * GPIO pin possible modes
*/
#define GPIO_MODE_IN			0
#define GPIO_MODE_OUT	 		1
#define GPIO_MODE_ALTFN 		2
#define GPIO_MODE_ANALOG		3
// When the GPIO pin is in input mode it can also have interrupts so
#define GPIO_MODE_IT_FT 		4  	// Input Falling Edge Trigger
#define GPIO_MODE_IT_RT 		5   // Input Raising Edge Trigger
#define GPIO_MODE_ITFRT			6 	// Input Raising Edge Falling Edge Trigger

/*
 * @GPIO_PIN_OUTPUT_MODES
 * GPIO Pin output modes
*/
#define GPIO_MODE_OUT_PUPL 		0	// GPIO Output mode: Push-pull
#define GPIO_MODE_OUT_OD		1	// GPIO Output mode: Open-drain


/*
 * @GPIO_OUTPUT_SPEED_MODES
 * GPIO pin Output Speed types
*/
#define GPIO_OUT_SPEED_LOW		0	//GPIO OUTPUT speed: low
#define GPIO_OUT_SPEED_MED		1	//GPIO OUTPUT speed: medium
#define GPIO_OUT_SPEED_HIGH		2	//GPIO OUTPUT speed: high
#define GPIO_OUT_SPEED_VHIGH	3	//GPIO OUTPUT speed: very high

/*
 * @GPIO_PUPD_MODES
 * GPIO pin pull-up/pull-down macros
*/
#define GPIO_PIN_NO_PUPD 		0	// GPIO Pin no pull-up/pull-down
#define GPIO_PIN_PU				1	// GPIO Pin: pull-up
#define GPIO_PIN_PD				2	// GPIO Pin: pull-down


/*
 * @GPIO_ALT_FUNC_MODES
 * GPIO pin alternate functionality modes
 */
#define GPIO_PIN_AF0			0
#define GPIO_PIN_AF1			1
#define GPIO_PIN_AF2			2
#define GPIO_PIN_AF3			3
#define GPIO_PIN_AF4			4
#define GPIO_PIN_AF5			5
#define GPIO_PIN_AF6			6
#define GPIO_PIN_AF7			7
#define GPIO_PIN_AF8			8
#define GPIO_PIN_AF9			9
#define GPIO_PIN_AF10			10
#define GPIO_PIN_AF11			11
#define GPIO_PIN_AF12			12
#define GPIO_PIN_AF13			13
#define GPIO_PIN_AF14			14
#define GPIO_PIN_AF15			15



/**********************************************************************************
 * 							API Supported by this driver
***********************************************************************************/

// Peripheral Clock Setup

void GPIO_PCLK_CTRL(GPIO_RegDef_t *pGPIOx, uint8_t EnORDi);

// GPIO Init and De-init
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

// Data Read and write
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

// IRQ configuration and IRQ handling
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnORDi);
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);
void GPIO_IRQHandling(uint8_t PinNumber); //interrupt for that Pin Number will be managed so we need only pi-number as a parameter






#endif /* INC_STM32G491XX_GPIO_DRIVER_H_ */
