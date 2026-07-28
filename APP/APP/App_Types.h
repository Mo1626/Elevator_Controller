/*
 * App_Types.h
 *
 *  Created on:Jul 25, 2026
 *      Author:HP
 */

#ifndef APP_APP_TYPES_H_
#define APP_APP_TYPES_H_

#include "../MCAL/ADC/primitiveTypes.h"

typedef enum
{
    APP_OK = 0U,
    APP_ERROR_TASK_TABLE_FULL    
} App_enuStatus_t;

typedef struct
{
    u8  u8CurrentFloor;
    u8  u8LoadPercent;
    BOOL bSystemReady;   
} App_strSnapshot_t;

#endif 