#ifndef SOFT_H
#define SOFT_H

#include "Timer_Event_Profile.h"

// SofT Class /////////////////////////////////////////////////////////////////////////////////////

class SofT
{
public:
	
	SofT(const Time_Resolution_T eResolution = Time_Resolution_T::eMillis);
	~SofT();
	
	//Public Functions
	void update(const ClockProfile & cUpdate);

	bool addEvent(const uint32_t nID, const ClockProfile & cTrigger_Time, const ClockProfile & cTrigger_Delay = 0);
	bool deleteEvent(const uint32_t nID);	
	bool checkEvent(const uint32_t nID);

private:
	
	void updateProfiles();
	
	//Member variables
	ClockProfile m_cCurrentTime, m_cElapsedTime, m_cLastUpdated;
	
	TimerEventProfile m_tEventArray[64];
	
};

#endif
