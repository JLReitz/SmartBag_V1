#include "SmartBag_LightSensor.hpp"

//  SmartBag_LightSensor -- Public Functions  //////////////////////////////////////////////////

/*-------------------------------------------------------------------------------------------------
    Overloaded Constructor

    INPUT(String &) --  sSensorName
                        English name for the sensor. For human debugging.

    INPUT (uint8_t) --  nPin
                        Analog pin to which the battery voltage can be read.
*/
SmartBag_LightSensor::SmartBag_LightSensor(String & sSensorName, uint8_t nPin)
{
    nReadout = 0;
}

/*-------------------------------------------------------------------------------------------------
    SmartBag_LightSensor::Read

    Returns the most recent reading of the battery voltage in raw format.

    INPUT (void)
    OUTPUT (int16_t)    --  Raw reading of the battery voltage.
*/
uint16_t SmartBag_LightSensor::Read()
{
    uint16_t nReadout;

    Read(&nReadout); //Call the overloaded Read routine, passing in the address of nReadout
    return nReadout; //Return the value of the current readout
}

/*-------------------------------------------------------------------------------------------------
    SmartBag_LightSensor::Update

    Overload of interface Sensor::Update().
    Updates the battery voltage reading.

    INPUT (void)
    OUTPUT (void)
*/
void SmartBag_LightSensor::Update()
{
    ArduinoSensor_Basic::ReadSensor(); //Call the parent Read() function while passing in a pointer to the readout
}

//  SmartBag_LightSensor -- Private Functions //////////////////////////////////////////////////

/*-------------------------------------------------------------------------------------------------
    SmartBag_LightSensor::Read

    Overload of interface Sensor::Read().
    Returns the most recent battery voltage reading in raw format.

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