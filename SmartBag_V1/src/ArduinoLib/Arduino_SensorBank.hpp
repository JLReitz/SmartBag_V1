#ifndef ARDUINO_SENSORBANK_HPP
#define ARDUINO_SENSORBANK_HPP

#include "../Arduino_FreeRTOS/Arduino_FreeRTOS.h"
#include "Arduino_FreeRTOS/semphr.h"
#include "../Arduino_FreeRTOS/task.h"

#include "../COMMON/SensorBank.hpp"

class Arduino_SensorBank : SensorBank
{
public:

    //Public Functions
    static SemaphoreHandle_t Get_Updated();

    static SensorHandle_t Add(Sensor & sensor);

    static const Sensor & Get_Sensor(const SensorHandle_t nSensorHandle) const;

    static void Delete(const SensorHandle_t nSensorHandle);
    static void Initialize();
    static void Task_Main(void * vParameters);

protected:

private:
}

#endif