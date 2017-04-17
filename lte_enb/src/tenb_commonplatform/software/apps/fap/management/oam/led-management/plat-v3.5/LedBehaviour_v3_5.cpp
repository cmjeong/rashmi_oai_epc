///////////////////////////////////////////////////////////////////////////////
//
// LedBehaviour_v3_5.cpp
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

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "LedBehaviour_v3_5.h"
#include "LedTypes_v3_5.h"

using namespace std;
using namespace boost;
using namespace threeway;

void LedBehaviour_v3_5::LoadDefaultMap(map<LedEvent, LedMap> &map)
{
    RSYS_ASSERT( map.size() == 0 );

    /* POWER_ON */
    LedMap ledMap;
    for (u32 i=0; i < LED_MAX_NUMBER; ++i)
    {
        ledMap.l[i].colour  = LED_NONE;
        ledMap.l[i].pattern = LED_SET_OFF;
    }

    ledMap.l[LED_ALARM].pattern    = LED_SET_OFF;
    ledMap.l[LED_ALARM].colour     = LED_NONE;
    ledMap.l[LED_ACCESS].pattern   = LED_SET_OFF;
    ledMap.l[LED_ACCESS].colour    = LED_NONE;
    map.insert( make_pair(POWER_ON, ledMap) );

    /* POWER_ON_SELF_TEST */
    ledMap.l[LED_ALARM].pattern    = LED_SET_OFF;
    ledMap.l[LED_ALARM].colour     = LED_NONE;
    ledMap.l[LED_ACCESS].pattern   = LED_SET_OFF;
    ledMap.l[LED_ACCESS].colour    = LED_NONE;
    map.insert( make_pair(POWER_ON_SELF_TEST, ledMap) );

    /* TEMPERATURE_OUT_OF_RANGE */
    ledMap.l[LED_ALARM].pattern    = LED_SET_ON;
    ledMap.l[LED_ALARM].colour     = LED_RED;
    ledMap.l[LED_ACCESS].pattern   = LED_SET_OFF;
    ledMap.l[LED_ACCESS].colour    = LED_NONE;
    map.insert( make_pair(TEMPERATURE_OUT_OF_RANGE, ledMap) );

    /* FAP_ERROR */
    ledMap.l[LED_ALARM].pattern    = LED_SET_ON;
    ledMap.l[LED_ALARM].colour     = LED_RED;
    ledMap.l[LED_ACCESS].pattern   = LED_SET_OFF;
    ledMap.l[LED_ACCESS].colour    = LED_NONE;
    map.insert( make_pair(FAP_ERROR, ledMap) );

    /* CONNECT_TO_SERVER */
    ledMap.l[LED_ALARM].pattern    = LED_SET_OFF;
    ledMap.l[LED_ALARM].colour     = LED_NONE;
    ledMap.l[LED_ACCESS].pattern   = LED_SET_OFF;
    ledMap.l[LED_ACCESS].colour    = LED_NONE;
    map.insert( make_pair(CONNECT_TO_SERVER, ledMap) );

    /* NO_CONNECTION_TO_SERVER */
    ledMap.l[LED_ALARM].pattern    = LED_SET_ON;
    ledMap.l[LED_ALARM].colour     = LED_RED;
    ledMap.l[LED_ACCESS].pattern   = LED_SET_OFF;
    ledMap.l[LED_ACCESS].colour    = LED_NONE;
    map.insert( make_pair(NO_CONNECTION_TO_SERVER, ledMap) );

    /* NOT_OPERATIONAL */
    ledMap.l[LED_ALARM].pattern    = LED_SET_OFF;
    ledMap.l[LED_ALARM].colour     = LED_NONE;
    ledMap.l[LED_ACCESS].pattern   = LED_SET_FLASHING;
    ledMap.l[LED_ACCESS].colour    = LED_GREEN;
    map.insert( make_pair(NOT_OPERATIONAL, ledMap) );

    /* OPERATIONAL_ERROR */
    ledMap.l[LED_ALARM].pattern    = LED_SET_ON;
    ledMap.l[LED_ALARM].colour     = LED_RED;
    ledMap.l[LED_ACCESS].pattern   = LED_SET_OFF;
    ledMap.l[LED_ACCESS].colour    = LED_NONE;
    map.insert( make_pair(OPERATIONAL_ERROR, ledMap) );

    /* OPERATIONAL */
    ledMap.l[LED_ALARM].pattern    = LED_SET_OFF;
    ledMap.l[LED_ALARM].colour     = LED_NONE;
    ledMap.l[LED_ACCESS].pattern   = LED_SET_ON;
    ledMap.l[LED_ACCESS].colour    = LED_GREEN;
    map.insert( make_pair(OPERATIONAL, ledMap) );

    // Not used in HW 3.5
//    ev = DETERMINING_LOCATION;
//    ev = WAITING_FOR_LOCATION_ACCEPTANCE;
//    ev = REM_IN_PROGRESS;
//    ev = HMS_ACCEPTS_REM_RESULTS;
//    ev = LOCATION_ACCEPTED;
//    ev = HNB_IS_LOCATION_LOCKED;
//    ev = HNB_HAS_NOT_STARTED_REM;
//    ev = LOCATION_ACQUISITION_NOT_STARTED;
//    ev = UNABLE_TO_DETERMINE_LOCATION;

}
