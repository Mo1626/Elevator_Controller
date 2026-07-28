/*

 * LED_int.h
 *
 *  Created on: Jul 24, 2026
 *      Author: Dell
 */

#ifndef LED_INT_H_
#define LED_INT_H_

void LED_voidInit(void);
void LED_voidOn(u8 u8LedId);
void LED_voidOff(u8 u8LedId);
void LED_voidToggle(u8 u8LedId);

#define LED_F1    0
#define LED_F2    1
#define LED_F3    2
#define LED_F4    3

#endif /* LED_INT_H_ */
