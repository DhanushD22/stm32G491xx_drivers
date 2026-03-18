/*
 * stm32G491xx_i2c_driver.c
 *
 *  Created on: 10-Mar-2026
 *      Author: dhanush
 */

#include "stm32G491xx.h"
#include "stm32G491xx_i2c_driver.h"

// AHB_Prescalar Division factors:
uint16_t AHB_PreScaler[8] = {2, 4, 8, 16, 32, 64, 128, 256, 512};

// APB1_PreScalar Division factors:
uint16_t APB1_PreScalar[4] = {2, 4, 8, 16};


uint32_t RCC_GetPLLOutputClock(){

    return 0;
}


uint32_t RCC_GET_APB1_CLK_VALUE(void){
    uint32_t pclk1, SysClk, temp;
    uint8_t clksrc, temp1, temp2, AHB_PRESEC, APB1_PRESEC;

    clksrc = (RCC->CFGR >> 2) & (0x03);
    if(clksrc == 0x01){
        SysClk = 16000000;
    }
    else if (clksrc = 0x10){
        SysClk = 8000000;
    }
    else if (clksrc = 0x11){
        SysClk = RCC_GetPLLOutputClock();
    }
    // calculating the AHB PreScalar
    temp1 = ((RCC->CFGR >> 4) & 0x0F);

    if(temp1 < 8 ){
        AHB_PRESEC = 1;
    }
    else{
        AHB_PRESEC = AHB_PreScaler[temp1 - 8];
    }
    // calculating the APB1 PreScalar

    temp2 = (RCC->CFGR >> 8) & 0x03; 

    if(temp2 < 4 ){
        APB1_PRESEC = 1;
    }else{
        APB1_PRESEC = APB1_PreScalar[temp2 - 4];
    }

    pclk1 = SysClk / ( AHB_PRESEC * APB1_PRESEC );

    // OR 

    // pclk1 = (SysClk / AHB_PRESEC) / APB1_PRESEC;  


    return pclk1;
}



/*********************************************************************************************************************************************
 * **********************************************API SUPPORTED BY THE PERIPHERAL**************************************************************
 ********************************************************************************************************************************************/


/**
 * 
*/
void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx, uint8_t EnORDi)
{
    if (EnORDi == ENABLE)
    {
        pI2Cx->I2C_CR1 |= (1 << I2C_CR1_PE);
    }
    else if (EnORDi == DISABLE)
    {
        pI2Cx->I2C_CR1 &= ~(1 << I2C_CR1_PE);
    }
}

/**
 *
 */

// Peripheral Clock Setup
void I2C_PCLK_CTRL(I2C_RegDef_t *pI2Cx, uint8_t EnORDi)
{
    if (EnORDi == ENABLE)
    {
        if (pI2Cx == I2C1)
        {
            I2C1_PCLK_EN();
        }
        else if (pI2Cx == I2C2)
        {
            I2C2_PCLK_EN();
        }
        else if (pI2Cx == I2C3)
        {
            I2C3_PCLK_EN();
        }
        else if (pI2Cx == I2C4)
        {
            I2C4_PCLK_EN();
        }
    }
    else
    {
        // TODO: Implement clock disable functionality if needed
    }
}

// I2C initialization and de-initialization
void I2C_Init(I2C_Handle_t *pI2CHandle)
{
    // All these below configurations have to be done when the I2C peripheral is disabled (diabled by default)
    // 1. Configure the Mode (stnadard or fast ....)
        // No need of configuring the mode of I2C because the SCL speed is completely controlled by the TIMINGR register.
        // so configure the register to control the speed directly . There is no need to switch the modes to control the speed.
    // 2. Configure the speed of the SCL 

    // 3. Configure the Device Address (applicable only when device behaves as slave)

    // 4. Enabling ACKing
        /**
         *  This is also done by the I2C hardware itself.
         *  here the peripheral uses a byte counter and automatic NACK generation
         *  In the I2C_CR2 register the fields: NBYTES, AUTOEND, RD_WRN, START. These fiels tell the hardware how many bytes are comming and it automatically decides when to ACK and when to NACK.
         * ACK is generated automatically for all bytes except the last byte. It sends NACK after receiving the last byte
         */
    
    // 5. Configure the rise time for I2C pins (later)
}

void I2C_DeInit(I2C_RegDef_t *pI2Cx)
{
    if (pI2Cx == I2C1)
    {
        I2C1_REG_RESET();
    }
    else if (pI2Cx == I2C2)
    {
        I2C2_REG_RESET();
    }
    else if (pI2Cx == I2C3)
    {
        I2C3_REG_RESET();
    }
    else if (pI2Cx == I2C4)
    {
        I2C4_REG_RESET();
    }
}

/*
 * Data Send and Receive
 * There are three ways of data transmission in I2C: Blocking, Non-Blocking(Interrupt based) and Non-Blocking with DMA.
 */

// IRQ Configuration and ISR handling
void I2C_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnORDi)
{
}
void I2C_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority)
{
}

// Other Peripheral Control APIs


uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx, uint32_t FlagName)
{
}

void I2C_ApplicationEventCallback(I2C_Handle_t *pI2CHandle, uint8_t AppEv)
{
}
