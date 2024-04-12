/**
* \copyright Copyright (c) 2019-2024, Buildstorm Pvt Ltd
*
* \file lib_http.h
* \brief Http library header file.
*
*
* This file defines the structure and enums used by the HTTP library and handles http requests.
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

#ifndef _LIB_HTTP_H_
#define _LIB_HTTP_H_

#include "lib_utils.h"
#include "lib_json.h"

#define HTTP_TIMEOUT 10000
#define MAX_HTTP_HEADERS 3
#define HTTP_GET_REQ_RETRY_LIMIT 3

/**
 * @enum httpReq_et
 * An enum that represents HTTP requests supported by the library.
 */
typedef enum
{
    HTTP_REQUEST_GET = 0,     /*!< HTTP GET Method */
    HTTP_REQUEST_POST,        /*!< HTTP POST Method */
    HTTP_REQUEST_PUT,         /*!< HTTP PUT Method */
    HTTP_REQUEST_PATCH,       /*!< HTTP PATCH Method */
    HTTP_REQUEST_DELETE,      /*!< HTTP DELETE Method */
    HTTP_REQUEST_HEAD,        /*!< HTTP HEAD Method */
    HTTP_REQUEST_NOTIFY,      /*!< HTTP NOTIFY Method */
    HTTP_REQUEST_SUBSCRIBE,   /*!< HTTP SUBSCRIBE Method */
    HTTP_REQUEST_UNSUBSCRIBE, /*!< HTTP UNSUBSCRIBE Method */
    HTTP_REQUEST_OPTIONS,     /*!< HTTP OPTIONS Method */
    HTTP_REQUEST_MAX,
} httpReq_et;



#define FOREACH_HTTP_STATE(HTTP_STATE)            \
    HTTP_STATE(STATE_HTTP_IDLE)                   \
    HTTP_STATE(STATE_HTTP_START)                  \
    HTTP_STATE(STATE_HTTP_SET_REQUEST_HEADER)     \
    HTTP_STATE(STATE_HTTP_SET_RESPONSE_HEADER)    \
    HTTP_STATE(STATE_HTTP_CONNECT)                \
    HTTP_STATE(STATE_HTTP_SET_URL)                \
    HTTP_STATE(STATE_HTTP_SET_SSLCFG)             \
    HTTP_STATE(STATE_HTTP_GET_REQUEST)            \
    HTTP_STATE(STATE_HTTP_POST_REQUEST)           \
    HTTP_STATE(STATE_HTTP_POST_DATA)              \
    HTTP_STATE(STATE_HTTP_WAIT_FOR_POST_RESPONSE) \
    HTTP_STATE(STATE_HTTP_READ)                   \
    HTTP_STATE(STATE_HTTP_WAIT_FOR_FILE_HEADER)   \
    HTTP_STATE(STATE_HTTP_DOWNLOAD_FILE)          \
    HTTP_STATE(STATE_HTTP_DOWNLOAD_COMPLETE)      \
    HTTP_STATE(STATE_HTTP_RETRY)                  \
    HTTP_STATE(STATE_HTTP_TIMEOUT)                \
    HTTP_STATE(STATE_HTTP_FAILED)                 \
    HTTP_STATE(STATE_HTTP_CLOSE)                  \
    HTTP_STATE(STATE_HTTP_MAX)

typedef enum
{
    FOREACH_HTTP_STATE(util_generateEnum)
} httpStates_et;

/**
 * @brief An HTTP Configuration structure.
 */
typedef struct
{
    httpReq_et reqType_e;                         /*!< HTTP request type */
    tagStructure_st as_headers[MAX_HTTP_HEADERS]; /*!< HTTP headers */
    char *pUrlStr;                                /*!< HTTP request URL */
    char *pPayloadStr;                            /*!< HTTP payload as string */
    bool header_b8;
} httpConfig_st;

/**
 * @brief Initialize HTTP configuration request and send the request.
 * @param [in] ps_config HTTP configuration
 * @returns Status of HTTP start request
 * @retval true on success
 * @retval false on failure
 */
bool HTTP_start(httpConfig_st *ps_config);

/**
 * @brief Check if HTTP data is available for read
 * @param none
 * @returns Number of bytes available to read
 */
uint16_t HTTP_availableToRead();

/**
 * @brief Read HTTP response
 * @param [out] ps_packet Response data
 * @returns read status
 * @retval true on success
 * @retval false on failure
 */
bool HTTP_read(packet_st *ps_packet);

/**
 * @brief Close HTTP connection
 * @param none
 * @returns none
 */
void HTTP_close();

/**
 * @brief Get HTTP state as string
 * @param [in] state_e HTTP state
 * @returns String version of HTTP states @ref httpStates_et
 *
 */
const char *HTTP_getStateString(httpStates_et state_e);

#endif //_LIB_HTTP_H_
