/*
 * Scheduler.h
 *
 *  Created on: Jul 26, 2026
 *      Author: HP
 */

#ifndef SERVICE_SCHEDULER_SCHEDULER_H_
#define SERVICE_SCHEDULER_SCHEDULER_H_

#include "../../MCAL/ADC/primitiveTypes.h"

typedef void (*Scheduler_Task_t)(void);

typedef struct
{
    Scheduler_Task_t Task;

    u32 Periodicity;

    u32 FirstDelay;

}Scheduler_strTask_t;

void Scheduler_vidInit(void);

void Scheduler_vidStart(void);

u8 Scheduler_u8CreateTask
(
        Scheduler_Task_t Copy_pfTask,
        u32 Copy_u32Periodicity,
        u32 Copy_u32FirstDelay
);

#endif /* SERVICE_SCHEDULER_SCHEDULER_H_ */