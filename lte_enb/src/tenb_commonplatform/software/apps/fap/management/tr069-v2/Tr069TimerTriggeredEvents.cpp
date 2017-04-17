///////////////////////////////////////////////////////////////////////////////
//
// TR069Application.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Trace.h>
#include <system/TimerEngine.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr069Application.h"
#include "Tr069TimerTriggeredEvents.h"

using namespace std;
using namespace threeway;
using namespace tr069;

///////////////////////////////////////////////////////////////////////////////
// Static Data
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////


threeway::TimerHandle TimerTriggeredEvents::Enqueue( boost::shared_ptr<tr069::Tr069QueueableEvent> event, u32 timeoutPeriodTicks)
{
    Tr069Application &app = Tr069Application::GetInstance();

    if(timeoutPeriodTicks < TimerEngineInterface::SecondsToTicks(1))
    {
        timeoutPeriodTicks = TimerEngineInterface::SecondsToTicks(1);
    }

    TRACE_PRINTF("Delay %s Enqueue (%" PRIu32 " ticks)", event->ToString(), timeoutPeriodTicks);

    threeway::TimerHandle timerHandle = app.CreateTimer( event->ToString(), timeoutPeriodTicks );

    delayedEvents[timerHandle] = event;

    return timerHandle;
}

bool TimerTriggeredEvents::Trigger( threeway::TimerHandle expiredTimer)
{
    Tr069Application &app = Tr069Application::GetInstance();

    shared_ptr<Tr069QueueableEvent> delayedEvent = delayedEvents[expiredTimer];

    if(delayedEvent)
    {
        TRACE_PRINTF("Send (%s) [delay expired]", delayedEvent->ToString());

        delayedEvents.erase(expiredTimer);

        app.Enqueue(delayedEvent);

        return true;
    }

    return false;
}

