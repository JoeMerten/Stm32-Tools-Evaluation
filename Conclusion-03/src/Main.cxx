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

#include <N4/UartStream.hxx>
#include <N4/Timeter.hxx>
#include <N4/Thread.hxx>
#include <N4/Logger.h>

N4_LOG_FILE_REGION(Main);



extern "C" {
void appInit() {
    HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
    try {
        throw std::exception();
        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
    } catch (...) {
        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14);
    }
    HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
}
}





// TODO: Move this code to Foundation
#define N4_CONSOLE_UART 2

N4::UartStream::UartStream(const char* optionalName): InOutStream(optionalName) {
#if N4_CONSOLE_UART
#endif
}

void N4::UartStream::write(const void* buffer, long length) {
#if N4_CONSOLE_UART
    //HAL_UART_Transmit(&huart2, (uint8_t*)buffer, length, 10000);
#endif
}
EXTERNC_DECL int uart_write_char(char c) {
#if N4_CONSOLE_UART
    //HAL_UART_Transmit(&huart2, (uint8_t*)&c, 1, 10000);
#endif
    return 0;
}


// TODO: Move this code to Foundation

uint32_t N4::Timeter::frequency = 1000000;
static uint64_t dummyTicker = 0;
uint64_t N4::Timeter::impGetTicks() noexcept {
    return dummyTicker++;
}

uint64_t N4::Timeter::impTicksToUs(uint64_t elapsed) noexcept {
    return elapsed;
}
uint64_t N4::Timeter::impTicksToMs(uint64_t elapsed) noexcept {
    return elapsed / 1000;
}


// TODO: Adjust this to linker script
extern uint32_t __section_start_data;
//extern uint32_t __section_start_stack;
extern uint32_t __section_end_stack;

uint32_t __section_start_data = 0;
//extern uint32_t __section_start_stack;
uint32_t __section_end_stack = 0;

