/*
 * TIMER0_int.h
 * Created on: Jul 23, 2026
 * Author: Ahmed El-Gaafrawy
 */

#ifndef MCAL_TIMER0_TIMER0_INT_H_
#define MCAL_TIMER0_TIMER0_INT_H_

void TIMER0_vidInit(void);
void TIMER0_vidSetCallBack(void (*pfunAppFunction)(void));
void TIMER0_vidDelayMs(u32 u32MilliSecond);
void TIMER0_vidDelayMsAsynch(u32 u32MilliSecond, void(*pfunAppFunction)(void));

#endif /* MCAL_TIMER0_TIMER0_INT_H_ */
