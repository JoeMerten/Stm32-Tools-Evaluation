/***********************************************************************************************************************
  N4 Foundation configuration for for this project
------------------------------------------------------------------------------------------------------------------------
  \copyright  © NumberFour 2015, all rights reserved
  \project    N4 Foundation
  \file       N4/Config/ProjectSettings.h
  \creation   2015-11-15, Joe Merten
------------------------------------------------------------------------------------------------------------------------
  This file sould not be included by the application directly,
  it rather was referenced from inside of the N4 Foundation header files.
***********************************************************************************************************************/

#ifndef N4_CONFIG_PROJECT_SETTINGS_H
#define N4_CONFIG_PROJECT_SETTINGS_H

#ifndef N4_ALLOW_CONFIG_SETTINGS_INCLUDE
  #error "Please dont include this file directly"
#endif

//#define N4_USE_PRINTF_LITE  1
//#define N4_USE_FLOAT        0

#define N4_USE_HEAPALYZER   (N4_TARGET_LINUX or N4_TARGET_BAREMETAL)
#define N4_USE_UNITTEST     0

#endif // N4_CONFIG_PROJECT_SETTINGS_H
