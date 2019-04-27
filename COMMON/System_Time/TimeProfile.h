#ifndef TIMEPROFILE_H
#define TIMEPROFILE_H

#include "typedef.h"

// Time Profile Class /////////////////////////////////////////////////////////////////////////////

class TimeProfile
{
public:
	
	TimeProfile(const uint32_t nNewData = 0);
	TimeProfile(const TimeProfile & T);
	~TimeProfile();
	
	//Public Functions
	uint32_t TimeData()	const { return m_nTimeData; }
	
	//Operator Overloads
	bool operator !	();
	
	bool operator >	(const TimeProfile & T);
	bool operator <	(const TimeProfile & T);
	bool operator >= (const TimeProfile & T);
	bool operator <= (const TimeProfile & T);
	bool operator == (const TimeProfile & T);
	bool operator != (const TimeProfile & T);
	
	void operator = (const uint32_t N);
	void operator = (const TimeProfile & T);
	
	TimeProfile operator + 	(const TimeProfile & T);
	TimeProfile operator - 	(const TimeProfile & T);
	TimeProfile operator * 	(const uint32_t nScalar);
	TimeProfile operator / 	(const uint32_t nScalar);
	TimeProfile operator % 	(const uint32_t nScalar);

private:
	
	uint32_t m_nTimeData;
};

// Clock Profile Class ////////////////////////////////////////////////////////////////////////////

//Support Structs
typedef enum class Time_Resolution_T
{
	eMicros		=	-6,
	eMillis		=	-3,
	eSeconds	=	0,
	eMinutes	=	1,
	eHours		=	2,
	eDays		=	3
	
};

//Class
class ClockProfile
{
public:

	ClockProfile(const float fNewData = 0, const Time_Resolution_T & eResolution = Time_Resolution_T::eSeconds);
	ClockProfile(const TimeProfile & tNewProfile , const Time_Resolution_T & eResolution);
	ClockProfile(const ClockProfile & C);
	
	//Public Functions
	uint32_t nMicroseconds() const	{ return m_tMicroseconds.TimeData(); }
	uint32_t nMilliseconds() const	{ return m_tMilliseconds.TimeData(); }
	uint32_t nSeconds()	const		{ return m_tSeconds.TimeData(); }
	uint32_t nMinutes() const		{ return m_tMinutes.TimeData(); }
	uint32_t nHours() const			{ return m_tHours.TimeData(); }
	uint32_t nDays() const			{ return m_tDays.TimeData(); }

	Time_Resolution_T TimeResolution() const	{ return m_eResolution; }
	TimeProfile tMicroseconds() const			{ return m_tMicroseconds; }
	TimeProfile tMilliseconds() const			{ return m_tMilliseconds; }
	TimeProfile tSeconds() const				{ return m_tSeconds; }
	TimeProfile tMinutes() const				{ return m_tMinutes; }
	TimeProfile tHours() const					{ return m_tHours; }
	TimeProfile tDays() const					{ return m_tDays; }
	
	//Operator Overloads
	bool operator !	();
	
	bool operator >	(const ClockProfile & C);
	bool operator <	(const ClockProfile & C);
	bool operator >= (const ClockProfile & C);
	bool operator <= (const ClockProfile & C);
	bool operator == (const ClockProfile & C);
	
	void operator =	(const uint32_t N);
	void operator = (const ClockProfile & C);
	
	ClockProfile operator + (const ClockProfile & C);
	ClockProfile operator - (const ClockProfile & C);
	ClockProfile operator * (const uint32_t nScalar);
	ClockProfile operator / (const uint32_t nScalar);

private:

	Time_Resolution_T m_eResolution;
	TimeProfile m_tMicroseconds, m_tMilliseconds, m_tSeconds;
	TimeProfile m_tMinutes, m_tHours, m_tDays;
	
};

#endif