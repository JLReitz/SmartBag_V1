#ifndef TIMER_EVENT_PROFILE_H
#define TIMER_EVENT_PROFILE_H

#include "TimeProfile.h"

// Timer_Event_Profile Class //////////////////////////////////////////////////////////////////////

//Support Structs

typedef enum class Event_Occ_Mode_T
{
	ePeriodic	=	0,
	eOne_Shot	=	1,
	
};

//Class
class TimerEventProfile
{
public:

	TimerEventProfile();
	TimerEventProfile(const uint32_t nID = 0, const ClockProfile & cTrigger = 0, const ClockProfile & cTriggerDelay = 0,
						const Event_Occ_Mode_T & eOccuranceMode = Event_Occ_Mode_T::eOne_Shot);
	TimerEventProfile(const TimerEventProfile & tProfile);
	~TimerEventProfile();
	
	//Public Functions
	uint32_t Index()	{ return m_nIndex; }

	bool checkID(const uint32_t nCheck);	
	bool Triggered();	
	void updateProfile(const ClockProfile & cCurrent_Profile);
	
private:
	
	//Member Variables
	bool m_bTrigger;	//Flag for when the event should occur
	uint32_t m_nIndex;	//Index for identification by the object the event is tried to
	
	Event_Occ_Mode_T m_eOccuranceMode;				//Mode for the event's occurance behavior
	ClockProfile m_cNextTrigger, m_cTriggerDelay;	//Profile for when the next event should trigger
	ClockProfile m_cLastTrigger;					//Last trigger occurance
};

#endif