///////////////////////////////////////////////////////////////////////////////
//
// Timer.cpp
//
// Wrapper class that manages NASTimer objects.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string.h>

#include <system/StringUtils.h>

#include <NASTrace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "NASTimer.h"

using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Local Definitions
///////////////////////////////////////////////////////////////////////////////

// Seeding used when creating new NASTimers.
TimerHandle NASTimer::s_nextTimerHandle = 1;


///////////////////////////////////////////////////////////////////////////////
// Class: NASTimer
//
// Manage a single NASTimer object in the system.
//
///////////////////////////////////////////////////////////////////////////////
NASTimer::NASTimer (u32 timeoutPeriod, bool deleteOnExpiry, const char *NASTimerName) :
	m_timerPeriod (timeoutPeriod),
	m_deleteOnExpiry (deleteOnExpiry)
{
	NAS_ENTER();

	// Small sanity check to make sure we don't run over the
	// end of the string name variable.
	memset (m_timerName, '\0', MAX_NASTimer_NAME);
	if (strlen (NASTimerName) > MAX_NASTimer_NAME)
	{
		// Truncation to fit in the member.
		memcpy (m_timerName, NASTimerName, MAX_NASTimer_NAME);
	}
	else
	{
		strncpysafe (m_timerName, NASTimerName, sizeof(m_timerName));
	}//end if

	// We don't allow 0 to be used, for purely aesthetic reasons.
	m_timerHandle = s_nextTimerHandle;
	if (++s_nextTimerHandle == NULL_TIMER)
		++s_nextTimerHandle;
	//end if

	NAS_EXIT();
}

NASTimer::~NASTimer(void)
{
	NAS_ENTER();
	NAS_EXIT();
}

TimerHandle NASTimer::GetHandle () const
{
	NAS_ENTER();
	NAS_RETURN (m_timerHandle);
}

u32 NASTimer::GetTimerPeriod () const
{
	NAS_ENTER();
	NAS_RETURN(m_timerPeriod);
}

bool NASTimer::DeleteOnExpiry () const
{
	NAS_ENTER();
	NAS_RETURN(m_deleteOnExpiry);
}

const char *NASTimer::GetTimerName () const
{
	NAS_ENTER();
	NAS_RETURN(m_timerName);
}
