/**
 * \copyright Copyright (c) 2019-2024, Buildstorm Pvt Ltd
 *
 * \file lib_config.h
 * \brief Config library header file.
 *
 *
 * The Config library takes care of the configurations needed for Wifi, Ble ,Device ,Http
 * MQTT, Task, Flash, Ota.
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

#ifndef _LIB_CONFIG_H_
#define _LIB_CONFIG_H_

#include <stdbool.h>
#include <stdint.h>




#include "lib_utils.h"

//---------------------------Debug CONFIG---------------------------/

/**
 * @enum logLevels_et
 * @brief Levels of debug messages for printing.
 */
typedef enum
{
    PRINT_LEVEL_NONE = 0,    /*!< Does not print any log messages */
    PRINT_LEVEL_ERROR = 1,   /*!< Prints Error level log messages alone */
    PRINT_LEVEL_VERBOSE = 1, /*!< Prints log messages of both Error & Verbose level */
    PRINT_LEVEL_INFO = 2,    /*!< Prints log messages of Error, Verbose & Info level */
    PRINT_LEVEL_DEBUG = 3,   /*!< Prints log messages of all levels */
    PRINT_LEVEL_MAX = 4      /*!< Total number of log levels */
} logLevels_et;

#define LOG_LEVEL_MAPPING  \
    {                      \
        'n', 'e', 'i', 'd' \
    }
#define GLOBAL_LOG_LEVEL PRINT_LEVEL_ERROR

/**
 * @enum menusLibModule_et
 * @brief An enum to represent Library modules.
 */
typedef enum
{
    LIB_MODULE_MAIN_MENU,
    LIB_MODULE_SYSTEM,
    LIB_MODULE_MQTT,
    LIB_MODULE_MODEM,
    LIB_MODULE_FLASH,
    LIB_MODULE_JSON,
    LIB_MODULE_HTTP,
    LIB_MODULE_OTA,

    LIB_MODULE_KAA,
    LIB_MODULE_MAX
} menusLibModule_et;

//--------------------------DEVICE CONFIG--------------------------------/
#define LENGTH_CHIP_ID LENGTH_MAC_ADDRESS
#define LENGTH_DEVICE_NAME 32
#define LENGTH_DEVICE_NAME_PREFIX 8 // it should be less than (LENGTH_DEVICE_NAME/2)
#define LENGTH_PRODUCT_ID LENGTH_DEVICE_NAME
#define LENGTH_APP_VERSION 10

#define TIME_MILLIS_ROLLOVER 0xFF000000 // in milli seconds (max millis

//--------------------------HTTP CONFIG--------------------------------/
#define LENGTH_HTTP_URL 150
#define LENGTH_HTTP_PACKET 1024
#define HTTP_RING_BUFFER_SIZE 4

//--------------------------MQTT CONFIG--------------------------------/

#define LENGTH_MQTT_HOST 150
#define LENGTH_MQTT_TOPIC 100
#define LENGTH_MQTT_PAYLOAD 1024
#define MQTT_MAX_SUBSCRIBE_TOPICS 4

#define LENGTH_MQTT_URI LENGTH_HTTP_URL
#define LENGTH_MQTT_USERNAME 32
#define LENGTH_MQTT_PASSWORD 32
#define LENGTH_MQTT_CLIENT_ID 32
#define LENGTH_THING_NAME LENGTH_DEVICE_NAME

#define MQTT_PUB_RING_BUFFER_SIZE 5
#define MQTT_SUB_RING_BUFFER_SIZE 1

//--------------------------Thingsboard CONFIG-------------------------/
#define MAX_TELEMETRY_ELEMETS 10
#define MAX_METADATA_ELEMETS 10
#define MAX_COMMAND_ELEMETS 10
#define LENGTH_METADATA_KEY_VALUE 20


#define MODEM_PUBLISH_RING_BUFFER_SIZE 5
#define MODEM_SUBSCRIBE_RING_BUFFER_SIZE 3
#define MODEM_HTTP_RING_BUFFER_SIZE 10


#define SIZE_JSON_PACKET_DATA_BUFFER 512
#define SIZE_JSON_SHARED_MSG_BUFFER 512

//-------------------------TASK CONFIG--------------------------/
#define TASK_SYSTEM_PRIORITY 5
#define TASK_SYSTEM_STACK_SIZE (6 * 1024) // reduce it to 4096

//------------------------OTA CONFIG--------------------------------/
#define LENGTH_OTA_URL LENGTH_HTTP_URL

#define TIME_MILLIS_ROLLOVER 0xFF000000 // in milli seconds (max millis value is 0xFFFFFFFF (uint32_t))

#endif
