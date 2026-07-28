typedef enum
{
    DOOR_CLOSED,
    DOOR_OPENING,
    DOOR_OPEN,
    DOOR_CLOSING

}DoorState_t;



extern DoorState_t DoorState;

void Elevator_vidInit(void);

void Elevator_vidDoorOpen(void);

void Elevator_vidDoorClose(void);

void Elevator_vidDoorTask(void);