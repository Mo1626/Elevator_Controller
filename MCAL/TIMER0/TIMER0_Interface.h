/*
 * TIMER0_Interface.h
 *
 *  Created on: Jul 26, 2026
 *      Author: AbdoFarouk
 */

#ifndef MCAL_TIMER0_TIMER0_INTERFACE_H_
#define MCAL_TIMER0_TIMER0_INTERFACE_H_

#include "../../primitiveTypes.h"

void TIMER0_vidInit(void);

u32  TIMER0_u32GetMillis(void);

void TIMER0_vidDelayMs(u32 u32DelayMs);

#endif /* MCAL_TIMER0_TIMER0_INTERFACE_H_ */
