/***********************************************************************************************************************
  N4 Foundation unittest configuration for this project
------------------------------------------------------------------------------------------------------------------------
  \copyright  © NumberFour 2015, all rights reserved
  \project    N4 Foundation
  \file       N4/Config/TestSettings.hxx
  \creation   2015-05-26, Joe Merten
------------------------------------------------------------------------------------------------------------------------
  This file sould not be included by the application directly,
  it rather was referenced from inside of the N4 Foundation header files.
***********************************************************************************************************************/

#ifndef N4_CONFIG_TEST_SETTINGS_HXX
#define N4_CONFIG_TEST_SETTINGS_HXX

#ifndef N4_ALLOW_CONFIG_SETTINGS_INCLUDE
  #error "Please dont include this file directly"
#endif

// Place your configuration stuff here

// TODO: make the test compile with below switches enabled
//#define N4_UNITTEST_FLOAT         N4_USE_FLOAT
#define N4_UNITTEST_HEAP          1
#define N4_UNITTEST_EXCEPTIONS    1
#define N4_UNITTEST_RTTI          1

#define N4_UNITTEST_INCLUDE_SELF_TEST    1
#define N4_UNITTEST_INCLUDE_FOUNDATION   1
#define N4_UNITTEST_INCLUDE_APPLICATION  1
#define N4_UNITTEST_INCLUDE_XML_REPORTER  1

#endif // N4_CONFIG_TEST_SETTINGS_HXX
