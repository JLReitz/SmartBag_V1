#ifndef SMARTBAG_DATABASE_HPP
#define SMARTBAG_DATABASE_HPP

#include "../Arduino_FreeRTOS/Arduino_FreeRTOS.h"
#include "../Arduino_FreeRTOS/semphr.h"
#include "../Arduino_FreeRTOS/task.h"

#include "../ArduinoLib/Arduino_SensorBank.hpp"
#include "SmartBag_BatterySensor.hpp"
#include "Smartbag_LightSensor.hpp"
#include "SmartBag_PressureSensor.hpp"

namespace Database 
{
    //  SmartBag_Database class
    class SmartBag_Database;

    //  Namespace Functions
    void Initialize();
}

class Database::SmartBag_Database 
{
public:

    //Public Functions
    SmartBag_Database();

    static void Task_SensorBank(void * vParameters);

protected:

private:

    //Private Functions

    //Private Members
    bool bSensorBank_Updated;
};

#endif