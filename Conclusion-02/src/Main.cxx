/***********************************************************************************************************************
  Stm Example
------------------------------------------------------------------------------------------------------------------------
  \copyright  © NumberFour 2015, all rights reserved
  \project    N4 Foundation
  \file       Main.cxx
  \creation   2015-11-15, Joe Merten
***********************************************************************************************************************/


#include <stm32f4xx.h>
#include <stm32f4xx_hal_uart.h>
#include <usart.h>
#include <exception>
#include <cstring>

void printString(const char* s) {
    HAL_UART_Transmit(&huart2, (uint8_t*)s, strlen(s), 10000);
    HAL_UART_Transmit(&huart2, (uint8_t*)"\n", 1, 10000);
}


extern "C" void appMain() {
    printString("Hello World!");

    for(;;) {
        int delay = 100;
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) != 0) delay = 40;
        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
        HAL_Delay(delay);
        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
        HAL_Delay(delay);
        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14);
        HAL_Delay(delay);
        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
        HAL_Delay(delay);
        /*try {
            printString("throwing");
            throw std::exception();
            printString("not thrown?!");
        } catch (...) {
            printString("catched :-)");
        }*/
    }
}

extern "C" void abort() {
    printString("!!! ABORT !!!");
    for (;;);
}
//extern "C" void _exit() {}
