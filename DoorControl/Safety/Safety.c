#include "../../DoorControl/Door/Door_config.h"
#include "../../DoorControl/Door/Door_init.h"
#include "../../DoorControl/sensor/Sensor.h"
#include "../../DoorControl/Safety/Safety_config.h"
#include "../../DoorControl/Safety/Safety_init.h"
#include "../../primitiveTypes.h"

#include "../../HAL/LCD/LCD_config.h"
#include "../../HAL/LCD/LCD_int.h"
#include "../../HAL/LCD/LCD_priv.h"

#include "../../HAL/Buzzer/BUZZ_config.h"
#include "../../HAL/Buzzer/BUZZ_int.h"
#include "../../HAL/Buzzer/BUZZ_priv.h"

#include "../../MCAL/DIO/DIO_Int.h"
#include "../../MCAL/DIO/DIO_Priv.h"

#include "../../MCAL/TIMER0/TIMER0_Int.h"

#include "../../MCAL/ADC/ADC_Config.h"
#include "../../MCAL/ADC/ADC_Int.h"
#include "../../MCAL/ADC/ADC_Priv.h"


static u16 LoadValue = 0;

static u8 ObstructionCounter = 0;
ElevatorState_t ElevatorState;
extern u8 DoorBusy ;

extern DoorState_t DoorState;

void Safety_vidinit(void)
{
    ElevatorState = ELEVATOR_IDLE;
    ObstructionCounter = 0;
}

void Elevator_vidObstructionISR(void)
{
    if(DoorState == DOOR_CLOSING)
    {
        if(IR_u8IsObjectDetected())
        {
            ObstructionCounter++;
    
            LCD_vidSendCommand(0x01);
            LCD_vidSendString("OBSTRUCTION");
    
            Buzzer_vidErrorKey();
    
            DoorBusy = 0;
    
            Elevator_vidDoorOpen();
        
            if(ObstructionCounter < MAX_OBSTRUCTION_COUNT)
            {
               TIMER0_vidDelayMs(DOOR_OPEN_TIME);
               DoorBusy = 0;
              Elevator_vidDoorClose();
            }
            else
            {
                ObstructionCounter = 0;
    
                DoorState = DOOR_CLOSED;
    
                LCD_vidSendCommand(0x01);
                LCD_vidSendString("FORCE CLOSE");
                Elevator_vidDoorClose();
            }
        }
    }
}

void Elevator_vidOverLoadCheck(void)
{
    ADC_vidSelectChannel(0);

    ADCSRA |= (1<<6);           // start conversion

    while(((ADCSRA>>4)&1)==0);  

    ADCSRA |= (1<<4);

    LoadValue = ADC_u8GetLoadPercentage(0);

    if(LoadValue > 820)
    {
        ElevatorState = ELEVATOR_OVERLOAD;

        LCD_vidSendCommand(0x01);
        LCD_vidSendString("OVERLOAD");

        while(LoadValue > 760)
        {
            Buzzer_vidOverload();

            ADCSRA |= (1<<6);

            while(((ADCSRA>>4)&1)==0);

            ADCSRA |= (1<<4);

            LoadValue = ADC_u8GetLoadPercentage(0);
        }

        ElevatorState = ELEVATOR_IDLE;

        LCD_vidSendCommand(0x01);
        LCD_vidSendString("READY");
    }
}

void Elevator_vidEmergency(void)
{
    ElevatorState = ELEVATOR_EMERGENCY;

    LCD_vidSendCommand(0x01);
    LCD_vidSendString("EMERGENCY");

    Buzzer_vidEstop();     

    DoorBusy = 0;
    Elevator_vidDoorOpen();

    while(Keypad_u8GetPressedKey() != '0')
    {

    }

    ElevatorState = ELEVATOR_IDLE;

    LCD_vidSendCommand(0x01);
    LCD_vidSendString("READY");
}

void Elevator_vidSafetyTask(void)
{
    Elevator_vidOverLoadCheck();

    if(Keypad_u8GetPressedKey() == '0')
    {
        Elevator_vidEmergency();
        return;
    }

    else if(ElevatorState == ELEVATOR_OVERLOAD)
    {
        return;
    }

    else if(ElevatorState == ELEVATOR_EMERGENCY)
    {
        return;
    }
}


