///////////////////////////////////////////////////////////////////////////////
//
// FreqNTP.h
//
// Send and receive UDP packets.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __FNTPTime_h_
#define __FNTPTime_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>
#include <netinet/ip.h>
#include <unistd.h>

#include <3waytypes.h>

#include <boost/shared_ptr.hpp>
#include <comms/IPv4Address.h>
#include <comms/UdpSocket.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

#define NTP_EPOCH (86400U * (365U * 70U + 17U))

#define MAX(a, b)  (((a) > (b)) ? (a) : (b))
#define MIN(a, b)  (((a) < (b)) ? (a) : (b))

long double NTPtoLongDouble(unsigned long inSecs, unsigned long inFrac);

void LongDoubletoNTP(long double inLD, unsigned long* inSecs, unsigned long* inFrac);

void GetTimeNTP(unsigned long* inSecs, unsigned long* inFrac);

long double GetLDTime(void);

long double ldSquare(long double inLD);

struct timeval LDtotv(long double timeLD);

struct timeval LDtotvAbs(long double timeLD);

void timevaladd(struct timeval *t1, struct timeval *t2);

long double ldrand();

long double ldSign(long double inVal);

long double ldModulus(long double inVal);

#endif
