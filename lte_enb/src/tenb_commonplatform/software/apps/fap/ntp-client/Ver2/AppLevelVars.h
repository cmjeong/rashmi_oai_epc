/*
 * AppLevelVars.h
 *
 *  Created on: 10-Sep-2009
 *      Author: jouroussoff
 */

#ifndef APPLEVELVARS_H_
#define APPLEVELVARS_H_
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

using namespace boost;
using namespace threeway;
//container for application wide vars & their accessors
class tAppLevelVars
{
    static const u32 DEFAULT_DEBUG_LEVEL = 2;
    //static const long double DEFAULT_DELAY_THRESHOLD = 0.15;
    //changed to 500ms for NSN. ToDo pin down a more robust and meaningful limit.
    static const long double DEFAULT_DELAY_THRESHOLD = 0.5;
    static const long double DEFAULT_MASSIVE_STEP = 0.00001;
    static const bool DEFAULT_CORRECT_STEP_CHANGE_RESULT = false;
    static const u32 UNCERTAINTY_INVALID_FACTOR = 5;
    static const u32 DEFAULT_SD_CALC_LENGTH = 5;
public:
    //all accessors
    static void InitVars();
    static void SetNumInBurst(u32 inNumInBurst);
    static u32 GetNumInBurst(void);
    static void SetDebugLevel(u32 inDebugLevel);
    static u32 GetDebugLevel(void);
    static long double GetdelayIgnoreThreshold(void);
    static void SetdelayIgnoreThreshold(long double inDelayThreshold);
    static long double GetMassiveStep(void) { return (m_massiveStep); }
    static void SetMassiveStep(long double massiveStep) { m_massiveStep = massiveStep; }
    static bool GetCorrectStepChangeResult(void) { return m_correctStepChangeResult; }
    static void SetCorrectStepChangeResult(bool correctStepChangeResult) { m_correctStepChangeResult = correctStepChangeResult; }
    static u32 GetUncertaintyInvalidFactor(void) { return (UNCERTAINTY_INVALID_FACTOR); }
    static u32 GetsdCalcLength(void) { return (m_sdCalcLength); }
    static void SetsdCalcLength(u32 sdCalcLength) { m_sdCalcLength = sdCalcLength; }

private:
    //Debug level that allows us to control debug output
    static u32 m_debugLevel;
    //Number of NTP sent packets in a burst.
    static u32 m_numInBurst;
    //round trip average packet delay, above which burst will be ignored (default 0.1s)
    static long double m_delayIgnoreThreshold;
    //Value of change in frequency above which the result will be ignored
    static long double m_massiveStep;
    //whether we should try to correct a stepped result or just remove
    static bool m_correctStepChangeResult;
    //number of the lowest latency packets over which the standard deviation of the burst is calculated
    static u32 m_sdCalcLength;
};

#endif /* APPLEVELVARS_H_ */
