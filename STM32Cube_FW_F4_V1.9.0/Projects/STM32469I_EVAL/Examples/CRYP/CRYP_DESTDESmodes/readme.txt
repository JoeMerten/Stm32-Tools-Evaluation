/**
  @page CRYP_DESTDESmodes  Encrypt and Decrypt data using DES and TDES Algorithms
  in all chaining modes.

  @verbatim
  ******************** (C) COPYRIGHT 2015 STMicroelectronics *******************
  * @file    CRYP/CRYP_DESTDESmodes/readme.txt
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    09-October-2015
  * @brief   Description of the CRYP DES and TDES Algorithm in all modes Example
  ******************************************************************************
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  @endverbatim

@par Example Description

This example provides a short description of how to use the CRYPTO peripheral to
encrypt and decrypt data using DES and TDES in all modes (ECB, CBC) Algorithm.

For this example, a firmware is used to interface with the Crypto peripheral
in polling mode.

This example is behaves as follows:
1. DES
  - DES ECB Encryption
  - DES ECB Decryption
  - DES CBC Encryption
  - DES CBC Decryption
2. TDES
  - TDES ECB Encryption
  - TDES ECB Decryption
  - TDES CBC Encryption
  - TDES CBC Decryption

The Plain data, encrypted data and decrypted data can be displayed on a PC
HyperTerminal using the USART.

The USARTx is configured as follows:
    - BaudRate = 115200 baud
    - Word Length = 8 Bits
    - One Stop Bit
    - No parity
    - Hardware flow control disabled (RTS and CTS signals)
    - Receive and transmit enabled

@note The connection of the LCD reset pin to a dedicated GPIO PK7 instead of the STM32F469 NRST pin may cause residual display on LCD with applications/examples that do not require display.
      The LCD clear can be ensured by hardware through the board's power off/power on or by software calling the BSP_LCD_Reset() function.

@par Directory contents

  - CRYP/CRYP_DESTDESmodes/Inc/stm32f4xx_hal_conf.h    HAL configuration file
  - CRYP/CRYP_DESTDESmodes/Inc/stm32f4xx_it.h          Interrupt handlers header file
  - CRYP/CRYP_DESTDESmodes/Inc/main.h                  Header for main.c module
  - CRYP/CRYP_DESTDESmodes/Src/stm32f4xx_it.c          Interrupt handlers
  - CRYP/CRYP_DESTDESmodes/Src/main.c                  Main program
  - CRYP/CRYP_DESTDESmodes/Src/stm32f4xx_hal_msp.c     HAL MSP module
  - CRYP/CRYP_DESTDESmodes/Src/system_stm32f4xx.c      STM32F4xx system source file


@par Hardware and Software environment

  - This example runs on STM32F479xx devices.

  - This example has been tested and validated with STM32479I-EVAL revB board and can be
    easily tailored to any other supported device and development board.

  - Hyperterminal configuration:
    - BaudRate = 115200 baud
    - Word Length = 8 Bits
    - One Stop Bit
    - No parity
    - Hardware flow control disabled (RTS and CTS signals)
    - Receive and transmit enabled

    @note Make sure that :
    - jumper JP8  is on RS232_RX position (1-2)  and
    - jumper JP15 is on USART1_RX position 1-2)and
    - jumper JP19 is on USART1_TX position (1-2).

@par How to use it ?

In order to make the program work, you must do the following:
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example


 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
