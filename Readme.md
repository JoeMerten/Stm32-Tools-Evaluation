Stm32 tools evaluation
======================

Trying out some setup combination with "Ac6 System Workbench" (Eclipse plugin) and Stm32cubemx


Setup start with Eclipse
========================

The "SW" in the project names below stands for "Ac6 System Workbench"
All projects are located in /D/git/Joe/Stm32-Tools-Evaluation/

- File → new → C++ Project → Ac6 Stm32 Mcu Project

  - Name = Stm32F4-SW-nofw
    - Location = /D/git/Joe/Stm32-Tools-Evaluation/Stm32F4-SW-nofw
    - Chips = Stm32F4, Board = Stm32F401C-Disco
    - Firmware Configuration = ⦿ No Firmware

  - Stm32F4-SW-cubehal
    - Firmware Configuration = ⦿ Cube Hal
      - Stm32Cube_FW_F4_V1.9.0
      ☐ Extract all firmware in separate folder
      ☐ Add low level drivers in this project

  - Stm32F4-SW-cubehal-sepfolder
    - Firmware Configuration = ⦿ Cube Hal
      ☑ Extract all firmware in separate folder
      ☐ Add low level drivers in this project

  - Stm32F4-SW-cubehal-source
    - Firmware Configuration = ⦿ Cube Hal
      ☐ Extract all firmware in separate folder
      ☑ Add low level drivers in this project
        ⦿ As sources in the application project
        ⦾ As static external libraries

  - Stm32F4-SW-cubehal-lib
    - Firmware Configuration = ⦿ Cube Hal
      ☐ Extract all firmware in separate folder
      ☑ Add low level drivers in this project
        ⦾ As sources in the application project
        ⦿ As static external libraries

  - Stm32F4-SW-cubehal-sepfolder-source
    - Firmware Configuration = ⦿ Cube Hal
      ☑ Extract all firmware in separate folder
      ☑ Add low level drivers in this project
        ⦿ As sources in the application project
        ⦾ As static external libraries

  - Stm32F4-SW-cubehal-sepfolder-lib
    - Firmware Configuration = ⦿ Cube Hal
      ☑ Extract all firmware in separate folder
      ☑ Add low level drivers in this project
        ⦾ As sources in the application project
        ⦿ As static external libraries

  - Stm32F4-SW-cubehal-source-freertos
    - Firmware Configuration = ⦿ Cube Hal
      ☐ Extract all firmware in separate folder
      ☑ Add low level drivers in this project
        ⦿ As sources in the application project
        ⦾ As static external libraries
        ☑ FreeRtos

  - Stm32F4-SW-cubehal-lib-freertos
    - Firmware Configuration = ⦿ Cube Hal
      ☐ Extract all firmware in separate folder
      ☑ Add low level drivers in this project
        ⦾ As sources in the application project
        ⦿ As static external libraries
        ☑ FreeRtos

  - Stm32F4-SW-cubehal-sepfolder-source-freertos
    - Firmware Configuration = ⦿ Cube Hal
      ☑ Extract all firmware in separate folder
      ☑ Add low level drivers in this project
        ⦿ As sources in the application project
        ⦾ As static external libraries
        ☑ FreeRtos

  - Stm32F4-SW-cubehal-sepfolder-lib-freertos
    - Firmware Configuration = ⦿ Cube Hal
      ☑ Extract all firmware in separate folder
      ☑ Add low level drivers in this project
        ⦾ As sources in the application project
        ⦿ As static external libraries
        ☑ FreeRtos



Setup start with CubeMX
========================

TODO
