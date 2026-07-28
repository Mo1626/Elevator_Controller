/*

 * Keypad_int.h

 */

#ifndef HAL_KEYPAD_KEYPAD_INT_H_
#define HAL_KEYPAD_KEYPAD_INT_H_

#define KEYPAD_NOT_PRESSED          (0xFFU)

void Keypad_vidInit(void);

u8 Keypad_u8GetPressedKey(void);

#endif /* HAL_KEYPAD_KEYPAD_INT_H_ */
