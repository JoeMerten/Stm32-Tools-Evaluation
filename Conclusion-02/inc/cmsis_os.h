/***********************************************************************************************************************
  Rtos api which is needed by some of the CubeMX generated code
------------------------------------------------------------------------------------------------------------------------
  \copyright  © NumberFour 2015, all rights reserved
  \project    N4 Foundation
  \file       cmsis_os.h
  \creation   2015-11-17, Joe Merten
***********************************************************************************************************************/

#ifndef N4_CMSIS_OS_H
#define N4_CMSIS_OS_H

#include <N4/Foundation.h>
#if N4_TARGET_STM32 and N4_THREADING_FREERTOS
EXTERNC_BEGIN

typedef enum  {
  osOK       =     0,       ///< function completed; no error or event occurred.
  osErrorOS  =  0xFF,       ///< unspecified RTOS error: run-time error but no other error message fits.
} osStatus;

osStatus osKernelStart();
void osSystickHandler();

EXTERNC_END
#endif // N4_TARGET_STM32 and N4_THREADING_FREERTOS
#endif // N4_CMSIS_OS_H
