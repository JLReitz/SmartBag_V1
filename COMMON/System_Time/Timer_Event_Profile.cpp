#include "Timer_Event_Profile.h"

TimerEventProfile::TimerEventProfile()
{
	//Set the index for this profile
	m_nIndex = 0;

	m_eOccuranceMode = Event_Occ_Mode_T::eOne_Shot;
	m_cNextTrigger = ClockProfile(0);
	m_cTriggerDelay = ClockProfile(0);
	m_cLastTrigger = ClockProfile(0);

	//Clear the trigger
	m_bTrigger = false;
}

TimerEventProfile::TimerEventProfile(const uint32_t nID, const ClockProfile & cTrigger, const ClockProfile & cTriggerDelay, const Event_Occ_Mode_T & eOccuranceMode)
{
	//Set the index for this profile
	m_nIndex = nID;
	
	//Read in the clock profiles
	m_cNextTrigger = cTrigger;
	m_cLastTrigger = ClockProfile(0, cTrigger.TimeResolution());
	
	//Set the event trigger configurations
	m_eOccuranceMode = eOccuranceMode;
	
	//Set the time between each event if periodic
	if(m_eOccuranceMode == Event_Occ_Mode_T::ePeriodic)
		m_cTriggerDelay = cTriggerDelay;
	
	//Clear the trigger flag
	m_bTrigger = false;
}

TimerEventProfile::TimerEventProfile(const TimerEventProfile & tProfile)
{
	this->m_nIndex = tProfile.m_nIndex;
	this->m_bTrigger = tProfile.m_bTrigger;
	
	this->m_eOccuranceMode = tProfile.m_eOccuranceMode;
	
	this->m_cNextTrigger = tProfile.m_cNextTrigger;
	this->m_cLastTrigger = tProfile.m_cLastTrigger;
}

TimerEventProfile::~TimerEventProfile()
{
}

/**************************************************************************************************
		Checks the passed-in number with the event profile's ID
		
		INPUT[unsigned int]		--	nCheck
									The number with which to check the profile's ID.
		OUTPUT[boolean]		
						Returns TRUE if the number is identical to the profile's ID. FALSE if not.
*/
TimerEventProfile::bool checkID(const uint32_t nCheck)
{
	if(m_nIndex == nCheck)
		return true;
	else
		return false;
}

/**************************************************************************************************
		Checks the trigger flag for the next timed event. The flag will be cleared during this
		check, and is the only way to clear any triggered flag.
		
		OUTPUT[boolean]
						Returns TRUE if the event should occur, returns FALSE if not.
*/
TimerEventProfile::bool Triggered()
{
	bool bTemp = m_bTrigger;
	
	m_bTrigger = false;	//Clear the trigger flag
	
	return bTemp;
}

/**************************************************************************************************
		Updates the profile with new clock data and checks for an event trigger. If an event should
		occur, the trigger flag will be set. If the event is configured as periodic, the next
		trigger time will already be set
		
		INPUT[ClockProfile &]	--		cCurrent_Profile
										Data with which to update the profile with and determine
										whether an event should occur.
		OUTPUT[void]
*/
TimerEventProfile::void updateProfile(const ClockProfile & cCurrent_Profile)
{
	if(cCurrent_Profile >= m_cNextTrigger)
	{
		m_bTrigger = true;
		m_cLastTrigger = cCurrent_Profile;
		
		if(m_eOccuranceMode == ePeriodic)
			m_cNextTrigger = m_cNextTrigger + m_cTriggerDelay;
	}
}
