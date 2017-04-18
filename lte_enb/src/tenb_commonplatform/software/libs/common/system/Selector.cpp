///////////////////////////////////////////////////////////////////////////////
//
// Selector.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Trace.h>
#include <vector>

#include <sys/select.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Selector.h"

using namespace std;
using namespace threeway;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Static Data
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Functions
///////////////////////////////////////////////////////////////////////////////


Selector::Selector() :
        m_uptime(true)
{
    ENTER();

    RSYS_ASSERT_PRINTF(m_uptime.GetMillisecs() > 0, "Up time broken!");

    EXIT();
}

Selector::~Selector()
{
    ENTER();

    m_fdMap.clear();

    m_timeoutMap.clear();

    EXIT();
}


void Selector::RegisterFD(int fd, SelectorCallBackInterface &cb)
{
    ENTER();

    RSYS_ASSERT(fd >= 0);

    RSYS_ASSERT_PRINTF(m_fdMap.find(fd) == m_fdMap.end(), "Error: attempt to register a file descriptor (%d) already in use for this application", fd);

    m_fdMap.insert( make_pair(fd, &cb) );

    EXIT();
}

void Selector::DeregisterFD(int fd)
{
    ENTER();

    RSYS_ASSERT(fd >= 0);

    if ( m_fdMap.find(fd) != m_fdMap.end() )
    {
        m_fdMap.erase( fd );
    }

    EXIT();
}


void Selector::RegisterTimeout(u32 timeoutMs, SelectorCallBackInterface& cb)
{
    ENTER();

    uptime_t uptimeTimeoutMs = timeoutMs + m_uptime.GetMillisecs();

    if ( m_timeoutMap.find(&cb) != m_timeoutMap.end() )
    {
        m_timeoutMap.erase( &cb);
    }

    m_timeoutMap.insert( make_pair(&cb, uptimeTimeoutMs) );

    EXIT();
}


void Selector::DoSelect(u32 maxBlockingMilliseconds)
{
    ENTER();

    fd_set fdSet;
    struct timeval tv;

    int maxfd = 0;
    FD_ZERO(&fdSet);

    RegisteredFdCallbacks::iterator ii = m_fdMap.begin();
    for ( ; ii != m_fdMap.end() ; ++ii )
    {
        int fd = (*ii).first;
        FD_SET( fd , &fdSet);

        maxfd = max(maxfd, fd);
    }

    GetSelectTimeout(tv, maxBlockingMilliseconds);

    int numberOfDescr = select(++maxfd, &fdSet, NULL, NULL, &tv);

    if (numberOfDescr == -1)
    {
        RSYS_ASSERT_PRINTF(errno == EINTR, "unhandled select error");
    }
    else
    {
        vector<SelectorCallBackInterface*> cbVector;

        for( ii = m_fdMap.begin();
             ii != m_fdMap.end() && numberOfDescr>0;
             ++ii)
        {
            int fd = (*ii).first;
            if ( FD_ISSET(fd, &fdSet) )
            {
                SelectorCallBackInterface* callBack = (*ii).second;
                cbVector.push_back( callBack );
                --numberOfDescr;
            }
        }

        /* Perform callbacks after fully analazying FD map
         * to protect when callbacks modify FD map
         * */
        CheckTimeouts();

        for ( vector<SelectorCallBackInterface*>::iterator vectorIter = cbVector.begin();
                vectorIter != cbVector.end();
                vectorIter++ )
        {
            SelectorCallBackInterface* callBack = *vectorIter;
            callBack->SelectCallBack();
        }
    }

    EXIT();
}


void Selector::CheckTimeouts()
{
    ENTER();

    uptime_t now = m_uptime.GetMillisecs();
    vector<SelectorCallBackInterface*> timedoutCallBacks;

    RegisteredTimeoutCallbacks::iterator timeIter = m_timeoutMap.begin();

    while(timeIter != m_timeoutMap.end())
    {
        RegisteredTimeoutCallbacks::iterator tempIter = timeIter++;

        uptime_t expiryTime = (*tempIter).second;

        bool expired = (expiryTime <= now);

        if ( expired )
        {
            SelectorCallBackInterface* cb = (*tempIter).first;

            timedoutCallBacks.push_back(cb);

            m_timeoutMap.erase(tempIter);
        }
    }

    for ( vector<SelectorCallBackInterface*>::iterator vectIter = timedoutCallBacks.begin();
            vectIter != timedoutCallBacks.end();
            ++vectIter )
    {
        SelectorCallBackInterface* cb = *vectIter;

        cb->SelectCallBack();
    }

    timedoutCallBacks.clear();

    EXIT();
}

void Selector::GetSelectTimeout(struct timeval& tv, u32 maxBlockingMilliseconds)
{
    ENTER();

    u32         nextTimeout = maxBlockingMilliseconds;
    uptime_t    now = m_uptime.GetMillisecs();

    RegisteredTimeoutCallbacks::iterator ii = m_timeoutMap.begin();

    for ( ; ii != m_timeoutMap.end(); ++ii)
    {
        uptime_t timeout = max(now, (*ii).second);
        u32 relativeTimeout = timeout - now;

        nextTimeout = min(relativeTimeout, nextTimeout);
    }

    tv.tv_sec = nextTimeout/1000;
    tv.tv_usec = (nextTimeout % 1000) * 1000;

    EXIT();
}

}

