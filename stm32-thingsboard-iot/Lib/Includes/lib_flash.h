/**
* \copyright Copyright (c) 2019-2024, Buildstorm Pvt Ltd
*
* \file lib_flash.h
* \brief Flash library header file.
*
* This file defines the structure and enums used by the Flash library.
*
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

#ifndef LIB_FLASH_H_
#define LIB_FLASH_H_

#include "lib_utils.h"
/*************************************************************
 *                    ENUMS
 *************************************************************/

#define FLASH_CONFIG_DEFAULT 0x99
#define FLASH_CONFIG_VALID 0x55



/*---------------------------structures-------------------------------------*/
/**
 * @enum flashStatus_t
 * An enum to represent the status of flash operations.
 */
typedef enum
{
    FLASH_STATUS_OK,              /*!< Status ok */
    FLASH_STATUS_BUSY,            /*!< Status busy */
    FLASH_STATUS_LOAD_DEFAULT,    /*!< Load default configuration values */
    FLASH_STATUS_READ_FAIL,       /*!< Read failed */
    FLASH_STATUS_WRITE_FAIL,      /*!< Write failed */
    FLASH_STATUS_INVALID_DATASET, /*!< Data is invalid */
    FLASH_STATUS_MAX              /*!< Total number of status for Flash library */
} flashStatus_t;

typedef enum
{
    OTA_STATUS_READY,
    OTA_STATUS_SUCCESS,
    OTA_STATUS_INTERNAL_UPDATE,
    OTA_STATUS_WRONG_CRC,
    OTA_STATUS_TIMEDOUT,
    OTA_STATUS_FALSH_ERROR,
    OTA_STATUS_MAX
} flashOtaStatus_et;

typedef enum
{
    OTA_UPDATE_TYPE_NONE,
    OTA_UPDATE_TYPE_INTERNAL,
    OTA_UPDATE_TYPE_SERIAL,
    OTA_UPDATE_TYPE_WEB,
    OTA_UPDATE_TYPE_MAX
} firmUpdateType_et;

/**********************************************************************/


bool FLASH_isBusy();
bool FLASH_isDeviceRegistered();

uint16_t FLASH_getAppData(uint8_t *pData, uint16_t len_u16);
flashStatus_t FLASH_updateAppData(uint8_t *pData, uint16_t len_u16);

#endif //LIB_FLASH_H_
