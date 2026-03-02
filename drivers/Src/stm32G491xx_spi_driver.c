/*
 * stm32G491xx_spi_driver.c
 *
 *  Created on: 18-Feb-2026
 *      Author: dhanush
 */

#include "stm32G491xx_spi_driver.h"
#include <stdint.h>

uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName)
{
    return ((pSPIx->SPIx_SR & FlagName) ? FLAG_SET : FLAG_RESET);
}

// 1. Peripheral Clock Setup
/**
 * @fn:          - SPI_PCLK_CTRL
 *
 * @brief:       - This function enables or disables the peripheral clock for the given SPI port
 *
 * @param[in]:   - SPI_RegDef_t *pSPIx			Base Address of the SPI peripheral (SPI1, SPI2, etc.)
 * @param[in]:   - uint8_t EnORDi      			Enable or Disable MACROS
 *
 * @return:      - void
 *
 * @note:        - none
 */
void SPI_PCLK_CTRL(SPI_RegDef_t *pSPIx, uint8_t EnORDi)
{
    if (EnORDi == ENABLE)
    {
        if (pSPIx == SPI1)
        {
            SPI1_PCLK_EN();
        }
        else if (pSPIx == SPI2)
        {
            SPI2_PCLK_EN();
        }
        else if (pSPIx == SPI3)
        {
            SPI3_PCLK_EN();
        }
        else if (pSPIx == SPI4)
        {
            SPI4_PCLK_EN();
        }
    }
    else
    {
        // TODO: Implement clock disable functionality if needed
    }
}

// 2. SPI initialization and de-initialization
/**
 * @fn:          SPI_Init
 *
 * @brief:       Initializes the SPI peripheral based on the configuration settings in the SPI handle
 *
 * @param[in]   pSPIHandle      Pointer to the SPI handle structure containing configuration settings
 *
 * @return      void
 *
 * @note        This function configures the SPI peripheral based on settings in the handle structure.
 */
void SPI_Init(SPI_Handle_t *pSPIHandle)
{
    // Enable the peripheral clock here so that the user need not to do it explicitly .
    SPI_PCLK_CTRL(pSPIHandle->pSPIx, ENABLE);
    /*
    Disable SPI before configuration
    Many configuration bits must not be modified while SPE = 1
    Without disabling, you may get unpredictable behavior.
    */
    pSPIHandle->pSPIx->SPIx_CR1 &= ~(1 << SPI_CR1_SPE);
    // Configure the SPI_CR1 register based on the settings in the SPI handle structure

    // 1. Configure the device mode (master/slave) 2nd bit of the SPI_CR1 register
    if (pSPIHandle->SPIConfig.SPI_DeviceMode == SPI_DEVICE_MODE_MASTER)
    {
        pSPIHandle->pSPIx->SPIx_CR1 |= (1 << SPI_CR1_MSTR); // Set the MSTR bit to configure as master
    }
    else
    {
        pSPIHandle->pSPIx->SPIx_CR1 &= ~(1 << SPI_CR1_MSTR); // Clear the MSTR bit to configure as slave
    }

    // 2. Configure the bus configuration (full-duplex, half-duplex, simplex)
    if (pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD)
    {
        // 15th bit of the SPI_CR1 register is BIDIMODE bit and 14th bit is BIDIOE bit
        // if BIDIMODE bit is  0 (which is by default) then SPI device is in full-duplex mode and we don't need to do anything because full-duplex is the default mode.
        // Clear the BIDIMODE bit and BIDIOE bit is tied to the BIDIMODE bit so we don't need to do anything for BIDIOE bit because when BIDIMODE bit is cleared, the BIDIOE bit is don't care bit.
        pSPIHandle->pSPIx->SPIx_CR1 &= ~((1 << SPI_CR1_BIDIMODE));
        // TO be sure also clear the RXONLY bit
        pSPIHandle->pSPIx->SPIx_CR1 &= ~(1 << SPI_CR1_RXONLY);
    }
    else if (pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD)
    {
        // set the BIDIMODE bit to configure to HD mode.
        pSPIHandle->pSPIx->SPIx_CR1 |= (1 << SPI_CR1_BIDIMODE);
        pSPIHandle->pSPIx->SPIx_CR1 |= (1 << SPI_CR1_BIDIOE); // set the BIDIOE bit to configure as transmitter. If we want to configure as receiver then we need to clear the BIDIOE bit.
    }

    // 3. Configure the Serial Clock speed
    uint8_t tempsclk_speed = pSPIHandle->SPIConfig.SPI_SclkSpeed;
    // First clear the bits 5:3 of the SPI_CR1 register
    pSPIHandle->pSPIx->SPIx_CR1 &= ~(7 << SPI_CR1_BR);
    // set the bits
    pSPIHandle->pSPIx->SPIx_CR1 |= (tempsclk_speed << SPI_CR1_BR); // SPI_CR1_BR is 3 because the baud rate bits start from bit number 3 in the SPI_CR1 register

    // 4. Data Frame Format
    pSPIHandle->pSPIx->SPIx_CR2 &= ~(15 << SPI_CR2_DS);                        // Clear the corresponding Data Size bits (4 bits belong to this field)
    pSPIHandle->pSPIx->SPIx_CR2 |= pSPIHandle->SPIConfig.SPI_DS << SPI_CR2_DS; // set the bits according to the user configurations

    // 5. Configure the CPHA bit
    if (pSPIHandle->SPIConfig.SPI_CPHA == SPI_CPHA_LOW)
    {
        pSPIHandle->pSPIx->SPIx_CR1 &= ~(1 << SPI_CR1_CPHA); // Clear the CPHA bit to configure as low
    }
    else
    {
        pSPIHandle->pSPIx->SPIx_CR1 |= (1 << SPI_CR1_CPHA); // Set the CPHA bit to configure as high
    }

    // 6. Configure the CPOL bit
    if (pSPIHandle->SPIConfig.SPI_CPOL == SPI_CPOL_LOW)
    {
        pSPIHandle->pSPIx->SPIx_CR1 &= ~(1 << SPI_CR1_CPOL); // Clear the CPOL bit to configure as low
    }
    else
    {
        pSPIHandle->pSPIx->SPIx_CR1 |= (1 << SPI_CR1_CPOL); // Set the CPOL bit to configure as high
    }
    // 7. Configure the SSM bit
    if (pSPIHandle->SPIConfig.SPI_SSM == SPI_SSM_EN)
    {
        pSPIHandle->pSPIx->SPIx_CR1 |= (1 << SPI_CR1_SSM); // Set the SSM bit to enable software slave management
    }
    else
    {
        pSPIHandle->pSPIx->SPIx_CR1 &= ~(1 << SPI_CR1_SSM); // Clear the SSM bit to disable software slave management
    }
}

// 3. De-initialization
/**
 * @fn:          SPI_DeInit
 *
 * @brief:       Resets the SPI peripheral registers to their default values
 *
 * @param[in]   pSPIx      Base address of the SPI peripheral (SPI1, SPI2, etc.)
 *
 * @return      void
 *
 * @note        This function can be used to reset the SPI peripheral to its default state.
 */
void SPI_DeInit(SPI_RegDef_t *pSPIx)
{
    if (pSPIx == SPI1)
    {
        SPI1_REG_RESET();
    }
    else if (pSPIx == SPI2)
    {
        SPI2_REG_RESET();
    }
    else if (pSPIx == SPI3)
    {
        SPI3_REG_RESET();
    }
    else if (pSPIx == SPI4)
    {
        SPI4_REG_RESET();
    }
}

/*
 * Data Send and Receive
 * There are three ways of data transmission in SPI: Blocking, Non-Blocking(Interrupt based) and Non-Blocking with DMA.
 */

// Blocking data send and receive
/**
 * @fn:          SPI_SendData
 *
 * @brief:       Sends data from the SPI peripheral in blocking mode (polling based)
 *
 * @param[in]   pSPIx      Base address of the SPI peripheral (SPI1, SPI2, etc.)
 * @param[in]   pTxBuffer  Pointer to the Tx buffer containing data to be sent
 * @param[in]   Len         Length of the data to be sent (in bytes)
 *
 * @return      void
 *
 * @note        This function sends data in blocking mode, meaning it will wait until the SPI peripheral is ready to transmit before sending each byte of data.
 */
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len)
{
    while (Len > 0)
    {
        // 1. Wait until the TXE (Transmit buffer empty) flag is set in the SPI_SR register.
        // Here we are polling untill the TXE flag is set, which indicates that the transmit buffer is empty and we can send data. This is a blocking call because the CPU will be stuck in this loop until the TXE flag is set.
        while (SPI_GetFlagStatus(pSPIx, SPI_TXE_FLAG) == FLAG_RESET)
            ; // Wait until TXE flag is set, which indicates that the transmit buffer is empty and we can send data
        // 2. Check the Data Size in the SPI_CR2 register (8-bit / 16-bit)
        uint32_t ds = (pSPIx->SPIx_CR2 >> SPI_CR2_DS) & 0xF; // Extract the Data Size bits (4 bits) from the SPI_CR2 register
        if (ds > 7)
        {
            // If true then the data size is greater than 8 bits, so we need to send 16 bits of data
            // Load the data into the SPI_DR register
            pSPIx->SPIx_DR = (*(uint16_t *)pTxBuffer);
            Len -= 2;       // Decrease the length by 2 because we have sent 16 bits of data which is equal to 2 bytes
            pTxBuffer += 2; // Move the Tx buffer pointer by 2 bytes to point to the next data to be sent
        }
        else
        {
            // If false then the data size is 8 bits, so we need to send 8 bits of data
            // Load the data into the SPI_DR register
            pSPIx->SPIx_DR = (*pTxBuffer);
            Len--;       // Decrease the length by 1 because we have sent 8 bits of data which is equal to 1 byte
            pTxBuffer++; // Move the Tx buffer pointer by 1 byte to point to the next data to be sent
        }
    }
}
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len)
{
    while (Len > 0)
    {
        // 1. Wait till the RXE flag is set in the SPI_SR register. (Set => data available in the RX Buffer)
        while (!(SPI_GetFlagStatus(pSPIx, SPI_RXNE_FLAG)))
            ;
        // 2. check the Data Size in tghe SPI_CR2 register
        uint8_t ds = (pSPIx->SPIx_CR2 >> SPI_CR2_DS) & 0xF;

        if (ds > 7)
        { //=> 16- bit
            *(uint16_t *)pRxBuffer = pSPIx->SPIx_DR;
            Len -= 2;
            pRxBuffer += 2;
        }
        else
        { // => 8 - bit
            *pRxBuffer = pSPIx->SPIx_DR;
            Len--;
            pRxBuffer++;
        }
    }
}

// Interrupt based data send and receive

uint8_t SPI_SendDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t Len)
{
    uint8_t txstate = pSPIHandle->TxState;
    if (txstate != SPI_BUSY_IN_TX)
    {
        // 1. Save the Tx buffer address and Len infromation in some global variables.
        pSPIHandle->pTxBuffer = pTxBuffer;
        pSPIHandle->TxLen = Len;

        // 2. Mark the SPI state as busy in transmission so that no other code can take over same SPI peripheral untill transmission is complete.
        pSPIHandle->TxState = SPI_BUSY_IN_TX;

        // 3. Enable the TXEIE control bit to get interrupt whenever the TXE flag is set in the SPI_SR register
        pSPIHandle->pSPIx->SPIx_CR2 |= (1 << SPI_CR2_TXEIE);

        // 4. Data transmission will be handeled by ISR code.(will be done later)
    }
    return txstate;
}
uint8_t SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pRxBuffer, uint32_t Len)
{
    uint8_t rxstate = pSPIHandle->RxState;
    if (rxstate != SPI_BUSY_IN_RX)
    {
        // 1. Save the Rx buffer address and Len infromation in some global variables.
        pSPIHandle->pRxBuffer = pRxBuffer;
        pSPIHandle->RxLen = Len;

        // 2. Mark the SPI state as busy in reception so that no other code can take over same SPI peripheral untill reception is complete.
        pSPIHandle->RxState = SPI_BUSY_IN_RX;

        // 3. Enable the RXNEIE control bit to get interrupt whenever the RXNE flag is set in the SPI_SR register
        pSPIHandle->pSPIx->SPIx_CR2 |= (1 << SPI_CR2_RXNEIE);

        // 4. Data reception will be handeled by ISR code.(will be done later)
    }
    return rxstate;
}

// IRQ Configuration and ISR handling
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnORDi)
{
    if (EnORDi == ENABLE)
    {
        if (IRQNumber <= 31)
        {
            // Program ISER0 register
            *NVIC_ISER0 |= (1 << IRQNumber);
        }
        else if (IRQNumber > 31 && IRQNumber < 64)
        {
            // Program ISER1 register
            *NVIC_ISER1 |= (1 << (IRQNumber % 32));
        }
        else if (IRQNumber >= 64 && IRQNumber < 96)
        {
            // Program ISER2 register
            *NVIC_ISER2 |= (1 << (IRQNumber % 64));
        }
        else if (IRQNumber >= 96 && IRQNumber < 128)
        { // there are Interrupts upto 101
            // Program ISER3 register
            *NVIC_ISER3 |= (1 << (IRQNumber % 96));
        }
    }
    else
    {
        if (IRQNumber <= 31)
        {
            // Program ICER0 register
            *NVIC_ICER0 |= (1 << IRQNumber);
        }
        else if (IRQNumber > 31 && IRQNumber < 64)
        {
            // Program ICER1 register
            *NVIC_ICER1 |= (1 << (IRQNumber % 32));
        }
        else if (IRQNumber >= 64 && IRQNumber < 96)
        {
            // Program ICER2 register
            *NVIC_ICER2 |= (1 << (IRQNumber % 64));
        }
        else if (IRQNumber >= 96 && IRQNumber < 128)
        { // there are Interrupts upto 101
            // Program ICER3 register
            *NVIC_ICER3 |= (1 << (IRQNumber % 96));
        }
    }
}

void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority)
{
    // 1. Find out the IPR register to be used
    uint8_t iprx = IRQNumber / 4;
    uint8_t offset = IRQNumber % 4;
    uint8_t shift_amount = (offset * 8) + (8 - no_of_PR_bits_implemented);
    *(NVIC_IPR + (iprx * 4)) |= (IRQPriority << shift_amount);
}

void SPI_IRQHandling(SPI_Handle_t *pHandle)
{
}

// Other Peripheral Control APIs
void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnORDi)
{
    if (EnORDi == ENABLE)
    {
        pSPIx->SPIx_CR1 |= (1 << SPI_CR1_SPE);
    }
    else
    {
        pSPIx->SPIx_CR1 &= ~(1 << SPI_CR1_SPE);
    }
}

void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnORDi)
{
    if (EnORDi == ENABLE)
    {
        pSPIx->SPIx_CR1 |= (1 << SPI_CR1_SSI);
    }
    else
    {
        pSPIx->SPIx_CR1 &= ~(1 << SPI_CR1_SSI);
    }
}

void SPI_SSOEConfig(SPI_RegDef_t *pSPIx, uint8_t EnORDi)
{
    if (EnORDi == ENABLE)
    {
        pSPIx->SPIx_CR2 |= (1 << SPI_CR2_SSOE);
    }
    else
    {
        pSPIx->SPIx_CR2 &= ~(1 << SPI_CR2_SSOE);
    }
}