#include "Arduino_SensorBank.hpp"

//  Semaphore for sensor bank tasking
SemaphoreHandle_t semUpdated;

//  Global SensorBank instance for static procedures
SensorBank g_SensorBank;

//  Arduino_SensorBank -- Public Functions  ///////////////////////////////////////////////////////

/*-------------------------------------------------------------------------------------------------
    Get_Updated

    Static call to access the semaphore "semUpdated".

    INPUT (void)
    OUTPUT (SemaphoreHandle_t)  --  Handle for semUpdated
*/
static SemaphoreHandle_t Arduino_SensorBank::Get_Updated()
{  
    return semUpdated;
}

/*-------------------------------------------------------------------------------------------------
    Add

    Static call to the global Arduino_SensorBank's Add() procedure.
    Adds a new sensor instance to the sensor bank.

    INPUT (Sensor &)    --  sensor
                            Sensor instance to be added.
    
    OUTPUT (SensorHandle_t) --  Handle which represents the sensor that was just added.
*/
static SensorHandle_t Arduino_SensorBank::SensorHandle_t Add(Sensor & sensor)
{
    return g_SensorBank.add(sensor);
}

/*-------------------------------------------------------------------------------------------------
    Get_Sensor

    Static call to the global Arduino_SensorBank's Get_Sensor() procedure.
    Returns the sensor instance referenced by the passed-in sensor handle.

    INPUT (SensorHandle_t)  --  nSensorHandle
                                Handle which represents the sensor to be returned.
    
    OUTPUT (Sensor &)   --  Reference to the sensor instance.
*/
static const Sensor & Arduino_SensorBank::Get_Sensor(const SensorHandle_t nSensorHandle) const
{
    return g_SensorBank.Get_Sensor(nSensorHandle);
}

/*-------------------------------------------------------------------------------------------------
    Delete

    Static call to the global Arduino_SensorBank's Delete() procedure. 
    Deletes the sensor instance referenced by the passed-in sensor handle.

    INPUT (SensorHandle_t)  --  nSensorHandle
                                Handle which represents the sensor to be deleted.
    
    OUTPUT (void)
*/
static void Arduino_SensorBank::Delete(const SensorHandle_t nSensorHandle)
{
    g_SensorBank.Delete(nSensorHandle);
}

/*-------------------------------------------------------------------------------------------------
    Initialize

    Initializes the main task for Arduino_SensorBank.

    INPUT (void)
    OUTPUT (void)
*/
static void Arduino_SensorBank::Initialize()
{
    //Launch task
    xTaskCreate(Task_Main,          //Arduino_SensorBank main task
                "SensorBank_Main",  //English name for humans
                64,                 //Stack depth of 64
                NULL,               //No parameters passed in
                5,                  //Priority of 5
                NULL);              //No handle passed back
}

/*-------------------------------------------------------------------------------------------------
    Task_Main

    Main task for the Arduino_SensorBank class.

    INPUT (void *)  --  vParameters
                        Parameters to pass in to the task upon initialization.

    OUTPUT (void)
*/
static void Arduino_SensorBank::Task_Main(void * vParameters)
{
    //Infinite loop
    while(1)
    {
        //Update the sensorbank, and then post the "semUpdated" semaphore
        g_SensorBank.Update();
        xSemaphoreGive(semUpdated);

        //Delay till next scheduler tick
        vTaskDelay(1);
    }
}