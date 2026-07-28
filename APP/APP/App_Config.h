/*
 * App_Config.h
 *
 * Created on:Jul 25, 2026
 * Author:HP
 */

#ifndef APP_APP_CONFIG_H_
#define APP_APP_CONFIG_H_

#include "../MCAL/EXTI/EXTI_int.h"

#define APP_OBSTRUCT_EXTI_LINE EXTI_INT_0       

#define APP_TASK_TICK_FIRST_DELAY_MS       (0UL)
#define APP_TASK_KEYPAD_FIRST_DELAY_MS      (2UL)
#define APP_TASK_HALL_FIRST_DELAY_MS        (5UL)
#define APP_TASK_ADC_FIRST_DELAY_MS         (11UL)
#define APP_TASK_LCD_FIRST_DELAY_MS         (17UL)
#define APP_TASK_TELEMETRY_FIRST_DELAY_MS   (23UL)

#endif 