#ifndef SENSOR_HPP
#define SENSOR_HPP

class Sensor
{
public:

    //Public Functions
    Sensor(String & sSensorName = "") : sSensorName(sSensorName)
    {}

    String Get_SensorName() { return sSensorName; } 

    void Set_SensorName(const String & nSensorName) { this->sSensorName = sSensorName; }

    //Virtual functions
    virtual void Read(void * vReadout);
    virtual void Update();

protected:

private:

    //Private Members
    const String sSensorName; //English name for the sensor, to serve as a handle and identification for humans

};

#endif