#ifndef PRESSURE_SENSOR_H
#define PRESSURE_SENSOR_H

#include "Arduino_Core.h"

class Piezo_Sensor
{
public:

	Piezo_Sensor(SINT08 nPin=-1)
	{
		if(!((nPin > -1) && g_AssignPin(m_pSensorPin, nPin, Pin::eANALOG_IN)))
			m_pSensorPin = NULL;
		
		m_fPressureVoltage = 0;
	}
	
	~Piezo_Sensor()
	{
		if(m_pSensorPin)
		{
			g_DeassignPin(m_pSensorPin)
			m_pSensorPin = NULL;
		}
	}
	
	//Public Functions
	void m_AquireInput(float & fReadOut)
	{
		if(m_PSensorPin)
			m_pSensorPin->m_PinFunction(m_fPressureVoltage);
		else
			m_fPressureVoltage = 0;
		
		fReadOut = m_fPressureVoltage;
	}

private:
	
	Pin * m_pSensorPin;
	float m_fPressureVoltage;
};

#endif