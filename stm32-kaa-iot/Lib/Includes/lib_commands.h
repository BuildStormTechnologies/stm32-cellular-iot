/**
 * \copyright Copyright (c) 2021-2024, Buildstorm Pvt Ltd
 *
 * \file lib_commands.h
 * \brief An Kaa Command library file
 *
 *  Command library handles synchronization of commands between the device and server
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

#ifndef _LIB_COMMANDS_H_
#define _LIB_COMMANDS_H_

#include "lib_config.h"
#include "lib_msg.h"
#include "lib_utils.h"
#include "lib_json.h"


/**
 * @brief Command update callback function type. The application should
 * define the callback function and intialize it in the @ref command_st
 * configuration.
 */
typedef void (*commandCallBack_t)(const char *pCmd, const char* pCmdId, const char *pPayload);

/**
 * @brief Register a command element to receive callbacks whenever the command
 * element is updated with a new value.
 * @param [in] pKeyStr A key representing command element
  * @param [in] callbackHandler to get notified on command update
 * @retval false when failed
 */
bool COMMAND_register(const char *pKey, commandCallBack_t callbackHandler);

/**
 * @brief Update the command status.
 * @param [in] pCmd   A key representing command
 * @param [in] pCmdId CMD Id received along with command
 * @param [in] pPayload Payload to be sent in cmd response
 * @param [in] statusCode 200-Success, 400+-Failed to be sent in cmd response
 * @param [in] phrase Ok for Success, or failed reason
 * @returns Command update status
 * @retval true on success
 * @retval false on failure
 */
bool COMMAND_updateStatus(const char *pCmd, const char *pCmdId,const char* pPayload,uint16_t statusCode,const char *phrase);
#endif