#include "SmartBag_PressureSensor.h"

//  SmartBag_PressureSensor -- Public Functions  //////////////////////////////////////////////////

/*-------------------------------------------------------------------------------------------------
    Overloaded Constructor

    INPUT(String &) --  sSensorName
                        English name for the sensor. For human debugging.

    INPUT (uint8_t) --  nPin
                        Analog pin to which the pressure sensor is connected.
*/
SmartBag_PressureSensor::SmartBag_PressureSensor(String & sSensorName, uint8_t nPin)
{
    nReadout = 0;
}

/*-------------------------------------------------------------------------------------------------
    SmartBag_PressureSensor::Read

    Returns the most recent reading of the pressure sensor in raw format.

    INPUT (void)
    OUTPUT (int16_t)    --  Raw reading of the pressure sensor.
*/
uint16_t SmartBag_PressureSensor::Read()
{
    uint16_t nReadout;

    Read(&nReadout); //Call the overloaded Read routine, passing in the address of nReadout
    return nReadout; //Return the value of the current readout
}

/*-------------------------------------------------------------------------------------------------
    SmartBag_PressureSensor::Update

    Overload of interface Sensor::Update().
    Updates the pressure sensor reading.

    INPUT (void)
    OUTPUT (void)
*/
void SmartBag_PressureSensor::Update()
{
    ArduinoSensor_Basic::ReadSensor(); //Call the parent Read() function while passing in a pointer to the readout
}

//  SmartBag_PressureSensor -- Private Functions //////////////////////////////////////////////////

/*-------------------------------------------------------------------------------------------------
    SmartBag_PressureSensor::Read

    Overload of interface Sensor::Read().
    Returns the most recent pressure sensor reading in raw format.

    INPUT (void *)  --  vReadout
                        Readout value from the sensor passed back through reference. Void pointer 
                        type to support any user-defined form of readout value.

    OUTPUT (void)
*/
void Read(void * vReadout) const
{
    uint16_t * nReadout = (uint16_t *)vReadout;   //Cast the parameter to the correct readout value

    *nReadout = Read();
}