/**
 * \copyright Copyright (c) 2021-2024, Buildstorm Pvt Ltd
 *
 * \file lib_metadatas.h
 * \brief An Kaa Metadata library file
 *
 *  Metadata library handles synchronization of Client and Shared metadatas between the device and server
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

#ifndef _LIB_METADATA_H_
#define _LIB_METADATA_H_

#include "lib_config.h"
#include "lib_msg.h"
#include "lib_utils.h"
#include "lib_json.h"
/**
 * @struct value_st
 * This is a twin value type.
 */
typedef struct
{
    int32_t val_i32;                        /*!< Value of type int32_t */
    float val_f32;                          /*!< Value of type float */
    char str[LENGTH_METADATA_KEY_VALUE]; /*!< Value of type string */
} value_st;

/**
 * @brief Metadata update callback function type. The application should
 * define the callback function and intialize it in the @ref metadata_st
 * configuration.
 */
typedef void (*metadataUpdateCallBack_t)(const char *pKeyStr, const void *pValue, valueType_et valuetype);

/**
 * @brief Register a metadata element to receive callbacks whenever the metadata
 * element is updated with a new value.
 * @param [in] pKeyStr A key representing metadata element
 * @param [in] valuetype Type of the meadatadata (int/float/string)
  * @param [in] callbackHandler to get notified on metadata update
 * @retval false when failed
 */
bool METADATA_register(const char *pKey, valueType_et valuetype, metadataUpdateCallBack_t callbackHandler);

/**
 * @brief Update the metadata element.
 * @param [in] pKeyStr A key representing metadata element
 * @param [in] pValue New value of the metadata element
 * @returns Metadata update status
 * @retval true on success
 * @retval false on failure
 */
bool METADATA_update(const char *pKeyStr, void *pValue, valueType_et valuetype);
#endif