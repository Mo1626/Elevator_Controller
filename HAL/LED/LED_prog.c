/*

 * LED_prog.c
 *
 *  Created on: Jul 24, 2026
 *      Author: Dell
 */

#include "../../MCAL/ADC/primitiveTypes.h"
#include "../../MCAL/DIO/DIO_int.h"
#include "LED_config.h"
#include "LED_priv.h"
#include "LED_int.h"

void LED_voidInit(void)
{
    // تهيئة أطراف ليدات الطوابق كـ Output Low في البداية
    DIO_vidSetPinMode(LED_F1_PIN, MODE_OUTPUT_LOW);
    DIO_vidSetPinMode(LED_F2_PIN, MODE_OUTPUT_LOW);
    DIO_vidSetPinMode(LED_F3_PIN, MODE_OUTPUT_LOW);
    DIO_vidSetPinMode(LED_F4_PIN, MODE_OUTPUT_LOW);
}

void LED_voidOn(u8 u8LedId)
{
    switch(u8LedId)
    {
        case LED_F1:
            DIO_vidSetPinValue(LED_F1_PIN, HIGH);
            break;
        case LED_F2:
            DIO_vidSetPinValue(LED_F2_PIN, HIGH);
            break;
        case LED_F3:
            DIO_vidSetPinValue(LED_F3_PIN, HIGH);
            break;
        case LED_F4:
            DIO_vidSetPinValue(LED_F4_PIN, HIGH);
            break;
    }
}

void LED_voidOff(u8 u8LedId)
{
    switch(u8LedId)
    {
        case LED_F1:
            DIO_vidSetPinValue(LED_F1_PIN, LOW);
            break;
        case LED_F2:
            DIO_vidSetPinValue(LED_F2_PIN, LOW);
            break;
        case LED_F3:
            DIO_vidSetPinValue(LED_F3_PIN, LOW);
            break;
        case LED_F4:
            DIO_vidSetPinValue(LED_F4_PIN, LOW);
            break;
    }
}

void LED_voidToggle(u8 u8LedId)
{
    switch(u8LedId)
    {
        case LED_F1:
            if(DIO_enuGetPinValue(LED_F1_PIN) == HIGH) {
                DIO_vidSetPinValue(LED_F1_PIN, LOW);
            } else {
                DIO_vidSetPinValue(LED_F1_PIN, HIGH);
            }
            break;

        case LED_F2:
            if(DIO_enuGetPinValue(LED_F2_PIN) == HIGH) {
                DIO_vidSetPinValue(LED_F2_PIN, LOW);
            } else {
                DIO_vidSetPinValue(LED_F2_PIN, HIGH);
            }
            break;

        case LED_F3:
            if(DIO_enuGetPinValue(LED_F3_PIN) == HIGH) {
                DIO_vidSetPinValue(LED_F3_PIN, LOW);
            } else {
                DIO_vidSetPinValue(LED_F3_PIN, HIGH);
            }
            break;

        case LED_F4:
            if(DIO_enuGetPinValue(LED_F4_PIN) == HIGH) {
                DIO_vidSetPinValue(LED_F4_PIN, LOW);
            } else {
                DIO_vidSetPinValue(LED_F4_PIN, HIGH);
            }
            break;
    }
}
