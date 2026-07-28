
#include "../../DoorControl/Door/Door_config.h"
#include "../../DoorControl/Door/Door_init.h"
#include "../../DoorControl/Queue/Queue_int.h"
#include "../../DoorControl/Safety/Safety_init.h"
#include "../../primitiveTypes.h"

#include "../../HAL/LCD/LCD_config.h"
#include "../../HAL/LCD/LCD_int.h"
#include "../../HAL/LCD/LCD_priv.h"

#include "../../HAL/LED/LED_config.h"
#include "../../HAL/LED/LED_int.h"
#include "../../HAL/LED/LED_priv.h"

#include "../../HAL/Switch/Switch_config.h"
#include "../../HAL/Switch/Switch_int.h"
#include "../../HAL/Switch/Switch_priv.h"

#include "../../MCAL/TIMER0/TIMER0_Int.h"


u8 TargetFloor = 1;

extern u8 CurrentFloor ;

extern ElevatorState_t ElevatorState;

extern DoorState_t  DoorState ;

#define QUEUE_SIZE 10
u8 RequestQueue[QUEUE_SIZE];

u8 Front = 0;
u8 Rear = 0;

void Elevator_vidReadCabinButtons(void)
{
    u8 Key;

    Key = Keypad_u8GetPressedKey();

    if((Key >= '1') && (Key <= '4'))
    {
        RequestQueue[Rear] = Key - '0';

        Rear++;

        if(Rear >= QUEUE_SIZE)
        {
            Rear = 0;
        }
    }
}

void Elevator_vidReadHallButtons(void)
{
    u8 Floor;

    for(Floor = 1 ; Floor <= 4 ; Floor++)
    {
        if(Switch_u8GetHallCall(Floor))
        {
            RequestQueue[Rear] = Floor;

            Rear++;

            if(Rear >= QUEUE_SIZE)
            {
                Rear = 0;
            }
        }
    }
}

void Elevator_vidProcessRequests(void)
{
    if(Front == Rear)
    {
        return;
    }

    TargetFloor = RequestQueue[Front];

    Front++;

    if(Front >= QUEUE_SIZE)
    {
        Front = 0;
    }
}

void Elevator_vidDisplayTask(void)
{
    LCD_vidSendCommand(0x01);

    LCD_vidSendString("Floor : ");

    LCD_vidSendIntegarNumber(CurrentFloor);
}

void Elevator_vidMove(void)
{
    if(TargetFloor > CurrentFloor)
    {
        while(CurrentFloor < TargetFloor)
        {
            TIMER0_vidDelayMs(3000);

            CurrentFloor++;
            if (CurrentFloor > 1)
            {
                LED_voidOff(CurrentFloor-1);
            }
            LED_voidOn(CurrentFloor);

            Elevator_vidDisplayTask();
        }
        ElevatorState = ELEVATOR_IDLE;
    }
    else if(TargetFloor < CurrentFloor)
    {
        while(CurrentFloor > TargetFloor)
        {
            TIMER0_vidDelayMs(3000);

            CurrentFloor--;

            if (CurrentFloor > 1)
            {
                LED_voidOff(CurrentFloor + 1);
            }
            LED_voidOn(CurrentFloor);
            Elevator_vidDisplayTask();
        }
        ElevatorState=ELEVATOR_IDLE;
    }
    Elevator_vidDoorOpen();
}

