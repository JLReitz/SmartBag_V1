#ifndef TIMER_H
#define TIMER_H

#include "Arduino_Core.h"

class Timer
{
private:

	//Type Definitions
	typedef enum TIMER_MAGNITUDE_T
	{
	};

	typedef struct TIMER_PROFILE_T
	{
		BOOLEAN m_bTriggered;
		DWORD m_dwTime_LastTriggered, m_dwTime_LastChecked, m_dwTriggerTime;
	}

public:

	Timer()
	{}
	
	~Timer()
	{}
	
	//Accessors
	
	
	//Mutators
	BOOLEAN m_Init_Profile(UINT08 nID, DWORD dwTrigger)
	
private:

	DWORD m_dwCurrentTime;
	TIMER_PROFILE_T m_tpProfiles[g_nPinMax];
	
};

#endif