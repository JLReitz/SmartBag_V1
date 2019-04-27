#ifndef SMARTBAG_BATTERYSENSOR_HPP
#define SMARTBAG_BATTERYSENSOR_HPP

#include "../ArduinoLib/ArduinoSensor_Basic.hpp"

class SmartBag_BatterySensor : ArduinoSensor_Basic
{
public:

    //Public Functions
    SmartBag_BatterySensor(String & sSensorName, uint8_t nPin) : 
		ArduinoSensor_Basic(sSensorName, nPin, _SENSORBASIC_ANALOG)
	{}

    uint16_t Read();

	void Update();

protected:

private:

	//Private Functions
	void Read(void * vReadout) const;

	//Private Members
	uint16_t nReadout; //Readout value from the battery sensor
}

#endif