///////////////////////////////////////////////////////////////////////////////
//
// Timer.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Timer.h"

using namespace std;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Static Data
///////////////////////////////////////////////////////////////////////////////

// Seeding used when creating new Timers.
TimerHandle Timer::s_nextTimerHandle = 1;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

Timer::Timer(u32 timeoutPeriodMs, TimerEngineInterface::TimerMode timerMode, const std::string& timerName,
             TimerNotifyInterface& timerNotifyInterface, TimerEngineInterface::TimerAlignment timerAlignment,
             bool traceTimerEvents) :
	m_timerPeriodMs(timeoutPeriodMs),
	m_timerMode(timerMode),
    m_timerName(timerName),
    m_timerNotifyInterface(timerNotifyInterface),
    m_timerAlignment(timerAlignment),
    m_traceTimerEvents(traceTimerEvents)
{
	ENTER();

	// We don't allow 0 to be used, for purely aesthetic reasons.
	m_timerHandle = s_nextTimerHandle;
	if (++s_nextTimerHandle == NULL_TIMER)
    {
		++s_nextTimerHandle;
    }

	EXIT();
}

Timer::~Timer(void)
{
	ENTER();
	EXIT();
}

TimerHandle Timer::GetHandle () const
{
	ENTER();
	RETURN (m_timerHandle);
}

u32 Timer::GetTimerPeriodMs () const
{
	ENTER();
	RETURN(m_timerPeriodMs);
}

bool Timer::IsDeleteOnExpiry () const
{
	ENTER();
	RETURN(m_timerMode == TimerEngineInterface::TIMER_SINGLE_SHOT);
}

TimerEngineInterface::TimerMode Timer::GetTimerMode () const
{
    ENTER();
    RETURN(m_timerMode);
}

const char * Timer::GetTimerName () const
{
	ENTER();
	RETURN(m_timerName.c_str());
}

TimerNotifyInterface& Timer::GetTimerNotifyInterface() const
{
    ENTER();
    RETURN(m_timerNotifyInterface);
}

TimerEngineInterface::TimerAlignment Timer::GetTimerAlignment() const
{
    ENTER();
    RETURN(m_timerAlignment);
}

bool Timer::GetTraceTimerEvents() const
{
    ENTER();
    RETURN(m_traceTimerEvents);
}

void Timer::SetTimerPeriodMs(u32 timerPeriodMs)
{
    ENTER();

    RSYS_ASSERT(timerPeriodMs > 0);

    m_timerPeriodMs = timerPeriodMs;

    EXIT();
}

std::string Timer::ToString() const
{
    std::ostringstream stream;

    stream << "Handle:" << (u32)m_timerHandle;
    stream << ", Name:" << m_timerName;
    stream << ", Period:" << m_timerPeriodMs;

    switch (m_timerMode)
    {
    case TimerEngineInterface::TIMER_SINGLE_SHOT:
        stream << ", Single Shot";
        break;
    case TimerEngineInterface::TIMER_SINGLE_SHOT_WITHOUT_DELETE:
        stream << ", Single Shot w/o Delete";
        break;
    case TimerEngineInterface::TIMER_REPEAT:
        stream << ", Repeating";
        break;
    // No default, let compiler pick up missing entries.
    }

    switch(m_timerAlignment)
    {
    case TimerEngineInterface::TIMER_UNALIGNED:
        break;
    case TimerEngineInterface::TIMER_WALL_CLOCK_ALIGNED:
        stream << ", Wall Clock Aligned";
        break;
    // No default, let compiler pick up missing entries.
    }

    return stream.str();
}
