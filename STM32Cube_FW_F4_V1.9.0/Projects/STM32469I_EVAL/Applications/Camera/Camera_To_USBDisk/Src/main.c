/**
  ******************************************************************************
  * @file    Camera/Camera_To_USBDisk/Src/main.c
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    09-October-2015
  * @brief   This application describes how to configure the camera in continuous mode
             and save picture under USBDisk.
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

/** @addtogroup STM32F4xx_HAL_Applications
  * @{
  */

/** @addtogroup Camera_To_USBDisk
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define PRESSED_FIRST    0x00

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t ubPressedButton = PRESSED_FIRST;

FATFS MSC_FatFs;  /* File system object for USB disk logical drive */
FIL MyFile;       /* File object */
char MSC_Path[4]; /* USB Host logical drive path */
USBH_HandleTypeDef  hUSB_Host;

/* Image header */
const uint32_t aBMPHeader[14]=
{0xFA364D42, 0x00000005, 0x00360000, 0x00280000, 0x01E00000, 0x01100000, 0x00010000,
 0x00000018, 0xF5400000, 0x00000006, 0x00000000, 0x00000000, 0x00000000, 0x0000};

typedef enum {
  STORAGE_IDLE = 0,
  STORAGE_READY,
}MSC_ApplicationTypeDef;

MSC_ApplicationTypeDef Appli_state = STORAGE_IDLE;

/* Camera resolution is 480x272 */
static uint32_t   CameraResX = CAMERA_480x272_RES_X;
static uint32_t   CameraResY = CAMERA_480x272_RES_Y;
static uint32_t   LcdResX    = WVGA_RES_X; /* WVGA landscape 800x480 */
static uint32_t   LcdResY    = WVGA_RES_Y;
static uint32_t   offset_address_area_cam_in_lcd_buffer =  0;
static uint32_t   lcd_datapointer = 0;

static uint8_t *  p_bmp_converted_pixel_data = (uint8_t *)CONVERTED_FRAME_BUFFER;

/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void PicturePrepare(void);
static void Error_Handler(void);
static void SavePicture(void);
static void LCD_LL_ConvertLineToARGB8888(void *pSrc, void *pDst);
static void CAMERA_Capture(void);
static void USBH_UserProcess(USBH_HandleTypeDef *phost, uint8_t id);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
    uint8_t lcd_status = LCD_OK;

  p_bmp_converted_pixel_data    = (uint8_t *)CONVERTED_FRAME_BUFFER;

  offset_address_area_cam_in_lcd_buffer = ((((LcdResY - CameraResY) / 2) * LcdResX)
                                          +   ((LcdResX - CameraResX) / 2))
                                          * ARGB8888_BYTE_PER_PIXEL;

  /* For the first Camera line event callback : set the offset to display camera image in the center */
  /* of LCD frame buffer background */
  lcd_datapointer = offset_address_area_cam_in_lcd_buffer;

    /* STM32F4xx HAL library initialization:
       - Configure the Flash prefetch, instruction and Data caches
       - Configure the Systick to generate an interrupt each 1 msec
       - Set NVIC Group Priority to 4
       - Global MSP (MCU Support Package) initialization
     */
  HAL_Init();

  /* Configure the system clock to 180 MHz */
  SystemClock_Config();

  BSP_IO_Init();

  /* Reset and power down camera to be sure camera is Off prior start testing BSP */
  BSP_CAMERA_HwReset();
  BSP_CAMERA_PwrDown();

  /* Configure LED1 and LED3 */
  BSP_LED_Init(LED1);
  BSP_LED_Init(LED3);

  /*##-1- LCD DSI initialization in mode Video Burst  with two LTDC layers of size 800x480 */
  lcd_status = BSP_LCD_Init();
  if(lcd_status != LCD_OK)
  {
      Error_Handler();
  }

  BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER_BACKGROUND, LCD_BG_LAYER_ADDRESS);
  BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER_FOREGROUND, LCD_FB_START_ADDRESS);

  /* Select Foreground Layer */
  BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER_FOREGROUND);

  /* Clear the LCD Foreground layer */
  BSP_LCD_Clear(LCD_COLOR_WHITE);

  /* Disable the LTDC Foreground layer */
  BSP_LCD_SetLayerVisible(LTDC_ACTIVE_LAYER_FOREGROUND, DISABLE);

  /* Select the LCD Background layer */
  BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER_BACKGROUND);
  BSP_LCD_Clear(LCD_COLOR_WHITE);

  /*##-2- Init Host Library ##################################################*/

  /* Display USB initialization message */
  BSP_LCD_SetTextColor(LCD_COLOR_DARKBLUE);
  BSP_LCD_SetFont(&Font24);
  BSP_LCD_DisplayStringAt(20, (BSP_LCD_GetYSize() - 24), (uint8_t *)"USB init ..", RIGHT_MODE);

  USBH_Init(&hUSB_Host, USBH_UserProcess, 0);

  /* Add Supported Class */
  USBH_RegisterClass(&hUSB_Host, USBH_MSC_CLASS);

  /* Start Host Process */
  USBH_Start(&hUSB_Host);

  /*##-3- Configure TAMPER Button ############################################*/
  BSP_PB_Init(BUTTON_TAMPER, BUTTON_MODE_GPIO);

  /*##-4- Link the USB Host disk I/O driver ##################################*/
  FATFS_LinkDriver(&USBH_Driver, MSC_Path);

  /*##-5- Camera Initialization and start capture ############################*/

  /* Display camera initialization message */
  BSP_LCD_DisplayStringAt(20, (BSP_LCD_GetYSize() - 24), (uint8_t *)"Camera init ..", RIGHT_MODE);

  /* Initialize the Camera */
  BSP_CAMERA_Init(RESOLUTION_R480x272);

  /* Start the Camera Capture */
  BSP_CAMERA_ContinuousStart((uint8_t *)CAMERA_FRAME_BUFFER);

  BSP_LCD_DisplayStringAt(20, (BSP_LCD_GetYSize() - 48), (uint8_t *)"Press TAMPER button to take snapshot", RIGHT_MODE);
  BSP_LCD_DisplayStringAt(20, (BSP_LCD_GetYSize() - 24), (uint8_t *)"Camera Play ..", RIGHT_MODE);

  /*##-6- Run Application ####################################################*/
  while (1)
  {
    /* USB Host Background task */
    USBH_Process(&hUSB_Host);

    switch(Appli_state)
    {
    case STORAGE_READY:
      CAMERA_Capture();
      break;

    case STORAGE_IDLE:
      break;
    }
  }
}

/**
  * @brief  Saves Picture into USB disk.
  * @param  None
  * @retval None
  */
static void SavePicture(void)
{
  FRESULT res1, res2;     /* FatFs function common result code */
  uint32_t byteswritten;  /* File write count */
  static uint32_t counter = 0;
  uint8_t str[30];
  uint8_t str_display[50];

  /* Suspend the camera capture */
  BSP_CAMERA_Suspend();

  BSP_LCD_DisplayStringAt(20, (BSP_LCD_GetYSize() - 24), (uint8_t *)"                     ", RIGHT_MODE);
  BSP_LCD_DisplayStringAt(20, (BSP_LCD_GetYSize() - 24), (uint8_t *)"Camera stopped...", RIGHT_MODE);

  /* Prepare the image to be saved */
  PicturePrepare();

  BSP_LCD_DisplayStringAt(20, (BSP_LCD_GetYSize() - 24), (uint8_t *)"                     ", RIGHT_MODE);
  BSP_LCD_DisplayStringAt(20, (BSP_LCD_GetYSize() - 24), (uint8_t *)"           Picture Prepared...", RIGHT_MODE);
  HAL_Delay(1000);
  BSP_LCD_DisplayStringAt(20, (BSP_LCD_GetYSize() - 24), (uint8_t *)"                                 ", RIGHT_MODE);

  /* Set foreground Layer as visible */
  BSP_LCD_SetLayerVisible(LTDC_ACTIVE_LAYER_FOREGROUND, ENABLE);
  BSP_LCD_SetColorKeying(LTDC_ACTIVE_LAYER_FOREGROUND, LCD_COLOR_WHITE);
  BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER_FOREGROUND);
  BSP_LCD_SetTextColor(LCD_COLOR_DARKRED);
  BSP_LCD_SetFont(&Font24);

  /* Format the string */
  sprintf((char *)str,"image_%d.bmp", (int)counter);
  sprintf((char *)str_display,"         Saving picture in file %s ..", str);

  /* Display text on LTDC layer foreground */
  BSP_LCD_DisplayStringAt(20, (BSP_LCD_GetYSize() - 24), str_display, RIGHT_MODE);

  /* Create and Open a new text file object with write access */
  if(f_open(&MyFile, (const char*)str, FA_CREATE_ALWAYS | FA_WRITE) != FR_OK)
  {
    Error_Handler();
  }
  else
  {
    /* Write data to the BMP file */
    res1 = f_write(&MyFile, (uint32_t *)aBMPHeader, 54, (void *)&byteswritten);
    BSP_LCD_DisplayStringAt(20, (BSP_LCD_GetYSize() - 24), (uint8_t *)"                                          ", RIGHT_MODE);
    BSP_LCD_DisplayStringAt(20, (BSP_LCD_GetYSize() - 24), (uint8_t *)"           Header BMP written...", RIGHT_MODE);
    HAL_Delay(1000);

    BSP_LCD_DisplayStringAt(20, (BSP_LCD_GetYSize() - 24), (uint8_t *)"                                          ", RIGHT_MODE);
    BSP_LCD_DisplayStringAt(20, (BSP_LCD_GetYSize() - 24), (uint8_t *)"           BMP pixel data save ongoing...", RIGHT_MODE);

    res2 = f_write(&MyFile, (uint8_t *)p_bmp_converted_pixel_data,
                   (CameraResX * CameraResY * RGB888_BYTE_PER_PIXEL),
                   (void *)&byteswritten);
    if((res1 != FR_OK) || (res2 != FR_OK) || (byteswritten == 0))
    {
      Error_Handler();
    }
    else
    {
      /* Close the open BMP file */
      f_close(&MyFile);

      /* Success of the demo: no error occurrence */
      BSP_LED_On(LED1);
      BSP_LCD_SetTextColor(LCD_COLOR_DARKGREEN);
      BSP_LCD_DisplayStringAt(20, (BSP_LCD_GetYSize() - 24), (uint8_t *)"                                          ", RIGHT_MODE);
      sprintf((char *)str_display,"File %s saved on USB disk ..", str);
      BSP_LCD_DisplayStringAt(20, (BSP_LCD_GetYSize()-24), str_display, RIGHT_MODE);
      /* Wait for 2s */
      HAL_Delay(2000);
      BSP_LCD_DisplayStringAt(20, (BSP_LCD_GetYSize() - 24), (uint8_t *)"                                          ", RIGHT_MODE);

      /* Disable the Layer Foreground */
      BSP_LCD_SetLayerVisible(LTDC_ACTIVE_LAYER_FOREGROUND, DISABLE);

      /* Select Layer Background */
      BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER_BACKGROUND);
      counter++;
      BSP_LED_Off(LED1);

      /* Resume the camera capture */
      BSP_CAMERA_Resume();
      BSP_LCD_DisplayStringAt(20, (BSP_LCD_GetYSize()-24), (uint8_t *)"Camera Play  ", RIGHT_MODE);
    }
  }
}

/**
  * @brief  Main routine for Camera capture
  * @param  None
  * @retval None
  */
static void CAMERA_Capture(void)
{
  while(1)
  {
    if(BSP_PB_GetState(BUTTON_TAMPER) == GPIO_PIN_RESET)
    {
       HAL_Delay(10);
       while (BSP_PB_GetState(BUTTON_TAMPER) == GPIO_PIN_RESET) { ; }
       SavePicture();
    }
    else if(BSP_PB_GetState(BUTTON_TAMPER) == GPIO_PIN_SET)
    {
       HAL_Delay(10);
       while (BSP_PB_GetState(BUTTON_TAMPER) == GPIO_PIN_SET) { ; }
       SavePicture();
    }
  }
}

/**
  * @brief  Line event callback.
  * @param  None
  * @retval None
  */
void BSP_CAMERA_LineEventCallback(void)
{
  static uint32_t camera_datapointer;
  static uint32_t line_number;

  if(line_number < CameraResY)
  {
    LCD_LL_ConvertLineToARGB8888((uint32_t *)(CAMERA_FRAME_BUFFER + camera_datapointer), (uint32_t *)(LCD_BG_LAYER_ADDRESS + lcd_datapointer));
    camera_datapointer = camera_datapointer + (CameraResX * RGB565_BYTE_PER_PIXEL);
    lcd_datapointer = lcd_datapointer + (LcdResX * ARGB8888_BYTE_PER_PIXEL);
    line_number++;
  }
  else
  {
    camera_datapointer = 0;
    lcd_datapointer = offset_address_area_cam_in_lcd_buffer;
    line_number = 0;
  }
}

/**
  * @brief  Prepares the picture to be Saved in USB.
  * @param  None
  * @retval None
  */
static void PicturePrepare(void)
{
  static DMA2D_HandleTypeDef hdma2d_eval;
  uint32_t addrSrc = LCD_BG_LAYER_ADDRESS + ((LcdResX - CameraResX) / 2 * ARGB8888_BYTE_PER_PIXEL);
  uint32_t addrDst = CONVERTED_FRAME_BUFFER;
  uint32_t lineCnt = 0;

  /* Configure the DMA2D Mode, Color Mode and output offset */
  hdma2d_eval.Init.Mode         = DMA2D_M2M_PFC;
  hdma2d_eval.Init.ColorMode    = DMA2D_RGB888; /* Output color mode at the output of DMA2D operation */
  hdma2d_eval.Init.OutputOffset = 0;

  /* Foreground Configuration */
  hdma2d_eval.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
  hdma2d_eval.LayerCfg[1].InputAlpha = 0xFF;
  hdma2d_eval.LayerCfg[1].InputColorMode = DMA2D_ARGB8888;
  hdma2d_eval.LayerCfg[1].InputOffset = 0;

  hdma2d_eval.Instance = DMA2D;

  /* Go to last line of camera image in LCD BG frame buffer in order to start building BMP file */
  /* As BMP file encoding starts with last line down to the first */
  addrSrc += (LcdResY - ((LcdResY - CameraResY) / 2) - 1 ) * LcdResX * ARGB8888_BYTE_PER_PIXEL;

  /* Convert picture line by line to RGB888 pixel format */
  for(lineCnt = 0; lineCnt < CameraResY; lineCnt++)
  {
    /* DMA2D Initialization */
    if(HAL_DMA2D_Init(&hdma2d_eval) == HAL_OK)
    {
      if(HAL_DMA2D_ConfigLayer(&hdma2d_eval, 1) == HAL_OK)
      {
        if (HAL_DMA2D_Start(&hdma2d_eval, addrSrc, addrDst, CameraResX, 1) == HAL_OK)
        {
          /* Polling For DMA transfer */
          HAL_DMA2D_PollForTransfer(&hdma2d_eval, 10);
        }
      }
    }
    /* Manage the source and destination buffers */
    addrDst += (CameraResX * RGB888_BYTE_PER_PIXEL);
    addrSrc -= (LcdResX * ARGB8888_BYTE_PER_PIXEL);
  }
}

/**
  * @brief  Converts a line to an ARGB8888 pixel format.
  * @param  pSrc: Pointer to source buffer
  * @param  pDst: Output color
  * @retval None
  */
static void LCD_LL_ConvertLineToARGB8888(void *pSrc, void *pDst)
{
  static DMA2D_HandleTypeDef hdma2d_eval;

  /* Configure the DMA2D Mode, Color Mode and output offset */
  hdma2d_eval.Init.Mode         = DMA2D_M2M_PFC;
  hdma2d_eval.Init.ColorMode    = DMA2D_ARGB8888; /* output color at output of DMA2D operation */
  hdma2d_eval.Init.OutputOffset = 0;

  /* Foreground Configuration */
  hdma2d_eval.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
  hdma2d_eval.LayerCfg[1].InputAlpha = 0xFF;
  hdma2d_eval.LayerCfg[1].InputColorMode = CM_RGB565;
  hdma2d_eval.LayerCfg[1].InputOffset = 0;

  hdma2d_eval.Instance = DMA2D;

  /* DMA2D Initialization */
  if(HAL_DMA2D_Init(&hdma2d_eval) == HAL_OK)
  {
    if(HAL_DMA2D_ConfigLayer(&hdma2d_eval, 1) == HAL_OK)
    {
      if (HAL_DMA2D_Start(&hdma2d_eval, (uint32_t)pSrc, (uint32_t)pDst, CameraResX, 1) == HAL_OK)
      {
        /* Polling For DMA transfer */
        HAL_DMA2D_PollForTransfer(&hdma2d_eval, 10);
      }
    }
  }
}

/**
  * @brief  User Process
  * @param  phost: Host handle
  * @param  id: Host Library user message ID
  * @retval None
  */
static void USBH_UserProcess(USBH_HandleTypeDef *phost, uint8_t id)
{
  switch (id)
  {
  case HOST_USER_SELECT_CONFIGURATION:
    break;

  case HOST_USER_DISCONNECTION:
    Appli_state = STORAGE_IDLE;
    f_mount(NULL, (TCHAR const*)"", 0);
    break;

  case HOST_USER_CLASS_ACTIVE:
    /* Register the file system object to the FatFs module */
    if(f_mount(&MSC_FatFs, (TCHAR const*)MSC_Path, 0) != FR_OK)
    {
      /* FatFs Initialization Error */
      Error_Handler();
    }
    else
    {
      Appli_state = STORAGE_READY;
    }
    break;
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* Turn LED3 on */
  BSP_LED_On(LED3);
  BSP_LCD_SelectLayer(0);
  while(1)
  {
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
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;
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

  /* Select PLLSAI output as USB clock source on ck_pll48 (48 MHz) */
  PeriphClkInitStruct.PLLSAI.PLLSAIN = 384;
  PeriphClkInitStruct.PLLSAI.PLLSAIP = RCC_PLLSAIP_DIV8;
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_CK48;
  PeriphClkInitStruct.Clk48ClockSelection = RCC_CK48CLKSOURCE_PLLSAIP;
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);

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
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
