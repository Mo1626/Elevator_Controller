/*

 * Buzz_prog.c
 *
 *  Created on: Jul 23, 2026
 *      Author: Dell
 */

/*
 * Buzz_prog.c
 *
 *  Created on: Jul 23, 2026
 *      Author: Dell
 */

#include "../../MCAL/ADC/primitiveTypes.h"
#include "../../MCAL/DIO/DIO_int.h"
#include <util/delay.h>

#include "Buzz_config.h"
#include "Buzz_int.h"
#include "Buzz_priv.h"

void Buzzer_vidInit(void)
{
    DIO_vidSetPinMode(BUZZER_PIN, MODE_OUTPUT_LOW);
}

void Buzzer_vidKeyClick(void) // 50 ms
{
    DIO_vidSetPinValue(BUZZER_PIN, HIGH);
    _delay_ms(50);
    DIO_vidSetPinValue(BUZZER_PIN, LOW);
}

void Buzzer_vidErrorKey(void) // 80 ms
{
    DIO_vidSetPinValue(BUZZER_PIN, HIGH);
    _delay_ms(80);
    DIO_vidSetPinValue(BUZZER_PIN, LOW);
}

void Buzzer_vidArrivalChime(void)
{
    DIO_vidSetPinValue(BUZZER_PIN, HIGH);
    _delay_ms(150);
    DIO_vidSetPinValue(BUZZER_PIN, LOW);
    _delay_ms(150);
    DIO_vidSetPinValue(BUZZER_PIN, HIGH);
    _delay_ms(150);
    DIO_vidSetPinValue(BUZZER_PIN, LOW);
}

void Buzzer_vidOverload(void) // 250ms ON / 250ms OFF
{
    DIO_vidSetPinValue(BUZZER_PIN, HIGH);
    _delay_ms(250);
    DIO_vidSetPinValue(BUZZER_PIN, LOW);
    _delay_ms(250);
}

void Buzzer_vidEstop(void) // 300
{
    DIO_vidSetPinValue(BUZZER_PIN, HIGH);
    _delay_ms(300);
    DIO_vidSetPinValue(BUZZER_PIN, LOW);
}
