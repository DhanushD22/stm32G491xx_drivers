/*
 * stm32G491xx_i2c_driver.h
 *
 *  Created on: 10-Mar-2026
 *      Author: dhanush
 */

#ifndef INC_STM32G491XX_I2C_DRIVER_H_
#define INC_STM32G491XX_I2C_DRIVER_H_

#include "stm32G491xx.h"

/**
 * Configuration structure for I2c
 */
typedef struct{
    uint32_t I2C_SCLSpeed;
    uint32_t I2C_DeviceAddress;
    uint8_t I2C_ACKControl;
    // uint16_t I2C_FMDutyCycle;

}I2C_Config_t;

/**
 * I2C Handle Structure
 */
typedef struct {
    I2C_RegDef_t *pI2Cx;
    I2C_Config_t I2C_Config;
}I2C_Handle_t;

/**
 * @I2C_SCLSpeed: Sets the SCL clock speed for the I2C peripheral
 */
#define I2C_SCL_SPEED_SM	100000U		/* Standard mode (up to 100 kHz) */
#define I2C_SCL_SPEED_FM4K	400000U		/* Fast mode (up to 400 kHz) */
#define I2C_SCL_SPEED_FM2M	1000000U	/* Fast mode plus (up to 1 MHz) */

/**
 * @I2C_ACKControl: Configures the ACK control for the I2C peripheral
 */
#define I2C_ACK_ENABLE		1
#define I2C_ACK_DISABLE		0


// This section is required for the old STM32G4 series 
// New STM32G4 series uses the I2C_TIMINGR register to contril the clock.
/* Instead of fixed duty cycle we can program the hight and low clock times directly using the register I2C_TIMINGR

Duty Cycle = SCLH / (SCLH + SCLL)

SCLH - SCL High period
SCLL - SCL Low period

// */
// /**
//  * @I2C_FMDutyCycle: Configures the duty cycle for fast mode in the I2C peripheral
//  */
// #define I2C_FM_DUTY_2	    0		/* Fast mode duty cycle 2:1 */
// #define I2C_FM_DUTY_16_9     1		/* Fast mode duty cycle 16:9 */

/***************************************************************************************************************** 
* 									API Supported by this driver (prototypes)	
******************************************************************************************************************/

// Peripheral Clock Setup
void I2C_PCLK_CTRL(I2C_RegDef_t *pI2Cx, uint8_t EnORDi);

// I2C initialization and de-initialization
void I2C_Init(I2C_Handle_t *pI2CHandle);

void I2C_DeInit(I2C_RegDef_t *pI2Cx);

/* 
* Data Send and Receive  
* There are three ways of data transmission in I2C: Blocking, Non-Blocking(Interrupt based) and Non-Blocking with DMA.
*/ 


// IRQ Configuration and ISR handling
void I2C_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnORDi);
void I2C_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);

// Other Peripheral Control APIs

void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx, uint8_t EnORDi); // API to enable or disable the I2C peripheral (by setting or clearing the SPE bit in the CR1 register)

uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx, uint32_t FlagName); 

void I2C_ApplicationEventCallback(I2C_Handle_t *pI2CHandle, uint8_t AppEv); 

#endif /* INC_STM32G491XX_I2C_DRIVER_H_ */
