/***********************************************************************************************************************
  Freertos Configuration
------------------------------------------------------------------------------------------------------------------------
  \copyright  © NumberFour 2015, all rights reserved
  \project    N4 Foundation
  \file       FreeRTOSConfig.h.h
  \creation   2015-11-15, Joe Merten
------------------------------------------------------------------------------------------------------------------------
  For the first tryout, this is copied from payment unittest
***********************************************************************************************************************/

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#define configUSE_PREEMPTION            1
#define configIDLE_SHOULD_YIELD         1
#define configUSE_IDLE_HOOK                     0
#define configUSE_TICKLESS_IDLE                 0
#define configEXPECTED_IDLE_TIME_BEFORE_SLEEP   3   // default is 2
//#   define configPRE_SLEEP_PROCESSING( x )      mml_pm_pre_sleep_processing(&(x))
//#   define configPOST_SLEEP_PROCESSING(x )      mml_pm_post_sleep_processing(&(x))
#define configUSE_TICK_HOOK             0
#define configCPU_CLOCK_HZ              ((unsigned long)84000000)
#define configTICK_RATE_HZ              ((portTickType)1000)
#define configMINIMAL_STACK_SIZE        ((unsigned short)170)
#define configTOTAL_HEAP_SIZE           ((size_t)40000)
#define configMAX_TASK_NAME_LEN         10
#define configUSE_TRACE_FACILITY        1
#define configUSE_16_BIT_TICKS          0
#define configUSE_CO_ROUTINES           0
#define configUSE_MUTEXES               1
#define configUSE_RECURSIVE_MUTEXES     1
#define configUSE_COUNTING_SEMAPHORES   1

#define configMAX_PRIORITIES            5
#define configMAX_CO_ROUTINE_PRIORITIES 2

// configUSE_PORT_OPTIMISED_TASK_SELECTION must be set to 0 for using the CodeConfidence debug plugin
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 0

#define configPORTMALLOC_SCHEME         4

// Set the following definitions to 1 to include the API function, or zero to exclude the API function.

#define INCLUDE_vTaskPrioritySet              1
#define INCLUDE_uxTaskPriorityGet             1
#define INCLUDE_vTaskDelete                   1
#define INCLUDE_vTaskCleanUpResources         1
#define INCLUDE_vTaskSuspend                  1
#define INCLUDE_vTaskDelayUntil               1
#define INCLUDE_vTaskDelay                    1
#define INCLUDE_eTaskGetState                 1
#define INCLUDE_pcTaskGetTaskName             1
#define INCLUDE_uxTaskGetStackHighWaterMark   1
#define INCLUDE_xTimerPendFunctionCall        1

#define configKERNEL_INTERRUPT_PRIORITY         255
// !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!! See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html.
#define configKERNEL_INTERRUPT_PRIORITY         255
#define configMAX_SYSCALL_INTERRUPT_PRIORITY    (1<<5) // equivalent to 0xa0, or priority 5.

#define configCHECK_FOR_STACK_OVERFLOW          2

// SPB added for timers to work
#define configUSE_TIMERS                        1
#define configTIMER_TASK_PRIORITY               3
#define configTIMER_QUEUE_LENGTH                10
#define configTIMER_TASK_STACK_DEPTH            (2*configMINIMAL_STACK_SIZE)

#if 1
  #include <N4/FreeRtos/FaultHooks.h>
  #define configASSERT(x)   if ((x) == 0) FreeRtosConfigAssert(__FILE__, __LINE__)
#else
  #define configASSERT(x)   if ((x) == 0) while(1)
#endif

#if 1
  // for tracking runtime stats
  #define configGENERATE_RUN_TIME_STATS   1
  #include <N4/FreeRtos/RuntimeStatsTimer.h>
#endif

#if 1
  // For tracking heaptraffic
  #include <N4/FreeRtos/HeapTrace.h>
  #define traceMALLOC(/*void**/ ptr, /*size_t*/ size) FreeRtosTraceMalloc(ptr, size)
  #define traceFREE(/*void**/ ptr, /*size_t*/ size)   FreeRtosTraceFree(ptr, size)
#endif

#endif // FREERTOS_CONFIG_H
