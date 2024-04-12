/**
 * \copyright Copyright (c) 2019-2024, Buildstorm Pvt Ltd
 *
 * \file lib_ota.h
 * \brief OTA library header file.
 *
 * The ota library provides the API's for ota operations
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

#ifndef _LIB_OTA_H_
#define _LIB_OTA_H_

#include "lib_flash.h"
#include "lib_utils.h"

#define MAX_APP_SIZE (0x1FFFFF) // ( 0x0807FFFF - 0x08010000)

uint8_t OTA_getProgressPercentage();
flashOtaStatus_et OTA_getLastOtaStatus();

#endif /* LIB_OTA_H_ */
