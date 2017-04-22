
///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <linux/watchdog.h>
#include <sstream>
#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "3waytypes.h"
#include "BfinDog.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

BfinDog::BfinDog()
{
    // Open and configure the dog
    m_dev = open("/dev/watchdog", O_WRONLY);
    if(m_dev != -1)
    {
        int r, timeoutsec = 25;

        r = ioctl(m_dev, WDIOC_SETTIMEOUT, &timeoutsec);
        if(r)
        {
            TRACE_PRINTF("Opened /dev/watchdog but failed to set timeout: %d", r);
        }
        else
        {
            TRACE_PRINTF("Opened /dev/watchdog and timeout set to %u seconds", timeoutsec);
        }
        Kick();
    }
    else
    {
        TRACE_PRINTF("Failed to open /dev/watchdog");
    }

    Kick();
}


BfinDog::~BfinDog()
{
    if(m_dev != -1)
    {
        TRACE_PRINTF("Shutting down and closing the watchdog: system unguarded");

        // Kick to give some time before reset incase magic close is not enabled
        Kick();

        // Write a magic 'V' to disable the watchdog on a normal close
        write(m_dev, "V", 1);
        close(m_dev);
    }
}


void BfinDog::Kick(void)
{
    const u8 v = 0;

    if(m_dev != -1)
    {
        write(m_dev, &v, 1);
        TRACE_PRINTF("Dog kicked");
    }
}

// END OF FILE
