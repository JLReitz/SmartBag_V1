#ifndef TIMER_H
#define TIMER_H

#include "Arduino_Core.h"

class Software_Timer
{
private:

	//Type Definitions
	typedef struct SoftTime_Profile_T
	{
		BOOLEAN m_bTriggered;					//Triggers event when true
		UINT32 m_nTrigger, m_nElapsedTime;		
		UINT32 m_nPrevTrigger, m_nPrevCheck;
		void * m_nIndex;					//Addr. of the object represented by the profile
	};

public:

	Timer()
	{
		m_nCurrentTime = m_nPreviousTime = 0;
		
		//Initialize timer profiles
		for(int i=0; i<g_nPinMax; i++)
		{
			m_tpProfiles[i].m_nIndex = 0;
			m_nTrigger = m_nElapsedTime = m_nPrevTrigger = m_nPrevCheck = 0;
			m_bTriggered = false;
		}
	}
	
	~Timer()
	{}
	
	//Accessors
	
	
	//Mutators
	
	void m_Update()
	{
		m_nCurrentTime_us = micros();
		m_nCurrentTime_ms = m_nCurrentTime_us * 1000;
		m_nCurrentTime_s = m_nCurrentTime_ms * 1000;
		
		for(int i=0; i<g_nPinMax; i++)
		{
			if((m_nCurrentTime_us - m_tpProfiles[i].m_nPrevTrigger) > m_tpProfiles[i].m_nTrigger)
				 m_tpProfiles[i].m_bTriggered = !m_tpProfiles[i].m_bTriggered;
		}
	}
	
	BOOLEAN m_Delete_Profile(void * const nIndex)
	{
		//Run through the profile array
		for(int i=0; i<g_nPinMax; i++)
		{
			if((DWORD *)nIndex == m_tpProfiles[i].m_nIndex) //If the indexes match
			{
				//Initialize this profile
				m_tpProfiles[i].m_nIndex = 0;
				m_nTrigger = m_nElapsedTime = m_nPrevTrigger = m_nPrevCheck = 0;
				m_bTriggered = false;
				
				return true;
			}
		}
		
		return false;
	}
	
	BOOLEAN m_Init_Profile(void * const nIndex, UINT32 nTrigger)
	{
		//Run through the profile array
		for(int i=0; i<g_nPinMax; i++)
		{
			if(!m_tpProfiles[i].m_nIndex) //If the index is null
			{
				//Configure this profile
				
				return true;
			}
			else if((DWORD *)nIndex == m_tpProfiles[i].m_nIndex) //If the indexes match
			{
				//Reconfigure this profile
				
				return true;
			}
		}
		
		return false;
	}
	
private:

	DWORD m_nCurrentTime_us, m_nCurrentTime_ms, m_nCurrentTime_s;
	TIMER_PROFILE_T m_tpProfiles[g_nPinMax];
	
};

#endif