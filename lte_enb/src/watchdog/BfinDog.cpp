///////////////////////////////////////////////////////////////////////////////
//
// $Id: BfinDog.cpp 15058 2009-06-19 16:56:09Z mrenwick $
//
///////////////////////////////////////////////////////////////////////////////

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
#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "3waytypes.h"
#include "BfinDog.h"

using namespace std;

#define FILE_OPEN_FAILED                     -1
#define KERNAL_WATCHDOG_TIMEOUT_VAL          25

extern int hardTimeOut;
///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

BfinDog::BfinDog()
{
    // Open and configure the dog
    m_dev = open("/dev/watchdog", O_WRONLY);
    if(m_dev != FILE_OPEN_FAILED)
    {
        int result, timeoutsec = hardTimeOut;

        result = ioctl(m_dev, WDIOC_SETTIMEOUT, &timeoutsec);
        if(result)
        {
            printf("Opened /dev/watchdog but failed to set timeout: %d\n", result);
        }
        else
        {
            printf("Opened /dev/watchdog and timeout set to %u seconds\n", timeoutsec);
        }
        Kick();
    }
    else
    {
        printf("Failed to open /dev/watchdog\n");
    }

    Kick();
}


BfinDog::~BfinDog()
{
    if(m_dev != -1)
    {
        printf("Shutting down and closing the watchdog: system unguarded\n");

        // Kick to give some time before reset incase magic close is not enabled
        Kick();

        // Write a magic 'V' to disable the watchdog on a normal close
        m_ret = write(m_dev, "V", 1);
        close(m_dev);
    }
}


void BfinDog::Kick(void)
{
    const u8 v = 0;

    if(m_dev != -1)
    {
        m_ret = write(m_dev, &v, 1);
        //printf("Dog kicked\n");
    }
}

// END OF FILE
