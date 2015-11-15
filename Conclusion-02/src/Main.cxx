/***********************************************************************************************************************
  Stm Example
------------------------------------------------------------------------------------------------------------------------
  \copyright  © NumberFour 2015, all rights reserved
  \project    N4 Foundation
  \file       Main.cxx
  \creation   2015-11-15, Joe Merten
***********************************************************************************************************************/

#define USE_THREADING 0

#include <stm32f4xx.h>
#include <stm32f4xx_hal_uart.h>
#include <usart.h>
#include <exception>
#include <cstring>

#include <N4/UartStream.hxx>
#include <N4/Timeter.hxx>
#include <N4/Thread.hxx>
#include <N4/Logger.h>

N4_LOG_FILE_REGION(Main);

void printString(const char* s) {
    HAL_UART_Transmit(&huart2, (uint8_t*)s, strlen(s), 10000);
    HAL_UART_Transmit(&huart2, (uint8_t*)"\n", 1, 10000);
}

void impDelay(int ms) {
#if USE_THREADING
    //N4::Thread::sleepMs(delay);
#else
    // HAL_Delay() geht nicht mehr, da wir Freertos mitbauen
    //HAL_Delay(ms);
    for (int i = 0; i < ms; i++) {
        for (int j = 0; j < 4000; j++) {
            asm volatile ( "NOP\n\t" "NOP\n\t" "NOP\n\t" "NOP\n\t" "NOP\n\t" "NOP\n\t" "NOP\n\t" "NOP\n\t" "NOP\n\t" "NOP\n\t" );
        }
    }
#endif
}


class MyThread: public N4::Thread {
    UNCOPYABLE(MyThread);
public:
    explicit MyThread(const char* name, uint32_t gpioPin, int delay): Thread(name, 1000), gpioPin(gpioPin), delay(delay) {}
    virtual void threadFunction() override {
        for (;;) {
            HAL_GPIO_TogglePin(GPIOD, gpioPin);
            sleepMs(delay);
        }
    }
private:
    uint32_t gpioPin;
    int delay;
};


extern "C" void appMain() {
    printString("Hello World!");
    LOG_INFO("Just started");

#if USE_THREADING
    new MyThread("1", GPIO_PIN_12, 500);
    new MyThread("2", GPIO_PIN_13, 700);
    new MyThread("3", GPIO_PIN_14, 900);
    new MyThread("4", GPIO_PIN_15, 1300);

    N4::Thread::startScheduler();
#else
    for(;;) {
        LOG_INFO("in the loop");
        int delay = 100;
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) != 0) delay = 40;
        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
        impDelay(delay);
        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
        impDelay(delay);
        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14);
        impDelay(delay);
        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
        impDelay(delay);
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) != 0)
        try {
            printString("throwing");
            throw std::exception();
            printString("not thrown?!");
        } catch (...) {
            printString("catched :-)");
        }
    }
#endif
}


// TODO: Move this code to Foundation
#define N4_CONSOLE_UART 2

N4::UartStream::UartStream(const char* optionalName): InOutStream(optionalName) {
#if N4_CONSOLE_UART
#endif
}

void N4::UartStream::write(const void* buffer, long length) {
#if N4_CONSOLE_UART
    HAL_UART_Transmit(&huart2, (uint8_t*)buffer, length, 10000);
#endif
}
EXTERNC_DECL int uart_write_char(char c) {
#if N4_CONSOLE_UART
    HAL_UART_Transmit(&huart2, (uint8_t*)&c, 1, 10000);
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

