Stm32 tools evaluation
======================

Trying out some setup combination with "Ac6 System Workbench" (Eclipse plugin) and Stm32cubemx


Setup start with Eclipse
========================

- the "SW" in the project names below stands for "Ac6 System Workbench"
- all projects are located in /D/git/Joe/Stm32-Tools-Evaluation
- example projecte created for Stm32F401C-Disco board with STM32F401VCTx (256k Flash, 64k Ram)

TODO:
- includepfade vergleichen
- .cproject vergleichen

- File → new → C++ Project → Ac6 Stm32 Mcu Project

  - Name = Stm32F4-SW-nofw
    - Location = /D/git/Joe/Stm32-Tools-Evaluation/Stm32F4-SW-nofw
    - Chips = Stm32F4, Board = Stm32F401C-Disco
    - Firmware Configuration = ⦿ No Firmware
  → no main.c

  - Stm32F4-SW-cubehal
    - Firmware Configuration = ⦿ Cube Hal
      - Stm32Cube_FW_F4_V1.9.0
      ☐ Extract all firmware in separate folder
      ☐ Add low level drivers in this project
  → project looks same as "nofw"

  - Stm32F4-SW-cubehal-sepfolder
    - Firmware Configuration = ⦿ Cube Hal
      ☑ Extract all firmware in separate folder
      ☐ Add low level drivers in this project
  → project looks same as "nofw" and "Stm32F4-SW-cubehal"
  → cube hal sources were put to to workspace/STM32Cube_FW_F4_V1.9.0 (23608 files, 7288 directories, 1,1 GiB!)
    - including things like "audio_sample.wav", "SetupSTM32CubeUpdater-4.2.0.exe" ...
  → I'd moved them to my git repo

  - Stm32F4-SW-cubehal-source
    - Firmware Configuration = ⦿ Cube Hal
      ☐ Extract all firmware in separate folder
      ☑ Add low level drivers in this project
        ⦿ As sources in the application project
        ⦾ As static external libraries
  → adds 3 directories (CMSIS, HAL_Driver, Utilities) to the project (171 files, 33 directories, 64 MiB)
  → much more stuff in .cproject

  - Stm32F4-SW-cubehal-lib
    - Firmware Configuration = ⦿ Cube Hal
      ☐ Extract all firmware in separate folder
      ☑ Add low level drivers in this project
        ⦾ As sources in the application project
        ⦿ As static external libraries
  → adds a project "stm32f401c-disco_hal_lib" to the workspace (default workspace location) with the 3 directories (CMSIS, HAL_Driver, Utilities) (279 files, 37 directories, 65 MiB!)
  → I'd moved them to my git repo

  - Stm32F4-SW-cubehal-sepfolder-source
    - Firmware Configuration = ⦿ Cube Hal
      ☑ Extract all firmware in separate folder
      ☑ Add low level drivers in this project
        ⦿ As sources in the application project
        ⦾ As static external libraries

  - Stm32F4-SW-cubehal-sepfolder-lib  --->>> skipped
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

  - Stm32F4-SW-cubehal-sepfolder-source-freertos  --->>> skipped
    - Firmware Configuration = ⦿ Cube Hal
      ☑ Extract all firmware in separate folder
      ☑ Add low level drivers in this project
        ⦿ As sources in the application project
        ⦾ As static external libraries
        ☑ FreeRtos

  - Stm32F4-SW-cubehal-sepfolder-lib-freertos  --->>> skipped
    - Firmware Configuration = ⦿ Cube Hal
      ☑ Extract all firmware in separate folder
      ☑ Add low level drivers in this project
        ⦾ As sources in the application project
        ⦿ As static external libraries
        ☑ FreeRtos



Setup start with CubeMX
========================

TODO
