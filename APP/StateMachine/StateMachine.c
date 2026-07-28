/*
 * StateMachine.c
 *
 * Created on: Jul 26, 2026
 * Author: HP
 */

#include "../../primitiveTypes.h"
#include "StateMachine.h"

#include "../../DoorControl/Safety/Safety_init.h"
#include "../../DoorControl/Door/Door_init.h"

extern u8 CurrentFloor;
extern u8 TargetFloor;

void StateMachine_vidInit(void)
{
    ElevatorState = ELEVATOR_IDLE;
}

void StateMachine_vidUpdate(void)
{
    switch(ElevatorState)
    {
        case ELEVATOR_IDLE:

            if(TargetFloor != CurrentFloor)
            {
                ElevatorState = ELEVATOR_MOVING;
            }

        break;

        case ELEVATOR_MOVING:

            if(TargetFloor == CurrentFloor)
            {
                ElevatorState = ELEVATOR_IDLE;
            }

        break;

        case ELEVATOR_OVERLOAD:

        break;

        case ELEVATOR_EMERGENCY:

        break;

        default:

            ElevatorState = ELEVATOR_IDLE;

        break;
    }
}
