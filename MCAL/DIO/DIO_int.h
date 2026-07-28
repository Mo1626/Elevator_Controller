/*
 * DIO_int.h
 *
 *  Created on: Jul 18, 2026
 *      Author: Ahmed El-Gaafrawy
 */

#ifndef DIO_INT_H_
#define DIO_INT_H_
#define EMERGENCY_PIN DIO_PIN_D5
typedef enum{
    PA0,    PA1,    PA2,    PA3,    PA4,    PA5,    PA6,    PA7,
    PB0,    PB1,    PB2,    PB3,    PB4,    PB5,    PB6,    PB7,
    PC0,    PC1,    PC2,    PC3,    PC4,    PC5,    PC6,    PC7,
    PD0,    PD1,    PD2,    PD3,    PD4,    PD5,    PD6,    PD7,
} enuPinNum_t;

typedef enum
{
    // bit0 == port register , bit1 == ddr register
    MODE_INPUT_FLOAT  = 0b00,
    MODE_INPUT_PULLUP = 0b01,
    MODE_OUTPUT_LOW   = 0b10,
    MODE_OUTPUT_HIGH  = 0b11,
} enuPinMode_t;

typedef enum
{
    LOW,
    HIGH,
    INVALID = 0xFF,
}enuPinValue_t;

void DIO_vidSetPinMode (enuPinNum_t enuPinNum , enuPinMode_t enuPinMode); // init function

void DIO_vidSetPinValue (enuPinNum_t enuPinNum , enuPinValue_t enuPinValue); // periodic function

void DIO_vidTogglePinValue (enuPinNum_t enuPinNum); // periodic function

enuPinValue_t DIO_enuGetPinValue (enuPinNum_t enuPinNum); // periodic function


#endif /* DIO_INT_H_ */
