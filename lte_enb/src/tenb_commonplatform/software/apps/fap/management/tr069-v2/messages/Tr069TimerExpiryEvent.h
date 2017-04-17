///////////////////////////////////////////////////////////////////////////////
//
// Tr069TimerExpiryEvent.h
//
// Queueable event for timer expiry in tr069 app.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Tr069TimerExpiryEvent_h_
#define __Tr069TimerExpiryEvent_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <boost/shared_ptr.hpp>
#include <libcsoap/soap-env.h>
#include <libcsoap/soap-ctx.h>
#include <system/ThreadWithQueue.h>
#include <system/TimerInterface.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr069QueueableEvent.h"

namespace tr069
{

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class TimerExpiryEvent : public tr069::Tr069QueueableEvent
{
public:
    TimerExpiryEvent( threeway::TimerHandle expiredTimer ) :
        tr069::Tr069QueueableEvent( TR069_EVENT(TIMER_EXPIRY_EVENT), TRANSACTION_SESSION_FSM ),
        m_timerHandle(expiredTimer),
        m_handled(false) {}

    virtual ~TimerExpiryEvent() {};

    bool operator== (threeway::TimerHandle h)
    {
        bool matched = (h==m_timerHandle);
        if(matched)
        {
            m_handled = true;
        }
        return matched;
    }

    bool GetHandled () const { return m_handled; }

    Tr069QueueableEvent::Id GetId() const { return m_id;}

private:
    static Tr069QueueableEvent::Id m_id;
    threeway::TimerHandle m_timerHandle;
    bool m_handled;
};

}

#endif
