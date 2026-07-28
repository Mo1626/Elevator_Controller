/*
 * DIO_prog.c
 *
 *  Created on: Jul 18, 2026
 *      Author: Ahmed El-Gaafrawy
 */

// public libraries [primitive, error, math, stdlib, ......]
#include "../ADC/primitiveTypes.h"

// include lower layers libraries


//my own libraries 
#include "DIO_priv.h"
#include "DIO_int.h"


void DIO_vidSetPinMode (enuPinNum_t enuPinNum , enuPinMode_t enuPinMode)
{
    if (enuPinMode <= MODE_OUTPUT_HIGH)
    { 
        u8 u8DdrReg  = ((enuPinMode >> 1U) & 1U);
        u8 u8PortReg = ((enuPinMode >> 0U) & 1U);
        u8 u8ActualPin = (enuPinNum % 8U);

        if ((enuPinNum >= PA0) && (enuPinNum <= PA7))
        {
            // registers PORTA or DDRA or PINA
            DDRA &= ~(1<<u8ActualPin);
            DDRA |= (u8DdrReg << u8ActualPin);
            
            PORTA &= ~(1<<u8ActualPin);
            PORTA |= (u8PortReg << u8ActualPin);
        }
        else if ((enuPinNum >= PB0) && (enuPinNum <= PB7))
        {
            // registers PORTC or DDRB or PINB
            DDRB &= ~(1<<u8ActualPin);
            DDRB |= (u8DdrReg << u8ActualPin);
            
            PORTB &= ~(1<<u8ActualPin);
            PORTB |= (u8PortReg << u8ActualPin);
        }
        else if ((enuPinNum >= PC0) && (enuPinNum <= PC7))
        {
            // registers PORTC or DDRC or PINC
            DDRC &= ~(1<<u8ActualPin);
            DDRC |= (u8DdrReg << u8ActualPin);
            
            PORTC &= ~(1<<u8ActualPin);
            PORTC |= (u8PortReg << u8ActualPin);
        }
        else if ((enuPinNum >= PD0) && (enuPinNum <= PD7))
        {
            // registers PORTD or DDRD or PIND
            DDRD &= ~(1<<u8ActualPin);
            DDRD |= (u8DdrReg << u8ActualPin);
            
            PORTD &= ~(1<<u8ActualPin);
            PORTD |= (u8PortReg << u8ActualPin);
        }
        else
        {
            // unexpected behaviour
        }
    }
}


void DIO_vidSetPinValue (enuPinNum_t enuPinNum , enuPinValue_t enuPinValue)
{
    if (enuPinValue <= HIGH)
    {
        u8 u8ActualPin = (enuPinNum % 8U);

        if ((enuPinNum >= PA0) && (enuPinNum <= PA7))
        {
            // registers PORTA or DDRA or PINA
            if (enuPinValue == HIGH)
                PORTA |= (1<<u8ActualPin);
            else
                PORTA &=~(1<<u8ActualPin);
        }
        else if ((enuPinNum >= PB0) && (enuPinNum <= PB7))
        {
            // registers PORTB or DDRB or PINB
            PORTB = (enuPinValue == HIGH)? (PORTB | (1<<u8ActualPin))  :  (PORTB & (~(1<<u8ActualPin)));
        }
        else if ((enuPinNum >= PC0) && (enuPinNum <= PC7))
        {
            // registers PORTC or DDRC or PINC
            PORTC = (enuPinValue == HIGH)? (PORTC | (1<<u8ActualPin))  :  (PORTC & (~(1<<u8ActualPin)));
        }
        else if ((enuPinNum >= PD0) && (enuPinNum <= PD7))
        {
            // registers PORTD or DDRD or PIND
            if (enuPinValue == HIGH)
                PORTD |= (1<<u8ActualPin);
            else
                PORTD &=~(1<<u8ActualPin);
        }
        else
        {
            // unexpected behaviour
        }
    }
}

void DIO_vidTogglePinValue (enuPinNum_t enuPinNum)
{
    u8 u8ActualPin = (enuPinNum % 8U);
    if ((enuPinNum >= PA0) && (enuPinNum <= PA7))
    {
        // registers PORTA or DDRA or PINA
        PORTA ^= (1<<u8ActualPin);
    }
    else if ((enuPinNum >= PB0) && (enuPinNum <= PB7))
    {
        // registers PORTB or DDRB or PINB
        PORTB ^= (1<<u8ActualPin);
    }
    else if ((enuPinNum >= PC0) && (enuPinNum <= PC7))
    {
        // registers PORTC or DDRC or PINC
        PORTC ^= (1<<u8ActualPin);
    }
    else if ((enuPinNum >= PD0) && (enuPinNum <= PD7))
    {
        // registers PORTD or DDRD or PIND
        PORTD ^= (1<<u8ActualPin);
    }
    else
    {
        // unexpected behaviour
    }
}

enuPinValue_t DIO_enuGetPinValue (enuPinNum_t enuPinNum)
{
    enuPinValue_t enuPinValue = INVALID;
    u8 u8ActualPin = (enuPinNum % 8U);

    if ((enuPinNum >= PA0) && (enuPinNum <= PA7))
    {
        // registers PORTA or DDRA or PINA
        enuPinValue = ((PINA >> u8ActualPin) & 1);
    }
    else if ((enuPinNum >= PB0) && (enuPinNum <= PB7))
    {
        // registers PORTB or DDRB or PINB
        enuPinValue = ((PINB >> u8ActualPin) & 1);
    }
    else if ((enuPinNum >= PC0) && (enuPinNum <= PC7))
    {
        // registers PORTC or DDRC or PINC
        enuPinValue = ((PINC >> u8ActualPin) & 1);
    }
    else if ((enuPinNum >= PD0) && (enuPinNum <= PD7))
    {
        // registers PORTD or DDRD or PIND
        enuPinValue = ((PIND >> u8ActualPin) & 1);
    }
    else
    {
        // unexpected behaviour
    }
    return enuPinValue;
}
