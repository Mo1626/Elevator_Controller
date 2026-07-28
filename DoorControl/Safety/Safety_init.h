typedef enum
{
    ELEVATOR_IDLE,
    ELEVATOR_MOVING,
    ELEVATOR_OVERLOAD,
    ELEVATOR_EMERGENCY

} ElevatorState_t;

extern ElevatorState_t ElevatorState;

void Safety_vidinit(void);

void Elevator_vidObstructionISR(void);

void Elevator_vidOverLoadCheck(void);

void Elevator_vidSafetyTask(void);

void Elevator_vidEmergency(void);
