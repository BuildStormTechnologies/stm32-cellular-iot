/**
* \copyright Copyright (c) 2019-2024, Buildstorm Pvt Ltd
*
* \file lib_utils.h
* \brief Utils library header file.
*
*
* The  Utils library handles the utilities for data extraction and hex dumps.
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

#ifndef _STD_UTIL_H_
#define _STD_UTIL_H_

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"

/**********************************************************************************************
                      LOGIC level
*********************************************************************************************/
#ifndef HIGH
#define LOW 0x00u
#define HIGH 0x01u
#endif
/***************************************************************************************/

/**********************************************************************************************
                      Commonly used constants
********************************************************************************************/

#ifndef NULL
#define NULL 0u
#endif

#ifndef TRUE
#define TRUE 1u
#endif

#ifndef true
#define true 1u
#endif

#ifndef FALSE
#define FALSE 0u
#endif

#ifndef false
#define false 0u
#endif

/***************************************************************************************/

/**********************************************************************************************
                    Standard Enumerations and Constants
*********************************************************************************************/

typedef enum
{
    STS_SUCCESS,
    STS_BUSY,
    STS_FAILED,
    STS_TIMEOUT
} status_et;

/**----------char 8-bit--------
     char (-128 to 127)
     signed char (-128 to 127)
     unsigned char (0 - 255)
	-----------------------------*/

/**---------int 16-bit----------
	 int (-32768 to 32767)
	 signed int (-32768 to 32767)
     unsigned int (0 to 65535)
	 -----------------------------*/

typedef signed char sint8_t;
typedef unsigned char uint8_t;

typedef signed int sint16_t;
//typedef unsigned int    uint16_t;

typedef signed long int sint32_t;
typedef unsigned long int uint32_t;

#define C_SINT8_MAX 0x7F
#define C_SINT8_MIN -128

#define C_UINT8_MAX 0xFFu
#define C_UINT8_MIN 0x00u

#define C_SINT16_MAX 32767
#define C_SINT16_MIN -32768

#define C_UINT16_MAX 0xFFFFu
#define C_UINT16_MIN 0x00u

#define C_SINT32_MAX 2147483647
#define C_SINT32_MIN -2147483648

#define C_UINT32_MAX 0xFFFFFFFFu
#define C_UINT32_MIN 0x00u

/***************************************************************************************/

/**********************************************************************************************
                    Macros for Bit Manipulation
**********************************************************************************************/
#define util_GetBitMask(bit) (1 << (bit))
#define util_BitSet(x, bit) ((x) |= util_GetBitMask(bit))
#define util_BitClear(x, bit) ((x) &= ~util_GetBitMask(bit))
#define util_BitToggle(x, bit) ((x) ^= util_GetBitMask(bit))
#define util_UpdateBit(x, bit, val) ((val) ? util_BitSet(x, bit) : util_BitClear(x, bit))

#define util_GetBitStatus(x, bit) (((x) & (util_GetBitMask(bit))) != 0u)
#define util_IsBitSet(x, bit) (((x) & (util_GetBitMask(bit))) != 0u)
#define util_IsBitCleared(x, bit) (((x) & (util_GetBitMask(bit))) == 0u)

#define util_AreAllBitsSet(x, BitMask) (((x) & (BitMask)) == BitMask)
#define util_AreAnyBitsSet(x, BitMask) (((x) & (BitMask)) != 0x00u)
/***************************************************************************************/

/**********************************************************************************************
                    Macros to find the mod of a number
*********************************************************************************************/
#define util_GetMod8(dividend, divisor) (uint8_t)(dividend - (divisor * (uint8_t)(dividend / divisor)))
#define util_GetMod16(dividend, divisor) (uint16_t)(dividend - (divisor * (uint16_t)(dividend / divisor)))
#define util_GetMod32(dividend, divisor) (uint32_t)(dividend - (divisor * (uint32_t)(dividend / divisor)))
/****************************************************************************************/

/**********************************************************************************************
                    Macros for Dec2Ascii,Hec2Ascii and Acsii2Hex conversion
**********************************************************************************************/
#define util_Dec2Ascii(Dec) ((Dec) + 0x30)
#define util_Ascii2Dec(Asc) ((Asc)-0x30)
#define util_Hex2Ascii(Hex) (((Hex) > 0x09) ? ((Hex) + 0x37) : ((Hex) + 0x30))
#define util_Ascii2Hex(Asc) (((Asc) > 0x39) ? ((Asc)-0x37) : ((Asc)-0x30))
#define util_IsUpperCase(Asc) (((Asc) >= 'A') && ((Asc) <= 'Z'))
#define util_IsLowerCase(Asc) (((Asc) >= 'a') && ((Asc) <= 'z'))
#define util_toLower(Asc) (util_IsUpperCase(Asc) ? ((Asc) + 0x20) : (Asc))
#define util_toUpper(Asc) (util_IsLowerCase(Asc) ? ((Asc)-0x20) : (Asc))
/***************************************************************************************************/

/**********************************************************************************************
                    Macros to extract the Nibbles
*********************************************************************************************/
#define util_ExtractBits0to4(x) (uint8_t)((x) & 0x0Fu)
#define util_ExtractBits4to8(x) (uint8_t)(((x) >> 4) & 0x0Fu)
#define util_ExtractBits8to12(x) (uint8_t)(((x) >> 8) & 0x0Fu)
#define util_ExtractBits12to16(x) (uint8_t)(((x) >> 12) & 0x0Fu)
/***************************************************************************************/

/**********************************************************************************************
                    Macros to extract the Byte
*********************************************************************************************/
#define util_ExtractBits0to8(x) (uint8_t)((x) & 0xFFu)
#define util_ExtractBits8to16(x) (uint8_t)(((x) >> 8) & 0xFFu)
#define util_ExtractBits16to24(x) (uint8_t)(((x) >> 16) & 0xFFu)
#define util_ExtractBits24to32(x) (uint8_t)(((x) >> 24) & 0xFFu)
/***************************************************************************************/

/**********************************************************************************************
                    Other Macros
*********************************************************************************************/
#define util_GetMax(num1, num2) (((num1) > (num2)) ? (num1) : (num2))
#define util_GetMin(num1, num2) (((num1) < (num2)) ? (num1) : (num2))

#define util_swap(x, y) (x ^= y ^= x ^= y)
#define util_GetAbsolute(x) (((x) < 0) ? -(x) : (x))
#define util_IsAsciiInt(Asc) (((Asc) >= '0') && ((Asc) <= '9'))
#define util_IsAsciiHex(Asc) ((util_IsAsciiInt(Asc)) ||             \
                              (((Asc) >= 'A') && ((Asc) <= 'F')) || \
                              (((Asc) >= 'a') && ((Asc) <= 'f')))

#define util_ShiftToRight(x, c) ((x) >> c)
#define util_ShiftToLeft(x, c) ((x) << c)
#define util_ShiftNibbleToRight(x) ((x) >> 4)
#define util_ShiftNibbleToLeft(x) ((x) << 4)
#define util_ShiftBytesToRight(x, c) ((x) >> (8 * (c)))
#define util_ShiftBytesToLeft(x, c) ((x) << (8 * (c)))

#define util_SecToMs(x) ((x) * 1000)

#define TIMEOUT_US(us) (us)
#define TIMEOUT_MS(ms) (ms)
#define TIMEOUT_SEC(sec) (sec)
#define TIMEOUT_MIN(min) (min)

#define util_generateEnum(ENUM) ENUM,
#define util_generateString(STRING) #STRING,
/***************************************************************************************/

uint32_t util_getNumFromStringU32(const char *pStr);
int32_t util_getNumFromStringI32(const char *pStr);
bool util_isValidString(const char *pStr);
void util_hexDump(uint8_t *buffPtr, uint16_t dumpSize, uint8_t charsPerLine, bool asciiEnable);
float util_getFloatFromString(const char *pStr, uint8_t decPoints);

uint32_t util_b64Encode(const uint8_t *in, uint32_t in_len, uint8_t *out);
uint32_t util_getCrc32OnFly(bool startFlag_b8, uint8_t data_u8);
uint32_t util_getCrc32(uint8_t *pData, uint32_t dataLen);
#endif
