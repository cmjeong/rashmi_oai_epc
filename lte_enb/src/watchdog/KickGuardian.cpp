///////////////////////////////////////////////////////////////////////////////
//
// KickGuardian.h
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <time.h>
#include <sstream>
#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "KickGuardian.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

KickGuardian::KickGuardian(u32 id, u16 soft, u16 hard) :
    m_id(id),
    m_softDelta(soft),
    m_hardDelta(hard)
{
    Kick();
}


KickGuardian::~KickGuardian()
{
}


void KickGuardian::Kick(void)
{
    m_lastKick = time(NULL);
}


bool KickGuardian::IsGood(void)
{
    time_t now = time(NULL);

    if(hasExpired(now, m_lastKick, m_lastKick + m_softDelta))
    {
        printf("KickGuardian passed soft limit: %s\n", ToString().c_str());
    }

    return !hasExpired(now, m_lastKick, m_lastKick + m_hardDelta);
}
                                                    

std::string KickGuardian::ToString()
{
    ostringstream s;

    s << "KickGuardian { id=" << m_id <<
         ", soft=" << m_softDelta <<
         ", hard=" << m_hardDelta <<
         ", lastKick=" << m_lastKick <<
         " }";

    return s.str();
}


bool KickGuardian::hasExpired(time_t now, time_t start, time_t end)
{
    bool result = false; 
    
    // Check if the timeline wraps
    if(start <= end)
    {
        result = ( now > end || now < start );
    }
    else
    {
        result = ( now > end && now < start );
    }
    
    return result;
}

// END OF FILE
