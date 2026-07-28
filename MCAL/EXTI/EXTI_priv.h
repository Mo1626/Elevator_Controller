/*
 * EXTI_priv.h
 *
 *  Created on: Jul 21, 2026
 *      Author: Ahmed El-Gaafrawy
 */

#ifndef MCAL_EXTI_EXTI_PRIV_H_
#define MCAL_EXTI_EXTI_PRIV_H_

#define EXTI_LOW_LEVEL             (0U)
#define EXTI_ANY_CHANGE            (1U)
#define EXTI_FALLING_EDGE          (2U)
#define EXTI_RISING_EDGE           (3U)

#define EXTI_ENABLE_INTERRUPT      (1U)
#define EXTI_DISABLE_INTERRUPT     (0U)



#define MCUCR                      *((volatile u8*)0x55)
#define MCUCSR                     *((volatile u8*)0x54)
#define GICR                       *((volatile u8*)0x5B)
#define GIFR                       *((volatile u8*)0x5A)


#endif /* MCAL_EXTI_EXTI_PRIV_H_ */
