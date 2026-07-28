/*
 * Scheduler.c
 *
 *  Created on: Jul 26, 2026
 *      Author: HP
 */

#include "Scheduler.h"
#include "Scheduler_config.h"

#include "../../MCAL/TIMER0/TIMER0_Interface.h"

static Scheduler_strTask_t SchedulerTasks[SCHEDULER_MAX_TASKS];

static volatile u8 Scheduler_u8TickFlag = 0;

static void Scheduler_vidTick(void);

void Scheduler_vidInit(void)
{
    u8 Index;

    for(Index = 0 ; Index < SCHEDULER_MAX_TASKS ; Index++)
    {
        SchedulerTasks[Index].Task = 0;
        SchedulerTasks[Index].Periodicity = 0;
        SchedulerTasks[Index].FirstDelay = 0;
    }

    TIMER0_vidSetCallBack(Scheduler_vidTick);
}

void Scheduler_vidStart(void)
{
    u8 Index;

    if(Scheduler_u8TickFlag == 0)
    {
        return;
    }

    Scheduler_u8TickFlag = 0;

    for(Index = 0 ; Index < SCHEDULER_MAX_TASKS ; Index++)
    {
        if(SchedulerTasks[Index].Task != 0)
        {
            if(SchedulerTasks[Index].FirstDelay == 0)
            {
                SchedulerTasks[Index].Task();

                SchedulerTasks[Index].FirstDelay =
                        SchedulerTasks[Index].Periodicity - 1;
            }
            else
            {
                SchedulerTasks[Index].FirstDelay--;
            }
        }
    }
}

u8 Scheduler_u8CreateTask
(
        Scheduler_Task_t Copy_pfTask,
        u32 Copy_u32Periodicity,
        u32 Copy_u32FirstDelay
)
{
    u8 Index;

    for(Index = 0 ; Index < SCHEDULER_MAX_TASKS ; Index++)
    {
        if(SchedulerTasks[Index].Task == 0)
        {
            SchedulerTasks[Index].Task = Copy_pfTask;
            SchedulerTasks[Index].Periodicity = Copy_u32Periodicity;
            SchedulerTasks[Index].FirstDelay = Copy_u32FirstDelay;

            return 1;
        }
    }

    return 0;
}

static void Scheduler_vidTick(void)
{
    Scheduler_u8TickFlag = 1;
}