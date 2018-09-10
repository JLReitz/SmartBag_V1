#ifndef ARDUINO_CORE_H
#define ARDUINO_CORE_H

// Platform Standards /////////////////
//#define NANO_ATMEGA328P
//#define UNO_ATMEGA328P
#define SQUAREWEAR_V2_ATMEGA328

// Platform Definitions ///////////////
#if defined(UNO_ATMEGA328P)
	#define PLATFORM_SPECIFIC_VOLTAGE_MAX	5
	#define PLATFORM_SPECIFIC_CLOCKSPEED 	1000000
#elif defined(NANO_ATMEGA328P)
	#define PLATFORM_SPECIFIC_VOLTAGE_MAX	3.3
	#define PLATFORM_SPECIFIC_CLOCKSPEED 	1000000
#elif defined(SQUAREWEAR_V2_ATMEGA328)
	#define PLATFORM_SPECIFIC_VOLTAGE_MAX	3.3
	#define PLATFORM_SPECIFIC_CLOCKSPEED 	1000000
#endif

#define PLATFORM_VOLTAGE_MAX 	PLATFORM_SPECIFIC_VOLTAGE_MAX
#define PLATFORM_CLOCKSPEED		PLATFORM_SPECIFIC_CLOCKSPEED

//Include the proprietary Arduino library
#include <Arduino.h>
#include <SoftPWM.h>


// Generic Types ///////////////////////////

typedef				 	bool	BOOLEAN;
typedef 	unsigned	char 	BYTE;
typedef 	unsigned 	short 	WORD;
typedef		unsigned 	long	DWORD;

// Integers -----------------------------------
typedef					int8_t 		SINT08;
typedef					int16_t 	SINT16;
typedef					int32_t 	SINT32;
typedef					uint8_t		UINT08;
typedef					uint16_t	UINT16;
typedef					uint32_t	UINT32;

// Structs /////////////////////////////////////////////////////////////////////////////////////////////

typedef enum PINMODE_T
{
	//Pin modes
	eDIGITAL_IN 			= 0xA0, //Digital input
	eDIGITAL_OUT 			= 0xA1, //Digital output
	eDIGITAL_PWM			= 0xA2, //Digital pin that utilizes the SoftPWM library
	eANALOG_IN				= 0xA3, //Analog input to the ADC
	eANALOG_PWM				= 0xA4, //Digital pin that is PWM-enabled
	eUNINITIALIZED			= 0xA5,
	
	//Default configuration for each pin
	eDIGITAL_CONFIG			= 0xAA,
	eANALOG_CONFIG			= 0xAB,
	eINTERNAL_CONFIG		= 0xAC,
	
	ePINMODE_MAX			= 0xAF
};

typedef struct PIN_CONFIG_T
{
	PINMODE_T m_pConfig 	: 	8;
	PINMODE_T m_pMode		:	8;
};

typedef struct Pin
{	
	BOOLEAN m_bReserved;
	UINT08 m_nPinNumber;
	PIN_CONFIG_T m_stPinConfig;
	
	//Getters
	BOOLEAN 	m_Get_Reserved() 	{ return m_bReserved; }
	UINT08 		m_Get_PinNumber() 	{ return m_nPinNumber; }
	PINMODE_T 	m_Get_PinConfig() 	{ return m_stPinConfig.m_pConfig; }
	PINMODE_T 	m_Get_PinMode() 	{ return m_stPinConfig.m_pMode; }
	
	//Setters
	void m_Reset_Configuration(BOOLEAN bReserved=false, UINT08 nPin=0, PINMODE_T ePinMode=ePINMODE_MAX)
	{
		m_bReserved = bReserved;
		m_nPinNumber = nPin;
		m_stPinConfig.m_pMode = ePinMode;
	}
	
	/*
	Calls the necessary confguration protocols to confiure a digital pin for operation
	
		INPUT[N/A]		-	None
		OUTPUT[N/A]		-	None
	*/
	void m_Attach()
	{
		switch(m_Get_PinMode())
		{
		case eDIGITAL_IN:
		
			pinMode(m_nPinNumber, INPUT);
		
			break;
		case eDIGITAL_OUT:
		
			pinMode(m_nPinNumber, OUTPUT);
			
			break;
		case eDIGITAL_PWM:
			
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
		case eDIGITAL_OUT:
			
			//Apply digital write to pin
			digitalWrite(m_nPinNumber, (bset) ? HIGH : LOW);
			
			break;
		case eDIGITAL_IN:
			
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
		case eDIGITAL_PWM:
		
			UINT08 nValue = (fValue > 100) 100 : ((fValue < 0) ? 0 : (UINT08)fValue);
			softPWMSetPercent(m_nPinNumber, fValue, false);
			
			break;
		case eANALOG_PWM:

			//Convert value that is in range of 0 - PLATFORM_MAX_VOLTAGE to 0 - 255 and write
			UINT08 nValue = (fValue > PLATFORM_MAX_VOLTAGE) ? PLATFORM_MAX_VOLTAGE : ((fValue < 0) ? 0 : (fValue/PLATFORM_MAX_VOLTAGE)*255);
			analogWrite(m_nPinNumber, nValue);
		
			break;
		case eANALOG_IN:
		
			//Read the analog voltage on the pin then convert it to range 0 - PLATFORM_MAX_VOLTAGE
			UINT08 nValue = analogRead(m_nPinNumber);
			fValue = (nValue/255) * PLATFORM_MAX_VOLTAGE;
		
			break;
		default:
			
			//Do nothing. This is the default, unused mode of the pin
			
			break;
		}
	}
};

// Arduino-Specific Initialization //////////////////////////////////////////////////////

	#ifdef SQUAREWEAR_V2_ATMEGA328 //Initialization for the SquareWear V2.0
	
	UINT08 g_nPinMax = 20, g_nArduinoPinMax_Digital = 13, g_nArduinoPinMax_Analog = 19;
	Pin g_pArduino_PinArray[g_nPinMax];
	
	void g_Arduino_Specific_Init()
	{
		//Assign g_pArduino_PinArray
		g_pArduino_PinArray =	{	{false, 	0,	{eDIGITAL_CONFIG, eUNINITIALIZED}},
									{false, 	1,	{eDIGITAL_CONFIG, eUNINITIALIZED}},
									{false, 	2,	{eDIGITAL_CONFIG, eUNINITIALIZED}},
									{false, 	3,	{eDIGITAL_CONFIG, eUNINITIALIZED}},
									{false, 	4,	{eDIGITAL_CONFIG, eUNINITIALIZED}},
									{false, 	5,	{eDIGITAL_CONFIG, eUNINITIALIZED}},
									{false, 	6,	{eDIGITAL_CONFIG, eUNINITIALIZED}},
									{false, 	7,	{eDIGITAL_CONFIG, eUNINITIALIZED}},
									{false, 	8,	{eDIGITAL_CONFIG, eUNINITIALIZED}},
									{false, 	9,	{eDIGITAL_CONFIG, eUNINITIALIZED}},
									{false, 	10,	{eDIGITAL_CONFIG, eUNINITIALIZED}},
									{false, 	11,	{eDIGITAL_CONFIG, eUNINITIALIZED}},
									{false, 	12,	{eDIGITAL_CONFIG, eUNINITIALIZED}},
									{false, 	13,	{eDIGITAL_CONFIG, eUNINITIALIZED}},
									{false, 	0,	{eANALOG_CONFIG, eUNINITIALIZED}},
									{false, 	1,	{eANALOG_CONFIG, eUNINITIALIZED}},
									{false, 	2,	{eANALOG_CONFIG, eUNINITIALIZED}},
									{false, 	3,	{eANALOG_CONFIG, eUNINITIALIZED}},
									{false, 	4,	{eANALOG_CONFIG, eUNINITIALIZED}},
									{false, 	5,	{eANALOG_CONFIG, eUNINITIALIZED}}	};
		
		//Configure the analog reference scale
		analogReference(DEFAULT);
		
		//Begin SoftPWM engine
		SoftPWMBegin();
	}

	#endif

// Arduino-Generic Initialization /////////////////////////////////////////////

void g_Arduino_Generic_Init()
{
	//Calls the Arduino-specific initialization defined above
	g_Arduino_Specific_Init();
}

// Core Functions ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
Reserves and configures an open pin within the Arduino's pin array

	INPUT[Pin *] 		-	pPin
							Pointer to a Pin object that can be populated with the assigned pins data
	INPUT[PINMODE_T]	-	ePinMode
							The pin mode to configure the pin to
	OUTPUT[BOOLEAN]
					Returns true if the pin was properly configured, false if not
*/
BOOLEAN g_AssignPin(Pin * pPin, UINT08 nPin, PINMODE_T ePinMode)
{
	if(((ePinMode == eDIGITAL_IN) || (ePinMode == eDIGITAL_OUT) || (ePinMode == eDIGITAL_PWM)) 
		&& (g_pArduino_PinArray[nPin].m_Get_PinConfig() == eDIGITAL_CONFIG))
	{
		//If the requested pin is of the correct configuration and also not reserved
		if(!g_pArduino_PinArray[nPin].m_Get_Reserved())
		{
			//Set up the pin and reserve it within the Pin array
			g_pArduino_PinArray[nPin].m_Reset_Configuration(true, nPin, ePinMode);
			pPin = &g_pArduino_PinArray[nPin];
			return true;
		}
	}
	else if(((ePinMode == eANALOG_IN) || (ePinMode == eANALOG_PWM))
	{
		//Need to calculate the location of the analog pin within the Pin Array
		UINT08 nAPin = g_Arduino_PinMax_Digital + nPin;
		
		if((g_pArduino_PinArray[nAPin].m_Get_PinConfig() == eANALOG_CONFIG) && (!g_pArduino_PinArray[nAPin].m_Get_Reserved()))
		{
			g_pArduino_PinArray[nAPin].m_Reset_Configuration(true, nAPin, ePinMode);
			pPin = &g_pArduino_PinArray[nAPin];
			return true;
		}
	}
	
	pPin = NULL;
	
	return false;
}

/*
Deassigns a pin within the Arduino's pin array

	- Internal pins cannot be reassigned or reconfigured after initialization

	INPUT[Pin *]	-	pPin
						Pointer to the pin that needs to be deassigned
	OUTPUT[BOOLEAN]
					Returns true if the pin was deassigned, false if not
*/
BOOLEAN g_DeassignPin(Pin * pPin)
{	
	if(pPin)
	{
		if(pPin->m_Get_PinConfig() != eINTERNAL_CONFIG)
		{
			//If the pin is configured for software PWM
			if(pPin->m_get_PinMode() == eDIGITAL_PWM)
				SoftPWMEnd(pPin->m_nPinNumber);
			
			//Reset the configuration of the pin and then return pPin as NULL (deassigned)
			pPin->m_Reset_Configuration();
			pPin = NULL;
			return true;
		}
	}
	
	return false;
}

#endif