/*
 * 006SPI_TX_testing.c
 *
 *  Created on: 24-Feb-2026
 *      Author: dhanush
 */

/*
 * Exercise:
 * Test the SPI_Send API to send "Hello World" and use the following configurations
 * 1. SPI-2 Master Mode
 * 2. SCLK - MAX Possible
 * 3. DFF = 0 and DFF = 1
 *
 */

/*
First decide how many lines are required to test the API 
We need MOSI and SCLK pins to test this API. NSS and MISO pins are not required because we areonly testing the TX functionality 

Now find out which pins are used for SPI-2 peripheral. You can get that in the datasheet of the STM32G491xx Microcontroller. And then go to the alternate functionality mapping section.

Pins :
1. PB13 - SPI2_SCLK
2. PB15 - SPI2_MOSI
3. PB12 - SPI2_NSS (not required for this exercise)
4. PB14 - SPI2_MISO (not required for this exercise)
Alternate Function Mode: 5

So you need to activate the GPIOB peripheral clock and configure the AF functionalites of the respective pins to AF5 because for SPI-2 peripheral, the alternate function number is 5.
Then you need to configure the SPI-2 peripheral in master mode, set the SCLK speed to the maximum possible value and set the DFF bit to 0 and then send "Hello World" using the SPI_SendData API.

*/
#include "stm32G491xx.h"
#include <stdio.h>
#include <string.h>

void SPI2_GPIO_Inits(void){
	GPIO_Handle_t SPIPins;
	SPIPins.pGPIOx = GPIOB;
	SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	SPIPins.GPIO_PinConfig.GPIO_AltFuncMode = GPIO_PIN_AF5;
	SPIPins.GPIO_PinConfig.GPIO_PinOType = GPIO_MODE_OUT_PUPL;
	SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_NO_PUPD;
	SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OUT_SPEED_HIGH;

	// Initialize both pins (PB13 and PB15)
	GPIO_Init(&SPIPins);
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_15;
	GPIO_Init(&SPIPins);
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_13;
	GPIO_Init(&SPIPins);

	// SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_14; // MISO pin (not required for this exercise but we will initialize it anyway)
	// GPIO_Init(&SPIPins);
	// SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_12; // NSS pin (not required for this exercise but we will initialize it anyway)
	// GPIO_Init(&SPIPins);	
}

void SPI2_Inits(void){
	SPI_Handle_t SPI2Handle;
	SPI2Handle.pSPIx = SPI2;
	SPI2Handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2Handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI2Handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV2; // SCLK speed = 16MHz/2 = 8MHz (maximum possible SCLK speed for SPI-2 peripheral when the APB clock is 16 MHz)
	SPI2Handle.SPIConfig.SPI_DS = SPI_DS_8BITS; // DFF = 0, 8 bits data frame format
	SPI2Handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI2Handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
	SPI2Handle.SPIConfig.SPI_SSM = SPI_SSM_EN; // Software slave management enabled for this exercise because we don't have the NSS pin connected to the slave device for slave select management

	SPI_Init(&SPI2Handle);
}


int main(void){
	char user_data[] = "Hello World";
	// This function will initialize the GPIO pins for SPI2 peripheral (PB13, PB15) and configure their alternate functions to AF5
	SPI2_GPIO_Inits();

	// SPI Initialization function will configure the SPI2 peripheral in master mode, set the SCLK speed to the maximum possible value and set the DFF bit to 0
	SPI2_Inits();
	// After the SPI2_Inits() the control registers will be loaded with the configurations but the SPI will not be active yet because the SPE bit in the CR1 register is not set. (by default it is inactive after reset).
	// All the necessary configurations should be done before enalbing the SPE bit 
	// After enabling the SPE bit the SPI will be busy in the data communications so SPE will be enabled after all the necessary configurations are done to the control registers of the SPI Peripheral.
	
	// since we are using the software slave management the NSS bit should be driven high by the software itself to avoid the MODF fault. Because when SSM is enabled and you are the MASTER, the Internal NSS should be driven high. (refer the notes )
	SPI_SSIConfig(SPI2, ENABLE); 

	// Enable the SPI2 peripheral (set the SPE bit in the CR1 register)
	SPI_PeripheralControl(SPI2, ENABLE);
	// First send length information
	uint8_t dataLen = strlen(user_data);
	SPI_SendData(SPI2, &dataLen, 1); // One byte of data is sent to the slave device which is the length of the actual data to be sent.
	
	// Then send the actual data
	SPI_SendData(SPI2, (uint8_t*)user_data, strlen(user_data)); // Send the data to the slave device

	// Before Disabling the SPI peripheral confirm that the SPI is not busy in communication by checking the BSY flag in the SPI_SR register.
	while( SPI_GetFlagStatus(SPI2, SPI_BUSY_FLAG) );

	// after confirming the BSY Flag is not set (i.e., SPI is not busy), disable the SPI peripheral
	SPI_PeripheralControl(SPI2, DISABLE);

	// An infinate while loop to hang the application after sending the data
	while(1);
	return 0;
}
