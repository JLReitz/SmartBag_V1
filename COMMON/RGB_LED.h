#ifndef RGB_LED_H
#define RGB_LED_H

#include "Arduino_Core.h"

class RGB_LED_H
{
public:

	RGB_LED(SINT08 nRedPin=-1, SINT08 nGreenPin=-1, SINT08 nBluePin=-1)
	{
		if((nRed > -1) && (nGreen > -1) && (nBlue > -1))
		{
			g_AssignPin(m_pRedPin, nRedPin, Pin::eDigital_PWM);
			g_AssignPin(m_pGreenPin, nGreenPin, Pin::eDigital_PWM);
			g_AssignPin(m_pBluePin, nBluePin, Pin::eDigital_PWM);
			
			m_pRedPin->m_Attach();
			m_pGreenPin->m_Attach();
			m_pBluePin->m_Attach();
		}
		else
		{
			m_pRedPin = NULL;
			m_pGreenPin = NULL;
			m_pBluePin = NULL;
		}
		
		m_nRedDuty = m_nGreenDuty = m_nBlueDuty = 0;
	}
	
	~RGB_LED()
	{
		if(m_pRedPin)
			g_DeassignPin(m_pRedPin->m_nPinNumber);
		if(m_pGreenPin)
			g_DeassignPin(m_pGreenPin->m_nPinNumber);
		if(m_pBluePin)
			g_DeassignPin(m_pBluePin->m_nPinNumber);
	}
	
	//Getters
	UINT08 m_get_RedDuty() { return m_nRedDuty; }
	UINT08 m_get_GreenDuty() { return m_nGreenDuty; }
	UINT08 m_get_BlueDuty() { return m_nBlueDuty; }
	
	//Setters
	void m_set_DutyCycle(UINT08 nRedDuty, UINT08 nGreenDuty, UINT08 nBlueDuty)
	{
		m_nRedDuty = (nRedDuty > 100) ? 100 : nRedDuty;
		m_nGreenDuty = (nGreenDuty > 100) ? 100 : nGreenDuty;
		m_nBlueDuty = (nBlueDuty > 100) ? 100 : nBlueDuty;
	}

	void m_set_Fadetime(UINT16 nFadeupTime, UINT16 nFadedownTime)
	{
		if(m_pRedPin)
			SoftPWMSetFadeTime(m_pRedPin->m_nPinNumber, nFadeupTime, nFadedownTime);
		if(m_pGreenPin)
			SoftPWMSetFadeTime(m_pGreenPin->m_nPinNumber, nFadeupTime, nFadedownTime);
		if(m_pBluePin)
			SoftPWMSetFadeTime(m_pBluePin->m_nPinNumber, nFadeupTime, nFadedownTime);
	}
	
	//Public Functions
	void m_ApplyOutput()
	{
		m_pRedPin->m_PinFunction(m_nRedDuty);
		m_mGreenPin->m_PinFunction(m_nGreenDuty);
		m_pBluePin->m_PinFunction(m_nBlueDuty);
	}

private:

	UINT08 m_nRedDuty, m_nGreenDuty, m_nBlueDuty;
	Pin * m_pRedPin, * m_pGreenPin, * m_pBluePin;

};

#endif