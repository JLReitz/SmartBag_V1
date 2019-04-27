#include "TimeProfile.h"

// TimeProfile Functions //////////////////////////////////////////////////////////////////////////

TimeProfile::TimeProfile(const uint32_t nNewData)
{
	m_nTimeData = nNewData;
}

TimeProfile::TimeProfile(const TimeProfile & T)
{
	this->m_nTimeData = T.m_nTimeData;
}

TimeProfile::~TimeProfile()
{
}

bool TimeProfile::operator ! ()
{
	return !m_nTimeData;
}

bool TimeProfile::operator > (const TimeProfile & T)
{
	return (this->m_nTimeData > T.m_nTimeData);
}

bool TimeProfile::operator < (const TimeProfile & T)
{
	return (this->m_nTimeData < T.m_nTimeData);
}

bool TimeProfile::operator >= (const TimeProfile & T)
{
	return (this->m_nTimeData >= T.m_nTimeData);
}

bool TimeProfile::operator <= (const TimeProfile & T)
{
	return (this->m_nTimeData <= T.m_nTimeData);
}

bool TimeProfile::operator == (const TimeProfile & T)
{
	return (this->m_nTimeData == T.m_nTimeData);
}

bool TimeProfile::operator != (const TimeProfile & T)
{
	return (this->m_nTimeData != T.m_nTimeData);
}

void TimeProfile::operator = (const uint32_t N)
{
	m_nTimeData = N;
}

void TimeProfile::operator = (const TimeProfile & T)
{
	this->m_nTimeData = T.m_nTimeData;
}

TimeProfile TimeProfile::operator + (const TimeProfile & T)
{
	TimeProfile tSumProfile(this->m_nTimeData + T.m_nTimeData);
	
	return tSumProfile;
}

TimeProfile TimeProfile::operator - (const TimeProfile & T)
{
	TimeProfile tSumProfile(this->m_nTimeData - T.m_nTimeData);
	
	return tSumProfile;
}

TimeProfile TimeProfile::operator * (const uint32_t nScalar)
{
	TimeProfile tProductProfile(this->m_nTimeData * nScalar);
	
	return tProductProfile;
}

TimeProfile TimeProfile::operator / (const uint32_t nScalar)
{
	TimeProfile tProductProfile(this->m_nTimeData / nScalar);
	
	return tProductProfile;
}

TimeProfile TimeProfile::operator % (const uint32_t nScalar)
{
	TimeProfile tModProfile(this->m_nTimeData % nScalar);
	
	return tModProfile;
}

// ClockProfile Functions /////////////////////////////////////////////////////////////////////////

ClockProfile::ClockProfile(const float fNewData, const Time_Resolution_T & eResolution)
{
	uint32_t nMicros = 0, nMillis = 0, nSecs = 0, nMins = 0, nHours = 0, nDays = 0;
	float fRemainder = fNewData;
	
	//Adjust time recorded to the proper resolution
	switch(eResolution)
	{
	case Time_Resolution_T::eDays:
		
		nSecs = (uint32_t)fRemainder;									//Store the integer component
		fRemainder = (fRemainder - m_tMilliseconds.TimeData()) * 24;	//Determine the remainder and prepare for next step to hours
		
		//No break, continue	
	
	case Time_Resolution_T::eHours:
		
		nSecs = (uint32_t)fRemainder;									//Store the integer component
		fRemainder = (fRemainder - m_tMilliseconds.TimeData()) * 60;	//Determine the remainder and prepare for next step to minutes
		
		//No break, continue	
	
	case Time_Resolution_T::eMinutes:
		
		nSecs = (uint32_t)fRemainder;									//Store the integer component
		fRemainder = (fRemainder - m_tMilliseconds.TimeData()) * 60;	//Determine the remainder and prepare for next step to seconds
		
		//No break, continue
		
	case Time_Resolution_T::eSeconds:
		
		nSecs = (uint32_t)fRemainder;									//Store the integer component
		fRemainder = (fRemainder - m_tMilliseconds.TimeData()) * 1000;	//Determine the remainder and prepare for next step to millis
		
		//No break, continue
		
	case Time_Resolution_T::eMillis:
		
		nMillis = (uint32_t)fRemainder;									//Store the integer component
		fRemainder = (fRemainder - m_tMilliseconds.TimeData()) * 1000;	//Determine the remainder and prepare for next step to micros
		
		//No break, continue
		
	case Time_Resolution_T::eMicros:
		
		nMicros = (uint32_t)fRemainder;
		
		break;
	}
	
	m_eResolution = eResolution;
	m_tMicroseconds = nMicros;
	m_tMilliseconds = nMillis;
	m_tSeconds = nSecs;
	m_tMinutes = nMins;
	m_tHours = nHours;
	m_tDays = nDays;
}

ClockProfile::ClockProfile(const TimeProfile & tNewProfile , const Time_Resolution_T & eResolution)
{
	uint32_t nNewProfileData = tNewProfile.TimeData;
	
	ClockProfile(nNewProfileData, eResolution);
}

ClockProfile::ClockProfile(const ClockProfile & C)
{
	this->m_eResolution = C.m_eResolution;
	this->m_tMicroseconds = C.m_tMicroseconds;
	this->m_tMilliseconds = C.m_tMilliseconds;
	this->m_tSeconds = C.m_tSeconds;
	this->m_tMinutes = C.m_tMinutes;
	this->m_tHours = C.m_tHours;
	this->m_tDays = C.m_tDays;
}

bool ClockProfile::operator ! ()
{
	return (!m_tMicroseconds && !m_tMilliseconds && !m_tSeconds && !m_tMinutes && !m_tHours && !m_tDays);
}

bool ClockProfile::operator > (const ClockProfile & C)
{
	if(this->m_tMicroseconds <= C.m_tMicroseconds)
		return false;
	if(this->m_tMilliseconds <= C.m_tMilliseconds)
		return false;
	if(this->m_tSeconds <= C.m_tSeconds)
		return false;
	if(this->m_tMinutes <= C.m_tMinutes)
		return false;
	if(this->m_tHours <= C.m_tHours)
		return false;
	if(this->m_tDays <= C.m_tDays)
		return false;
	
	return true;
}

bool ClockProfile::operator < (const ClockProfile & C)
{
	if(this->m_tMicroseconds >= C.m_tMicroseconds)
		return false;
	if(this->m_tMilliseconds >= C.m_tMilliseconds)
		return false;
	if(this->m_tSeconds >= C.m_tSeconds)
		return false;
	if(this->m_tMinutes >= C.m_tMinutes)
		return false;
	if(this->m_tHours >= C.m_tHours)
		return false;
	if(this->m_tDays >= C.m_tDays)
		return false;
	
	return true;
}

bool ClockProfile::operator >= (const ClockProfile & C)
{
	return ((*this > C) && (*this == C));
}

bool ClockProfile::operator <= (const ClockProfile & C)
{
	return ((*this < C) && (*this == C));
}

bool ClockProfile::operator == (const ClockProfile & C)
{
	if(this->m_tMicroseconds != C.m_tMicroseconds)
		return false;
	if(this->m_tMilliseconds != C.m_tMilliseconds)
		return false;
	if(this->m_tSeconds != C.m_tSeconds)
		return false;
	if(this->m_tMinutes != C.m_tMinutes)
		return false;
	if(this->m_tHours != C.m_tHours)
		return false;
	if(this->m_tDays != C.m_tDays)
		return false;
	
	return true;
}

void ClockProfile::operator = (const uint32_t N)
{
	switch(m_eResolution)
	{
	case Time_Resolution_T::eMicros:

		m_tMicroseconds = N;
		break;
	case Time_Resolution_T::eMillis:

		m_tMilliseconds = N;
		break;
	case Time_Resolution_T::eSeconds:

		m_tSeconds = N;
		break;
	case Time_Resolution_T::eMinutes:

		m_tMinutes = N;
		break;
	case Time_Resolution_T::eHours:

		m_tHours = N;
		break;

	case Time_Resolution_T::eDays:

		m_tHours = N;
		break;
	}
}

void ClockProfile::operator = (const ClockProfile & C)
{
	this->m_eResolution = C.m_eResolution;
	this->m_tMicroseconds = C.m_tMicroseconds;
	this->m_tMilliseconds = C.m_tMilliseconds;
	this->m_tSeconds = C.m_tSeconds;
	this->m_tMinutes = C.m_tMinutes;
	this->m_tHours = C.m_tHours;
	this->m_tDays = C.m_tDays;
}

ClockProfile ClockProfile::operator + (const ClockProfile & C)
{
	uint32_t nCarryover = 0;
	ClockProfile cSumProfile(0, C.m_eResolution);
	
	//Add microseconds
	cSumProfile.m_tMicroseconds = this->m_tMicroseconds + C.m_tMicroseconds;
	if(cSumProfile.m_tMicroseconds.TimeData() >= 1000)
	{
		//Assign the carryover and decrease micros to under 1000
		nCarryover = cSumProfile.m_tMicroseconds.TimeData() / 1000;
		cSumProfile.m_tMicroseconds = cSumProfile.m_tMicroseconds % 1000;
	}
	
	//Add milliseconds
	cSumProfile.m_tMilliseconds = this->m_tMilliseconds + C.m_tMilliseconds + nCarryover;
	if(cSumProfile.m_tMilliseconds.TimeData() >= 1000)
	{
		//Assign the carryover and decrease micros to under 1000
		nCarryover = cSumProfile.m_tMilliseconds.TimeData() / 1000;
		cSumProfile.m_tMilliseconds = cSumProfile.m_tMilliseconds % 1000;
	}
	
	//Add seconds
	cSumProfile.m_tSeconds = this->m_tSeconds + C.m_tSeconds + nCarryover;
	if(cSumProfile.m_tSeconds.TimeData() >= 60)
	{
		//Assign the carryover and decrease micros to under 60
		nCarryover = cSumProfile.m_tSeconds.TimeData() / 60;
		cSumProfile.m_tSeconds = cSumProfile.m_tSeconds % 60;
	}
	
	//Add minutes
	cSumProfile.m_tMinutes = this->m_tMinutes + C.m_tMinutes + nCarryover;
	if(cSumProfile.m_tMinutes.TimeData() >= 60)
	{
		//Assign the carryover and decrease micros to under 60
		nCarryover = cSumProfile.m_tMinutes.TimeData() / 60;
		cSumProfile.m_tMinutes = cSumProfile.m_tMinutes % 60;
	}
	
	//Add hours
	cSumProfile.m_tHours = this->m_tHours + C.m_tHours + nCarryover;
	if(cSumProfile.m_tHours.TimeData() >= 24)
	{
		//Assign the carryover and decrease micros to under 24
		nCarryover = cSumProfile.m_tHours.TimeData() / 24;
		cSumProfile.m_tHours = cSumProfile.m_tHours % 24;
	}
	
	//Add days
	cSumProfile.m_tDays = this->m_tDays + C.m_tDays + nCarryover;
	
	return cSumProfile;
}

ClockProfile ClockProfile::operator - (const ClockProfile & C)
{
	long nSum, nCarryover = 0; //No longer unsigned
	ClockProfile cSumProfile(0, this->m_eResolution);
	
	//Subtract microseconds
	nSum = this->m_tMicroseconds.TimeData() - C.m_tMicroseconds.TimeData();
	if(nSum < 0)
	{
		//Use carryover to decrease the next value by 1 and set nSum to a value between 0 and 1000
		nCarryover = 1;
		nSum += 1000;
	}
	
	cSumProfile.m_tMicroseconds = nSum;
	
	//Subtract milliseconds
	nSum = this->m_tMilliseconds.TimeData() - C.m_tMilliseconds.TimeData() - nCarryover;
	if(nSum < 0)
	{
		//Use carryover to decrease the next value by 1 and set nSum to a value between 0 and 1000
		nCarryover = 1;
		nSum += 1000;
	}
	else
		nCarryover = 0;
	
	
	cSumProfile.m_tMilliseconds = nSum;
	
	//Subtract seconds
	nSum = this->m_tSeconds.TimeData() - C.m_tSeconds.TimeData() - nCarryover;
	if(nSum < 0)
	{
		//Use carryover to decrease the next value by 1 and set nSum to a value between 0 and 60
		nCarryover = 1;
		nSum += 60;
	}
	else
		nCarryover = 0;
	
	cSumProfile.m_tSeconds = nSum;
	
	//Subtract minutes
	nSum = this->m_tMinutes.TimeData() - C.m_tMinutes.TimeData() - nCarryover;
	if(nSum < 0)
	{
		//Use carryover to decrease the next value by 1 and set nSum to a value between 0 and 60
		nCarryover = 1;
		nSum += 60;
	}
	else
		nCarryover = 0;
	
	cSumProfile.m_tMinutes = nSum;
	
	//Subtract hours
	nSum = this->m_tHours.TimeData() - C.m_tHours.TimeData() - nCarryover;
	if(nSum < 0)
	{
		//Use carryover to decrease the next value by 1 and set nSum to a value between 0 and 24
		nCarryover = 1;
		nSum += 24;
	}
	else
		nCarryover = 0;
	
	cSumProfile.m_tHours = nSum;
	
	//Subtract days
	nSum = this->m_tDays.TimeData() - C.m_tDays.TimeData() - nCarryover;
	if(nSum < 0)
		cSumProfile = ClockProfile(0, this->m_eResolution); //If the largest order of magnitude is negative, set the whole profile to 0
	else
		cSumProfile.m_tDays = nSum;
	
	return cSumProfile;
}

ClockProfile ClockProfile::operator * (const uint32_t nScalar)
{
	uint32_t nCarryover = 0;
	ClockProfile cSumProfile(0, m_eResolution);
	
	//Multiply microseconds
	cSumProfile.m_tMicroseconds = m_tMicroseconds * nScalar;
	if(cSumProfile.m_tMicroseconds.TimeData() >= 1000)
	{
		//Assign the carryover and decrease micros to under 1000
		nCarryover = cSumProfile.m_tMicroseconds.TimeData() / 1000;
		cSumProfile.m_tMicroseconds = cSumProfile.m_tMicroseconds % 1000;
	}
	
	//Multiply milliseconds
	cSumProfile.m_tMilliseconds = m_tMilliseconds * nScalar + nCarryover;
	if(cSumProfile.m_tMilliseconds.TimeData() >= 1000)
	{
		//Assign the carryover and decrease micros to under 1000
		nCarryover = cSumProfile.m_tMilliseconds.TimeData() / 1000;
		cSumProfile.m_tMilliseconds = cSumProfile.m_tMilliseconds % 1000;
	}
	
	//Multiply seconds
	cSumProfile.m_tSeconds = m_tSeconds * nScalar + nCarryover;
	if(cSumProfile.m_tSeconds.TimeData() >= 60)
	{
		//Assign the carryover and decrease micros to under 60
		nCarryover = cSumProfile.m_tSeconds.TimeData() / 60;
		cSumProfile.m_tSeconds = cSumProfile.m_tSeconds % 60;
	}
	
	//Multiply minutes
	cSumProfile.m_tMinutes = m_tMinutes * nScalar + nCarryover;
	if(cSumProfile.m_tMinutes.TimeData() >= 60)
	{
		//Assign the carryover and decrease micros to under 60
		nCarryover = cSumProfile.m_tMinutes.TimeData() / 60;
		cSumProfile.m_tMinutes = cSumProfile.m_tMinutes % 60;
	}
	
	//Multiply hours
	cSumProfile.m_tHours = m_tHours * nScalar + nCarryover;
	if(cSumProfile.m_tHours.TimeData() >= 24)
	{
		//Assign the carryover and decrease micros to under 24
		nCarryover = cSumProfile.m_tHours.TimeData() / 24;
		cSumProfile.m_tHours = cSumProfile.m_tHours % 24;
	}
	
	//Multiply days
	cSumProfile.m_tDays = this->m_tDays * nScalar + nCarryover;
	
	return cSumProfile;
}

ClockProfile ClockProfile::operator / (const uint32_t nScalar)
{
	ClockProfile cSumProfile(0, m_eResolution);
	
	//Divide microseconds
	cSumProfile.m_tMicroseconds = m_tMicroseconds / nScalar;
	
	//Divide milliseconds
	cSumProfile.m_tMilliseconds = m_tMilliseconds / nScalar;
	
	//Divide seconds
	cSumProfile.m_tSeconds = m_tSeconds / nScalar;
	
	//Divide minutes
	cSumProfile.m_tMinutes = m_tMinutes / nScalar;
	
	//Divide hours
	cSumProfile.m_tHours = m_tHours / nScalar;
	
	//Divide days
	cSumProfile.m_tDays = m_tDays / nScalar;
	
	return cSumProfile;
}
