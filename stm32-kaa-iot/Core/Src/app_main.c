/*
 * app_main.c
 *
 *  Created on: 20-Nov-2022
 *      Author: bagwan
 */

#include "app_config.h"
#include "lib_system.h"
#include "lib_print.h"
#include "lib_metadata.h"
#include "lib_telemetry.h"
#include "lib_commands.h"



#define thisModule APP_MODULE_MAIN

#define LED_BLINK_VERSION TRUE

uint32_t ledBlinkCount_u32 = 0;
uint32_t nextBlinkTime_u32 = 0;

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
        print_verbose("EVENT_MQTT_CONNECTED");
        break;
    case EVENT_MQTT_DISCONNECTED:
        print_verbose("EVENT_MQTT_DISCONNECTED");
        break;

    default:
        break;
    }
}


void cmd_callBackHander(const char *pCmd, const char* pCmdId, const char *pPayload)
{
    print_verbose("id:%s [%s]:%s",pCmdId,pCmd,pPayload);
    if(strcmp(pCmd,"LED")==0)
    {
        ledBlinkCount_u32 = util_getNumFromStringU32(pPayload);
        if((ledBlinkCount_u32 == 0) || (ledBlinkCount_u32 == 1))
        {
           app_updateLedState(ledBlinkCount_u32); // 0-LED OFF,  1-> LED ON
           ledBlinkCount_u32 = 0;
        }
        else //N- Blink led N-times
        {
            ledBlinkCount_u32 = ledBlinkCount_u32*2; // double it for ON->OFF cycle
        }
    }
    COMMAND_updateStatus(pCmd,pCmdId,pPayload,200,"Ok");
}

void app_handleLedCmd()
{
    if (ledBlinkCount_u32)
    {
        if (millis() > nextBlinkTime_u32)
        {
            ledBlinkCount_u32--;
            nextBlinkTime_u32 = millis() + 500;
            app_updateLedState(ledBlinkCount_u32 & 0x01);
        }
    }
}

void metadata_updateCallBack(const char *pKeyStr, const void *pValue, valueType_et valuetype)
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
}



void sys_init()
{
	/* USER CODE BEGIN systemTask */
	systemInitConfig_st s_sysConfig = {
			.systemEventCallbackHandler = app_eventsCallBackHandler,
			.pAppVersionStr = APP_VERSION,
			.pDebugUarthandle = &huart2, //Tx:PA2  Rx:PA3
			.maxMetaElements_u8 = 4,
			.maxTelemetryElements_u8 = 2,
             .maxCommands_u8 = 2,
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
					.pUriStr = KAA_URI,
					 .port_u16 = KAA_PORT,
					 .pKaaApplicationVersionStr = KAA_APPLICATION_VERSION,
                    .pAccessTokenStr = KAA_ENDPOINT_TOKEN
			}


	};

	if(SYSTEM_init(&s_sysConfig)==TRUE)
	{
		if(SYSTEM_getMode() == SYSTEM_MODE_NORMAL)
		{
			METADATA_register("testMeta", VALUE_TYPE_STRING, metadata_updateCallBack);
            COMMAND_register("LED", cmd_callBackHander);		
		}
			}
}


void app_main()
{
  static uint32_t nextPubTime = 0;
    uint32_t temp_u32 = 20;
    float humidity = 10.0;

    if(nextPubTime == 0)
    {
       nextPubTime = millis();
       METADATA_update("platform", (void *)"ESP32", VALUE_TYPE_STRING);
       METADATA_update("bootTime", &nextPubTime, VALUE_TYPE_INT);
    }

    while (1)
    {
        if (SYSTEM_getMode() == SYSTEM_MODE_NORMAL)
        {
            if (KAA_isConnected())
            {
                if ((millis() > nextPubTime))
                {
                    TELEMETRY_update("temp", &temp_u32, VALUE_TYPE_INT);
                    TELEMETRY_update("hum", &humidity, VALUE_TYPE_FLOAT);
                    print_verbose("[temp]:%d [hum]: %.2f\n", temp_u32, humidity);

                    temp_u32++;
                    humidity = humidity + 1.1;
                    nextPubTime = millis() + 5000;
                }
                app_handleLedCmd();
            }
        }

        TASK_DELAY_MS(200);
    }
	}







