///////////////////////////////////////////////////////////////////////////////
//
// Tr069Shutdown
//
// Message to perform clean shutdown of Transaction Sessions
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Tr069Shutdown_h_
#define __Tr069Shutdown_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <boost/shared_ptr.hpp>
#include <system/ThreadWithQueue.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr069QueueableEvent.h"

namespace tr069
{

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////



class Shutdown : public tr069::Tr069QueueableEvent
{
public:
    Shutdown( Tr069QueueableEvent::Handler dst) :
        tr069::Tr069QueueableEvent( TR069_EVENT(SHUTDOWN), dst )
    {}
    virtual ~Shutdown(){};

private:
};

}

#endif
