///////////////////////////////////////////////////////////////////////////////
//
// FNTPTime.cpp
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
#include <sys/time.h>
#include <time.h>
///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
#include "FNTPTime.h"
//using namespace std;
//namespace threeway
//{


long double NTPtoLongDouble(unsigned long inSecs, unsigned long inFrac)
{
    ENTER();
    long double sum;
    sum = ntohl(inFrac);
    sum /= 4294967296.0;
    sum += ntohl(inSecs);
    /*TRACE_PRINTF("in = %u,%u\n",ntohl(InSecs),ntohl(InFrac));
     TRACE_PRINTF("out = %Lf\n",sum);*/
    RETURN(sum);
}

void LongDoubletoNTP(long double inLD, unsigned long* inSecs, unsigned long* inFrac)
{
    ENTER();
    unsigned long secs = (unsigned long) inLD;
    *inSecs = htonl(secs);
    *inFrac = htonl((unsigned long) ((inLD - (long double) secs) * 4294967296.0));
    EXIT();
}

void GetTimeNTP(unsigned long* inSecs, unsigned long* inFrac)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    *inSecs = htonl((tv.tv_sec + NTP_EPOCH));
    *inFrac = htonl((tv.tv_usec * 4295));
}

long double GetLDTime(void)
{
    ENTER();
    long double ret;
    struct timeval tv;

    gettimeofday(&tv, NULL);
    ret = tv.tv_usec;
    ret /= 1000000;
    ret += tv.tv_sec;
    ret += NTP_EPOCH;
    RETURN(ret);
}

long double ldSquare(long double inLD)
{
    //ENTER();
    //RETURN(InLD * InLD);
    return (inLD * inLD);
}

//converts long double time (in seconds) to a timeval struct
struct timeval LDtotv(long double timeLD)
{
    struct timeval retVal;

    retVal.tv_sec = (long int) timeLD;
    timeLD -= (long double) retVal.tv_sec;
    retVal.tv_usec = (long int) (timeLD * 1000000);
    return retVal;
}

struct timeval LDtotvAbs(long double timeLD)
{
    struct timeval retVal;

    timeLD -= (long double) NTP_EPOCH;
    retVal.tv_sec = (long int) timeLD;
    timeLD -= (long double) retVal.tv_sec;
    retVal.tv_usec = (long int) (timeLD * 1000000);
    return retVal;
}

void timevaladd(struct timeval *t1, struct timeval *t2)
{
    t1->tv_sec += t2->tv_sec;
    if ((t1->tv_usec += t2->tv_usec) > 1000000)
    {
        t1->tv_sec++;
        t1->tv_usec -= 1000000;
    }
}

long double ldrand()
{
    long double retVal;

    /*retVal = (long double)random();
     retVal /= 0x7FFFFFFF;*/
    retVal = (rand() / (RAND_MAX + 1.0));
    return retVal;
}

long double ldSign(long double inVal)
{
    if (inVal < 0.0)
        return (-1.0);
    else
        return (1.0);
}

long double ldModulus(long double inVal)
{
    if (inVal < 0.0)
        return (-inVal);
    else
        return (inVal);
}

//}//end of namespace threeway
