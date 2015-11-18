/***********************************************************************************************************************
  Rtos api which is needed by some of the CubeMX generated code
------------------------------------------------------------------------------------------------------------------------
  \copyright  © NumberFour 2015, all rights reserved
  \project    N4 Foundation
  \file       cmsis_os.c
  \creation   2015-11-17, Joe Merten
------------------------------------------------------------------------------------------------------------------------
  Alternatively, we could use the likely full implemented cmsis_os from the cube hal library which is located in
  STM32Cube_FW_F4_V1.9.0/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.h/.c
  Maybe this is needed when using other cube hal middleware components.
***********************************************************************************************************************/

#include <cmsis_os.h>
#if N4_TARGET_STM32 and N4_THREADING_FREERTOS
#include <N4/Emergency.h>

#include "FreeRTOS.h"
#include "task.h"


osStatus osKernelStart() {
    vTaskStartScheduler();
    emergency("StartScheduler returned");
    return osErrorOS;
}

extern void xPortSysTickHandler();
void osSystickHandler() {
    xPortSysTickHandler();
}

#endif // N4_TARGET_STM32 and N4_THREADING_FREERTOS
