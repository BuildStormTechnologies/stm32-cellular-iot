/**
 * \copyright Copyright (c) 2021-2024, Buildstorm Pvt Ltd
 *
 * \file lib_attributes.h
 * \brief An Thingboard Attribute library file
 *
 *  Attribute library handles synchronization of Client and Shared attributes between the device and server
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

#ifndef _LIB_ATTRIBUTE_H_
#define _LIB_ATTRIBUTE_H_

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
    char str[LENGTH_THINGSBOARD_KEY_VALUE]; /*!< Value of type string */
} value_st;

/**
 * @enum attributeType_et
 * An enum that represents all possible attribute value types.
 */
typedef enum
{
    ATTRIBUTE_CLIENT, /*!< Client Attributes*/
    ATTRIBUTE_SHARED, /*!< Shared Attributes */
    ATTRIBUTE_MAX,    /*!< Total number of attribute types */
} attributeType_et;

/**
 * @brief Attribute update callback function type. The application should
 * define the callback function and intialize it in the @ref attribute_st
 * configuration.
 */
typedef void (*attributeUpdateCallBack_t)(const char *pKeyStr, const void *pValue, valueType_et valuetype);

/**
 * @brief Register a attribute element to receive callbacks whenever the attribute
 * element is updated with a new value.
 * @param [in] attribute_st Pointer to attribute element configuration
 * @returns Status to indicate if the attribute element is registered
 * @retval true registered successfully
 * @retval false when failed
 */
bool ATTRIBUTE_register(const char *pKey, attributeType_et attrType, valueType_et valuetype, attributeUpdateCallBack_t callbackHandler);

/**
 * @brief Update the attribute element.
 * @param [in] attributeIndex (0-Classic, 1--n Named Twins)
 * @param [in] pKeyStr A key representing attribute element
 * @param [in] pValue New value of the attribute element
 * @param [in] attributeUpdateType_et Type of attribute update
 * @returns Attribute update status
 * @retval true on success
 * @retval false on failure
 */
bool ATTRIBUTE_update(const char *pKeyStr, void *pValue);

#endif //_LIB_ATTRIBUTE_H_