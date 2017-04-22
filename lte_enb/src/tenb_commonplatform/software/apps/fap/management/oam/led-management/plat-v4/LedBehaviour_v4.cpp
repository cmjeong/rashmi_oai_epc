///////////////////////////////////////////////////////////////////////////////
//
// LedBehaviour_v4.cpp
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
#include <messaging/messages/oam/LedInfo.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "LedBehaviour_v4.h"

using namespace std;
using namespace boost;
using namespace threeway;

void LedBehaviour_v4::LoadDefaultMap(map<LedEvent, LedMap> &map)
{
    RSYS_ASSERT( map.size() == 0 );

    LedMap ledMap;
    for (int i=0; i < LED_MAX_NUMBER; ++i)
    {
        ledMap.l[i].colour  = LED_NONE;
        ledMap.l[i].pattern = LED_SET_OFF;
    }

    /* POWER_ON */
    ledMap.l[LED_POWER].colour  = LED_YELLOW;
    ledMap.l[LED_POWER].pattern = LED_SET_ON;
    ledMap.l[LED_INTERNET].colour  = LED_NONE;
    ledMap.l[LED_INTERNET].pattern = LED_SET_OFF;
    ledMap.l[LED_LOCATION].colour  = LED_SAME_COLOUR;
    ledMap.l[LED_LOCATION].pattern = LED_SAME_PATTERN;
    ledMap.l[LED_SERVICE].colour  = LED_NONE;
    ledMap.l[LED_SERVICE].pattern = LED_SET_OFF;
    map.insert( make_pair(POWER_ON, ledMap) );

    /* POWER_ON_SELF_TEST */
    ledMap.l[LED_POWER].colour  = LED_GREEN;
    ledMap.l[LED_POWER].pattern = LED_SET_FLASHING;
    ledMap.l[LED_INTERNET].colour  = LED_NONE;
    ledMap.l[LED_INTERNET].pattern = LED_SET_OFF;
    ledMap.l[LED_LOCATION].colour  = LED_SAME_COLOUR;
    ledMap.l[LED_LOCATION].pattern = LED_SAME_PATTERN;
    ledMap.l[LED_SERVICE].colour  = LED_NONE;
    ledMap.l[LED_SERVICE].pattern = LED_SET_OFF;
    map.insert( make_pair(POWER_ON_SELF_TEST, ledMap) );

    /* TEMPERATURE_OUT_OF_RANGE */
    ledMap.l[LED_POWER].colour  = LED_RED;
    ledMap.l[LED_POWER].pattern = LED_SET_FLASHING;
    ledMap.l[LED_INTERNET].colour  = LED_NONE;
    ledMap.l[LED_INTERNET].pattern = LED_SET_OFF;
    ledMap.l[LED_LOCATION].colour  = LED_SAME_COLOUR;
    ledMap.l[LED_LOCATION].pattern = LED_SAME_PATTERN;
    ledMap.l[LED_SERVICE].colour  = LED_NONE;
    ledMap.l[LED_SERVICE].pattern = LED_SET_OFF;
    map.insert( make_pair(TEMPERATURE_OUT_OF_RANGE, ledMap) );

    /* FAP_ERROR */
    ledMap.l[LED_POWER].colour  = LED_RED;
    ledMap.l[LED_POWER].pattern = LED_SET_ON;
    ledMap.l[LED_INTERNET].colour  = LED_NONE;
    ledMap.l[LED_INTERNET].pattern = LED_SET_OFF;
    ledMap.l[LED_LOCATION].colour  = LED_SAME_COLOUR;
    ledMap.l[LED_LOCATION].pattern = LED_SAME_PATTERN;
    ledMap.l[LED_SERVICE].colour  = LED_NONE;
    ledMap.l[LED_SERVICE].pattern = LED_SET_OFF;
    map.insert( make_pair(FAP_ERROR, ledMap) );

    /* CONNECT_TO_SERVER */
    ledMap.l[LED_POWER].colour  = LED_GREEN;
    ledMap.l[LED_POWER].pattern = LED_SET_ON;
    ledMap.l[LED_INTERNET].colour  = LED_GREEN;
    ledMap.l[LED_INTERNET].pattern = LED_SET_FLASHING;
    ledMap.l[LED_LOCATION].colour  = LED_SAME_COLOUR;
    ledMap.l[LED_LOCATION].pattern = LED_SAME_PATTERN;
    ledMap.l[LED_SERVICE].colour  = LED_NONE;
    ledMap.l[LED_SERVICE].pattern = LED_SET_OFF;
    map.insert( make_pair(CONNECT_TO_SERVER, ledMap) );

    /* NO_CONNECTION_TO_SERVER */
    ledMap.l[LED_POWER].colour  = LED_GREEN;
    ledMap.l[LED_POWER].pattern = LED_SET_ON;
    ledMap.l[LED_INTERNET].colour  = LED_RED;
    ledMap.l[LED_INTERNET].pattern = LED_SET_ON;
    ledMap.l[LED_LOCATION].colour  = LED_SAME_COLOUR;
    ledMap.l[LED_LOCATION].pattern = LED_SAME_PATTERN;
    ledMap.l[LED_SERVICE].colour  = LED_NONE;
    ledMap.l[LED_SERVICE].pattern = LED_SET_OFF;
    map.insert( make_pair(NO_CONNECTION_TO_SERVER, ledMap) );

    /* NOT_OPERATIONAL */
    ledMap.l[LED_POWER].colour  = LED_GREEN;
    ledMap.l[LED_POWER].pattern = LED_SET_ON;
    ledMap.l[LED_INTERNET].colour  = LED_GREEN;
    ledMap.l[LED_INTERNET].pattern = LED_SET_ON;
    ledMap.l[LED_LOCATION].colour  = LED_SAME_COLOUR;
    ledMap.l[LED_LOCATION].pattern = LED_SAME_PATTERN;
    ledMap.l[LED_SERVICE].colour  = LED_GREEN;
    ledMap.l[LED_SERVICE].pattern = LED_SET_FLASHING;
    map.insert( make_pair(NOT_OPERATIONAL, ledMap) );

    /* OPERATIONAL_ERROR */
    ledMap.l[LED_POWER].colour  = LED_GREEN;
    ledMap.l[LED_POWER].pattern = LED_SET_ON;
    ledMap.l[LED_INTERNET].colour  = LED_GREEN;
    ledMap.l[LED_INTERNET].pattern = LED_SET_ON;
    ledMap.l[LED_LOCATION].colour  = LED_SAME_COLOUR;
    ledMap.l[LED_LOCATION].pattern = LED_SAME_PATTERN;
    ledMap.l[LED_SERVICE].colour  = LED_RED;
    ledMap.l[LED_SERVICE].pattern = LED_SET_ON;
    map.insert( make_pair(OPERATIONAL_ERROR, ledMap) );

    /* OPERATIONAL */
    ledMap.l[LED_POWER].colour  = LED_GREEN;
    ledMap.l[LED_POWER].pattern = LED_SET_ON;
    ledMap.l[LED_INTERNET].colour  = LED_GREEN;
    ledMap.l[LED_INTERNET].pattern = LED_SET_ON;
    ledMap.l[LED_LOCATION].colour  = LED_SAME_COLOUR;
    ledMap.l[LED_LOCATION].pattern = LED_SAME_PATTERN;
    ledMap.l[LED_SERVICE].colour  = LED_GREEN;
    ledMap.l[LED_SERVICE].pattern = LED_SET_ON;
    map.insert( make_pair(OPERATIONAL, ledMap) );

    /* REM_IN_PROGRESS */
    ledMap.l[LED_POWER].colour  = LED_SAME_COLOUR;
    ledMap.l[LED_POWER].pattern = LED_SAME_PATTERN;
    ledMap.l[LED_INTERNET].colour  = LED_SAME_COLOUR;
    ledMap.l[LED_INTERNET].pattern = LED_SAME_PATTERN;
    ledMap.l[LED_LOCATION].colour  = LED_GREEN;
    ledMap.l[LED_LOCATION].pattern = LED_SET_FLASHING;
    ledMap.l[LED_SERVICE].colour  = LED_SAME_COLOUR;
    ledMap.l[LED_SERVICE].pattern = LED_SAME_PATTERN;
    map.insert( make_pair(REM_IN_PROGRESS, ledMap) );

    map.insert( make_pair(DETERMINING_LOCATION, ledMap) );
    map.insert( make_pair(WAITING_FOR_LOCATION_ACCEPTANCE, ledMap) );

    /* HMS_ACCEPTS_REM_RESULTS */
    ledMap.l[LED_POWER].colour  = LED_SAME_COLOUR;
    ledMap.l[LED_POWER].pattern = LED_SAME_PATTERN;
    ledMap.l[LED_INTERNET].colour  = LED_SAME_COLOUR;
    ledMap.l[LED_INTERNET].pattern = LED_SAME_PATTERN;
    ledMap.l[LED_LOCATION].colour  = LED_GREEN;
    ledMap.l[LED_LOCATION].pattern = LED_SET_ON;
    ledMap.l[LED_SERVICE].colour  = LED_SAME_COLOUR;
    ledMap.l[LED_SERVICE].pattern = LED_SAME_PATTERN;
    map.insert( make_pair(HMS_ACCEPTS_REM_RESULTS, ledMap) );

    map.insert( make_pair(LOCATION_ACCEPTED, ledMap) );

    /* HNB_IS_LOCATION_LOCKED */
    ledMap.l[LED_POWER].colour  = LED_SAME_COLOUR;
    ledMap.l[LED_POWER].pattern = LED_SAME_PATTERN;
    ledMap.l[LED_INTERNET].colour  = LED_SAME_COLOUR;
    ledMap.l[LED_INTERNET].pattern = LED_SAME_PATTERN;
    ledMap.l[LED_LOCATION].colour  = LED_RED;
    ledMap.l[LED_LOCATION].pattern = LED_SET_ON;
    ledMap.l[LED_SERVICE].colour  = LED_SAME_COLOUR;
    ledMap.l[LED_SERVICE].pattern = LED_SAME_PATTERN;
    map.insert( make_pair(HNB_IS_LOCATION_LOCKED, ledMap) );

    /* HNB_HAS_NOT_STARTED_REM */
    ledMap.l[LED_POWER].colour  = LED_SAME_COLOUR;
    ledMap.l[LED_POWER].pattern = LED_SAME_PATTERN;
    ledMap.l[LED_INTERNET].colour  = LED_SAME_COLOUR;
    ledMap.l[LED_INTERNET].pattern = LED_SAME_PATTERN;
    ledMap.l[LED_LOCATION].colour  = LED_NONE;
    ledMap.l[LED_LOCATION].pattern = LED_SET_OFF;
    ledMap.l[LED_SERVICE].colour  = LED_SAME_COLOUR;
    ledMap.l[LED_SERVICE].pattern = LED_SAME_PATTERN;
    map.insert( make_pair(HNB_HAS_NOT_STARTED_REM, ledMap) );

    map.insert( make_pair(LOCATION_ACQUISITION_NOT_STARTED, ledMap) );

    /* UNABLE_TO_DETERMINE_LOCATION */
    ledMap.l[LED_POWER].colour  = LED_SAME_COLOUR;
    ledMap.l[LED_POWER].pattern = LED_SAME_PATTERN;
    ledMap.l[LED_INTERNET].colour  = LED_SAME_COLOUR;
    ledMap.l[LED_INTERNET].pattern = LED_SAME_PATTERN;
    ledMap.l[LED_LOCATION].colour  = LED_YELLOW;
    ledMap.l[LED_LOCATION].pattern = LED_SET_ON;
    ledMap.l[LED_SERVICE].colour  = LED_SAME_COLOUR;
    ledMap.l[LED_SERVICE].pattern = LED_SAME_PATTERN;
    map.insert( make_pair(UNABLE_TO_DETERMINE_LOCATION, ledMap) );

}

