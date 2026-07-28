#include "../../DoorControl/Door/Door_config.h"
#include "../../DoorControl/Door/Door_init.h"
#include "../../DoorControl/Safety/Safety_init.h"
#include "../../primitiveTypes.h"

#include "../../MCAL/EXTI/EXTI_Config.h"
#include "../../MCAL/EXTI/EXTI_Int.h"
#include "../../MCAL/EXTI/EXTI_Priv.h"

#include "../../MCAL/TIMER0/TIMER0_Int.h"

#include "../../HAL/LCD/LCD_config.h"
#include "../../HAL/LCD/LCD_int.h"
#include "../../HAL/LCD/LCD_priv.h"


DoorState_t DoorState = DOOR_CLOSED;

ElevatorState_t ElevatorState = ELEVATOR_IDLE;

u8 CurrentFloor = 1;

u8 DoorBusy = 0;

void Elevator_vidInit(void)
{
    DoorState = DOOR_CLOSED;

    CurrentFloor = 1;

    DoorBusy = 0;

    EXTI_vidSetCallback(Elevator_vidObstructionISR , EXTI_INT_0 );
}

void Elevator_vidDoorOpen(void)
{
    if(DoorBusy)
        return;

    DoorBusy = 1;

    DoorState = DOOR_OPENING;

    LCD_vidSendCommand(0x01);
    LCD_vidSendString("DOOR OPENING");

    TIMER0_vidDelayMs(DOOR_OPENING_TIME);

    DoorState = DOOR_OPEN;

    LCD_vidSendCommand(0x01);
    LCD_vidSendString("DOOR OPEN");

    TIMER0_vidDelayMs(DOOR_OPEN_TIME);

    DoorBusy = 0;
}

void Elevator_vidDoorClose(void)
{
    if(DoorBusy)
        return;

    DoorBusy = 1;

    DoorState = DOOR_CLOSING;

    LCD_vidSendCommand(0x01);
    LCD_vidSendString("DOOR CLOSING");

    TIMER0_vidDelayMs(DOOR_CLOSING_TIME);

    DoorState = DOOR_CLOSED;

    LCD_vidSendCommand(0x01);
    LCD_vidSendString("DOOR CLOSED");

    DoorBusy = 0;
}

void Elevator_vidDoorTask(void)
{
    switch(DoorState)
    {
        case DOOR_OPENING:
            Elevator_vidDoorOpen();
            break;

        case DOOR_CLOSING:
            Elevator_vidDoorClose();
            break;

        case DOOR_OPEN:
        case DOOR_CLOSED:
        default:
            break;
    }
}
