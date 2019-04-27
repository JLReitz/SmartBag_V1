#include "SofT.h"

SofT::SofT(const Time_Resolution_T eResolution)
{
    //Configure timer clock profiles and initialize to time 0
    m_cCurrentTime = ClockProfile(0, eResolution);
    m_cElapsedTime = ClockProfile(0, eResolution);
    m_cLastUpdated = ClockProfile(0, eResolution);

    //TimerEvenProfiles should already be initialized and ready for assignment
}

~SofT()
{

}

SofT::bool addEvent(const uint32_t nID, const ClockProfile & cTrigger_Time, const ClockProfile & cTrigger_Delay)
{
    //Look through the event array for an unassigned slot
    for(int i=0; i<64; i++)
    {
        if(!m_tEventArray[i].Index()) //If slot is currently unassigned
        {
            //Check for a trigger delay
            if(!cTrigger_Delay)
            {
                //One Shot config
                m_tEventArray[i] = TimerEventProfile(nID, cTrigger_Time, m_cCurrentTime, cTrigger_Delay, Event_Occ_Mode_T::eOne_Shot);
            }
            else
            {
                //Periodic config
                m_tEventArray[i] = TimerEventProfile(nID, cTrigger_Time, m_cCurrentTime, cTrigger_Delay, Event_Occ_Mode_T::ePeriodic);
            }

            return true;
        }
    }

    return false;
}

SofT::bool deleteEvent(const uint32_t nID)
{
    //Look through the event array for the correct profile
    for(int i=0; i<64; i++)
    {
        if(m_tEventArray[i].checkID(nID))
        {
            m_tEventArray[i] = TimerEventProfile();
            return true;
        }
    }

    return false;
}

SofT::void update(const ClockProfile & cUpdate)
{
    m_cCurrentTime = cUpdate;
    m_cElapsedTime = m_cCurrentTime - m_cLastUpdated;
    m_cLastUpdated = m_cCurrentTime;

    updateProfiles();
}
	
SofT::bool checkEvent(const uint32_t nID)
{
    //Loop througb the event array for the correct profile
    for(int i=0; i<64; i++)
    {
        if(m_tEventArray[i].checkID(nID))
            return m_tEventArray[i].Triggered();
    }
}

SofT::void updateProfiles()
{
    //Loop through the profiles
    for(int i=0; i<64; i++)
        m_tEventArray[i].updateProfile(m_cCurrentTime);
}