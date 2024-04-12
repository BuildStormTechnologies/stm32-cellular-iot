/**
 * \copyright Copyright (c) 2019 - 2024, Buildstorm Pvt Ltd
 *
 * \file lib_telemetry.h
 * \brief Kaa telemetry library file
 *
 * This library handles updating the telemetry data to the thingsboard cloud.
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

#ifndef _LIB_TELEMETRY_H_
#define _LIB_TELEMERY_H_

#include "lib_config.h"
#include "lib_msg.h"
#include "lib_utils.h"
#include "lib_json.h"

/**
 * @brief Update the telemetry element.
 * @param [in] pKeyStr A key representing telemetry element
 * @param [in] pValue New value to be sent to telemetry
 * @returns telemetry update status
 * @retval true on success
 * @retval false on failure
 */
bool TELEMETRY_update(const char *pkey, void *pValue, valueType_et valType);

#endif