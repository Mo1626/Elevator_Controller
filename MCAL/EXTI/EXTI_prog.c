/*
 * EXTI_prog.c
 */
// public libraries [primitive, error, math, stdlib, ......]
#include "../ADC/primitiveTypes.h"

// include lower layers libraries


//my own libraries 
#include "EXTI_config.h"
#include "EXTI_priv.h"
#include "EXTI_int.h"


static void(*LOC_pfunIsr0Function)(void) = NULL;
static void(*LOC_pfunIsr1Function)(void) = NULL;
static void(*LOC_pfunIsr2Function)(void) = NULL;


void EXTI_vidInit(void)
{
    #if EXTI_INT0_SENSE_LEVEL == EXTI_LOW_LEVEL
        MCUCR &=~(1<<0);
        MCUCR &=~(1<<1);
    #elif EXTI_INT0_SENSE_LEVEL == EXTI_ANY_CHANGE
        MCUCR |= (1<<0);
        MCUCR &=~(1<<1);
    #elif EXTI_INT0_SENSE_LEVEL == EXTI_FALLING_EDGE
        MCUCR &=~(1<<0);
        MCUCR |= (1<<1);
    #elif EXTI_INT0_SENSE_LEVEL == EXTI_RISING_EDGE
        MCUCR |= (1<<0);
        MCUCR |= (1<<1);
    #else
        #error INT0 Pin level wrong
    #endif
    
    #if EXTI_INT1_SENSE_LEVEL == EXTI_LOW_LEVEL
        MCUCR &=~(1<<2);
        MCUCR &=~(1<<3);
    #elif EXTI_INT1_SENSE_LEVEL == EXTI_ANY_CHANGE
        MCUCR |= (1<<2);
        MCUCR &=~(1<<3);
    #elif EXTI_INT1_SENSE_LEVEL == EXTI_FALLING_EDGE
        MCUCR &=~(1<<2);
        MCUCR |= (1<<3);
    #elif EXTI_INT1_SENSE_LEVEL == EXTI_RISING_EDGE
        MCUCR |= (1<<2);
        MCUCR |= (1<<3);
    #else
        #error INT1 Pin level wrong
    #endif
    
    #if EXTI_INT2_SENSE_LEVEL == EXTI_FALLING_EDGE
        MCUCSR &=~(1<<6);
    #elif EXTI_INT2_SENSE_LEVEL == EXTI_RISING_EDGE
        MCUCSR |= (1<<6);
    #else
        #error INT2 Pin level wrong
    #endif

    #if EXTI_INT0_INTERRPUT == EXTI_ENABLE_INTERRUPT
        GICR |= (1<<6);
    #elif EXTI_INT0_INTERRPUT == EXTI_DISABLE_INTERRUPT
        GICR &=~(1<<6);
    #else
        #error INT0 Interrupt mode has an issue
    #endif

    #if EXTI_INT1_INTERRPUT == EXTI_ENABLE_INTERRUPT
        GICR |= (1<<7);
    #elif EXTI_INT1_INTERRPUT == EXTI_DISABLE_INTERRUPT
        GICR &=~(1<<7);
    #else
        #error INT1 Interrupt mode has an issue
    #endif

    #if EXTI_INT2_INTERRPUT == EXTI_ENABLE_INTERRUPT
        GICR |= (1<<5);
    #elif EXTI_INT2_INTERRPUT == EXTI_DISABLE_INTERRUPT
        GICR &=~(1<<5);
    #else
        #error INT2 Interrupt mode has an issue
    #endif
}

void EXTI_vidSetCallback(void(*pfunAppFunction)(void) , u8 u8IntPin)
{
    if (pfunAppFunction != NULL)
    {
        if (u8IntPin == EXTI_INT_0)
        {
            LOC_pfunIsr0Function = pfunAppFunction;
        }
        else if (u8IntPin == EXTI_INT_1)
        {
            LOC_pfunIsr1Function = pfunAppFunction;
        }
        else if (u8IntPin == EXTI_INT_2)
        {
            LOC_pfunIsr2Function = pfunAppFunction;
        }
    }
}



//ISR
// int0 
void __vector_1 (void)__attribute__((signal));
void __vector_1 (void)
{
    if (LOC_pfunIsr0Function != NULL)
    {
        LOC_pfunIsr0Function();
    }
}
// int1
void __vector_2 (void)__attribute__((signal));
void __vector_2 (void)
{
    if (LOC_pfunIsr1Function != NULL)
    {
        LOC_pfunIsr1Function();
    }
    
}
// int2
void __vector_3 (void)__attribute__((signal));
void __vector_3 (void)
{
    if (LOC_pfunIsr2Function != NULL)
    {
        LOC_pfunIsr2Function();
    }

}
