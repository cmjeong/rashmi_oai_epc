///////////////////////////////////////////////////////////////////////////////
//
// UpTime.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <time.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sstream>
#include <iomanip>
#include <system/Trace.h>
#include <system/Timer.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////
const char UpTime::m_fileName[] = "/proc/uptime";

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////


UpTime::UpTime( bool singleThreaded ) :
        m_uptimeFpReadMutex(NULL)

{
    //Need for this mutex to be reconsidered when attending to the TODO below.
    if( !singleThreaded )
    {
        m_uptimeFpReadMutex = new Mutex;

        Thread::InitialiseMutex(*m_uptimeFpReadMutex);
    }

    // TODO - This is a temporary fix to workaround not being able to get
    // a monotonic tick count from user space.  In time we can replace this with
    // a driver to get kernel tick, tick maintained by FPGA interrupt or whatever.
    // Needed a quick fix and investigations into checking how long it takes to
    // read /proc/uptime show it is not significantly slower than gettimeofday.
    // Still, it's not ideal....

    // TODO - change to use clock_gettime(CLOCK_MONOTONIC)...

    m_uptimeFp = fopen(m_fileName, "r");

    if(!m_uptimeFp)
    {
        TRACE_MSG("Failed to open handle to /proc/uptime");
    }
    else
    {
        SetCloExec(fileno(m_uptimeFp));
    }
}

UpTime::~UpTime ()
{
   if(m_uptimeFp)
   {
      fclose(m_uptimeFp);
      m_uptimeFp = NULL;
   }

   if(m_uptimeFpReadMutex)
   {
      Thread::DestroyMutex(*m_uptimeFpReadMutex);
      delete m_uptimeFpReadMutex;
      m_uptimeFpReadMutex = NULL;
   }
}

uptime_t UpTime::GetMillisecs() const
{
    unsigned seconds = 0;
    unsigned hundredths = 0;

    if(m_uptimeFpReadMutex)
    {
        // TODO - change to use clock_gettime(CLOCK_MONOTONIC)...
        Thread::Guard guard(*m_uptimeFpReadMutex);

        ReadUpTimeFile(seconds, hundredths);
    }
    else
    {
        ReadUpTimeFile(seconds, hundredths);
    }

    // This wraps roughly every 136 years!
    uptime_t uptime;

    uptime  = seconds;
    uptime *= 1000;
    uptime += uptime_t(hundredths) * 10;

    return uptime;
}

void UpTime::ReadUpTimeFile( unsigned & seconds, unsigned & hundredths ) const
{
   do
   {
#ifndef HARDWARE_hbs2_3_5
      m_uptimeFp = freopen(m_fileName, "r", m_uptimeFp);
      RSYS_ASSERT(m_uptimeFp!= NULL);
      SetCloExec(fileno(m_uptimeFp));
#endif
      RSYS_ASSERT(m_uptimeFp!= NULL);
      rewind(m_uptimeFp);

   } while( 2 != fscanf(m_uptimeFp, "%u.%u", &seconds, &hundredths) );
}

void UpTime::SetCloExec(const int fd) const
{
    // Set the close on exec flag if possible.
    //  If the application calls exec(), this automatically closes this
    //  file to prevent file descriptor resource leaks.
    int flags = fcntl(fd, F_GETFD);

    if(flags != -1)
    {
        fcntl(fd, F_SETFD, flags | FD_CLOEXEC);
    }
}

}
