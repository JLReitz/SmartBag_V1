#ifndef BATTERY_H
#define BATTERY_H

#include "Arduino_Core.h"

class Battery
{
public:

	Battery(SINT08 nBattPin=-1, SINT08 nTempPin=-1, SINT nCurrentPin=-1)
	{
		if(!((nBattPin > -1) && g_AssignPin(m_pBattPin, nBattPin, Pin::eANALOG_IN)))
			nBattPin = NULL;
		if(!((nTempPin > -1) && g_AssignPin(m_pTempPin, nTempPin, Pin::eANALOG_IN)))
			nTempPin = NULL;
		if(!((nCurrentPin > -1) && g_AssignPin(m_pCurrentPin, nCurrentPin, Pin::eANALOG_IN)))
			nTempPin = NULL;
		
		m_fBattVoltage = 0;
	}
	
	~Battery()
	{
		if(m_pBattPin)
		{
			g_DeassignPin(m_pBattPin);
			m_pBattPin = NULL;
		}
		if(m_pTempPin)
		{
			g_DeassignPin(m_pTempPin);
			m_pTempPin = NULL;
		}
		if(m_pCurrentPin)
		{
			g_DeassignPin(m_pCurrentPin);
			m_pCurrentPin = NULL;
		}
	}
	
	//Public Functions
	void m_Update()
	{
		if(m_pBattPin)
			m_pBattPin->m_PinFunction(m_fBattVoltage);
		else
			m_fBattVoltage = 0;
		
		if(m_pTempPin)
			m_pTempPin->m_PinFunction(m_fTempVoltage);
		else
			m_fTempVoltage = 0;
		
		if(m_pCurrentPin)
			m_pCurrentPin->m_PinFunction(m_fCurrentVoltage);
		else
			m_fCurrentVoltage = 0;	
	}

private:
	
	float m_fBattVoltage, m_fTempVoltage, m_fCurrentVoltage;
	Pin * m_pBattPin, m_pTempPin, m_pCurrentPin;
	
};

#endif