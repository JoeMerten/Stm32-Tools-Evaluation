/**
  ******************************************************************************
  * @file    USB_Host/MSC_RTOS/Src/menu.c
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    09-October-2015
  * @brief   This file implements Menu Functions
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

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
MSC_DEMO_StateMachine msc_demo;
osSemaphoreId MenuEvent;
__IO uint8_t ExploreDisk_State = 0;

/* Private function prototypes -----------------------------------------------*/
static void MSC_MenuThread(void const *argument);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Demo state machine.
  * @param  None
  * @retval None
  */
void Menu_Init(void)
{
  /* Create Menu Semaphore */
  osSemaphoreDef(osSem);

  MenuEvent = osSemaphoreCreate(osSemaphore(osSem), 1);

  /* Force menu to show Item 0 by default */
  osSemaphoreRelease(MenuEvent);

  /* Menu task */
  osThreadDef(Menu_Thread, MSC_MenuThread, osPriorityHigh, 0, 8 * configMINIMAL_STACK_SIZE);
  osThreadCreate(osThread(Menu_Thread), NULL);

  msc_demo.state = MSC_DEMO_IDLE;
  USBH_UsrLog("Starting MSC Demo");
}

/**
  * @brief  User task
  * @param  argument not used
  * @retval None
  */
void MSC_MenuThread(void const *argument)
{
  for(;;)
  {
    if(osSemaphoreWait(MenuEvent , osWaitForever) == osOK)
    {
      switch(msc_demo.state)
      {
      case MSC_DEMO_IDLE:
        msc_demo.state = MSC_DEMO_START;
        osSemaphoreRelease(MenuEvent);
        break;

      case MSC_DEMO_START:
        if(Appli_state == APPLICATION_READY)
        {
          BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
          BSP_LCD_DisplayStringAtLine(19, (uint8_t *)"Press User button to start read and write operations");

          msc_demo.state = MSC_DEMO_FILE_OPERATIONS;
      osSemaphoreRelease(MenuEvent);
        }
        break;

      case MSC_DEMO_FILE_OPERATIONS:
        /* Read and Write File Here */
        if(Appli_state == APPLICATION_READY)
        {
          BSP_LCD_ClearStringLine(19);
          MSC_File_Operations();

          BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
          BSP_LCD_DisplayStringAtLine(19, (uint8_t *)"Press User button to display disk content");
          msc_demo.state = MSC_DEMO_EXPLORER;
    }
        break;

      case MSC_DEMO_EXPLORER:
        /* Display disk content */
        if(Appli_state == APPLICATION_READY)
        {
          BSP_LCD_ClearStringLine(19);
          ExploreDisk_State = 1;

          Explore_Disk("0:/", 1);
          msc_demo.state = MSC_DEMO_START;

          ExploreDisk_State = 0;
          BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
          BSP_LCD_DisplayStringAtLine(19, (uint8_t *)"Press User button to start read and write operations");
        }
        break;

      default:
        break;
      }

      if(Appli_state == APPLICATION_DISCONNECT)
      {
        Appli_state = APPLICATION_IDLE;
        LCD_LOG_ClearTextZone();
        BSP_LCD_ClearStringLine(19);
        LCD_ErrLog("MSC device disconnected!\n");
        msc_demo.state = MSC_DEMO_IDLE;
      }
    }
  }
}

/**
  * @brief  EXTI line detection callbacks.
  * @param  GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin == WAKEUP_BUTTON_PIN)
  {
    if(ExploreDisk_State == 0)
    {
      osSemaphoreRelease(MenuEvent);
    }
  }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
