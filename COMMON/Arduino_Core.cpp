#include "Arduino_Core.h"


// Arduino-Specific Initialization ////////////////////////////////////////////////////////////////

#ifdef SQUAREWEAR_V2_ATMEGA328 //Initialization for the SquareWear V2.0
	
	void g_Arduino_Specific_Init()
	{
		//Configure the analog reference scale
		analogReference(DEFAULT);
		
		//Begin SoftPWM engine
		SoftPWMBegin();
	}

#endif

// Arduino-Generic Initialization /////////////////////////////////////////////////////////////////

void g_Arduino_Generic_Init()
{
	//Calls the Arduino-specific initialization defined above
	g_Arduino_Specific_Init();
}

// PinMatrix Member Functions /////////////////////////////////////////////////////////////////////

PinMatrix::PinMatrix()
{
	int i = 0;
		
	//Configure digital pins
	for(i; i<_PLATFORM_DIGITAL_PINMAX; i++)
	`	m_Matrix[i].reset(false, i, {PINCONFIG_T::eDIGITAL_CONFIG, PINMODE_T::eUNINITIALIZED});

	//Configure analog pins
	for(i; i<_PLATFORM_ANALOG_PINMAX; i++)
		m_Matrix[i].reset(false, i, {PINCONFIG_T::eANALOG_CONFIG, PINMODE_T::eUNINITIALIZED});
}
	
PinMatrix::~PinMatrix()
{
}

/**************************************************************************************************
Reserves and configures an open pin within the Arduino's pin array

	INPUT[Pin *] 		-	pPin
							Pointer to a Pin object that can be populated with the assigned pins data
	INPUT[PINMODE_T]	-	ePinMode
							The pin mode to configure the pin to
	OUTPUT[BOOLEAN]
					Returns true if the pin was properly configured, false if not
*/
static PinMatrix::BOOLEAN g_AssignPin(Pin * pPin, UINT08 nPin, PINMODE_T ePinMode)
{
	if(((ePinMode == PINMODE_T::eDIGITAL_IN) || (ePinMode == PINMODE_T::eDIGITAL_OUT) || (ePinMode == PINMODE_T::eDIGITAL_PWM)) 
		&& (m_Matrix[nPin].m_Get_PinConfig() == PINMODE_T::eDIGITAL_CONFIG))
	{
		//If the requested pin is of the correct configuration and also not reserved
		if(!m_Matrix[nPin].m_Get_Reserved())
		{
			//Set up the pin and reserve it within the Pin array
			m_Matrix[nPin].m_Reset(true, nPin, ePinMode);
			pPin = &m_Matrix[nPin];
			return true;
		}
	}
	else if(((ePinMode == PINMODE_T::eANALOG_IN) || (ePinMode == PINMODE_T::eANALOG_PWM))
	{
		//Need to calculate the location of the analog pin within the Pin Array
		UINT08 nAPin = g_Arduino_PinMax_Digital + nPin;
		
		if((g_pArduino_PinArray[nAPin].m_Get_PinConfig() == PINMODE_T::eANALOG_CONFIG) && (!g_pArduino_PinArray[nAPin].m_Get_Reserved()))
		{
			g_pArduino_PinArray[nAPin].m_Reset_Configuration(true, nAPin, ePinMode);
			pPin = &g_pArduino_PinArray[nAPin];
			return true;
		}
	}
	
	pPin = NULL;
	
	return false;
}

/**************************************************************************************************
Deassigns a pin within the Arduino's pin array

	- Internal pins cannot be reassigned or reconfigured after initialization

	INPUT[Pin *]	-	pPin
						Pointer to the pin that needs to be deassigned
	OUTPUT[BOOLEAN]
					Returns true if the pin was deassigned, false if not
*/
static PinMatrix::BOOLEAN g_DeassignPin(Pin * pPin)
{	
	if(pPin)
	{
		if(pPin->m_Get_PinConfig() != PINMODE_T::eINTERNAL_CONFIG)
		{
			//If the pin is configured for software PWM
			if(pPin->m_get_PinMode() == PINMODE_T::eDIGITAL_PWM)
				SoftPWMEnd(pPin->m_nPinNumber);
			
			//Reset the configuration of the pin and then return pPin as NULL (deassigned)
			pPin->m_Reset();
			pPin = NULL;
			return true;
		}
	}
	
	return false;
}