#include "../../DoorControl/sensor/Sensor.h"

#include "../../primitiveTypes.h"

#include "../../MCAL/DIO/DIO_Int.h"
#include "../../MCAL/DIO/DIO_Priv.h"


void IR_vidInit(void)
{
	DIO_vidSetPinMode( 0 , MODE_INPUT_PULLUP);
    DIO_vidSetPinValue( 0 , HIGH);
}

u8 IR_u8IsObjectDetected(void)
{
    return (DIO_enuGetPinValue(0));
}
