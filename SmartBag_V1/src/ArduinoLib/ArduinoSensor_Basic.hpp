#ifndef ARDUINOSENSOR_BASIC_HPP
#define ARDUINOSENSOR_BASIC_HPP

#include <Arduino.h>
#include "../COMMON/Sensor.hpp"

#define _SENSORBASIC_ANALOG     SensorBasicType_t::eAnalog
#define _SENSORBASIC_DIGITAL    SensorBasicType_t::eDigital

class ArduinoSensor_Basic : Sensor
{
public:

    //Public Structs
    typedef enum class SensorBasicType_t
    {
        eAnalog     =   0,
        eDigital    =   1,
    };

    //Public Functions
    ArduinoSensor_Basic(String sSensorName, uint8_t nPin, SensorBasicType_t sensorType) : 
        Sensor(sSensorName),
        nPin(nPin),
        sensorType(sensorType)
    {}

protected:

    //Protected Functions
    const uint16_t ReadSensor() const;

private:

    //Private Functions
    const bool ReadDigital() const;

    uint16_t ReadAnalog() const;

    //Private Members
    const uint8_t nPin;                    //Pin number (Arduinos don't have more than 255 pins)
    const SensorBasicType_t sensorType;   //Basic type of the sensor

};

#endif