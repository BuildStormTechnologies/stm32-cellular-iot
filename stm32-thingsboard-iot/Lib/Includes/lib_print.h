/**
 * \copyright Copyright (c) 2019-2024, Buildstorm Pvt Ltd
 *
 * \file lib_print.h
 * \brief Print library header file.
 *
 * The print library provides the API's for print operations
 *
 * The libraries have been tested on the ESP32 modules.
 * Buildstorm explicitly denies responsibility for any hardware failures
 * arising from the use of these libraries, whether directly or indirectly.

 *
 * EULA LICENSE:
 * This library is licensed under end user license EULA agreement.
 * The EULA is available at https://buildstorm.com/eula/
 * For any support contact us at hello@buildstorm.com
 *
 */

#ifndef LIB_PRINT_H_
#define LIB_PRINT_H_

#include "stm32f4xx_hal.h"

#include "lib_config.h"

/***************************************************************************************************
                             Commonly used UART macros/Constants
 ***************************************************************************************************/
#define C_BINARY_U8 2u
#define C_DECIMAL_U8 10u
#define C_HEX_U8 16u
#define C_DefaultDigitsToTransmit_U8 0xffu                               // Will transmit the exact digits in the number
#define C_MaxDigitsToTransmit_U8 10u                                     // Max decimal/hexadecimal digits to be transmitted
#define C_NumOfBinDigitsToTransmit_U8 16u                                // Max bits of a binary number to be transmitted
#define C_MaxDigitsToTransmitUsingPrintf_U8 C_DefaultDigitsToTransmit_U8 /* Max dec/hexadecimal digits to be displayed using printf */
/**************************************************************************************************/

/***************************************************************************************************
                             Function Prototypes
 ***************************************************************************************************/


void PRINTF(const char *argList, ...);
void print_failedMsg(const char *pFunNameStr, const char *failMsg);
void print_mallocFailedMsg(const char *pFunNameStr, const char *failMsg);
void print_serial(menusLibModule_et libModule, logLevels_et e_logLevel, const char *funName, const char *argList, ...);

#define print_verbose(var_arg_list...) print_serial(thisModule, PRINT_LEVEL_ERROR, __func__, var_arg_list)
#define print_error(var_arg_list...) print_serial(thisModule, PRINT_LEVEL_ERROR, __func__, var_arg_list)
#define print_info(var_arg_list...) print_serial(thisModule, PRINT_LEVEL_INFO, __func__, var_arg_list)
#define print_debug(var_arg_list...) print_serial(thisModule, PRINT_LEVEL_DEBUG, __func__, var_arg_list)

#define print_verbose_raw(var_arg_list...) print_serial(thisModule, PRINT_LEVEL_ERROR, NULL, var_arg_list)
#define print_error_raw(var_arg_list...) print_serial(thisModule, PRINT_LEVEL_ERROR, NULL, var_arg_list)
#define print_info_raw(var_arg_list...) print_serial(thisModule, PRINT_LEVEL_INFO, NULL, var_arg_list)
#define print_debug_raw(var_arg_list...) print_serial(thisModule, PRINT_LEVEL_DEBUG, NULL, var_arg_list)

#define print_failed(failMsg) print_failedMsg(__func__, failMsg)
#define print_mallocFailed(failMsg) print_mallocFailedMsg(__func__, failMsg)

/**************************************************************************************************/

#endif //LIB_PRINT_H_
