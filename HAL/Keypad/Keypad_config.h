/*

 * Keypad_config.h
 */

/*
 * Keypad_config.h
 */

#ifndef HAL_KEYPAD_KEYPAD_CONFIG_H_
#define HAL_KEYPAD_KEYPAD_CONFIG_H_

/********************************************************/
/****        Keypad Row/Col configuration "3x4"      ****/
/********************************************************/
#define KEYPAD_ROW_COUNT                    (4U)
#define KEYPAD_COL_COUNT                    (3U)

/********************************************************/
/****        Keypad Row/Col configuration "Connected pins" ****/
/********************************************************/
#define KEYPAD_R1_PIN                       PD0
#define KEYPAD_R2_PIN                       PD1
#define KEYPAD_R3_PIN                       PD2
#define KEYPAD_R4_PIN                       PD3

#define KEYPAD_C1_PIN                       PC6
#define KEYPAD_C2_PIN                       PC5
#define KEYPAD_C3_PIN                       PC4

/********************************************************/
/****         Keypad Row/Col configuration "key values"    ****/
/********************************************************/
#define KEYPAD_MATRIX_VALUES        {\
                                        {'1' , '2', '3'},\
                                        {'4' , '5', '6'},\
                                        {'7' , '8', '9'},\
                                        {'*' , '0', '#'},\
                                    }

#endif /* HAL_KEYPAD_KEYPAD_CONFIG_H_ */
