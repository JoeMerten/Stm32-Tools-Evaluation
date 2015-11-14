/**
  ******************************************************************************
  * @file    USB_Host/CDC_Standalone/Src/menu.c
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
CDC_DEMO_StateMachine CdcDemo;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Demo state machine.
  * @param  None
  * @retval None
  */
void Menu_Init(void)
{
  USBH_UsrLog("Starting CDC Demo");
  CdcDemo.state = CDC_DEMO_WAIT;
}

/**
  * @brief  Manages CDC Menu Process.
  * @param  None
  * @retval None
  */
void CDC_MenuProcess(void)
{
  switch(CdcDemo.state)
  {
  case CDC_DEMO_WAIT:
    if(Appli_state == APPLICATION_READY)
    {
      BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
      BSP_LCD_DisplayStringAtLine(19, (uint8_t *)"Press User button to start sending data ");

      /* Wait for User Input */
      while((BSP_PB_GetState(BUTTON_WAKEUP) != SET) && (Appli_state != APPLICATION_DISCONNECT))
      {
      }
      CdcDemo.state = CDC_DEMO_SEND;

      /* Prevent debounce effect for user key */
      HAL_Delay(400);

      BSP_LCD_ClearStringLine(19);
    }
    break;

  case CDC_DEMO_SEND:
    /* Read and Write File Here */
    if(Appli_state == APPLICATION_READY)
    {
      CDC_Handle_Send_Menu();
    }
    break;

    case CDC_DEMO_RECEIVE:
    if(Appli_state == APPLICATION_READY)
    {
      CDC_Handle_Receive_Menu();
    }
    break;

  default:
    break;
  }

  if(Appli_state == APPLICATION_DISCONNECT)
  {
    Appli_state = APPLICATION_IDLE;
    LCD_LOG_ClearTextZone();
    LCD_ErrLog("CDC device disconnected!\n");
    CdcDemo.state = CDC_DEMO_WAIT;
    CdcDemo.Receive_state = CDC_RECEIVE_IDLE;
    CdcDemo.Send_state = CDC_SEND_IDLE;
    CdcDemo.select = 0;
  }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
