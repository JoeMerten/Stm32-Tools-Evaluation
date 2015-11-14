/**
  ******************************************************************************
  * @file    thirdparty_win.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    09-October-2015
  * @brief   third party functions
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "third_party_res.c"

/** @addtogroup THIRD_PARTY_MODULE
  * @{
  */

/** @defgroup THIRD PARTY
  * @brief third party routines
  * @{
  */

/* External variables --------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void Startup(WM_HWIN hWin, uint16_t xpos, uint16_t ypos);

/* Private typedef -----------------------------------------------------------*/
K_ModuleItem_Typedef  third_party_board =
{
  9,
  "Touch GFX",
  open_thirdprty,
  0,
  Startup,
  NULL,
};

/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  third party module window Startup
  * @param  hWin: pointer to the parent handle.
  * @param  xpos: X position
  * @param  ypos: Y position
  * @retval None
  */
static void Startup(WM_HWIN hWin, uint16_t xpos, uint16_t ypos)
{
  #ifdef INCLUDE_THIRD_PARTY_MODULE
  if(((*(uint32_t *)(GFX_DEMO_ADDRESS)) & 0x20000000)  == 0x20000000)
  {
    *(uint32_t *)(0x40024000) = GFX_DEMO_SIGNATURE_A;
    LCD_X_DisplayDriver(NULL, LCD_X_OFF, NULL);
    NVIC_SystemReset();
  }
  #endif
}

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
