#ifndef PIN_H
#define PIN_H

#include <Arduino.h> //Include the proprietary Arduino library

//Structs **************************************************************************
typedef enum class PINMODE_T
{
	//Pin modes
	eDIGITAL_IN 			= 0x00, //Digital input
	eDIGITAL_OUT 			= 0x01, //Digital output
	eDIGITAL_PWM			= 0x02, //Digital pin that utilizes the SoftPWM library
	eANALOG_IN				= 0x03, //Analog input to the ADC
	eANALOG_PWM				= 0x04, //Digital pin that is PWM-enabled
	eUNINITIALIZED			= 0x05,
	
	ePINMODE_MAX			= 0x09
};

typedef enum class PINCONFIG_T
{
	//Default configuration for each pin
	eDIGITAL_CONFIG			= 0x0A,
	eANALOG_CONFIG			= 0x0B,
	eINTERNAL_CONFIG		= 0x0C,
	
	ePINCONFIG_MAX			= 0x0F
}

typedef struct PINTYPE_T
{
	PINMODE_T m_eMode;
	PINCONFIG_T m_eConfig;
};

// Classes *********************************************************************************************

class Pin
{
public:
	
	Pin(BOOLEAN bReserved=false, UINT08 nPinNumber=0, PINTYPE_T stPinType=0xFF)
	{
		m_bReserved = bReserved;
		m_nPinNumber = nPinNumber;
		m_stPinType = stPinType;
	}
	
	~Pin()
	{
	}
	
	//Getters
	BOOLEAN 	m_Get_Reserved() 	{ return m_bReserved; }
	UINT08 		m_Get_PinNumber() 	{ return m_nPinNumber; }
	PINCONFIG_T m_Get_PinConfig() 	{ return m_stPinType.m_eConfig; }
	PINMODE_T 	m_Get_PinMode() 	{ return m_stPinType.m_eMode; }
	
	//Setters
	void m_Reset(BOOLEAN bReserved=false, UINT08 nPin=0, PINMODE_T ePinMode=ePINMODE_MAX)
	{
		m_bReserved = bReserved;
		m_nPinNumber = nPin;
		m_stPinType.m_pMode = ePinMode;
	}
	
	//Public Functions
	/*
	Calls the necessary confguration protocols to confiure a digital pin for operation
	
		INPUT[N/A]		-	None
		OUTPUT[N/A]		-	None
	*/
	void m_Attach()
	{
		switch(m_Get_PinMode())
		{
		case PINMODE_T::eDIGITAL_IN:
		
			pinMode(m_nPinNumber, INPUT);
		
			break;
		case PINMODE_T::eDIGITAL_OUT:
		
			pinMode(m_nPinNumber, OUTPUT);
			
			break;
		case PINMODE_T::eDIGITAL_PWM:
			
			pinMode(m_nPinNumber, OUTPUT);
			SoftPWMSet(m_nPinNumber, 0);
		
			break;
		default:
		
			//Do nothing
			
			break;
		}
	}

	/*
	Performs the operable function of the pin based on its configured mode
	
		INPUT[BOOLEAN &]	-	bSet
								Referenced boolean that contains digital information -- true (HIGH) and
								false (LOW). If the pin is configured as eDIGITAL_IN, bSet will intrinsically
								return its read-in value. If the pin is eDIGITAL_OUT, bSet will serve as
								the value to be output.
		OUTPUT[N/A]			-	None
	*/
	void m_PinFunction(BOOLEAN & bSet)
	{
		switch(m_Get_PinMode())
		{
		case PINMODE_T::eDIGITAL_OUT:
			
			//Apply digital write to pin
			digitalWrite(m_nPinNumber, (bset) ? HIGH : LOW);
			
			break;
		case PINMODE_T::eDIGITAL_IN:
			
			//Read the digital state of the pin
			bSet = digitalRead(m_nPinNumber);
		
			break;
		default:
			
			//Do nothing. This is the default, unused mode of the pin
			
			break;
		}
	}

	/*
	Performs the operable function of the pin based on its configured mode
	
		INPUT[float &]		-	fValue
								Referenced float that contains analog information -- 0 - PLATFORM_MAX_VOLTAGE.
								If the pin is configured as eANALOG_IN, fValue will intrinsically return 
								the value returned from the ADC. If the pin is eDIGITAL_PWM, fValue will 
								set the duty cycle to be assigned to that pin. If the pin is eANALOG_PWM,
								fValue will set the voltage of the analog signal to be output.
		OUTPUT[N/A]			-	None
	*/
	void m_PinFunction(float & fValue)
	{
		switch(m_Get_PinMode())
		{
		case PINMODE_T::eDIGITAL_PWM:
		
			UINT08 nValue = (fValue > 100) 100 : ((fValue < 0) ? 0 : (UINT08)fValue);
			softPWMSetPercent(m_nPinNumber, fValue, false);
			
			break;
		case PINMODE_T::eANALOG_PWM:

			//Convert value that is in range of 0 - PLATFORM_MAX_VOLTAGE to 0 - 255 and write
			UINT08 nValue = (fValue > PLATFORM_MAX_VOLTAGE) ? PLATFORM_MAX_VOLTAGE : ((fValue < 0) ? 0 : (fValue/PLATFORM_MAX_VOLTAGE)*255);
			analogWrite(m_nPinNumber, nValue);
		
			break;
		case PINMODE_T::eANALOG_IN:
		
			//Read the analog voltage on the pin then convert it to range 0 - PLATFORM_MAX_VOLTAGE
			UINT08 nValue = analogRead(m_nPinNumber);
			fValue = (nValue/255) * PLATFORM_MAX_VOLTAGE;
		
			break;
		default:
			
			//Do nothing. This is the default, unused mode of the pin
			
			break;
		}
	}
	
private:

	BOOLEAN m_bReserved;
	UINT08 m_nPinNumber;
	PINTYPE_T m_stPinType;
};

#endif