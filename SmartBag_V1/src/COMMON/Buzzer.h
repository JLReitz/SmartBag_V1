#ifndef BUZZER_H
#define BUZZER_H

#include "Arduino_Core.h"

class Buzzer
{
public:
	
	Buzzer(SINT08 nPin=-1, float fFrequency)
	{
		if((nBuzzerPin > -1) && g_AssignPin(m_pBuzzerPin, nPin, Pin::eDIGITAL_OUT))
		{
			m_pMotorPin->m_Attach(); //Digital pins need to be attached
			
			m_fFrequency = fFrequency;
			m_fHalfPeriod = (1/(m_fFrequency*2)) * 1000000; //Convert this from seconds to microseconds
		}
		else
		{
			m_nFrequency = m_fHalfPeriod = 0;
			m_pBuzzerPin = NULL;
		}
		
		m_bEnable = false;
	}
	
	~Buzzer()
	{
		if(m_pBuzzerPin)
			g_DeassignPin(m_pBuzzerPin);
	}
	
	//Accessors
	float m_Get_Frequency() { return m_fFrequency; }
	
	//Mutators
	void m_Set_Enable(BOOLEAN bSet) { m_bEnable = bSet; }
	
	//Public Functions
	void m_ApplyOutput()
	{
		//TODO implement timer and timing structure
		//Determine the time that has elapsed
		m_dwTimeDiff = micros() - dwPrevTime;
		
		if(m_bEnable && (m_dwPrevTime >= m_fHalfPeriod)) //If half of the period has passed
		{
			//Invert the output
			m_bState = !m_bState;
			m_pBuzzerPin->m_PinFunction(m_bState); //Write this inversion
		}
		else if(!m_bEnable)
			m_pBuzzerPin->m_PinFunction(false);
	}
	
private:

	BOOLEAN m_bEnable, m_bState;
	DWORD m_dwPrevTime, m_dwTimeDiff;
	float m_fFrequency, m_fHalfPeriod;
	Pin m_pBuzzerPin;
	
};

#endif