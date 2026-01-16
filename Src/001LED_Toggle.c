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
    for(uint32_t i = 0; i < 500000; i++);
}

int main(void){

    GPIO_Handle_t Gpioled;
    // Select the port for pin PA5
    Gpioled.pGPIOx = GPIOA;
    // Pin configurations				
    Gpioled.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_5;
    Gpioled.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    Gpioled.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OUT_SPEED_HIGH;
    Gpioled.GPIO_PinConfig.GPIO_PinOType = GPIO_MODE_OUT_OD;
    Gpioled.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;

    // Enable the clock for the GPIOA peripheral
    GPIO_PCLK_CTRL(GPIOA, ENABLE);
    // Initialise the GPIOA register with the above declared variables
    GPIO_Init(&Gpioled);



    
    // Infinite loop
    while(1){
        GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_5);
        delay(); 
    }
    return 0;
}
