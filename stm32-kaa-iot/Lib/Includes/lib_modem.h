/**
* \copyright Copyright (c) 2019-2024, Buildstorm Pvt Ltd
*
* \file lib_http.h
* \brief Modem library header file.
*
*
* This file defines the structure and enums used for modem configurations and state handling.
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

#ifndef _LIB_MODEM_H_
#define _LIB_MODEM_H_

#include <stdint.h>
#include "stm32f4xx_hal.h"

#include "lib_msg.h"
#include "lib_http.h"

#define ENABLE_MODEM_RESPONSE_LOG TRUE

#define MAX_HTTP_POST_DATA_LEN 512
#define MAX_HTTP_RESPONSE_DATA_LEN 1250 // should be more than LENGTH_HTTP_PACKET
#define MODEM_RESPONSE_DATA_LEN 2048

typedef enum {
    STATE_MODEM_IDLE,
    STATE_MODEM_POWER_OFF,
    STATE_MODEM_POWER_ON,
    STATE_MODEM_RESET,
    STATE_MODEM_START,
    STATE_MODEM_WAIT_FOR_READY,
    STATE_MODEM_GET_INFO,
    STATE_MODEM_GET_IMEI_NUM,
    STATE_MODEM_VERIFY_SIM_STATUS,
    STATE_MODEM_WAIT_FOR_NW_REG,
    STATE_MODEM_SET_APN,
    STATE_MODEM_GPRS_CONFIG,
    STATE_MODEM_ACTIVATE_GPRS,
    STATE_MODEM_WAIT_FOR_IP,
    STATE_MODEM_CONFIGURE_MQTT_SSL,
    STATE_MODEM_DELETE_CA_CERTIFICATE,
    STATE_MODEM_DELETE_CLIENT_CERTIFICATE,
    STATE_MODEM_DELETE_CLIENT_KEY_CERTIFICATE,
    STATE_MODEM_WRITE_CA_CERTIFICATE,
    STATE_MODEM_WRITE_CLIENT_CERTIFICATE,
    STATE_MODEM_WRITE_CLIENT_KEY_CERTIFICATE,
    STATE_MODEM_CONFIGURE_CERTIFICATES,
    STATE_MODEM_CONFIGURE_QSSL,
    STATE_MODEM_MQTT_OPEN,
    STATE_MODEM_MQTT_CONNECTING,
    STATE_MODEM_MQTT_SUBSCRIBE,
    STATE_MODEM_MQTT_CONNECTED,
    STATE_MODEM_MQTT_DISCONNECT,
    STATE_MODEM_MAX
}modemStates_et;

typedef enum{
    QUECTEL_M66,
    QUECTEL_M95,
    QUECTEL_BG96,
    QUECTEL_EC200U,
    SIMA7670C,
    SIMA7670E,
    MODEM_MODEL_MAX
}modemModel_et;

typedef struct
{
    modemModel_et model;
    UART_HandleTypeDef *pUartHandle;
    GPIO_TypeDef *pPwKeyPort;
    uint16_t pwKeyPin_u8;
    uint16_t resetKeyPin_u8;
    char *pApn;
    char *pApnUsrName;
    char *pApnPwd;
} modemPortConfig_st;

typedef struct
{
  char timeUTC[12];
  char status[2];
  char lat[11];
  char ns[2];
  char lon[12];
  char ew[2];
  char speed[10];
  char course[10];
  char dateUTC[7];
  bool gpsValid;       // 0-Invalid, 1-Valid
  uint8_t newDataReceived; // not for user, do not modify this value.
} gpsData_st;


char *MODEM_getImei();
int8_t MODEM_getRssi();

modemStates_et MODEM_getState();
const char *MODEM_getStateString();

void MODEM_printStatus();
void MODEM_restart();

char *MODEM_getRevision();
const char *MODEM_getModel();
httpStates_et MODEM_getHttpState();

bool MODEM_isConnected();
bool MODEM_isMqttConnected();
bool MODEM_isReadyToPublish();


bool GPS_getData(gpsData_st *ps_gpsData);
void GPS_enableDisable(uint8_t enable);

#endif
