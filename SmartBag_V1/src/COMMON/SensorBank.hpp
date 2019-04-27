#ifndef SENSORBANK_HPP
#define SENSORBANK_HPP

#include "Sensor.hpp"

#define _SENSORBANK_SIZE 16

typedef uint16_t SensorHandle_t;

class SensorBank
{
public:

protected:
    
    //Protected Functions
    SensorHandle_t Add(Sensor & sensor);

    const Sensor & Get_Sensor(const SensorHandle_t nSensorHandle) const;

    void Delete(const SensorHandle_t nSensorHandle);
    void Update();

private:

    //Private Members
    Sensor sensorBank[_SENSORBANK_SIZE];
};

#endif