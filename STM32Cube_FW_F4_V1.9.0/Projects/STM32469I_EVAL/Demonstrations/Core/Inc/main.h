/**
  ******************************************************************************
  * @file    main.h
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    09-October-2015
  * @brief   Header for main.c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
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
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx_it.h"

/* EVAL includes component */
#include "stm32469i_eval.h"
#include "stm32469i_eval_lcd.h"
#include "stm32469i_eval_ts.h"
#include "stm32469i_eval_sdram.h"
#include "stm32469i_eval_camera.h"
#include "stm32469i_eval_sd.h"
#include "stm32469i_eval_audio.h"
#include "stm32469i_eval_qspi.h"
#include "stm32469i_eval_eeprom.h"
#include "stm32469i_eval_nor.h"

/* FatFs includes components */
#include "ff_gen_drv.h"
#include "usbh_diskio.h"
#include "sd_diskio.h"

/* GUI includes components */
#include "gui.h"
#include "dialog.h"
#include "ST_GUI_Addons.h"

 /* Kernel includes components */
#include "k_module.h"
#include "k_storage.h"
#include "k_rtc.h"
#include "k_bsp.h"

/* utilities and standard includes components */
#include "cpu_utils.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* Exported types ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#ifdef INCLUDE_THIRD_PARTY_MODULE
 #define GFX_DEMO_ADDRESS                0x08100000
 #define GFX_DEMO_SIGNATURE_A            0x5AA55AAA
 #define GFX_DEMO_SIGNATURE_B            0x5AA55BBB
#endif
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
