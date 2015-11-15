Stm32 tools evaluation
======================

Trying out some setup combination with "Ac6 System Workbench" (Eclipse plugin) and Stm32cubemx


Conclusion
==========

Conclusion-01
-------------

- create projects using System Workbench (eclipse plugin)
  - Name = Conclusion-01
  - ⦿ Cube Hal
  - ☑ Add low level drivers in this project
  - ⦿ As sources in the application project
  - about the CMSIS, HAL_Driver and Utility directory (and maybe even the startup directory), I think I'll move it later to a central place (e.g. Foundation)
- create CubeMX project with the same name
  - locate it into a subfolder (cubemx) of the System Workbench project
  - Project
    - Name = Conclusion-01
    - Project Location = C:\Papa\git\Joe\Stm32-Tools-Evaluation\Conclusion-01\cubemx
    - Toolchain = SW4STM32
    - and ignore the generated .project / .cproject
    - save 
      → C:\Papa\git\Joe\Stm32-Tools-Evaluation\Conclusion-01\cubemx\Conclusion-01\Conclusion-01.ioc
      →      /D/git/Joe/Stm32-Tools-Evaluation/Conclusion-01/cubemx/Conclusion-01/Conclusion-01.ioc
    - generate code
- add cubemx include path and source path to eclipse project
- main redirect, missing include in gpio.c, 
- TODO ...


Conclusion-02
-------------

- create projects using System Workbench (eclipse plugin)
  - new C++ project
    - Name = Conclusion-02
    - Location = /D/git/Joe/Stm32-Tools-Evaluation/Conclusion-02
    - Ac6 Mcu Project
  - Mcu Configuration
    - Series = Stm32F4
    - Board = Stm32F401C-Disco
  - Firmware Configuration
    - ⦿ Cube Hal
    - ☑ Add low level drivers in this project
    - ⦿ As sources in the application project
    - no additional drivers and no third party unitities (for the first)
  - add org.eclispe.cdt/core*.prefs to .settings
  - delete directories CMSIS, HAL_Driver, Utilities
  - delete stm32f4xx_it.h, stm32f4xx_it.c, syscalls.c
  - TODO: check if we could also delete system_stm32f4xx.c, startup_stm32f401xc.s, LinkerScript.ld
  - rename main.c to Main.cxx
  - add eclipse links for Foundation, Cubehal and Freertos
  - Path and Symbols, include paths (see below)
- create CubeMX project with the same name
  - locate it into a subfolder (cubemx) of the System Workbench project
  - Project
    - Name = Conclusion-01
    - Project Location = C:\Papa\git\Joe\Stm32-Tools-Evaluation\Conclusion-01\cubemx
    - Toolchain = SW4STM32
    - and ignore the generated .project / .cproject
    - save 
      → C:\Papa\git\Joe\Stm32-Tools-Evaluation\Conclusion-01\cubemx\Conclusion-01\Conclusion-01.ioc
      →      /D/git/Joe/Stm32-Tools-Evaluation/Conclusion-01/cubemx/Conclusion-01/Conclusion-01.ioc
    - generate code
- add cubemx include path and source path to eclipse project
- main redirect, missing include in gpio.c, 
- TODO ...


- Include Paths
    - ${ProjDirPath}/inc
    - ${Foundation}/include
    - ${Freertos}/FreeRtos/Source/Include
    - ${Freertos}/FreeRtos/Source/portable/GCC/ARM_CM4F
    - ${Cubehal}/Drivers/STM32F4xx_HAL_Driver/Inc
    - ${Cubehal}/Drivers/CMSIS/Include
    - ${Cubehal}/Drivers/CMSIS/Device/ST/STM32F4xx/Include
    - ...
    - → unfortunately not working, see http://stackoverflow.com/questions/33722497/how-to-use-an-eclipse-variable-for-include-path
        therefore set this instead:
    - ${ProjDirPath}/inc
    - ${ProjDirPath}/cubemx/Conclusion-02/Inc
    - ../../../N4/n4-Foundation/Framework/include
    - ../../../N4/n4-Foundation/Framework/lib/FreeRtos/FreeRtos_8.2.2/FreeRtos/Source/include
    - ../../../N4/n4-Foundation/Framework/lib/FreeRtos/FreeRtos_8.2.2/FreeRtos/Source/portable/GCC/ARM_CM4F
    - ../../../N4/n4-Foundation/Framework/lib/Stm/STM32Cube_FW_F4_V1.9.0/Drivers/STM32F4xx_HAL_Driver/Inc
    - ../../../N4/n4-Foundation/Framework/lib/Stm/STM32Cube_FW_F4_V1.9.0/Drivers/CMSIS/Include
    - ../../../N4/n4-Foundation/Framework/lib/Stm/STM32Cube_FW_F4_V1.9.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include

- <sourceEntries>
  - inc
  - src
  - startup
  - cubemx                                   /Conclusion-02/Src
  - Cubehal/Drivers/STM32F4xx_HAL_Driver     /Src  
  - Foundation/src
  - Foundation/tests       TODO
  - Freertos/FreeRtos/Source/portable/GCC/ARM_CM4F ...
    <entry excluding="portable/GCC/ARM_CM0/|portable/GCC/ARM_CM3/|portable/GCC/ARM_CM3_MPU/|portable/GCC/ARM_CM7/|portable/MemMang/heap_1.c|portable/MemMang/heap_2.c|portable/MemMang/heap_3.c|portable/MemMang/heap_5.c|portable/MSVC-MingW/" flags="VALUE_WORKSPACE_PATH" kind="sourcePath" name="Freertos/FreeRtos/Source"/>

- C/C++ Build → Settings
  - All confiburations?
  - GCC
    - Dialect       -std=gnu11
    - Optimization  -Og  (maybe)  -fdata-sections
    - Warnings      -Wall -Wextra   -Wconversion?
    - Miscellaneous -Wundef 
  - G++
    - Dialect        -std=gnu++1y
    - Optimization like gcc
    - Warnings like gcc
    - Miscellaneous  -Wundef -Weffc++ -Woverloaded-virtual
    - Miscellaneous allow exceptions and rtti
    - Miscellaneous TODO: what about -slow-flash-data?
  - Linker
    - Miscellaneous allow exceptions and rtti


Setup start with Eclipse
========================

- means "Ac6-Tools System Workbench for STM32 - Bare Metal Edition", plugin installed in eclipse luna sr2 running on Kubuntu 14.04 32 Bit
  - ARM Compiler for MCU (for Linux 32 bits)  1.3.0.201507241119    fr.ac6.feature.mcu.externaltools.armnone.linux32.feature.group
  - External Tools for Linux (32 bits)        1.3.0.201507241119    fr.ac6.feature.mcu.externaltools.linux32.feature.group
    - OpenOCD (for Linux 32 bits)             1.5.0.201510231515    fr.ac6.feature.mcu.externaltools.openocd.linux32.feature.group
  - OpenSTM32 IDE                             1.5.1.201511021136    fr.ac6.feature.mcu.ide.feature.group
  - OpenSTM32 Linker Script editor            1.3.0.201507241045    fr.ac6.feature.mcu.ldscript.feature.group
  - OpenSTM32 Remote debugging support        1.5.0.201510231435    fr.ac6.feature.mcu.debug.feature.group
- the "SW" in the project names below stands for "System Workbench"
- all projects are located locally in /D/git/Joe/Stm32-Tools-Evaluation
- example project created for Stm32F401C-Disco board with STM32F401VCTx (256k Flash, 64k Ram)


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
  → !!! for unknown reason, this generates a project with a linker script differen to e.g. Stm32F4-SW-cubehal
    - Stm32F4-SW-cubehal: Linker script for STM32F401VCTx
    - but here: Linker script for STM32F401CC
    - http://www.openstm32.org/tiki-view_forum_thread.php?comments_parentId=1438
  → different things in startup directory
    - Stm32F4-SW-cubehal: startup_stm32.s (author="Ac6")
    - Stm32F4-SW-cubehal-source: versus startup_stm32f401xc.s (author="MCD Application Team")
  → 32 include paths added (all for 6 times gcc, gxx, asm / debug & release)

  - Stm32F4-SW-cubehal-lib
    - Firmware Configuration = ⦿ Cube Hal
      ☐ Extract all firmware in separate folder
      ☑ Add low level drivers in this project
        ⦾ As sources in the application project
        ⦿ As static external libraries
  → adds a project "stm32f401c-disco_hal_lib" to the workspace (default workspace location) with the 3 directories (CMSIS, HAL_Driver, Utilities) (279 files, 37 directories, 65 MiB!)
  → I'd moved them to my git repo
  → when creating such project a second time, the .cproject seems to be incomplete (e.g. all of the includepaths, ...)

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
=======================

- projects created with CubeMX Version 4.11.0, running on Windows 7, 64 Bit
- File → New Project → Board Selector → Stm32F401C-Disco
- Project Settings
  - see also 05_STM32L4_Putting_All_Together.pdf, page 49ff
  - Project
    - Name = Stm32F4-MX-copyAll
    - Project Location = C:\Papa\git\Joe\Stm32-Tools-Evaluation
    - Toolchain = SW4STM32
  - Code Generator
    - Cube Firmware Library Package
      - ⦾ Copy all used libraries into the project folder                                             → TODO: check the effect
      - ⦿ Copy only the necessary library files                                                       → TODO: check the effect
      - ⦾ Add necessary library files as reference in the toolchain project configuration file        → TODO: check the effect
    - Generated Files
      - ☑ Generate peripheral initialization as a pair of .c/.h files per IP                          → TODO: check the effect
      - ☐ Backup previously generated files when re-generating
      - ☑ Keep user code when when re-generating
      - ☑ Delete previously generated files when not re-generated
    - Hal Settings
      - ☐ Set all free pins as analog                                                                 → TODO: check the effect
      - ☐ Enable full assert                                                                          → TODO: check the effect
- Save Project, results in a Stm32F4-MX-copyAll/Stm32F4-MX-copyAll.ioc

- removed that "Configuration" postfix from .project (1x) and .cproject (5x)
→ STM32F401VCTx_FLASH.ld looks close like the LinkerScript.ld in Stm32F4-SW-cubehal-source and Stm32F4-SW-cubehal-lib
→ 


Directory Structure
===================
- ProjectRoot
  - .project, .cproject, .settings → generated by Eclipse Wizard
  - cubemx → generated code from cubemx
  - inc, src → application source
  - Debug, Release → output directories



GCC Invocation
==============

arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32F401C_DISCO -DSTM32F401VCTx -DSTM32 -DSTM32F4 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -I"/D/git/Joe/Stm32-Tools-Evaluation/Conclusion-01/inc" -I"/D/git/Joe/Stm32-Tools-Evaluation/Conclusion-01/Utilities/STM32F401-Discovery" -I"/D/git/Joe/Stm32-Tools-Evaluation/Conclusion-01/Utilities/Fonts" -I"/D/git/Joe/Stm32-Tools-Evaluation/Conclusion-01/Utilities/Components/lis302dl" -I"/D/git/Joe/Stm32-Tools-Evaluation/Conclusion-01/Utilities/Components/ov2640" -I"/D/git/Joe/Stm32-Tools-Evaluation/Conclusion-01/Utilities/Components/stmpe1600" -I"/D/git/Joe/Stm32-Tools-Evaluation/Conclusion-01/Utilities/Components/otm8009a" -I"/D/git/Joe/Stm32-Tools-Evaluation/Conclusion-01/Utilities/Components/ft6x06" -I"/D/git/Joe/Stm32-Tools-Evaluation/Conclusion-01/Utilities/Components/ili9325" -I"/D/git/Joe/Stm32-Tools-Evaluation/Conclusion-01/Utilities/Components/cs43l22" -I"/D/git/Joe/Stm32-Tools-Evaluation/Conclusion-01/Utilities/Components/ili9341" -I"/D/git/Joe/Stm32-Tools-Evaluation/Conclusion-01/Utilities/Components/mfxstm32l152" -I"/D/git/Joe/Stm32-Tools-Evaluation/Conclusion-01/Utilities/Components/lis3dsh" -I"/D/git/Joe/Stm32-Tools-Evaluation/Conclusion-01/Utilities/Components/st7735" -I"/D/git/Joe/Stm32-Tools-Evaluation/Conclusion-01/Utilities/Components/n25q512a" -I"/D/git/Joe/Stm32-Tools-Evaluation/Conclusion-01/Utilities/Components/n25q256a" -I"/D/git/Joe/Stm32-Tools-Evaluation/Conclusion-01/Utilities/Components/Common" -I"/D/git/Joe/Stm32-Tools-Evaluation/Conclusion-01/Utilities/Components/ts3510" -I"/D/git/Joe/Stm32-Tools-Evaluation/Conclusion-01/Utilities/Components/s5k5cag" -I"/D/git/Joe/Stm32-Tools-Evaluation/Conclusion-01/Utilities/Components/ampire640480" -I"/D/git/Joe/Stm32-Tools-Evaluation/Conclusion-01/Utilities/Components/s25fl512s" -I"/D/git/Joe/Stm32-Tools-Evaluation/Conclusion-01/Utilities/Components/ampire480272" -I"/D/git/Joe/Stm32-Tools-Evaluation/Conclusion-01/Utilities/Components/lsm303dlhc" -I"/D/git/Joe/Stm32-Tools-Evaluation/Conclusion-01/Utilities/Components/stmpe811" -I"/D/git/Joe/Stm32-Tools-Evaluation/Conclusion-01/Utilities/Components/exc7200" -I"/D/git/Joe/Stm32-Tools-Evaluation/Conclusion-01/Utilities/Components/n25q128a" -I"/D/git/Joe/Stm32-Tools-Evaluation/Conclusion-01/Utilities/Components/wm8994" -I"/D/git/Joe/Stm32-Tools-Evaluation/Conclusion-01/Utilities/Components/l3gd20" -I"/D/git/Joe/Stm32-Tools-Evaluation/Conclusion-01/Utilities" -I"/D/git/Joe/Stm32-Tools-Evaluation/Conclusion-01/HAL_Driver/Inc" -I"/D/git/Joe/Stm32-Tools-Evaluation/Conclusion-01/HAL_Driver/Inc/Legacy" -I"/D/git/Joe/Stm32-Tools-Evaluation/Conclusion-01/CMSIS/core" -I"/D/git/Joe/Stm32-Tools-Evaluation/Conclusion-01/CMSIS/device" -I"/D/git/Joe/Stm32-Tools-Evaluation/Conclusion-01/cubemx/Conclusion-01/Inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"cubemx/Conclusion-01/Src/usart.d" -MT"cubemx/Conclusion-01/Src/usart.o" -o "cubemx/Conclusion-01/Src/usart.o" "../cubemx/Conclusion-01/Src/usart.c"
arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32F401C_DISCO -DSTM32F401VCTx -DSTM32 -DSTM32F4 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC

-fno-exceptions -mslow-flash-data -fno-rtti 

-DSTM32F401C_DISCO -DSTM32F401VCTx -DSTM32 -DSTM32F4 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC 