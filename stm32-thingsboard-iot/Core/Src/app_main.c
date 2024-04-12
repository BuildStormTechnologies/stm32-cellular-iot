/*
 * app_main.c
 *
 *  Created on: 20-Nov-2022
 *      Author: bagwan
 */

#include "app_config.h"
#include "lib_system.h"
#include "lib_print.h"
#include "lib_attributes.h"
#include "lib_telemetry.h"



#define thisModule APP_MODULE_MAIN

#define LED_BLINK_VERSION TRUE

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

void app_updateLedState(uint8_t val)
{
  GPIO_PinState pinState = val ? GPIO_PIN_SET : GPIO_PIN_RESET;

  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, pinState);
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, pinState);
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, pinState);
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, pinState);
}


void app_eventsCallBackHandler(systemEvents_et event_e)
{
  switch (event_e)
  {
    case EVENT_MQTT_CONNECTED:
      print_info("EVENT_AWS_CONNECTED");
      break;
    case EVENT_MQTT_DISCONNECTED:
      print_info("EVENT_AWS_DISCONNECTED");
      break;

    default:
      break;
  }
}

void attributeUpdateCallBack(const char *pKeyStr, const void *pValue, valueType_et valuetype)
{
  switch (valuetype)
  {
    case VALUE_TYPE_INT:
      print_verbose("[%s]: %d", pKeyStr, *(int *)pValue);
      break;

    case VALUE_TYPE_FLOAT:
      print_verbose("[%s]: %.2f", pKeyStr, *(float *)pValue);
      break;

    case VALUE_TYPE_STRING:
      print_verbose("[%s]: %s", pKeyStr, pValue);
      break;

    default:
      break;
  }

  if(strcmp(pKeyStr,"LED")==0)
    {
      app_updateLedState( *(int *)pValue);
    }
}


void sys_init()
{
  /* USER CODE BEGIN systemTask */
  systemInitConfig_st s_sysConfig = {
      .systemEventCallbackHandler = app_eventsCallBackHandler,
      .pAppVersionStr = APP_VERSION,
      .pDebugUarthandle = &huart2, //Tx:PA2  Rx:PA3
      .maxAttributes_u8 = 4,
      .maxTelemetryElements_u8 = 2,
      .s_modemConfig =
          {
              .model = QUECTEL_EC200U,
              .pUartHandle = &huart1, //Tx:PB6  Rx:PB7
              .pPwKeyPort = MODEM_POWERKEY_GPIO_PORT, //PD11
              .pwKeyPin_u8 = MODEM_POWERKEY_GPIO_PIN,  //PD11
              .pApn = APN,
              .pApnUsrName = USERID,
              .pApnPwd = PASSWORD,
          },

          /* Thingsboard Configuration */
          .s_mqttClientConfig = {
              .pUriStr = THINGSBOARD_URI,
              .pThingNameStr = THING_NAME,
              .pAccessTokenStr = ACCESS_TOKEN,
              //					.pProvisionDeviceKey = PROVISION_DEVICE_KEY,
              //					.pProvisionDeviceSecret = PROVISION_DEVICE_SECRET
      }


  };

  if(SYSTEM_init(&s_sysConfig)==TRUE)
    {
      if(SYSTEM_getMode() == SYSTEM_MODE_NORMAL)
        {
          ATTRIBUTE_register("testString", ATTRIBUTE_SHARED, VALUE_TYPE_STRING, attributeUpdateCallBack);
          ATTRIBUTE_register("testInt", ATTRIBUTE_SHARED, VALUE_TYPE_INT, attributeUpdateCallBack);
          ATTRIBUTE_register("testFloat", ATTRIBUTE_SHARED, VALUE_TYPE_FLOAT, attributeUpdateCallBack);
          ATTRIBUTE_register("LED", ATTRIBUTE_SHARED, VALUE_TYPE_INT, attributeUpdateCallBack);
        }

    }
}


void app_main()
{
  static uint32_t temp_u32 = 10;
  static float humidity = 10;
  static uint32_t nextUpdateTime_u32 = 0;
  static uint8_t led;

  app_updateLedState(0);

  while(1)
    {

      switch (SYSTEM_getMode())
      {
        case SYSTEM_MODE_CONFIG:
          if(millis()>nextUpdateTime_u32)
            {
              app_updateLedState(led);
              nextUpdateTime_u32 = millis()+1000;
              led=!led;
            }
          break;
        case SYSTEM_MODE_NORMAL:
          if (TB_isConnected())
            {
              if ((millis() > nextUpdateTime_u32))
                {
                  TELEMETRY_update("temp", &temp_u32, VALUE_TYPE_INT);
                  TELEMETRY_update("hum", &humidity, VALUE_TYPE_FLOAT);
                  print_verbose("[temp]:%d [hum]: %.2f\n", temp_u32, humidity);

                  temp_u32++;
                  humidity+=1.1;
                  nextUpdateTime_u32 = millis() + 5000;

                }
            }
          break;
        case SYSTEM_MODE_OTA:
          break;
        default:
          break;
      }

      TASK_DELAY_MS(100);
    }
}







