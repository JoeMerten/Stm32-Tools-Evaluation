/**
  ******************************************************************************
  * @file    DCMI/DCMI_SnapshotMode/Src/main.c
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    09-October-2015
  * @brief   This example describe how to configure the camera interface (DCMI) in snapshot
  *          mode to handle a single image capture in QVGA (320x240) resolution and RGB565
  *          format and display the obtained image on LCD screen.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32F4xx_HAL_Examples
  * @{
  */

/** @addtogroup DCMI_SnapshotMode
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Camera resolution is QVGA (320x240) */
static uint8_t    mfx_toggle_led = 0;
static uint32_t   CameraResX = 320;
static uint32_t   CameraResY = 240;
static uint32_t   LcdResX    = 800; /* WVGA landscape */
static uint32_t   LcdResY    = 480;

static uint32_t          offset_cam = 0;
static uint32_t          offset_lcd = 0;
static uint32_t          display_line_counter = 0;
static volatile uint32_t lcd_frame_buffer_ready = 0;
static volatile uint32_t start_the_camera_capture = 0;
static volatile uint32_t end_the_camera_capture = 0;

/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);

static void LCD_LL_ConvertLineToARGB8888(void *pSrc, void *pDst, uint32_t xSize);
static uint8_t CameraFrameBufferRgb565_Init(uint32_t sizeX, uint32_t sizeY, uint32_t argb8888_Value);
static void CopyCameraFrameBufferLineToLcdFrameBufferLine(void);
static void OnError_Handler(uint32_t condition);

/* Exported functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  uint8_t  lcd_status = LCD_OK;
  mfx_toggle_led = 0;
  CameraResX = 320;
  CameraResY = 240;
  LcdResX    = 800; /* WVGA landscape */
  LcdResY    = 480;
  offset_cam = 0;
  offset_lcd = 0;
  display_line_counter = 0;
  lcd_frame_buffer_ready = 0;
  start_the_camera_capture = 0;
  end_the_camera_capture = 0;

  /* STM32F4xx HAL library initialization:
       - Configure the Flash prefetch, instruction and Data caches
       - Systick timer is configured by default as source of time base, but user
         can eventually implement his proper time base source (a general purpose
         timer for example or other time source), keeping in mind that Time base
         duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and
         handled in milliseconds basis.
       - Set NVIC Group Priority to 4
       - Low Level Initialization: global MSP (MCU Support Package) initialization
     */
  HAL_Init();

  /* Configure the system clock to 180 MHz */
  SystemClock_Config();

  /* Initialize MFX */
  BSP_IO_Init();

  /* Initialize used Leds */
  BSP_LED_Init(LED1);
  BSP_LED_Init(LED3);

  /*##-1- Initialise the LCD #################################################*/

  /* Initialize and start the LCD display in mode LCD_MODE_ADAPTED_COMMAND_TE_DSI_LINK
   * and orientation mode LCD_ORIENTATION_LANDSCAPE, using LCD_FRAME_BUFFER
   * as LCD frame buffer address.
   */
  BSP_LCD_Init();
  BSP_LCD_LayerDefaultInit(0, LCD_FB_START_ADDRESS);
  OnError_Handler(lcd_status != LCD_OK);

  /* Prepare using DMA2D the 800x480 LCD frame buffer to display background color black */
  /* and title of the example                                                           */
  BSP_LCD_Clear(LCD_COLOR_BLACK);
  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
  BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
  BSP_LCD_SetFont(&Font16);

  /* Print example description */
  BSP_LCD_DisplayStringAt(0, 440, (uint8_t *)"DCMI Snapshot example", CENTER_MODE);
  BSP_LCD_DisplayStringAt(0, 460, (uint8_t *)"Initialize Camera", CENTER_MODE);

  /* Initialize the camera frame buffer 320x240 in RGB565 to a fixed grey pattern */
  lcd_status = CameraFrameBufferRgb565_Init(CameraResX, CameraResY, 0x55555555);
  OnError_Handler(lcd_status != LCD_OK);

  /*##-2- Camera Initialization and start capture ############################*/
  /* Initialize the Camera in QVGA mode */
  BSP_CAMERA_Init(CAMERA_R320x240);

  /* Wait 1s to let auto-loops in the camera module converge and lead to correct exposure */
  HAL_Delay(1000);

  /* Start the Camera Snapshot Capture */
  BSP_CAMERA_SnapshotStart((uint8_t *)CAMERA_FRAME_BUFFER);

  /* Wait until LCD frame buffer is ready */
  while(lcd_frame_buffer_ready == 0) {;}

  /* Stop the camera to avoid having the DMA2D work in parallel of Display */
  /* which cause perturbation of LTDC                                      */
  BSP_CAMERA_Stop();

  BSP_LCD_ClearStringLine(460);
  BSP_LCD_DisplayStringAt(0, 460, (uint8_t *)"Capture OK - Test End", CENTER_MODE);

  /* Notify Test OK */
  BSP_LED_On(LED1);

  while (1)
  {
    if ( mfx_toggle_led == 1)
    {
      BSP_LED_Toggle(LED3);
      mfx_toggle_led = 0;
    }
  }
}

/**
  * @brief  Camera line event callback
  */
void BSP_CAMERA_LineEventCallback(void)
{
  if(start_the_camera_capture == 1)
  {
    if(display_line_counter < CameraResY)
    {
      /* Start DMA2D copy of current line                                         */
      /* Note for the last line BSP_CAMERA_FrameEventCallback() is called instead */
      CopyCameraFrameBufferLineToLcdFrameBufferLine();
    }

    /* If we have copied the last line of Camera Frame buffer to LCD frame buffer */
    /* then the LCD frame buffer is ready for display                             */
    if((display_line_counter == CameraResY) &&
        (end_the_camera_capture == 0))
    {
      end_the_camera_capture = 1;
      start_the_camera_capture = 0;

      /* Suspend Camera DMA */
      BSP_CAMERA_Suspend();

      /* LCD frame buffer is now ready */
      lcd_frame_buffer_ready = 1;
    }
  } /* of if(start_the_camera_capture == 1) */
}

/**
  * @brief  Camera Frame Event callback.
  */
void BSP_CAMERA_FrameEventCallback(void)
{
  start_the_camera_capture = 1;
}

/**
  * @brief  Toggle Leds.
  * @param  None
  * @retval None
  */
void Toggle_Leds(void)
{
  static uint32_t ticks = 0;

  if (ticks++ > 1000)
  {
    mfx_toggle_led = 1;
    ticks = 0;
  }
}



/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Converts a RGB565 camera frame buffer line (width = 320 pixels)
  * into a ARGB8888 LCD Frame buffer line (of same width 320 pixels).
  * @param  pSrc: Pointer to source buffer in Camera frame buffer (camera frame buffer line)
  * @param  pDst: Pointer to destination buffer in LCD frame buffer (LCD frame buffer line)
  * @param  xSize: Buffer width
  * @retval None
  */
static void LCD_LL_ConvertLineToARGB8888(void *pSrc, void *pDst, uint32_t xSize)
{
  DMA2D_HandleTypeDef hdma2d_eval;

  /* Configure the DMA2D Mode, Color Mode and output offset */
  hdma2d_eval.Init.Mode         = DMA2D_M2M_PFC;
  hdma2d_eval.Init.ColorMode    = DMA2D_ARGB8888; /* Output color out of PFC */
  hdma2d_eval.Init.OutputOffset = 0;

  /* Foreground Configuration */
  hdma2d_eval.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
  hdma2d_eval.LayerCfg[1].InputAlpha = 0xFF; /* fully opaque */
  hdma2d_eval.LayerCfg[1].InputColorMode = CM_RGB565;
  hdma2d_eval.LayerCfg[1].InputOffset = 0;

  hdma2d_eval.Instance = DMA2D;

  /* DMA2D Initialization */
  if(HAL_DMA2D_Init(&hdma2d_eval) == HAL_OK)
  {
    if(HAL_DMA2D_ConfigLayer(&hdma2d_eval, 1) == HAL_OK)
    {
      if (HAL_DMA2D_Start(&hdma2d_eval, (uint32_t)pSrc, (uint32_t)pDst, xSize, 1) == HAL_OK)
      {
        /* Polling For DMA transfer */
        HAL_DMA2D_PollForTransfer(&hdma2d_eval, 10);
      }
    }
  }
  else
  {
    while(1);
  }
}

/**
  * @brief  Init camera frame buffer with fixed color in format RGB565
  *         to a LCD display frame buffer line in format ARGB8888 using DMA2D service.
  * @param  sizeX: Size in X of rectangular region of the Camera frame buffer to initialize (in pixels unit)
  * @param  sizeX: Size in X of rectangular region of the Camera frame buffer to initialize (in pixels unit)
  * @param  argb_Value : Initialization value (pattern ARGB8888) to be applied to all rectangular region selected.
  * @retval Status LCD_OK or LCD_ERROR
  */
static uint8_t CameraFrameBufferRgb565_Init(uint32_t sizeX, uint32_t sizeY, uint32_t argb8888_Value)
{
  HAL_StatusTypeDef hal_status = HAL_OK;
  uint8_t lcd_status = LCD_ERROR;
  DMA2D_HandleTypeDef hdma2d_eval;

  if((sizeX <= CAMERA_VGA_RES_X) && (sizeY <= CAMERA_VGA_RES_Y))
  {
    /* Register to memory mode with RGB565 as colorMode */
    hdma2d_eval.Init.Mode         = DMA2D_R2M; /* Mode Register to Memory */
    hdma2d_eval.Init.ColorMode    = DMA2D_RGB565; /* Output color mode */
    hdma2d_eval.Init.OutputOffset = 0x0; /* No offset in output */

    hdma2d_eval.Instance = DMA2D;

    hal_status = HAL_DMA2D_Init(&hdma2d_eval);
    if(hal_status == HAL_OK)
    {
        if (HAL_DMA2D_Start(&hdma2d_eval, argb8888_Value, (uint32_t)CAMERA_FRAME_BUFFER, sizeX, sizeY) == HAL_OK)
        {
          /* Polling For DMA transfer */
          HAL_DMA2D_PollForTransfer(&hdma2d_eval, 10);

          /* Return good status on exit */
          lcd_status = LCD_OK;
        }
    }
  }

  return (lcd_status);
}

/**
  * @brief  Copy a Camera frame buffer line in RGB565 and convert it to LCD Frame buffer line in ARGB8888 format.
  *         This process uses the DMA2D and its integrated Pixel Format Converter (PFC).
  */
static void CopyCameraFrameBufferLineToLcdFrameBufferLine(void)
{
    if ((offset_lcd == 0) && (CameraResX <= LcdResX) && (CameraResY <= LcdResY))
    {
      /* If Camera resolution is lower than LCD resolution, set display in the middle of the screen */
      offset_lcd =   ((((LcdResY - CameraResY) / 2) * LcdResX)   /* Middle of the screen on Y axis */
                      +   ((LcdResX - CameraResX) / 2))             /* Middle of the screen on X axis */
                     * sizeof(uint32_t);
    }

    if (display_line_counter < CameraResY)
    {
      if (display_line_counter < LcdResY)
      {
        if (CameraResX < LcdResX)
        {
          LCD_LL_ConvertLineToARGB8888((uint32_t *)(CAMERA_FRAME_BUFFER + offset_cam),
                                         (uint32_t *)(LCD_FRAME_BUFFER + offset_lcd),
                                         CameraResX);
        }
        else
        {
          LCD_LL_ConvertLineToARGB8888((uint32_t *)(CAMERA_FRAME_BUFFER + offset_cam),
                                         (uint32_t *)(LCD_FRAME_BUFFER + offset_lcd),
                                         LcdResX);
        }

        offset_cam  = offset_cam + (CameraResX * sizeof(uint16_t)); /* RGB565 2 bytes per pixel   */
        offset_lcd  = offset_lcd + (LcdResX * sizeof(uint32_t));    /* ARGB8888 4 bytes per pixel */
      }

      display_line_counter++;
    }
    else
    {
      offset_cam = 0;
      offset_lcd = 0;
      display_line_counter = 0;
    }
}

/**
  * @brief  On Error Handler on condition TRUE.
  * @param  condition : Can be TRUE or FALSE
  * @retval None
  */
static void OnError_Handler(uint32_t condition)
{
  if(condition)
  {
    BSP_LED_On(LED3);
    while(1) { ; } /* Blocking on error */
  }
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 180000000
  *            HCLK(Hz)                       = 180000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 25000000
  *            PLL_M                          = 25
  *            PLL_N                          = 360
  *            PLL_P                          = 2
  *            PLL_Q                          = 7
  *            PLL_R                          = 6
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  HAL_StatusTypeDef ret = HAL_OK;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the device is
     clocked below the maximum system frequency, to update the voltage scaling value
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  RCC_OscInitStruct.PLL.PLLR = 6;

  ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }

  /* Activate the OverDrive to reach the 180 MHz Frequency */
  ret = HAL_PWREx_EnableOverDrive();
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
