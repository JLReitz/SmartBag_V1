#ifndef VIBRATIONAL_MOTOR_H
#define VIBRATIONAL_MOTOR_H

#include "Arduino_Core.h"

class Vibrational_Motor
{
public:
	
	VibrationalMotor(UINT08 nPin=-1)
	{
		if((nPin > -1) && g_AssignPin(m_pMotorPin, nPin, Pin::eDIGITAL_OUT))
			m_pMotorPin->m_Attach(); //Digital pins need to be attached
		else
			m_pSensorPin = NULL;
		
		m_bEnable = false;
	}
	
	~VibrationalMotor()
	{
		if(m_pMotorPin)
		{
			g_DeassignPin(m_pMotorPin)
			m_pMotorPin = NULL;
		}
	}
	
	//Mutators
	void m_Set_Enable(BOOLEAN bSet) { m_bEnable = bSet; }
	
	//Public Functions
	BOOLEAN m_ApplyOutput()
	{
		if(m_pMotorPin)
		{
			if(m_bEnable)
				m_pMotorPin->PinFunction(true);
			else
				m_pMotorPin->PinFunction(false);
		}
		
		return m_bEnable;
	}

private:
	
	BOOLEAN	m_bEnable;
	Pin * m_pMotorPin;
	
};

#endif