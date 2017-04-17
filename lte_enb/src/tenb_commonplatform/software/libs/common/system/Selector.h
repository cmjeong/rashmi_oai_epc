///////////////////////////////////////////////////////////////////////////////
//
// Selector.h
//
// Perform "select" on multiple registered file descriptors,
// each with an associated callback.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Selector_h_
#define __Selector_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <stddef.h>
#include <map>

#include <system/TimerInterface.h>
#include <Radisys.h>


///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include "SelectorInterfaces.h"


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

using namespace std;

namespace threeway
{



class Selector : public SelectorRegisterInterface
{

public:
    Selector();

    ~Selector();

    /**
     * Register an <FD, Callback> pair for use with select.
     */
    void RegisterFD(int fd, SelectorCallBackInterface& cb);
    void DeregisterFD(int fd);

    /**
     * Register a <Timeout, Callback> pair for use with select.
     */
    void RegisterTimeout(u32 timeoutMilliseconds, SelectorCallBackInterface& cb);

    /**
     * This calls "select", and blocks until the first of:
     * o   a registered FD is ready (and callback performed)
     * o   a registered timeout expires (and callback performed)
     * o   the maxBlockingMilliseconds duration has elapsed
     */
    void DoSelect(u32 maxBlockingMilliseconds = 60000 );

protected:

private:
    typedef map<int, SelectorCallBackInterface*> RegisteredFdCallbacks;

    typedef map<SelectorCallBackInterface*, uptime_t> RegisteredTimeoutCallbacks;

    void  GetSelectTimeout(struct timeval&, u32 maxBlockingMilliseconds);

    void CheckTimeouts();

    RegisteredFdCallbacks m_fdMap;

    RegisteredTimeoutCallbacks m_timeoutMap;

    UpTime m_uptime;
};

}

#endif
