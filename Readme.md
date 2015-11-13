Stm32 tools evaluation
======================

Trying out some setup combination with "Ac6 System Workbench" (Eclipse plugin) and Stm32cubemx


Setup start with Eclipse
========================

- File → new → C++ Project → Ac6 Stm32 Mcu Project

  - Name = Stm32F4-SW-nofw
    - Location = /D/git/Joe/Stm32-Tools-Evaluation/Stm32F4-SW-nofw
    - Chips = Stm32F4, Board = Stm32F401C-Disco
    - Firmware Configuration = ⦿ No Firmware

  - Stm32F4-SW-cubefw
    - Firmware Configuration = ⦿ Cube Hal
      - Stm32Cube_FW_F4_V1.9.0
      ☐ Extract all firmware in separate folder
      ☐ Add low level drivers in this project

  - Stm32F4-SW-cubefw-sepfolder
    - Firmware Configuration = ⦿ Cube Hal
      ☑ Extract all firmware in separate folder
      ☐ Add low level drivers in this project

  - Stm32F4-SW-cubefw-source
    - Firmware Configuration = ⦿ Cube Hal
      ☐ Extract all firmware in separate folder
      ☑ Add low level drivers in this project
        ⦿ As sources in the application project
        ⦾ As static external libraries

  - Stm32F4-SW-cubefw-lib
    - Firmware Configuration = ⦿ Cube Hal
      ☐ Extract all firmware in separate folder
      ☑ Add low level drivers in this project
        ⦾ As sources in the application project
        ⦿ As static external libraries

  - Stm32F4-SW-cubefw-sepfolder-source
    - Firmware Configuration = ⦿ Cube Hal
      ☑ Extract all firmware in separate folder
      ☑ Add low level drivers in this project
        ⦿ As sources in the application project
        ⦾ As static external libraries

  - Stm32F4-SW-cubefw-sepfolder-lib
    - Firmware Configuration = ⦿ Cube Hal
      ☑ Extract all firmware in separate folder
      ☑ Add low level drivers in this project
        ⦾ As sources in the application project
        ⦿ As static external libraries

  - Stm32F4-SW-cubefw-source-freertos
    - Firmware Configuration = ⦿ Cube Hal
      ☐ Extract all firmware in separate folder
      ☑ Add low level drivers in this project
        ⦿ As sources in the application project
        ⦾ As static external libraries
        ☑ FreeRtos

  - Stm32F4-SW-cubefw-lib-freertos
    - Firmware Configuration = ⦿ Cube Hal
      ☐ Extract all firmware in separate folder
      ☑ Add low level drivers in this project
        ⦾ As sources in the application project
        ⦿ As static external libraries
        ☑ FreeRtos

  - Stm32F4-SW-cubefw-sepfolder-source-freertos
    - Firmware Configuration = ⦿ Cube Hal
      ☑ Extract all firmware in separate folder
      ☑ Add low level drivers in this project
        ⦿ As sources in the application project
        ⦾ As static external libraries
        ☑ FreeRtos

  - Stm32F4-SW-cubefw-sepfolder-lib-freertos
    - Firmware Configuration = ⦿ Cube Hal
      ☑ Extract all firmware in separate folder
      ☑ Add low level drivers in this project
        ⦾ As sources in the application project
        ⦿ As static external libraries
        ☑ FreeRtos



Setup start with CubeMX
========================

TODO
