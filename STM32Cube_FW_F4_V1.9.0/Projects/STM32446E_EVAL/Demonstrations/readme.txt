/**
  @page Demo   STM32446E-EVAL Demonstration Firmware

  @verbatim
  ******************** (C) COPYRIGHT 2015 STMicroelectronics *******************
  * @file    Demonstrations/readme.txt
  * @author  MCD Application Team
  * @version V1.2.1
  * @date    09-October-2015
  * @brief   Description of STM32446E-EVAL Demonstration
  ******************************************************************************
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  @endverbatim

@par Demo Description

The STM32Cube Demonstration platform comes on top of the STM32CubeTM as a firmware
package that offers a full set of software components based on a modules architecture
allowing re-using them separately in standalone applications. All these modules are
managed by the STM32Cube Demonstration kernel allowing to dynamically adding new
modules and access to common resources (storage, graphical components and widgets,
memory management, Real-Time operating system)

The STM32Cube Demonstration platform is built around the powerful graphical library
STemWin and the FreeRTOS real time operating system and uses almost the whole STM32
capability to offer a large scope of usage based on the STM32Cube HAL BSP and several
middleware components.

@par Demonstration Overview

When the STM32446E-EVAL demonstration is launched for the first time, the touch screen
need to be calibrated.
You have to follow the displayed calibration instructions by touching the screen
at the indicated positions.
Once the touch screen calibrated, the supported demos will be viewed per icon.

 @note All icons are stored into external QSPI Flash memory.

Below you find an overview of the different offered modules in the demonstration:

 + System
 --------
 The system module provides three control tabs: system information, general settings
 and clock settings

 + File browser
 --------------
 The File browser module allows to explore the connected storage unit(s), to delete
 or to open a selected file.

 + Game
 -------
 The game coming in the STM32Cube demonstration is based on the Reversi game.

 + Benchmark
 -----------
 The Benchmark module allows measure the graphical performance by measuring the
 time needed to draw several coloured rectangles in random position with random
 size during a specific period.

 + Audio
 -------
 The audio player module supports playing music in WAV format.
 You can use the *.wav audio provided under "/Media/Audio" or any other ones.

 @note: Supported audio format: the audio player supports all wav PCM audio files with the following configurations:
          + Sample rate: 8 to 96 kHz
          + Channel number: stereo/mono
          + Audio data format: 16 bits
 @note: you can copy these file at the root any directory of the uSD or USB key

 + USB Mass storage Device
 -------------------------
 The USB device module includes mass storage device application using the MicroSD
 memory. The USB HS is used for the USB disk Flash storage unit.

 + Camera
 --------
 The camera application allows to directly and permanently display on the LCD the image
 captured using the camera module.

 + Image viewer
 --------------
 The Image viewer module allows displaying bmp and jpg pictures.
 You can use the *.jpg image files provided under "Utilities/Media/Pictures/JPG" or any other ones.

 @note: you can copy these file at the root any directory of the uSD or USB key

 For more details about the demonstration modules please refers to  STM32CubeF4 demonstration (UM1743)

 @note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
       based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
       a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
       than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
       To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.

 @note The application needs to ensure that the SysTick time base is always set to 1 millisecond
       to have correct HAL operation.


@par Hardware and Software environment

  - This demonstration runs on STM32F446xx RevA devices.
  - This demonstration has been tested with STM32446E-EVAL RevB evaluation board.
  - Jumpers configuration:
      - JP4: <2-3> (used for USB device module)
      - JP19: <1-2> (used for audio player module)


@par How to use it ?

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files
 - Open STM32 ST-Link Utility V3.6, click on "External Loader" from the bar menu then check "N25Q256A_STM32446E-EVAL" box
 - Connect the STM32446E-EVAL board to PC with USB cable through CN16
 - Set BOOT0 pin (SW1) to 1 to select RAM Boot
 - Use "STM32CubeDemo_STM32446E-EVAL_V1.0.0.hex" file with STM32 ST-Link Utility to program both internal Flash and external QSPI memory
 - Change BOOT0 pin (SW1) to 0, and reset the Board
 - Run the demonstration

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */

