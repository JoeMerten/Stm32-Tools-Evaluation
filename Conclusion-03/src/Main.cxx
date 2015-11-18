/***********************************************************************************************************************
  Stm Example
------------------------------------------------------------------------------------------------------------------------
  \copyright  © NumberFour 2015, all rights reserved
  \project    N4 Foundation
  \file       Main.cxx
  \creation   2015-11-18, Joe Merten
***********************************************************************************************************************/


#include <stm32f4xx.h>
#include <stm32f4xx_hal_uart.h>
//#include <usart.h>
#include <exception>
#include <cstring>

extern "C" {
void appInit() {
    HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
    //try {
    //    throw std::exception();
    //    HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
    //} catch (...) {
    //    HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14);
    //}
    //HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
}
}

// TODO: use Foundation instead
extern "C" {

__attribute__((used)) void _exit(int code) {
    (void)code;
    for (;;);
}

__attribute__((used)) void abort() {
    for (;;);
}


void myTerminateHandler() {
    for (;;);
}

namespace __cxxabiv1 {
    void (*__terminate_handler)() = myTerminateHandler;
}

__attribute__((used))  void __cxa_pure_virtual() {
    for (;;);
}

}
