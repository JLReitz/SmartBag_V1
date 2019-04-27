#ifndef AMB_LIGHT_SENSOR_H
#define AMB_LIGHT_SENSOR_H

#include "Arduino_Core.h"

class Ambient_Light_Sensor
{
public:

	Ambient_Light_Sensor(SINT08 nPin=-1)
	{
		if(!((nPin > -1) && g_AssignPin(m_pPSensorPin, nPin, Pin::eANALOG_IN)))
			m_pSensorPin = NULL;
		
		m_bValidRead = false;
		m_fAnalogRaw = -1;
	}
	
	~Ambient_Light_Sensor()
	{
		if(m_pPSensorPin)
		{
			g_DeassignPin(m_PSensorPin)
			m_pSensorPin = NULL;
		}
	}
	
	//Public Functions
	float m_AquireInput()
	{
		if(m_PSensorPin)
			m_pPSensorPin.m_PinFunction(m_fVoltageRaw);
		else
			m_fVoltageRaw = 0;
		
		return m_fVoltageRaw;
	}

private:

	BOOLEAN m_bValidRead;
	Pin * m_pSensorPin;
	float m_fVoltageRaw;

};

#endif