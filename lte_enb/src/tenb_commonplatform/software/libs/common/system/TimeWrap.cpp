///////////////////////////////////////////////////////////////////////////////
//
// TimeWrap.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include <stdio.h>
#include <sys/time.h>

#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "TimeWrap.h"

using namespace std;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

TimeWrap::TimeWrap (time_t unixTime) :
    m_theTimeAsSafeFileName()
{
    ENTER();

    // We have an admitted problem here: since we archive time_t
    // objects we lose the microseconds, but is this a big deal?  I think
    // it's more important that the time detail is available to the
    // debug output only (i.e. it _doesn't_ matter).
    Set(unixTime, 0);

    EXIT();
}

TimeWrap::TimeWrap () :
    m_theTimeAsSafeFileName()
{
    ENTER();

	// Default constructor will use the current time.
	Touch ();

	EXIT();
}

TimeWrap::~TimeWrap ()
{
    ENTER();

    EXIT();
}

void TimeWrap::Set(time_t unixTime, u32 microSecs)
{
    ENTER();

    struct tm *tmVal = gmtime (&unixTime); // gmtime works in UTC.

    if(tmVal)
    {
        m_theTime.theDay = tmVal->tm_mday;
        m_theTime.theMonth = tmVal->tm_mon + 1;
        m_theTime.theYear = tmVal->tm_year + 1900;

        m_theTime.theHour = tmVal->tm_hour;
        m_theTime.theMinutes = tmVal->tm_min;
        m_theTime.theSeconds = tmVal->tm_sec;
    }
    else
    {
        memset ((void*)(&m_theTime), 0, sizeof (m_theTime));
    }

    m_theTime.theUSeconds = microSecs;

    EXIT();
}

void TimeWrap::Set( const char *dateAndTimeAsString)
{
    ENTER();
    
    struct tm timeStruct;
    memset((void*)&timeStruct, 0, sizeof(timeStruct));
    strptime(dateAndTimeAsString, "%Y-%m-%dT%H:%M:%S", &timeStruct);
    
    time_t unixTime = timegm(&timeStruct);
    struct tm *tmVal = gmtime (&unixTime); // gmtime works in UTC.

    if( (-1 != unixTime) && tmVal )
    {
       m_theTime.theDay = tmVal->tm_mday;
       m_theTime.theMonth = tmVal->tm_mon + 1;
       m_theTime.theYear = tmVal->tm_year + 1900;
       m_theTime.theHour = tmVal->tm_hour;
       m_theTime.theMinutes = tmVal->tm_min;
       m_theTime.theSeconds = tmVal->tm_sec;
    }
    else
    {
       memset ((void*)(&m_theTime), 0, sizeof (m_theTime));
    }

    EXIT();
}


void TimeWrap::GetTimeStr (char *timeBuffer, u32 timeBufferLen, bool includeMicrosecs) const
{
    // Format for friendly output...
    // Format: HH:MM:SS[.000000]
	if (includeMicrosecs)
	{
		snprintf (
			timeBuffer,
            timeBufferLen,
			"%02" PRIu32 ":%02" PRIu32 ":%02" PRIu32 ".%.06" PRIu32,
			m_theTime.theHour,
			m_theTime.theMinutes,
			m_theTime.theSeconds,
			m_theTime.theUSeconds);
	}
	else
	{
		snprintf (
			timeBuffer,
            timeBufferLen,
			"%02" PRIu32 ":%02" PRIu32 ":%02" PRIu32,
			m_theTime.theHour,
			m_theTime.theMinutes,
			m_theTime.theSeconds);
	}//end if
}

void TimeWrap::GetDateStr (char *dateBuffer, u32 dateBufferLen, bool includeMicrosecs) const
{
    // Format: DD/MM/YY HH:MM:SS[.000000]

    if (includeMicrosecs)
	{
		// Format for friendly output...
		snprintf (
			dateBuffer,
            dateBufferLen - 1,
			"%02" PRIu32 "/%02" PRIu32 "/%02" PRIu32 " %02" PRIu32 ":%02" PRIu32 ":%02" PRIu32 ".%.06" PRIu32,
			m_theTime.theDay,
			m_theTime.theMonth,
			m_theTime.theYear,
			m_theTime.theHour,
			m_theTime.theMinutes,
			m_theTime.theSeconds,
			m_theTime.theUSeconds);
	}
	else
	{
		snprintf (
			dateBuffer,
            dateBufferLen - 1,
			"%02" PRIu32 "/%02" PRIu32 "/%02" PRIu32 " %02" PRIu32 ":%02" PRIu32 ":%02" PRIu32,
			m_theTime.theDay,
			m_theTime.theMonth,
			m_theTime.theYear,
			m_theTime.theHour,
			m_theTime.theMinutes,
			m_theTime.theSeconds);
	}//end if
    dateBuffer[dateBufferLen - 1] = '\0';
}

void TimeWrap::GetUnfriendlyTime (char *timeBuffer, u32 bufferLen) const
{
    // Format: DDMMYY.HHMMSS
	snprintf (
		timeBuffer, bufferLen,
		"%02" PRIu32 "%02" PRIu32 "%02" PRIu32 ".%02" PRIu32 "%02" PRIu32 "%02" PRIu32,
		m_theTime.theDay,
		m_theTime.theMonth,
		m_theTime.theYear,
		m_theTime.theHour,
		m_theTime.theMinutes,
		m_theTime.theSeconds);
}

const TimeStructure &TimeWrap::GetTimeStructure () const
{
	return m_theTime;
}

const char *TimeWrap::GetSafeFileName () const
{
	GetDateStr (m_theTimeAsSafeFileName, sizeof(m_theTimeAsSafeFileName));

	u8 dateLength = (u8) strlen (m_theTimeAsSafeFileName);
	for (u8 k=0;k<dateLength;k++)
	{
		switch (m_theTimeAsSafeFileName[k])
		{
		case '/':
        case ':':
            {
                m_theTimeAsSafeFileName[k] = '-';
            }
            break;

        case ' ':
            {
                m_theTimeAsSafeFileName[k] = '_';
            }
            break;

		default:
			{
				// Do Nothing: the char is valid...
			}
		}//end switch
	}//end for

	return m_theTimeAsSafeFileName;
}

void TimeWrap:: ReadUnixTimeAgain() const
{
 
   TimeStructure *sptr=(TimeStructure*)&m_theTime;
   struct timeval timeVal;
   struct timezone timeZone;
   gettimeofday (&timeVal, &timeZone);
   struct tm *tmVal = gmtime (&(timeVal.tv_sec));  // gmtime works in UTC.
   sptr->theDay = tmVal->tm_mday;
   sptr->theMonth = tmVal->tm_mon + 1;
   sptr->theYear = tmVal->tm_year + 1900;
 
   sptr->theHour = tmVal->tm_hour;
   sptr->theMinutes = tmVal->tm_min;
   sptr->theSeconds = tmVal->tm_sec;
}

u32 TimeWrap::GetUnixTime() const
{
    ENTER();

    if ((m_theTime.theYear < 1970) || (m_theTime.theMonth < 0))
    {

        ReadUnixTimeAgain();
    }
    struct tm timeStruct;

    memset((void*)&timeStruct, 0, sizeof(timeStruct));

    timeStruct.tm_sec = m_theTime.theSeconds;
    timeStruct.tm_min = m_theTime.theMinutes;
    timeStruct.tm_hour = m_theTime.theHour;
    timeStruct.tm_mday = m_theTime.theDay;
    timeStruct.tm_mon = m_theTime.theMonth - 1;
    timeStruct.tm_year = m_theTime.theYear - 1900;

    time_t unixTime = timegm(&timeStruct);

    RETURN((u32)unixTime);
}

u32 TimeWrap::GetMicroSecs() const
{
    ENTER();

    RETURN(m_theTime.theUSeconds);
}

s32 TimeWrap::GetSecondsElapsed() const
{
    TimeWrap nowTimeWrap;

    u32 now  = nowTimeWrap.GetUnixTime();
    u32 then = GetUnixTime();

    return now - then;
}

TimeWrap& TimeWrap::operator= (const TimeWrap &rhs)
{
    ENTER();

    // Check for self-assignment!
    if (this == &rhs)
    {
        RETURN(*this);
    }

    memcpy (&m_theTime, &rhs.m_theTime, sizeof (TimeStructure));

    RETURN(*this);
}

void TimeWrap::Touch ()
{
	memset (&m_theTime, 0, sizeof (TimeStructure));

	struct timeval timeVal;
	struct timezone timeZone;

	gettimeofday (&timeVal, &timeZone);
	struct tm *tmVal = gmtime (&(timeVal.tv_sec));  // gmtime works in UTC.

	m_theTime.theDay = tmVal->tm_mday;
	m_theTime.theMonth = tmVal->tm_mon + 1;
	m_theTime.theYear = tmVal->tm_year + 1900;

	m_theTime.theHour = tmVal->tm_hour;
	m_theTime.theMinutes = tmVal->tm_min;
	m_theTime.theSeconds = tmVal->tm_sec;

	m_theTime.theUSeconds = timeVal.tv_usec;
}

std::string TimeWrap::ToString( u8 subSecondDecimalPlaces ) const
{
    ENTER();

    string timeStr;
    char timeBuffer[128];

    // Format: YYYY-MM-DDTHH:MM:SS
    snprintf (
        timeBuffer, sizeof(timeBuffer),
        "%04" PRIu32 "-%02" PRIu32 "-%02" PRIu32 "T%02" PRIu32 ":%02" PRIu32 ":%02" PRIu32,
        m_theTime.theYear,
        m_theTime.theMonth,
        m_theTime.theDay,
        m_theTime.theHour,
        m_theTime.theMinutes,
        m_theTime.theSeconds);

    timeStr = timeBuffer;

    if(subSecondDecimalPlaces)
    {
        const int maxSignificantDigits = 6;
        const size_t lengthOfDecimalPointAndDigits = 1 + maxSignificantDigits;
        char subSecondBuffer[ lengthOfDecimalPointAndDigits + 1];

        // Format: .123456
        size_t suffixLength = snprintf (
            &subSecondBuffer[0],
            sizeof(subSecondBuffer),
            ".%0*" PRIu32,
            maxSignificantDigits,
            m_theTime.theUSeconds);

        size_t desiredSuffixLength = subSecondDecimalPlaces + 1;

        if(suffixLength > desiredSuffixLength)
        {
            subSecondBuffer[desiredSuffixLength] = '\0';
            suffixLength = desiredSuffixLength;
        }

        timeStr += subSecondBuffer;

        while(suffixLength < desiredSuffixLength)
        {
            timeStr += "0";
            suffixLength++;
        }
    }

    RETURN(timeStr);
}

std::string TimeWrap::ToString( const char * offsetToGmt, u8 subSecondDecimalPlaces ) const
{
    char unknownTimeZone[] = "-00:00";

    s32 offsetSeconds = 0;

    ENTER();

    signed hoursOffset = 0;
    unsigned minutesOffset = 0;

    if( (offsetToGmt == NULL) ||
        (0 == sscanf(offsetToGmt, "%d:%u", &hoursOffset, &minutesOffset)) )
    {
        offsetToGmt = &unknownTimeZone[0];
    }

    if(offsetToGmt[0] == '-')
    {
        offsetSeconds = ((hoursOffset * 60) - minutesOffset) * 60;
    }
    else
    {
        offsetSeconds = ((hoursOffset * 60) + minutesOffset) * 60;
    }

    /* ISC 8601: Negative Offset means West-Of-GMT
     * eg. 12:00-06:00 is noon in Texas, or 18:00 UTC
     */
    TimeWrap localTime( GetUnixTime() + offsetSeconds);

    // Ensure time format as per ISO8601: [+/-]hh:mm
    char tempBuffer[10];
    snprintf(tempBuffer, sizeof(tempBuffer), "%+03i:%02u",hoursOffset,minutesOffset);

    string timeStr = localTime.ToString( subSecondDecimalPlaces );
    timeStr += tempBuffer;

    RETURN(timeStr);
}


}
