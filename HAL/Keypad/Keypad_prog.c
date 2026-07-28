/*

 * Keypad_prog.c
 */
// public libraries [primitive, error, math, stdlib, ......]
#include "../../MCAL/ADC/primitiveTypes.h"
#include <util/delay.h>

#include "../../MCAL/DIO/DIO_int.h"

#include "Keypad_config.h"
#include "Keypad_priv.h"
#include "Keypad_int.h"

#if (KEYPAD_COL_COUNT < 0 || KEYPAD_COL_COUNT > 4)
    #error Keypad Column counts must be "1:4"
#endif
#if (KEYPAD_ROW_COUNT < 0 || KEYPAD_ROW_COUNT > 4)
    #error Keypad Row counts must be "1:4"
#endif

void Keypad_vidInit(void)
{
    DIO_vidSetPinMode(KEYPAD_C1_PIN , MODE_OUTPUT_HIGH);
    #if KEYPAD_COL_COUNT > 1
    DIO_vidSetPinMode(KEYPAD_C2_PIN , MODE_OUTPUT_HIGH);
    #endif
    #if KEYPAD_COL_COUNT > 2
    DIO_vidSetPinMode(KEYPAD_C3_PIN , MODE_OUTPUT_HIGH);
    #endif
    #if KEYPAD_COL_COUNT > 3
    //DIO_vidSetPinMode(KEYPAD_C4_PIN , MODE_OUTPUT_HIGH);
    #endif

    DIO_vidSetPinMode(KEYPAD_R1_PIN , MODE_INPUT_PULLUP);
    #if KEYPAD_ROW_COUNT > 1
    DIO_vidSetPinMode(KEYPAD_R2_PIN , MODE_INPUT_PULLUP);
    #endif
    #if KEYPAD_ROW_COUNT > 2
    DIO_vidSetPinMode(KEYPAD_R3_PIN , MODE_INPUT_PULLUP);
    #endif
    #if KEYPAD_ROW_COUNT > 3
    DIO_vidSetPinMode(KEYPAD_R4_PIN , MODE_INPUT_PULLUP);
    #endif
}

u8 Keypad_u8GetPressedKey(void)
{
    BOOL bIsKeyDetected = FALSE;
    u8 u8KeyValue = KEYPAD_NOT_PRESSED;

    u8 au8Cols[KEYPAD_COL_COUNT] = 
    {
        KEYPAD_C1_PIN,
        #if KEYPAD_COL_COUNT > 1
            KEYPAD_C2_PIN,
        #endif
        #if KEYPAD_COL_COUNT > 2
            KEYPAD_C3_PIN,
        #endif
        #if KEYPAD_COL_COUNT > 3
           // KEYPAD_C4_PIN,
        #endif        
    };

    u8 au8Rows[KEYPAD_ROW_COUNT] = 
    {
        KEYPAD_R1_PIN,
        #if KEYPAD_ROW_COUNT > 1
            KEYPAD_R2_PIN,
        #endif
        #if KEYPAD_ROW_COUNT > 2
            KEYPAD_R3_PIN,
        #endif
        #if KEYPAD_ROW_COUNT > 3
            KEYPAD_R4_PIN,
        #endif
    };

    for (u8 u8Col = 0U; u8Col < KEYPAD_COL_COUNT; u8Col++)
    {
        DIO_vidSetPinValue(au8Cols[u8Col] , LOW);
        for (u8 u8Row = 0U; u8Row < KEYPAD_ROW_COUNT; u8Row++)
        {
            enuPinValue_t enuPinVal = DIO_enuGetPinValue(au8Rows[u8Row]);
            if (enuPinVal == LOW)
            {
                _delay_ms(5); // Debouncing
                enuPinVal = DIO_enuGetPinValue(au8Rows[u8Row]);
                if (enuPinVal == LOW)
                {
                    u8 au8KeyValues[KEYPAD_ROW_COUNT][KEYPAD_COL_COUNT] = KEYPAD_MATRIX_VALUES;
                    u8KeyValue = au8KeyValues[u8Row][u8Col];

                    while(LOW == DIO_enuGetPinValue(au8Rows[u8Row])); // Avoiding hold pressing
                    bIsKeyDetected = TRUE;
                    break;
                }
            }
        }
        DIO_vidSetPinValue(au8Cols[u8Col] , HIGH);
        if (bIsKeyDetected == TRUE)
        {
            break;
        }
    }

    return u8KeyValue;
}
