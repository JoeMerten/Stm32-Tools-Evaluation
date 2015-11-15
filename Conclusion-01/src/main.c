/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f4xx.h"
#include "stm32f401_discovery.h"
#include "JoeTest.h"


int main(void)
{
    doJoeTest();
    for(;;);
}
