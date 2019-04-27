#include "SensorBank.hpp"

//  SensorBank -- Protected Functions   ///////////////////////////////////////////////////////////

/*-------------------------------------------------------------------------------------------------
    SensorBank::Add

    Adds a new sensor instance to the sensor bank.

    INPUT (Sensor &)    --  sensor
                            Sensor instance to be added.
    
    OUTPUT (SensorHandle_t) --  Handle which represents the sensor that was just added.
*/
SensorHandle_t SensorBank::Add(Sensor & sensor)
{
    //Loop through bank and look for an available slot
    for(int i=0; i<_SENSORBANK_SIZE; i++)
    {
        if(sensorBank[i].Get_SensorName() == "")    //If the sensor's name is blank
        {
            sensorBank[i] = sensor;                     //Reassign to the new sensor
            return (SensorHandle_t)(i+1);               //Return the index value as the sensor handle
        }
    }

    //If there was no slot available, return 0
    return (SensorHandle_t)0;
}

/*-------------------------------------------------------------------------------------------------
    SensorBank::Get_Sensor

    Returns the sensor instance referenced by the passed-in sensor handle.

    INPUT (SensorHandle_t)  --  nSensorHandle
                                Handle which represents the sensor to be returned.
    
    OUTPUT (Sensor &)   --  Reference to the sensor instance.
*/
const Sensor & SensorBank::Get_Sensor(const SensorHandle_t nSensorHandle) const
{
    return sensorBank[nSensorHandle-1];
}

/*-------------------------------------------------------------------------------------------------
    SensorBank::Delete
 
    Deletes the sensor instance referenced by the passed-in sensor handle.

    INPUT (SensorHandle_t)  --  nSensorHandle
                                Handle which represents the sensor to be deleted.
    
    OUTPUT (void)
*/
void SensorBank::Delete(const SensorHandle_t nSensorHandle)
{
    //Set the sensor at the index of the provided sensor handle to blank
    sensorBank[nSensorHandle].Set_SensorName("");
}

/*-------------------------------------------------------------------------------------------------
    SensorBank::Update

    Updates each initialized sensor within the sensor bank by calling their interfaced Update routine.

    INPUT (void)
    OUTPUT(void)
*/
void SensorBank::Update()
{
    //Run through each sensor in the bank and call its update routine
    for(int i=0; i<_SENSORBANK_SIZE; i++)
    {
        if(sensorBank[i].Get_SensorName() != "")    //If the sensor's name is not blank (unregistered)
            sensorBank[i].Update();                     //Call the update routine
    }
}
