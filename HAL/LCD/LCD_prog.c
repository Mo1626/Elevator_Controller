/*
 * LCD_prog.c
 *
 *  Created on: Jul 23, 2026
 *      Author: Dell
 */

// public libraries [primitive, error, math, stdlib, ......]
#include "../../MCAL/ADC/primitiveTypes.h"
#include "../../MCAL/TIMER0/TIMER0_int.h"

#include "../../MCAL/DIO/DIO_int.h"
#include "LCD_config.h"
#include "LCD_priv.h"
#include "LCD_int.h"

static void vidWriteNLatch(u8 u8Byte)
{
    DIO_vidSetPinValue(LCD_D0_PIN, (u8Byte >> 0) & 0x01);
    DIO_vidSetPinValue(LCD_D1_PIN, (u8Byte >> 1) & 0x01);
    DIO_vidSetPinValue(LCD_D2_PIN, (u8Byte >> 2) & 0x01);
    DIO_vidSetPinValue(LCD_D3_PIN, (u8Byte >> 3) & 0x01);
    DIO_vidSetPinValue(LCD_D4_PIN, (u8Byte >> 4) & 0x01);
    DIO_vidSetPinValue(LCD_D5_PIN, (u8Byte >> 5) & 0x01);
    DIO_vidSetPinValue(LCD_D6_PIN, (u8Byte >> 6) & 0x01);
    DIO_vidSetPinValue(LCD_D7_PIN, (u8Byte >> 7) & 0x01);

    DIO_vidSetPinValue(LCD_EN_PIN, HIGH);
    DIO_vidSetPinValue(LCD_EN_PIN, LOW);
}

void LCD_vidSendCommand(u8 u8Command)
{
    DIO_vidSetPinValue(LCD_RS_PIN, LOW);
    DIO_vidSetPinValue(LCD_RW_PIN, LOW);
    vidWriteNLatch(u8Command);
}

void LCD_vidSendData(u8 u8Data)
{
    DIO_vidSetPinValue(LCD_RS_PIN, HIGH);
    DIO_vidSetPinValue(LCD_RW_PIN, LOW);
    vidWriteNLatch(u8Data);
}

void LCD_vidInit(void)
{
    DIO_vidSetPinMode(LCD_RS_PIN, MODE_OUTPUT_HIGH);
    DIO_vidSetPinMode(LCD_RW_PIN, MODE_OUTPUT_HIGH);
    DIO_vidSetPinMode(LCD_EN_PIN, MODE_OUTPUT_HIGH);

    DIO_vidSetPinMode(LCD_D0_PIN, MODE_OUTPUT_HIGH);
    DIO_vidSetPinMode(LCD_D1_PIN, MODE_OUTPUT_HIGH);
    DIO_vidSetPinMode(LCD_D2_PIN, MODE_OUTPUT_HIGH);
    DIO_vidSetPinMode(LCD_D3_PIN, MODE_OUTPUT_HIGH);
    DIO_vidSetPinMode(LCD_D4_PIN, MODE_OUTPUT_HIGH);
    DIO_vidSetPinMode(LCD_D5_PIN, MODE_OUTPUT_HIGH);
    DIO_vidSetPinMode(LCD_D6_PIN, MODE_OUTPUT_HIGH);
    DIO_vidSetPinMode(LCD_D7_PIN, MODE_OUTPUT_HIGH);

#if LCD_MODE == LCD_8_BIT
    LCD_vidSendCommand(LCD_EIGHT_BIT_FUNCTION_SET);
#endif

    LCD_vidSendCommand(LCD_DISPLAY_ON_OFF);
    LCD_vidSendCommand(LCD_CLEAR_DISPLAY);
    LCD_vidSendCommand(LCD_ENTRY_MODE_SET);
}

void LCD_vidSendString(const char* pcString)
{
    u8 u8Index = 0;
    while (pcString[u8Index] != '\0')
    {
        LCD_vidSendData(pcString[u8Index]);
        u8Index++;
    }
}

void LCD_vidSetPositionXY(u8 u8X, u8 u8Y)
{
    u8 u8Address = 0;

    if (u8X == 0)
    {
        u8Address = 0x80 + u8Y;
    }
    else if (u8X == 1)
    {
        u8Address = 0xC0 + u8Y;
    }

    LCD_vidSendCommand(u8Address);
}

void LCD_vidSendIntegarNumber(s32 s32Number)
{
    char szBuffer[16];
    char *pStr = &szBuffer[15];
    *pStr = '\0';

    int bIsNegative = 0;
    if (s32Number < 0)
    {
        bIsNegative = 1;
        s32Number = -s32Number;
    }

    if (s32Number == 0)
    {
        *--pStr = '0';
    }
    else
    {
        while (s32Number > 0)
        {
            *--pStr = '0' + (s32Number % 10);
            s32Number /= 10;
        }
    }

    if (bIsNegative)
    {
        *--pStr = '-';
    }

    LCD_vidSendString(pStr);
}

void LCD_vidSendFloatNumber(float fNumber)
{
    s32 s32IntegerPart = (s32)fNumber;
    LCD_vidSendIntegarNumber(s32IntegerPart);

    LCD_vidSendData('.');

    float fFractionalPart = fNumber - (float)s32IntegerPart;
    if (fFractionalPart < 0)
    {
        fFractionalPart = -fFractionalPart;
    }
    s32 s32FractionalScaled = (s32)(fFractionalPart * 100.0f);

    if (s32FractionalScaled < 10)
    {
        LCD_vidSendData('0');
    }
    LCD_vidSendIntegarNumber(s32FractionalScaled);
}

void LCD_vidSendPattern(u8 *pu8Patterns, u8 u8PatternCount, u8 u8X, u8 u8Y, u8 u8DisplayDirection)
{
    u8 u8LoopCounter, u8ByteIdx;

    for (u8LoopCounter = 0; u8LoopCounter < u8PatternCount; u8LoopCounter++)
    {
        LCD_vidSendCommand(PATTERN0 + (u8LoopCounter * 8));
        for (u8ByteIdx = 0; u8ByteIdx < 8; u8ByteIdx++)
        {
            LCD_vidSendData(pu8Patterns[(u8LoopCounter * 8) + u8ByteIdx]);
        }
    }

    LCD_vidSetPositionXY(u8X, u8Y);
    for (u8LoopCounter = 0; u8LoopCounter < u8PatternCount; u8LoopCounter++)
    {
        LCD_vidSendData(u8LoopCounter);
    }

    (void)u8DisplayDirection;
}
