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


extern "C" void appMain() {
    HAL_UART_Transmit(&huart2, (uint8_t*)"Hello World!\n", 13, 10000);

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
    }
}
