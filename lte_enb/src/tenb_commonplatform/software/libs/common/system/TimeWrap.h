///////////////////////////////////////////////////////////////////////////////
//
// TimeWrap.h
//
// Wrapper class for time_t data type.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __TimeWrap_h_
#define __TimeWrap_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <time.h>
#include <3waytypes.h>

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

typedef struct tagTimeStructure
{
	u32 theDay;			// Day of the month
	u32 theMonth;		// Month of the year, 1-12
	u32 theYear;		// Current year
	u32 theHour;		// Hour of day, 0-23
	u32	theMinutes;		// Minute of hour
	u32 theSeconds;		// Seconds within hour
	u32	theUSeconds;	// Microseconds within second
} TimeStructure;

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class TimeWrap
{
public:
	/**
	 * Construct with current time.
	 */
	TimeWrap ();

	/**
	 * Construct from unix time.
	 */
	TimeWrap (time_t unixTime);

	virtual ~TimeWrap ();

	/**
	 * Set time from unix time and microseconds.
	 * \param unixTime Seconds since 1970.
	 * \param microSecs Microsecond part of time.
	 */
	void Set(time_t unixTime, u32 microSecs);
	void Set(const char *dateAndTimeAsString);

	// Retrieve a formatted text string with the time_t.
	void GetTimeStr (char *timeBuffer, u32 timeBufferLen, bool includeMicrosecs = true) const;
	void GetDateStr (char *dateBuffer, u32 dateBufferLen, bool includeMicrosecs = true) const;
	void GetUnfriendlyTime (char *timeBuffer, u32 bufferLen) const;
	const TimeStructure &GetTimeStructure () const;
	const char *GetSafeFileName () const;

	/**
	 * Get time as 'unix time' i.e. number of secs since 1970.
	 * Note, this will obviously drop any sub-second info we have.
	 *
	 * \return Time value in secs since 1970.
	 */
	u32 GetUnixTime() const;
        void ReadUnixTimeAgain()const;

	/**
     * Get the microseconds component.
     *
     * \return Microseconds component of the time value.
     */
    u32 GetMicroSecs() const;

    /**
     * Return number of minutes.  Used typically when this is the result
     * of diff'ing two times and we expect a relatively small result.
     * I.e. less than one day.
     */
	//u32 NumberOfMinutes () const;

	/* Relative to "now"
	 * Returns +ive for a TimeWrap in the past
	 *         -ive for a TimeWrap in the future.
	 */
    s32 GetSecondsElapsed() const;

	// Operators to set the member data.
    TimeWrap& operator= (const TimeWrap &rhs);

	// Share the implementation of the time_t -> TimeStructure logic,
	// so we don't duplicate it in constructurs, operators, etc.
	void Touch ();

	/**
	 * Get as pretty string.
	 */
    std::string ToString( u8 subSecondDecimalPlaces = 0 ) const;
     /* Offset To GMT, e.g. "+01:00" */
    std::string ToString( const char * offsetToGmt, u8 subSecondDecimalPlaces = 0 ) const;

private:

	// Use this internal time structure so we can calculate
	// the time in sub-second units, and offset for the time zone.
	TimeStructure m_theTime;

	// Since there are _lots_ of occasions when we will build
	// filename using the date/time string, we will do it here and
	// store the result to prevent lots of duplicate, messy code.
	mutable char m_theTimeAsSafeFileName[32];
};

}

#endif
