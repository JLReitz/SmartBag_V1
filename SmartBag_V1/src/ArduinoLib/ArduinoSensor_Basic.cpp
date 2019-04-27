#include "ArduinoSensor_Basic.hpp"

//  ArduinoSensor_Basic -- Protected Functions  ///////////////////////////////////////////////////

/*-------------------------------------------------------------------------------------------------
    ArduinoSensor_Basic::ReadSensor

    Protected read routine for ArduinoSensor_Basic.

    INPUT (void)
    OUTPUT (uint16_t)
*/
const uint16_t ArduinoSensor_Basic::ReadSensor() const
{
    if(sensorType == _SENSORBASIC_ANALOG)   //If the sensor is analog
        return ReadAnalog();                    //Perform an analog read
    else                                    //Else
        return (int16_t)ReadDigital();          //Perform a digital read
}

//  ArduinoSensor_Basic -- Private Functions    ///////////////////////////////////////////////////

/*-------------------------------------------------------------------------------------------------
    ArduinoSensor_Basic::ReadDigital

    Performs the Arduino-defined digitalRead() procedure on the sensor's pin.

    INPUT (void)
    OUTPUT (bool)   --  Redout from the digitalRead() procedure.
*/
const bool ArduinoSensor_Basic::ReadDigital() const 
{
    return digitalRead(nPin);
}

/*-------------------------------------------------------------------------------------------------
    ArduinoSensor_Basic::ReadAnalog

    Performs the Arduino-defined analogRead() procedure on the sensor's pin.

    INPUT (void)
    OUTPUT (uint16_t)   --  Redout from the analogRead() procedure.
*/
const uint16_t ArduinoSensor_Basic::ReadAnalog() const
{
    return analogRead(nPin);
}