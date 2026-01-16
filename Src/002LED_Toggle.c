/*
 * 001LED_Toggle.c
 *
 *  Created on: 15 Jan 2026
 *      Author: dhanushd
 */

// To blink the user LED LD2 which is connected to PA5 pin
#include<stdint.h>
#include "stm32G491xx.h"

void delay(void){
    for(uint32_t i = 0; i < 500000/2; i++);
}

int main(void){

    GPIO_Handle_t Gpioled, UserIn;

    // Select the port for pin PA5
    Gpioled.pGPIOx = GPIOA;
    // Pin configurations
    Gpioled.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_5;
    Gpioled.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    Gpioled.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OUT_SPEED_HIGH;
    Gpioled.GPIO_PinConfig.GPIO_PinOType = GPIO_MODE_OUT_PUPL;
    Gpioled.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_NO_PUPD;

    // Select the port for pin PA5
    UserIn.pGPIOx = GPIOC;
    // Pin configurations
    UserIn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_13;
    UserIn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
    UserIn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OUT_SPEED_HIGH;
    UserIn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_NO_PUPD;

    // Enable the clock for the GPIOA peripheral
    GPIO_PCLK_CTRL(GPIOA, ENABLE);
    // Enable the clock for the GPIOC peripheral
    GPIO_PCLK_CTRL(GPIOC, ENABLE);
    
    // Initialise the GPIOA register with the above declared variables
    GPIO_Init(&Gpioled);
    // Initialise the GPIOC register with the above declared variables
    GPIO_Init(&UserIn);

    // Make sure LED starts OFF
    GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

    // Infinite loop
    while(1){
        uint8_t in = 0;
        in = GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_13);
        if(in == GPIO_PIN_SET){ //Active High for the User button  (look at the schematics)
            delay(); // to wait for the button to debouce. Learn about button debouncing
            GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_5);
        }
    }
    return 0;
}
