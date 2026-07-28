/*
 * ADC_prog.c
 *
 *  Created on: Jul 22, 2026
 *      Author: Ahmed El-Gaafrawy
 */

// public libraries [primitive, error, math, stdlib, ......]
#include "primitiveTypes.h"

// include lower layers libraries

//my own libraries 
#include "ADC_config.h"
#include "ADC_int.h"
#include "ADC_priv.h"

static void(*LOC_pfunIsrCallback)(void) = NULL;

void ADC_vidSelectChannel(u8 u8AdcChannel)
{
    if(u8AdcChannel <= 31)
    {
        ADMUX &= 0xE0;          
        ADMUX |= u8AdcChannel;  
    }
}

void ADC_vidInit(void)
{
    ADMUX = 0;
    ADMUX |= (ADC_REFERENCE_VOLT << 6);
    ADMUX |= (ADC_ADJUSTMENT << 5);
    ADMUX |= ADC_INIT_CHANNEL;
    ADCSRA = 0;
    ADCSRA |= (1 << 7);
    ADCSRA |= ADC_PRESCALER;
}

u16 ADC_u8GetLoadPercentage(u8 Channel)
{
    ADC_vidSelectChannel(Channel);

    /* Start Conversion */
    ADCSRA |= (1 << 6);

    /* Wait until conversion is complete */
    while(((ADCSRA >> 4) & 1) == 0);

    /* Clear ADIF flag */
    ADCSRA |= (1 << 4);

    /* Return the ADC reading */
    return ADC_u16GetRead();
}

u8 ADC_u8GetHighRead(void)
{
    return ADCH;
}

u16 ADC_u16GetRead(void)
{
    u16 u16Read;

    u16Read = ADCL;
    u16Read |= ((u16)ADCH << 8);

    return u16Read;
}

void ADC_vidSelectAutoTrigger(u8 u8TriggerSource)
{
    if(u8TriggerSource <= 7)
    {
        SFIOR &= 0x1F;                    
        SFIOR |= (u8TriggerSource << 5);  
    }
}

void ADC_vidEnable(void)
{
    ADCSRA |= (1<<7);
}

void ADC_vidDisable(void)
{
    ADCSRA &= ~(1<<7);
}

void ADC_vidEnableInterrupt(void)
{
    ADCSRA |= (1<<3);
}

void ADC_vidDisableInterrupt(void)
{
    ADCSRA &=~ (1<<3);
}

void ADC_vidSetCallback(void (*pfunAppFunction)(void))
{
    if(pfunAppFunction != NULL)
    {
        LOC_pfunIsrCallback = pfunAppFunction;
    }
}


void __vector_16 (void)__attribute__((signal));
void __vector_16 (void)
{
    if (LOC_pfunIsrCallback != NULL)
    {
        LOC_pfunIsrCallback ();
    }
}
