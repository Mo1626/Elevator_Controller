/*
 * Switch_config.h
 *  Created on: Jul 23, 202
 *      Author: Dell
 */
#include "../../MCAL/DIO/DIO_int.h"
#ifndef SWITCH_CONFIG_H_
#define SWITCH_CONFIG_H_

#define MAX_SWIRCHES_COUNT          (4U)

typedef struct Switch_config
{
    enuPinNum_t enuSwitchPin;
    u8 u8SwitchState;
    BOOL bFirstPress;
    BOOL bHoldPress;
} strSwitchInfo_t;

#endif /* SWITCH_CONFIG_H_ */
