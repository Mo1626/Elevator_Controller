/*
 * EXTI_int.h
 *
 *  Created on: Jul 21, 2026
 *      Author: Ahmed El-Gaafrawy
 */

#ifndef MCAL_EXTI_EXTI_INT_H_
#define MCAL_EXTI_EXTI_INT_H_

#define EXTI_INT_0               (0U)
#define EXTI_INT_1               (1U)
#define EXTI_INT_2               (2U)

void EXTI_vidInit(void);


void EXTI_vidSetSenseLevel(u8 u8IntPin, u8 u8SenseLevel);

void EXTI_vidEnableInterrupt(u8 u8IntPin );
void EXTI_vidDisableInterrupt(u8 u8IntPin);

void EXTI_vidSetCallback(void (*pfunAppFunction)(void), u8 u8IntPin);

#endif /* MCAL_EXTI_EXTI_INT_H_ */
