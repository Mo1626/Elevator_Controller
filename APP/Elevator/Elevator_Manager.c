/*
 * Elevator_Manager.c
 *
 *  Created on: Jul 26, 2026
 *      Author: HP
 */

#include "Elevator_Manager.h"
#include "../../primitiveTypes.h"

#include "../../DoorControl/Door/Door_init.h"
#include "../../DoorControl/Queue/Queue_int.h"
#include "../../DoorControl/Safety/Safety_init.h"

extern u8 CurrentFloor;
extern u8 TargetFloor;

void ElevatorManager_vidInit(void)
{
    Elevator_vidInit();
}

void ElevatorManager_vidUpdate(void)
{
    /* Safety Check */
    Elevator_vidSafetyTask();

    if(ElevatorState != ELEVATOR_IDLE)
    {
        return;
    }

    /* Read Cabin Requests */
    Elevator_vidReadCabinButtons();

    /* Read Hall Requests */
    Elevator_vidReadHallButtons();

    /* Get Next Target */
    Elevator_vidProcessRequests();

    /* Move Elevator */
    if(TargetFloor != CurrentFloor)
    {
        ElevatorState = ELEVATOR_MOVING;

        Elevator_vidDoorClose();

        Elevator_vidMove();
    }

    /* LCD Update */
    Elevator_vidDisplayTask();

    /* Door Task */
    Elevator_vidDoorTask();
}
