/*
 * App_Private.h
 *
 * Created on: Jul 25, 2026
 * Author:HP
 */


#ifndef APP_APP_PRIVATE_H_
#define APP_APP_PRIVATE_H_

#include "../Service/Scheduler/Scheduler_config.h"

#define APP_TASK_COUNT              (6U)

#if (APP_TASK_COUNT > SCHEDULER_MAX_TASKS)
    #error "APP_TASK_COUNT exceeds SCHEDULER_MAX_TASKS -- raise the table size in Scheduler_config.h"
#endif

#define APP_READY_MAGIC              (0xA5U)

#endif