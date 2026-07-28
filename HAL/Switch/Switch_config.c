/*

 * Switch_config.c
 *
 *  Created on: Jul 23, 2026
 *      Author: Dell
 */

// include lower layers libraries
#include "../../MCAL/ADC/primitiveTypes.h"
#include "../../MCAL/DIO/DIO_int.h"

//my own libraries
#include "Switch_config.h"
#include "Switch_priv.h"

u8 Switch_u8MaxCount = 4; // عدد أزرار الطوابق

strSwitchInfo_t Switch_astrSwInfos[4] =
{
    {.enuSwitchPin = PA0, .u8SwitchState = SW_PULLUP}, // Hall 1
    {.enuSwitchPin = PA1, .u8SwitchState = SW_PULLUP}, // Hall 2
    {.enuSwitchPin = PA2, .u8SwitchState = SW_PULLUP}, // Hall 3
    {.enuSwitchPin = PA3, .u8SwitchState = SW_PULLUP}  // Hall 4
};
