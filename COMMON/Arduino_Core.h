#ifndef ARDUINO_CORE_H
#define ARDUINO_CORE_H

#include "System_Time/SofT.h"

// Preprocessor Directives ////////////////////////////////////////////////////////////////////////

//#define _NANO_ATMEGA328P
//#define _UNO_ATMEGA328P
#define _SQUAREWEAR_V2_ATMEGA328

// Preprocessor Directives
//Platform Specifics
#if defined(_UNO_ATMEGA328P)

	#define _PLATFORM_SPECIFIC_VOLTAGE_MAX	5
	#define _PLATFORM_SPECIFIC_CLOCKSPEED 	1000000
	
#elif defined(_NANO_ATMEGA328P)

	#define _PLATFORM_SPECIFIC_VOLTAGE_MAX	3.3
	#define _PLATFORM_SPECIFIC_CLOCKSPEED 	1000000
	
#elif defined(_SQUAREWEAR_V2_ATMEGA328)

	#define _PLATFORM_SPECIFIC_VOLTAGE_MAX	3.3
	#define _PLATFORM_SPECIFIC_CLOCKSPEED 	1000000
	
	#define _PLATFORM_SPECIFIC_PIN_MAX			20
	#define _PLATFORM_SPECIFIC_DIGITAL_PINMAX	13
	#define _PLATFORM_SPECIFIC_ANALOG_PINMAX	19
	
#endif


//Platform generics
#define _PLATFORM_VOLTAGE_MAX 		_PLATFORM_SPECIFIC_VOLTAGE_MAX

#define _PLATFORM_CLOCKSPEED		_PLATFORM_SPECIFIC_CLOCKSPEED

#define _PLATFORM_PINMAX			_PLATFORM_SPECIFIC_PIN_MAX
#define _PLATFORM_DIGITAL_PINMAX	_PLATFORM_SPECIFIC_DIGITAL_PINMAX
#define _PLATFORM_ANALOG_PINMAX		_PLATFORM_SPECIFIC_ANALOG_PINMAX

// Structs and Enumerated Types ///////////////////////////////////////////////////////////////////

typedef enum class System_Status_T
{

};

// Classes ////////////////////////////////////////////////////////////////////////////////////////

class System
{
public:

	System()	{}
	~System()	{}

	//Public Functions
	static void update();
	
	static System_Status_T addTimerEvent(const uint32_t nID, const ClockProfile & cTrigger_Time, const ClockProfile & cTrigger_Delay = 0);
	static System_Status_T deleteTimerEvent(const uint32_t nID);
	static System_Status_T checkEventTrigger(const uint32_t nID);

	static System_Status_T connectPin();
	static System_Status_T disconnectPin();

private:

	static SofT sTimer;

};

class PinMatrix
{
public:

	PinMatrix();
	
	~PinMatrix();
	
	// Public Functions -------------------------------------------------------
	
	static BOOLEAN g_AssignPin(Pin * pPin, UINT08 nPin, PINMODE_T ePinMode);
	/*----------------------------------------------------------------------
	Reserves and configures an open pin within the Arduino's pin array

	INPUT[Pin *] 		-	pPin
							Pointer to a Pin object that can be populated with the assigned pins data
	INPUT[PINMODE_T]	-	ePinMode
							The pin mode to configure the pin to
	OUTPUT[BOOLEAN]
						Returns true if the pin was properly configured, false if not
	*/
	
	static PinMatrix::BOOLEAN g_DeassignPin(Pin * pPin);
	/*--------------------------------------------------
	Deassigns a pin within the Arduino's pin array

		- Internal pins cannot be reassigned or reconfigured after initialization

		INPUT[Pin *]	-	pPin
							Pointer to the pin that needs to be deassigned
		OUTPUT[BOOLEAN]
							Returns true if the pin was deassigned, false if not
	*/
	
private:
	
	static Pin m_Matrix[PLATFORM_PINMAX];
};

#endif