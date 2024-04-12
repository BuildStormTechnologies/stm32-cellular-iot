/**
* \copyright Copyright (c) 2019-2024, Buildstorm Pvt Ltd
*
* \file lib_thingsboard.h
* \brief Thingsboard library header file.
*
*
*  This library handles the ThingsBoard platform's core features:
*   - Device Provisioning
*   - Telemetry updates
*   - Client and Shared Attribute hanlding
*   - OTA
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

#ifndef _THINGSBOARD_H_
#define _THINGSBOARD_H_

#include "lib_config.h"
#include "lib_msg.h"
#include "lib_utils.h"

typedef struct
{
    char *pUriStr;                /*!< MQTT broker URI */
    char *pHostNameStr;           /*!< MQTT IoT Endpoint */
    uint16_t port_u16;            /*!< MQTT IoT port number */
    char *pCertStr;               /*!< Certificate string */
    char *pUserNameStr;           /*!< MQTT username */
    char *pPasswordStr;           /*!< MQTT password */
    char *pAccessTokenStr;        /*!< MQTT password */
    char *pClientIdStr;           /*!< MQTT password */
    const char *pThingNameStr;    /*!< MQTT IoT thing name */
    char *pProvisionDeviceSecret; /*!< Provision Device Secret */
    char *pProvisionDeviceKey;    /*!< Provision Device Key */
} mqttClientConfig_st;

/**
 * @enum valueType_et
 * An enum that represents all possible thingsboard value types.
 */
typedef enum
{
    VALUE_TYPE_INT,    /*!< Attribute value type as integer */
    VALUE_TYPE_FLOAT,  /*!< Attribute value type as float */
    VALUE_TYPE_STRING, /*!< Attribute value type as string */
    VALUE_TYPE_MAX,    /*!< Total number of attribute value types */
} valueType_et;

/**
 * @brief Check if thingsboard is connected to broker.
 * @param none
 * @returns Status of connection
 * @retval true if connected
 * @retval false if disconnected
 */
bool TB_isConnected();

/**
 * @brief Check if thingsboard is initialized and has started.
 * @param none
 * @return status of thingsboard has started or not
 * @retval true if thingsboard has started
 * @retval false if thingsboard has not started
 */
bool TB_isStarted();

/**
 * @brief Close and terminate thingsboard connection
 * @param none
 * @returns Status of close request
 * @retval true if closed successfully
 * @retval false if failed to close
 */
bool TB_close();

/**
 * @brief Subscribe to a give topic.
 * @param [in] pTopicStr Topic to subscribe
 * @param [in] qos_e QOS Level
 * @returns Status to indicate if subscrption was successful or not
 * @retval true subscribed successfully
 * @retval false failed to subscribe
 */
bool TB_subscribe(char *pTopicStr, uint8_t qos_e);

/**
 * @brief Publish a given message.
 * @param [in] ps_msg Message to be published
 * @returns Status of publish request
 * @retval true if published
 * @retval false on error
 */
bool TB_publish(mqttMsg_st *ps_msg);

/**
 * @brief Check is messages are available on subsribed topics. The library
 * maintains a buffer to store received messages.
 * @param none
 * @returns Number of bytes available
 */
uint8_t TB_availableToRead();

/**
 * @brief Read the received message received.
 * @param [out] ps_msg
 * @returns Status of read message
 * @retval true on success
 * @retval false on failure
 */
bool TB_read(mqttMsg_st *ps_msg);

/**
 * @brief Print the status of thingsboard library.
 * @param none
 * @returns none
 */
void TB_printStatus();

void TB_restart();
const char *TB_getThingName();

#endif //_THINGSBOARD_H_
