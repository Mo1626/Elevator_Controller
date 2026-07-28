/*
 * main.c
 *      Author: Dell
 */

#include "DoorControl/Door/Door_init.h"
#include "DoorControl/Queue/Queue_int.h"
#include "DoorControl/sensor/Sensor.h"
#include "DoorControl/Safety/Safety_init.h"
#include "primitiveTypes.h"

// Elevator Modules
#include "HAL/LCD/LCD_int.h"
#include "HAL/Keypad/Keypad_int.h"
#include "HAL/LED/LED_int.h"
#include "HAL/Switch/Switch_int.h"
#include "HAL/Buzzer/Buzz_int.h"

// MCAL
#include "MCAL/ADC/ADC_Int.h"
#include "MCAL/TIMER0/TIMER0_Int.h"
#include "MCAL/EXTI/EXTI_Int.h"
#include "MCAL/DIO/DIO_Int.h"


#include "MCAL/ADC/primitiveTypes.h"
#include "MCAL/DIO/DIO_int.h"
#include "MCAL/TIMER0/TIMER0_int.h"

#include "HAL/LCD/LCD_int.h"
#include "HAL/Keypad/Keypad_int.h"
#include "HAL/LED/LED_int.h"
#include "HAL/Switch/Switch_int.h"
#include "HAL/Buzzer/Buzz_int.h"

#define FLOOR_MIN               1U
#define FLOOR_MAX               4U

#define ELEVATOR_EMERGENCY_PIN   PD5   
#define EMERGENCY_CLEAR_KEY      '#'

#define TIME_BOOT_MS          2000U
#define TIME_MSG_MS           2000U
#define TIME_CLICK_MS           500U
#define TIME_FLOOR_TRAVEL_MS  2000U
#define TIME_DEBOUNCE_MS         5U

static u8   g_u8CurrentFloor  = FLOOR_MIN;
static BOOL g_bDoorIsClosed   = FALSE;

static void Elevator_vidShowMessage(const char *pcLine1)
{
    LCD_vidSendCommand(0x01);
    LCD_vidSendString(pcLine1);
}

static void Elevator_vidShowFloorMessage(const char *pcPrefix, u8 u8Floor)
{
    LCD_vidSendCommand(0x01);
    LCD_vidSendString(pcPrefix);
    LCD_vidSendIntegarNumber(u8Floor);
}

static void Elevator_vidUpdateFloorLED(u8 u8Floor)
{
    LED_voidOff(LED_F1);
    LED_voidOff(LED_F2);
    LED_voidOff(LED_F3);
    LED_voidOff(LED_F4);

    switch (u8Floor)
    {
        case 1: LED_voidOn(LED_F1); break;
        case 2: LED_voidOn(LED_F2); break;
        case 3: LED_voidOn(LED_F3); break;
        case 4: LED_voidOn(LED_F4); break;
        default: break;
    }
}

static void Elevator_vidInitAll(void)
{
    LCD_vidInit();
    Keypad_vidInit();
    LED_voidInit();
    Switch_vidInit();
    Buzzer_vidInit();
    TIMER0_vidInit();


    DIO_vidSetPinMode(ELEVATOR_EMERGENCY_PIN, MODE_INPUT_PULLUP);

    g_u8CurrentFloor = FLOOR_MIN;
    g_bDoorIsClosed  = FALSE;

    Elevator_vidShowMessage("Elevator System");
    TIMER0_vidDelayMs(TIME_BOOT_MS);

    Elevator_vidShowFloorMessage("Ready. Flr: ", g_u8CurrentFloor);
    Elevator_vidUpdateFloorLED(g_u8CurrentFloor);
}

static void Elevator_vidMoveToFloor(u8 u8TargetFloor)
{
    while (g_u8CurrentFloor < u8TargetFloor)
    {
        TIMER0_vidDelayMs(TIME_FLOOR_TRAVEL_MS);
        g_u8CurrentFloor++;
        Elevator_vidShowFloorMessage("Moving Up ", g_u8CurrentFloor);
        Elevator_vidUpdateFloorLED(g_u8CurrentFloor);
    }

    while (g_u8CurrentFloor > u8TargetFloor)
    {
        TIMER0_vidDelayMs(TIME_FLOOR_TRAVEL_MS);
        g_u8CurrentFloor--;
        Elevator_vidShowFloorMessage("Moving Down ", g_u8CurrentFloor);
        Elevator_vidUpdateFloorLED(g_u8CurrentFloor);
    }

    Elevator_vidShowFloorMessage("Arrived. Flr: ", g_u8CurrentFloor);
    Buzzer_vidArrivalChime();
    TIMER0_vidDelayMs(TIME_MSG_MS);
    g_bDoorIsClosed = FALSE;
}

static void Elevator_vidRequestFloor(u8 u8TargetFloor)
{
    if (g_bDoorIsClosed == FALSE)
    {
        Elevator_vidShowMessage("Close Door First!");
        Buzzer_vidErrorKey();
        TIMER0_vidDelayMs(TIME_MSG_MS);
        return;
    }

    if (u8TargetFloor == g_u8CurrentFloor)
    {
        Elevator_vidShowFloorMessage("Already at Flr ", g_u8CurrentFloor);
        Buzzer_vidKeyClick();
        TIMER0_vidDelayMs(TIME_MSG_MS);
        return;
    }

    Buzzer_vidKeyClick();
    Elevator_vidMoveToFloor(u8TargetFloor);
}

/* =====================================================================
 *                            DOOR CONTROL
 * ===================================================================== */
static void Elevator_vidOpenDoor(void)
{
    g_bDoorIsClosed = FALSE;

    Elevator_vidShowMessage("Door Opening");
    Buzzer_vidKeyClick();
    TIMER0_vidDelayMs(TIME_CLICK_MS);

    Elevator_vidShowMessage("Door Opened");
    TIMER0_vidDelayMs(TIME_MSG_MS);
}

static void Elevator_vidCloseDoor(void)
{
    g_bDoorIsClosed = TRUE;

    Elevator_vidShowMessage("Door Closing");
    Buzzer_vidKeyClick();
    TIMER0_vidDelayMs(TIME_CLICK_MS);

    Elevator_vidShowMessage("Door Closed.");
    TIMER0_vidDelayMs(TIME_MSG_MS);
}

static BOOL Elevator_bIsEmergencyPressed(void)
{
    if (DIO_enuGetPinValue(ELEVATOR_EMERGENCY_PIN) != LOW)
    {
        return FALSE;
    }

    TIMER0_vidDelayMs(TIME_DEBOUNCE_MS); /* Debouncing */
    return (DIO_enuGetPinValue(ELEVATOR_EMERGENCY_PIN) == LOW) ? TRUE : FALSE;
}

static void Elevator_vidHandleEmergency(void)
{
    LED_voidOff(LED_F1);
    LED_voidOff(LED_F2);
    LED_voidOff(LED_F3);
    LED_voidOff(LED_F4);

    Elevator_vidShowMessage("CABIN EMERGENCY!");
    Buzzer_vidEstop();

    while (TRUE)
    {
        if (Keypad_u8GetPressedKey() == EMERGENCY_CLEAR_KEY)
        {
            Buzzer_vidKeyClick();
            TIMER0_vidDelayMs(TIME_CLICK_MS);
            break;
        }
    }

    Elevator_vidShowFloorMessage("Resumed. Flr: ", g_u8CurrentFloor);
    Elevator_vidUpdateFloorLED(g_u8CurrentFloor);
    TIMER0_vidDelayMs(TIME_MSG_MS);
}

static void Elevator_vidHandleHallCalls(void)
{
    u8 u8Floor;

    for (u8Floor = FLOOR_MIN; u8Floor <= FLOOR_MAX; u8Floor++)
    {
        if (Switch_u8GetHallCall(u8Floor) == TRUE)
        {
            Elevator_vidRequestFloor(u8Floor);
            return; /* طلب واحد لكل دورة loop */
        }
    }
}

static void Elevator_vidHandleKeypad(u8 u8PressedKey)
{
    switch (u8PressedKey)
    {
        case '*': 
            Elevator_vidOpenDoor();
            break;

        case '#': 
            Elevator_vidCloseDoor();
            break;

        case '1':
        case '2':
        case '3':
        case '4':
            Elevator_vidRequestFloor((u8)(u8PressedKey - '0'));
            break;

        case KEYPAD_NOT_PRESSED:
            break;

        default:
            Elevator_vidShowMessage("Invalid Key!");
            Buzzer_vidErrorKey();
            TIMER0_vidDelayMs(TIME_MSG_MS);
            break;
    }
}

int main(void)
{
	u8 CurrentFloor=1;
	extern u8 ElevatorState;
	extern TargetFloor;

	/* Drivers Initialization */
	LCD_vidInit();
	Keypad_vidInit();
	ADC_vidInit();
	TIMER0_vidInit();
	EXTI_vidInit();
	IR_vidInit();
	LED_voidInit();
	Switch_vidInit();

	/* Elevator Initialization */
	Elevator_vidInit();
    Safety_vidinit();

    LED_voidOn(CurrentFloor);

    while(1)
    {
    	/* Safety First */
    	Elevator_vidSafetyTask();

	    if(ElevatorState != ELEVATOR_IDLE)
	    {
	        continue;
	    }

	    /* Read Requests */
	    Elevator_vidReadCabinButtons();
	    Elevator_vidReadHallButtons();

	    /* Check Queue */
	    Elevator_vidProcessRequests();

	    /* Move Elevator */
	    if(TargetFloor != CurrentFloor)
	    {
	        ElevatorState = ELEVATOR_MOVING;

	        Elevator_vidDoorClose();
	        Elevator_vidMove();
	    }

	    /* Display Current Floor */
	    Elevator_vidDisplayTask();
	}

    Elevator_vidInitAll();

    while (TRUE)
    {
        
        if (Elevator_bIsEmergencyPressed() == TRUE)
        {
            Elevator_vidHandleEmergency();
            continue;
        }

        Elevator_vidHandleKeypad(Keypad_u8GetPressedKey());

        Elevator_vidHandleHallCalls();
    }

    return 0;
}
