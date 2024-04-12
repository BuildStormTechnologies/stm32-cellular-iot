/*
 * app_main.c
 *
 *  Created on: 20-Nov-2022
 *      Author: bagwan
 */

#include <lib_jobs.h>
#include <lib_system.h>

#include "app_config.h"


#define thisModule APP_MODULE_MAIN

#define USE_FLASH_CERTIFICATES FALSE
#define LED_BLINK_VERSION TRUE

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

#define MAX_LED_BLINK_COUNT 5

#define STR_SHADOW_KEY_LED "LED"
#define STR_SHADOW_KEY_COLOR "COLOR"

#define DESIRED_LED_STATE 0
#define DESIRED_COLOR "RED"

#define PUBLISH_TOPIC_STR "devicePubTopic"
#define SUBSCRIBE_TOPIC_STR "deviceSubTopic"

mqttMsg_st pubMsg = {0};
mqttMsg_st subMsg = {0};

int32_t gDesiredLedState_s32=0,gReportedLedState_s32=0;
char gDesiredColorStr[12]=DESIRED_COLOR, gReportedColorStr[12]=DESIRED_COLOR;

static char gJobIdStr[LENGTH_JOB_ID] = {0};
static char gJobDocumentStr[LENGTH_JOB_DOCUMENT] = {0};
static bool gJobReceived_b8 = FALSE;

void classicShadowUpdateCallBack(uint8_t elementIndex_u8,const char *pKeyStr,const void *pValue);

#define CLASSIC_SHADOW 0
#define MAX_TYPES_OF_SHADOWS 1

const awsShadowElement_st classicShadowElements[] ={
                         /* Shaodw Value type          Key         value                    needToPublish shadowUpdateType*/
                        {SHADOW_VALUE_TYPE_STRING,   "fw_ver",   s_value:{pStr:APP_VERSION},     TRUE,   SHADOW_UPDATE_TYPE_ALL},
                        {SHADOW_VALUE_TYPE_INT,      "LED",      s_value:{val_i32:0},           TRUE,   SHADOW_UPDATE_TYPE_ALL},
                        {SHADOW_VALUE_TYPE_STRING,   "COLOR",    s_value:{pStr:DESIRED_COLOR},   TRUE,   SHADOW_UPDATE_TYPE_ALL},
                     };


const shadowConfigTable_st shadowTable[MAX_TYPES_OF_SHADOWS]=
{
   { // CLASSIC_SHADOW
      ptrShadowName:NULL,
      maxElementCount_u8:(sizeof(classicShadowElements)/sizeof(classicShadowElements[0])),
	  callbackHandler:classicShadowUpdateCallBack,
      pShadowElementsTable: classicShadowElements,
    },
};


void classicShadowUpdateCallBack(uint8_t elementIndex_u8, const char *pKeyStr, const void *pValue)
{
   print_verbose("Classic shadow: %s",pKeyStr);
    if(elementIndex_u8 == 1) // 0-FV, 1-LED, 2-COLOR
    {
        gDesiredLedState_s32 = *(uint8_t *)pValue;
        print_info("Delta update desired Led : %d", gDesiredLedState_s32);
    }
    else if(elementIndex_u8 == 2) // 0-FV, 1-LED, 2-COLOR
    {
        if ((strcmp((char *)pValue, "WHITE") == 0) ||
            (strcmp((char *)pValue, "RED") == 0) ||
            (strcmp((char *)pValue, "GREEN") == 0) ||
            (strcmp((char *)pValue, "BLUE") == 0))
        {
            strcpy(gDesiredColorStr, (char *)pValue);
            print_info("gDesiredColorStr:%s gReportedColorStr:%s", gDesiredColorStr, gReportedColorStr);
        }
    }
}


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
    case EVENT_WIFI_CONNECTED:
        print_info("EVENT_WIFI_CONNECTED");
        break;
    case EVENT_WIFI_DISCONNECTED:
        print_info("EVENT_WIFI_DISCONNECTED");
        break;

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


jobsStatus_et app_jobHandlerLed(const job_st *ps_job)
{
    print_verbose("%s : %s", ps_job->idStr, ps_job->documentStr);

    // copy gJobIdStr & gJobDocumentStr
    strcpy(gJobIdStr, ps_job->idStr);
    strcpy(gJobDocumentStr, ps_job->documentStr);

    // handle the operation in application task
    gJobReceived_b8 = true;

    return JOB_STATUS_IN_PROGRESS;
}

void app_jobCheck()
{
    // job received? perform operation
    if (gJobReceived_b8)
    {
        gJobReceived_b8 = FALSE;

        uint32_t countValue_u32 = 0;
        uint32_t onTime_u32 = 0;
        uint32_t offTime_u32 = 0;
        char countStr[4] = {0};
        char onTimeStr[4] = {0};
        char offTimeStr[4] = {0};

        // variable for extracting json key-value pair
        tagStructure_st jobKeyValuePair[3] = {
            {"count", countStr},
            {"onTime", onTimeStr},
            {"offTime", offTimeStr}};

        // parse job document to initialize count value
        if (JSON_processString(gJobDocumentStr, jobKeyValuePair, 3, FALSE))
        {
            countValue_u32 = util_getNumFromStringU32(countStr);
            onTime_u32 = util_getNumFromStringU32(onTimeStr);
            offTime_u32 = util_getNumFromStringU32(offTimeStr);

            print_verbose("blink %d times => ON:%dms OFF:%dms", countValue_u32, onTime_u32, offTime_u32);
            if (countValue_u32 <= MAX_LED_BLINK_COUNT)
            {
                // blink 3 times
                for (uint32_t i = 0; i < countValue_u32; i++)
                {
                    if (onTime_u32)
                    {
                    	app_updateLedState(HIGH);
                        TASK_DELAY_MS(onTime_u32);
                    }
                    if (offTime_u32)
                    {
                    	app_updateLedState(LOW);
                        TASK_DELAY_MS(offTime_u32);
                    }
                }

                JOBS_updateStatus(gJobIdStr, JOB_STATUS_SUCCESSED);
            }
            else
            {
                print_error("Error: blink count %d is greater than allowed blinks (%d)", countValue_u32, MAX_LED_BLINK_COUNT);
                JOBS_updateStatus(gJobIdStr, JOB_STATUS_FAILED);
            }
        }
        else
        {
            print_error("Error: Invalid job document: %s", gJobDocumentStr);
        }
    }
}


void sys_init()
{
	/* USER CODE BEGIN systemTask */
		systemInitConfig_st s_sysConfig = {
				.systemEventCallbackHandler = app_eventsCallBackHandler,
				.pAppVersionStr = APP_VERSION,
				.pDebugUarthandle = &huart2, //Tx:PA2  Rx:PA3
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

		        .s_mqttClientConfig = {
		        	 .pThingNameStr = THING_NAME,
		        	 .pHostNameStr = AWS_IOT_MQTT_HOST,
		        	 .port_u16 = AWS_IOT_MQTT_PORT,
		             .maxPubMsgToStore_u8 = 6,
		             .maxSubMsgToStore_u8 = 4,
		             .maxSubscribeTopics_u8 = 4,
		             .maxJobs_u8 = 4,
		             .pRootCaStr = AWS_CA_CERT,
					 .pThingCertStr = AWS_CLIENT_CERT,
					 .pThingPrivateKeyStr = AWS_PRIVATE_KEY,
				}


		};
	    if(SYSTEM_init(&s_sysConfig))
	    {
	        if (SYSTEM_getMode() == SYSTEM_MODE_NORMAL)
	        {
	            SHADOW_register(shadowTable, MAX_TYPES_OF_SHADOWS);
	            if (JOBS_register("blink", 0, app_jobHandlerLed))
	            {
	            	print_verbose("blink job reg success");
	            }
	            else
	            {
	            	print_verbose("blink job reg failed");
	            }
	        }
	    }
}



void app_main()
{
    static uint8_t publishCount = 0;
    static uint32_t nextUpdateTime_u32 = 0;
    static uint8_t led = 0;

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
	            if (AWS_isConnected())
	            {
	            	app_jobCheck();

	                if (gDesiredLedState_s32 != gReportedLedState_s32)
	                {
	                    gReportedLedState_s32 = gDesiredLedState_s32;
	                    app_updateLedState(gDesiredLedState_s32);
	                    print_info("gDesiredLedState_s32:%d gReportedLedState_s32:%d", gDesiredLedState_s32, gReportedLedState_s32);
	                    SHADOW_update(CLASSIC_SHADOW,STR_SHADOW_KEY_LED, &gReportedLedState_s32, SHADOW_UPDATE_TYPE_REPORTED);
	                }
	                else if (strcmp(gDesiredColorStr, gReportedColorStr) != 0)
	                {
	                    strcpy(gReportedColorStr, gDesiredColorStr);
	                    print_info("gDesiredColorStr:%s gReportedColorStr:%s", gDesiredColorStr, gReportedColorStr);
	                    SHADOW_update(CLASSIC_SHADOW,STR_SHADOW_KEY_COLOR, gReportedColorStr, SHADOW_UPDATE_TYPE_REPORTED);
	                }

	                if (millis() > nextUpdateTime_u32)
	                {
	                    nextUpdateTime_u32 = millis() + 10000;

	                    if (publishCount < 5)
	                    {
	                        pubMsg.payloadLen_u16 = sprintf(pubMsg.payloadStr, "Hello World %03d", publishCount++);
	                        pubMsg.topicLen_u8 = sprintf(pubMsg.topicStr, PUBLISH_TOPIC_STR);
	                        print_info("%s", pubMsg.payloadStr);
	                        AWS_publish(&pubMsg);
	                    }
	                }

	                if (AWS_subMsgAvailable())
	                {
	                    if (AWS_subMsgRead(&subMsg))
	                    {
	                        print_info("\n\r[SUB Message]  topic:%s  payload:%s", subMsg.topicStr, subMsg.payloadStr);
	                    }
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



