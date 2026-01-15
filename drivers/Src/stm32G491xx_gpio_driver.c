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
		temp = 0;
	}else{
		//<TODO>
		// hey 
		temp = 0;
	}

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

void GPIO_IRQCOnfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnORDi){

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

void GPIO_IRQHandling(uint8_t PinNumber){//interrupt for that Pin Number will be managed so we need only pi-number as a parameter

}


