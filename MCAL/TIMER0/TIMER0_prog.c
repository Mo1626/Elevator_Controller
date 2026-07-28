/*
 * TIMER0_prog.c
 * Created on: Jul 23, 2026
 * Author: Ahmed El-Gaafrawy
 */

#include "../ADC/primitiveTypes.h"
#include "TIMER0_int.h"

#define TCCR0               *((volatile u8*)0x53)
#define TCNT0               *((volatile u8*)0x52)
#define OCR0                *((volatile u8*)0x5C)
#define TIMSK               *((volatile u8*)0x59)
#define TIFR                *((volatile u8*)0x58)

#define TIMER0_OVERFLOW_COUNT       (256UL)

static void(*LOC_pfunIsrFunction)(void) = NULL;

void TIMER0_vidInit(void)
{
    // Normal mode, prescaler = 64
    TCCR0 = 0x03;
    // Enable Overflow Interrupt
    TIMSK |= (1 << 0);
}

void TIMER0_vidSetCallBack(void (*pfunAppFunction)(void))
{
    if (pfunAppFunction != NULL)
    {
        LOC_pfunIsrFunction = pfunAppFunction;
    }
}

void TIMER0_vidDelayMs(u32 u32MilliSecond)
{
    u32 u32Counts = (u32MilliSecond * (F_CPU/1000UL)) / 64UL;
    u32 u32NumOvf = (u32Counts + (TIMER0_OVERFLOW_COUNT - 1)) / (TIMER0_OVERFLOW_COUNT);
    u8 u8Preload = TIMER0_OVERFLOW_COUNT - (u32Counts % TIMER0_OVERFLOW_COUNT);
    TCNT0 = u8Preload;
    while(u32NumOvf--)
    {
        while (((TIFR>>0)&1) == 0);
        TIFR |= (1<<0);
    }
}

void TIMER0_vidDelayMsAsynch(u32 u32MilliSecond, void(*pfunAppFunction)(void))
{
    (void)u32MilliSecond;
    (void)pfunAppFunction;
}

/* Timer0 Overflow Interrupt Vector */
void __vector_11 (void) __attribute__((signal));
void __vector_11 (void)
{
    if (LOC_pfunIsrFunction != NULL)
    {
        LOC_pfunIsrFunction();
    }
}
