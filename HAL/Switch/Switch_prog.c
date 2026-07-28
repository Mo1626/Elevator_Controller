/*

 * Switch_prog.c
 *
 *  Created on: Jul 23, 2026
 *      Author: Dell
 */

#include "../../MCAL/ADC/primitiveTypes.h"
#include <util/delay.h>
#include "../../MCAL/DIO/DIO_int.h"
#include "Switch_config.h"
#include "Switch_priv.h"
#include "Switch_int.h"

// تعريف أطراف أزرار الأدوار (Hall Buttons 1 to 4)
#define HALL_BTN_1    PA0
#define HALL_BTN_2    PA1
#define HALL_BTN_3    PA2
#define HALL_BTN_4    PA3

void Switch_vidInit(void) {
    DIO_vidSetPinMode(HALL_BTN_1, MODE_INPUT_PULLUP);
    DIO_vidSetPinMode(HALL_BTN_2, MODE_INPUT_PULLUP);
    DIO_vidSetPinMode(HALL_BTN_3, MODE_INPUT_PULLUP);
    DIO_vidSetPinMode(HALL_BTN_4, MODE_INPUT_PULLUP);
}

u8 Switch_u8GetHallCall(u8 u8FloorNumber) {
    u8 u8Pressed = FALSE;
    u8 u8Pin = 0xFF;

    switch(u8FloorNumber) {
        case 1: u8Pin = HALL_BTN_1; break;
        case 2: u8Pin = HALL_BTN_2; break;
        case 3: u8Pin = HALL_BTN_3; break;
        case 4: u8Pin = HALL_BTN_4; break;
        default: return FALSE;
    }

    if(DIO_enuGetPinValue(u8Pin) == LOW) {
        _delay_ms(50); // Debounce time (50 ms) طبقًا للـ SRS
        if(DIO_enuGetPinValue(u8Pin) == LOW) {
            u8Pressed = TRUE;
            // الانتظار لحين ترك الزرار لمنع التكرار المزعج
            while(DIO_enuGetPinValue(u8Pin) == LOW);
        }
    }

    return u8Pressed;
}
