/**
  ******************************************************************************
  * @file    LibJPEG/LibJPEG_Encoding/Src/encode.c
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    09-October-2015
  * @brief   This file contain the compress method.
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
#include "encode.h"

/* Private typedef -----------------------------------------------------------*/
   /* This struct contains the JPEG compression parameters */
   static struct jpeg_compress_struct cinfo;
   /* This struct represents a JPEG error handler */
   static struct jpeg_error_mgr jerr;

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
extern RGB_typedef *RGB_matrix;

/**
  * @brief  Jpeg Encode
  * @param  file:          pointer to the bmp file
  * @param  file1:         pointer to the jpg file
  * @param  width:         image width
  * @param  height:        image height
  * @param  image_quality: image quality
  * @param  buff:          pointer to the image line
  * @retval None
  */
void jpeg_encode(FIL *file, FIL *file1, uint32_t width, uint32_t height, uint32_t image_quality, uint8_t * buff)
{

  /* Encode BMP Image to JPEG */
  JSAMPROW row_pointer;    /* Pointer to a single row */
  uint32_t bytesread;
  uint8_t b_to_r;
  uint32_t i = 0;

  /* Step 1: allocate and initialize JPEG compression object */
  /* Set up the error handler */
  cinfo.err = jpeg_std_error(&jerr);

  /* Initialize the JPEG compression object */
  jpeg_create_compress(&cinfo);

  /* Step 2: specify data destination */
  jpeg_stdio_dest(&cinfo, file1);

  /* Step 3: set parameters for compression */
  cinfo.image_width = width;
  cinfo.image_height = height;
  cinfo.input_components = 3;
  cinfo.in_color_space = JCS_RGB;

  /* Set default compression parameters */
  jpeg_set_defaults(&cinfo);

  cinfo.dct_method  = JDCT_FLOAT;

  jpeg_set_quality(&cinfo, image_quality, TRUE);

  /* Step 4: start compressor */
  jpeg_start_compress(&cinfo, TRUE);

  /* Bypass the header bmp file */
  f_read(file, buff, 54, (UINT*)&bytesread);

  while (cinfo.next_scanline < cinfo.image_height)
  {
/* In this application, the input file is a BMP, which first encodes the bottom of the picture */
/* JPEG encodes the highest part of the picture first. We need to read the lines upside down   */
/* Move the read pointer to 'last line of the picture - next_scanline'    */
    f_lseek(file, ((cinfo.image_height-1-cinfo.next_scanline)*width*3)+54);
    if(f_read(file, buff, width*3, (UINT*)&bytesread) == FR_OK)
    {
/* In this application, the input file is a BMP, which is encoded in BGR format */
/* We need to swap the R and the B, as JPEG encoder is waiting for RGB format   */
      RGB_matrix =  (RGB_typedef*)buff;
      for(i = 0; i < IMAGE_WIDTH; i++)
      {
        b_to_r = RGB_matrix[i].B;
        RGB_matrix[i].B = RGB_matrix[i].R;
        RGB_matrix[i].R = b_to_r;
      }

      row_pointer = (JSAMPROW)buff;
      jpeg_write_scanlines(&cinfo, &row_pointer, 1);
    }
  }

  /* Step 5: finish compression */
  jpeg_finish_compress(&cinfo);

  /* Step 6: release JPEG compression object */
  jpeg_destroy_compress(&cinfo);

}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
