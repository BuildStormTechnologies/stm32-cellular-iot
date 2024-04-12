/***************************************************************************************************
                                   BuildStorm.com
 ****************************************************************************************************
 * File        : app_config.h
 * Description : This file provides the user application configuration

Copyright ? 2021 BuildStorm Private Limited

The software is licensed to you under End-User License Agreement (EULA) of BuildStorm Software and Firmware Libraries.
A copy of EULA is available for you https://buildstorm.com/eula
**************************************************************************************************/

#ifndef _APP_CONFIG_H_
#define _APP_CONFIG_H_

#include <stdbool.h>
#include <stdint.h>

#include "stdbool.h"
#include "stdint.h"

#include "lib_config.h"

#define APP_MODULE_MAIN LIB_MODULE_MAX

//-------------------------APP CONFIG--------------------------/

#define KAA_URI "mqtt://mqtt.cloud.kaaiot.com"
#define KAA_PORT 1883

#define KAA_APPLICATION_VERSION "YOUR DEVICE APPLICATION VERSION"
#define KAA_ENDPOINT_TOKEN "YOUR DEVICE ENDPOINT TOKEN"


#define APN "airtelgprs.com"
#define USERID ""
#define PASSWORD ""

#define MODEM_POWERKEY_GPIO_PORT GPIOD
#define MODEM_POWERKEY_GPIO_PIN GPIO_PIN_11

#define APP_VERSION "v1.0.0"

void app_main();
void sys_init();

#endif //_APP_CONFIG_H_
