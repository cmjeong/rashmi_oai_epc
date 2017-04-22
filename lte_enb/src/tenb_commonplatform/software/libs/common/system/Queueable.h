///////////////////////////////////////////////////////////////////////////////
//
// Queueable.h
//
// Interface for declaring that an instance of a class can be queued.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Queueable_h_
#define __Queueable_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <3waytypes.h>
#include <boost/shared_ptr.hpp>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

using namespace boost;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class Queueable
{
public:
    // Domain is used to indicate top-level type of object
    typedef enum QueueableDomain_tag
    {
        NOT_DEFINED,

        THREAD_QUEUED_MESSAGE,   // ThreadQueuedMessage derived object
        MESSAGE_SERIALISED_DATA, // MessageSerialisedData object
        TIMER_EXPIRY,            //
        OTHER                    // Other application specific object
    } QueueableDomain;

    Queueable() : m_domain(Queueable::NOT_DEFINED) {};
    Queueable(const QueueableDomain domain) : m_domain(domain) {};
    virtual ~Queueable() {};

    QueueableDomain GetDomain() const { return m_domain; };
    void SetDomain(const QueueableDomain domain) { m_domain = domain; };

private:
    QueueableDomain m_domain;
};

}

#endif
