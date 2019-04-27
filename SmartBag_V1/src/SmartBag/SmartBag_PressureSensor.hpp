#ifndef SMARTBAG_PRESSURESENSOR_H
#define SMARTBAG_PRESSURESENSOR_H

#include "../ArduinoLib/ArduinoSensor_Basic.hpp"

class SmartBag_PressureSensor : ArduinoSensor_Basic
{
public:

	//Public Functions
	SmartBag_PressureSensor(String & sSensorName, uint8_t nPin) : 
		ArduinoSensor_Basic(sSensorName, nPin, _SENSORBASIC_ANALOG)
	{}

	uint16_t Read();

	void Update();

protected:

private:

	//Private Functions
	void Read(void * vReadout) const;

	//Private Members
	uint16_t nReadout;	//Readout value from the pressure sensor

};
	

#endif