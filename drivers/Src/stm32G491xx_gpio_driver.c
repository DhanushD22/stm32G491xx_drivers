/*
 * stm32G491xx_gpio_driver.c
 *
 *  Created on: 15 Jan 2026
 *      Author: dhanushd
 */


// Driver Source file should always contain the driver header file so:
#include "stm32G491xx_gpio_driver.h"




/**********************************************************************************
 * 							API Supported by this driver
***********************************************************************************/

// 1. Peripheral Clock Setup
/**
 * @fn:          - GPIO_PCLK_CTRL
 *
 * @brief:       - This function enables or disables the peripheral clock for the given GPIO port
 *
 * @param[in]:   - GPIO_RegDef_t *pGPIOx			Base Address of the GPIO peripheral (A or B or .....)
 * @param[in]:   - uint8_t EnORDi      			Enable or Disable MACROS
 *
 * @return:      - void
 *
 * @note:        - none
 */

void GPIO_PCLK_CTRL(GPIO_RegDef_t *pGPIOx, uint8_t EnORDi){
	if(EnORDi == ENABLE){
		if(pGPIOx == GPIOA){
			GPIOA_PCLK_EN();
		}else if(pGPIOx == GPIOB){
			GPIOB_PCLK_EN();
		}else if(pGPIOx == GPIOC){
			GPIOC_PCLK_EN();
		}else if(pGPIOx == GPIOD){
			GPIOD_PCLK_EN();
		}else if(pGPIOx == GPIOE){
			GPIOE_PCLK_EN();
		}else if(pGPIOx == GPIOF){
			GPIOF_PCLK_EN();
		}else if(pGPIOx == GPIOG){
			GPIOG_PCLK_EN();
		}
	}else{
		// <TODO>
	}
}



// 2. GPIO Init and De-init

/**
 * @fn:          GPIO_Init
 *
 * @brief:       Initialise the given GPIO port, pin, mode, output type, ,,,,,.
 *
 * @param[in]:   GPIO_Handle_t *pGPIOHandle  -> GPIO pin handler structure.
 *
 * @return:      none
 *
 * @note:        none
 *  */


void GPIO_Init(GPIO_Handle_t *pGPIOHandle){
	uint32_t temp = 0;
	uint8_t pin = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber;
	// 1. Configure the mode of the pin
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG){
		temp = ( (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode) << (2 * pin) );
		pGPIOHandle->pGPIOx->MODER &= ~( 3 << (2 * pin) );
		pGPIOHandle->pGPIOx->MODER |= temp;
	}else{
		if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT){
			//1. Configure the FTSR 
			EXTI->FTSR1 |= (1 << pin);
			// clear the corresponding RTSR bit
			EXTI->RTSR1 &= ~(1 << pin);
		}else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT){
			//1. COnfigure the RTSR
			EXTI->RTSR1 |= (1 << pin);
			// clear the corresponding FTSR bit
			EXTI->FTSR1 &= ~(1 << pin);
		}else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ITFRT){
			//1. COnfigure both FTSR and RTSR
			EXTI->RTSR1 |= (1 << pin);
			EXTI->FTSR1 |= (1 << pin);
		}
		//2. Confiure the SYSCFG_EXTICRx Register
		uint8_t temp1, temp2, portcode;
		temp1 = pin/4;
		temp2 = pin%4;
		temp2 *= 4;
		portcode = GPIOB_BASEADDR_TO_CODE((pGPIOHandle->pGPIOx));
		SYSCONFIG_PCLK_EN();
		SYSCFG->EXTICR[temp1] |= (portcode << temp2);
		//3. Enable the EXTI interrupt delivery using the interrupt mask register
		EXTI->IMR1 |= (1 << pin);
		//4. 
	}

	temp = 0;

	// 2. Configure the speed
	temp = ( (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed) << (2 * pin) );
	pGPIOHandle->pGPIOx->OSPEEDR &= ~( 0x03 << (2 * pin) );
	pGPIOHandle->pGPIOx->OSPEEDR |= temp;

	temp = 0;
	// 3. Configure the Pull-up/Pull-Down
	temp = ( (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl) << (2 * pin) );
	pGPIOHandle->pGPIOx->PUPDR &= ~( 0x03 << (2 * pin) );
	pGPIOHandle->pGPIOx->PUPDR |= temp;

	temp = 0;
	// 4. Configure the Output type
	temp = ( (pGPIOHandle->GPIO_PinConfig.GPIO_PinOType) << (pin) );
	pGPIOHandle->pGPIOx->OTYPER &= ~ ( 0x01 << (pin) );
	pGPIOHandle->pGPIOx->OTYPER |= temp;

	temp = 0;
	// 5. Configure the Alternate Function
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN){
		if(pin <= GPIO_PIN_7){
			temp = ( (pGPIOHandle->GPIO_PinConfig.GPIO_AltFuncMode) << (4 * pin) );
			pGPIOHandle->pGPIOx->AFRL &= ~( 0x0F << (4 * pin) );
			pGPIOHandle->pGPIOx->AFRL |= temp;
		}else{
			temp = ( (pGPIOHandle->GPIO_PinConfig.GPIO_AltFuncMode) << (4 * (pin - GPIO_PIN_8)) );
			pGPIOHandle->pGPIOx->AFRH &= ~( 0x0F << (4 * (pin - GPIO_PIN_8)) );
			pGPIOHandle->pGPIOx->AFRH |= temp;
		}
	}
	
}


/**
 * @fn:          GPIO_DeInit
 *
 * @brief:       Reset the regester values of corresponding GPIO peripheral
 *
 * @param[in]:   GPIO_RegDef_t *pGPIOx		GPIO peripheral example: GPIOA / GPIOB / ......
 *
 * @return:      none
 *
 * @note:        none
 */

void GPIO_DeInit(GPIO_RegDef_t *pGPIOx){
	if(pGPIOx == GPIOA){
		GPIOA_REG_RESET();
	}else if(pGPIOx == GPIOB){
		GPIOB_REG_RESET();
	}else if(pGPIOx == GPIOC){
		GPIOC_REG_RESET();
	}else if(pGPIOx == GPIOD){
		GPIOD_REG_RESET();
	}else if(pGPIOx == GPIOE){
		GPIOE_REG_RESET();
	}else if(pGPIOx == GPIOF){
		GPIOF_REG_RESET();
	}else if(pGPIOx == GPIOG){
		GPIOG_REG_RESET();
	}
}

// 3. Data Read and write


/**
 * @fn:          GPIO_ReadFromInputPin
 *
 * @brief:       Read value from a particular GPIO pin 
 *
 * @param[in]:   GPIO_RegDef_t *pGPIOx      GPIOA or GPIOB ......
 * @param[in]:   PinNumber      			Pin number 0-15
 *
 * @return:      0 or 1
 *              (e.g. 0 on success, -1 on error, or void)
 *
 * @note:        none
 */


uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber){
	uint8_t value = 0;

	value = ((pGPIOx->IDR >> PinNumber) & 0x00000001);
	
	return value;
}

/**
 * @fn:          GPIO_ReadFromInputPort
 *
 * @brief:       Read the entire port value (example reading GPIOA port value)
 *
 * @param[in]:   GPIO_RegDef_t *pGPIOx      GPIOA or GPIOB ......
 *
 * @return:      A 16-bit value 
 *
 * @note:        none
 */



uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx){
	uint16_t value = 0;

	value = (uint16_t)(pGPIOx->IDR); 
	
	return value;
}



/**
 * @fn          GPIO_WriteToOutputPin
 *
 * @brief       Short description of what the function does (1-2 lines)
 *
 * @param[in]   param1      Description of first parameter
 * @param[in]   param2      Description of second parameter (if any)
 * @param[out]  param3      Description of output parameter (if any)
 *
 * @return      Description of return value
 *              (e.g. 0 on success, -1 on error, or void)
 *
 * @note        Any important note, limitation or usage tip
 */


void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value){

	if(Value == GPIO_PIN_SET){
		pGPIOx->ODR |= (1 << PinNumber);
	}else{
		pGPIOx->ODR &= ~(1 << PinNumber);
	}
}



/**
 * @fn          GPIO_WriteToOutputPort
 *
 * @brief       Short description of what the function does (1-2 lines)
 *
 * @param[in]   param1      Description of first parameter
 * @param[in]   param2      Description of second parameter (if any)
 * @param[out]  param3      Description of output parameter (if any)
 *
 * @return      Description of return value
 *              (e.g. 0 on success, -1 on error, or void)
 *
 * @note        Any important note, limitation or usage tip
 */

void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value){
	pGPIOx->ODR = Value;
}



/**
 * @fn          GPIO_ToggleOutputPin
 *
 * @brief       Short description of what the function does (1-2 lines)
 *
 * @param[in]   param1      Description of first parameter
 * @param[in]   param2      Description of second parameter (if any)
 * @param[out]  param3      Description of output parameter (if any)
 *
 * @return      Description of return value
 *              (e.g. 0 on success, -1 on error, or void)
 *
 * @note        Any important note, limitation or usage tip
 */

void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber){
	pGPIOx->ODR ^= (1 << PinNumber);
}



// IRQ configuration and IRQ handling

/**
 * @fn          GPIO_IRQCOnfig
 *
 * @brief       Short description of what the function does (1-2 lines)
 *
 * @param[in]   param1      Description of first parameter
 * @param[in]   param2      Description of second parameter (if any)
 * @param[out]  param3      Description of output parameter (if any)
 *
 * @return      Description of return value
 *              (e.g. 0 on success, -1 on error, or void)
 *
 * @note        Any important note, limitation or usage tip
 */

void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnORDi){
	if(EnORDi == ENABLE){
		if(IRQNumber <=31){
			// Program ISER0 register
			*NVIC_ISER0 |= (1 << IRQNumber);
		}else if(IRQNumber > 31 && IRQNumber < 64){
			// Program ISER1 register
			*NVIC_ISER1 |= (1 << (IRQNumber%32));
		}else if(IRQNumber >= 64 && IRQNumber < 96){
			// Program ISER2 register
			*NVIC_ISER2 |= (1 << (IRQNumber%64));
		}else if(IRQNumber >= 96 && IRQNumber < 128){ // there are Interrupts upto 101 
			// Program ISER3 register
			*NVIC_ISER3 |= (1 << (IRQNumber%96));
		}
	}else{
		if(IRQNumber <=31){
			// Program ICER0 register
			*NVIC_ICER0 |= (1 << IRQNumber);
		}else if(IRQNumber > 31 && IRQNumber < 64){
			// Program ICER1 register
			*NVIC_ICER1 |= (1 << (IRQNumber%32));
		}else if(IRQNumber >= 64 && IRQNumber < 96){
			// Program ICER2 register
			*NVIC_ICER2 |= (1 << (IRQNumber%64));
		}else if(IRQNumber >= 96 && IRQNumber < 128){ // there are Interrupts upto 101 
			// Program ICER3 register
			*NVIC_ICER3 |= (1 << (IRQNumber%96));
		}

	}
}


/**
 * @fn          GPIO_IRQPriorityConfig
 *
 * @brief       Set priority to the Interrupt 
 *
 * @param[in]   uint8_t IRQNumber      Description of first parameter
 * @param[in]   uint8_t IRQPriority      Description of second parameter (if any)
 * @param[out]  param3      Description of output parameter (if any)
 *
 * @return      Description of return value
 *              (e.g. 0 on success, -1 on error, or void)
 *
 * @note        Any important note, limitation or usage tip
 */

void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority){
	// 1. Find out the IPR register to be used
	uint8_t iprx = IRQNumber / 4;
	uint8_t offset = IRQNumber % 4;
	uint8_t shift_amount = (offset * 8) + (8 - no_of_PR_bits_implemented);
	*( NVIC_IPR + (iprx * 4) ) |= ( IRQPriority << shift_amount );
}

/**
 * @fn          GPIO_IRQHandling
 *
 * @brief       Short description of what the function does (1-2 lines)
 *
 * @param[in]   param1      Description of first parameter
 * @param[in]   param2      Description of second parameter (if any)
 * @param[out]  param3      Description of output parameter (if any)
 *
 * @return      Description of return value
 *              (e.g. 0 on success, -1 on error, or void)
 *
 * @note        Any important note, limitation or usage tip
 */
/*
Strictly speaking the ISR's are not really implemented in the driver code. 
They are application specific so they are implemented in the user application.
The ISr implemented in the application area should call the driver supported GPIO handler 
in order to process that input.
If you go through the startup code there are ISR's implemented(the weak implementaion of ISR's)
whenever you need to implement the ISR you need to overwrite that ISR 
To do so, go to the startup folder open the .s file and search for the handler you need and then copy 
the name of the handler and implement in the main user applicaiton.
Remember: These functions dosen't take any arguments and do not return anything.
Inside this function you need to handle the interrupt. 
*/ 
void GPIO_IRQHandling(uint8_t PinNumber){//interrupt for that Pin Number will be managed so we need only pi-number as a parameter
	// Clear the EXTI Pending Register corresponding to the pin number.
	if(EXTI->PR1 & (1 << PinNumber)){
		// Clear the pending register bit
		// Writing one to the bit clears it accroding to the manual
		EXTI->PR1 |= (1 << PinNumber);
	}
}


