/**
 * \copyright Copyright (c) 2019-2024, Buildstorm Pvt Ltd
 *
 * \file app_config.h
 * \brief app_config header file.
 *
 * The app_config Contains macros for the application.
 *
 *
 */

#ifndef _APP_CONFIG_H_
#define _APP_CONFIG_H_

#include <stdbool.h>
#include <stdint.h>

#include "stdbool.h"
#include "stdint.h"

#include "lib_config.h"

#define APP_MODULE_MAIN LIB_MODULE_MAX

//-------------------------APP CONFIG--------------------------/
#define THING_NAME "DEVICE NAME"
#define ACCESS_TOKEN "DEVICE ACCESS TOKEN"

#define THINGSBOARD_URI "mqtt://cloud.thingsboard.io"
#define THINGSBOARD_PORT 1883

#define PROVISION_DEVICE_KEY    "DEVICE PROVISION KEY"
#define PROVISION_DEVICE_SECRET "DEVICE PROVISION SECRET"

#define THINGSBOARD_TELEMETRY_TOPIC "v1/devices/me/telemetry"

#define APN "airtelgprs.com"
#define USERID ""
#define PASSWORD ""

#define MODEM_POWERKEY_GPIO_PORT  GPIOD
#define MODEM_POWERKEY_GPIO_PIN   GPIO_PIN_11

#define APP_VERSION "v1.0.0"

void app_main();
void sys_init();

#endif //_APP_CONFIG_H_
