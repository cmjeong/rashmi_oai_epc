///////////////////////////////////////////////////////////////////////////////
//
// LedInfo.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "LedInfo.h"

using namespace std;
using namespace boost;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Functions
///////////////////////////////////////////////////////////////////////////////

const char* ledPatternToString(LedPattern lp)
{
    switch (lp)
    {
        case LED_SET_OFF:
            return "OFF";

        case LED_SET_ON:
            return "ON";

        case LED_SET_FLASHING:
            return "FLASHING";

        case LED_SAME_PATTERN:
            return "SAME PATTERN";

        case LED_SET_BLINKING:
        case LED_SET_FADING:
        default:
            return "NOT SUPPORTED";
    }
};


const char* ledColourToString(LedColour colour)
{
    switch (colour)
    {
        case LED_NONE:
            return "NONE";
        case LED_GREEN:
            return "GREEN";
        case LED_RED:
            return "RED";
        case LED_YELLOW:
            return "YELLOW";
        case LED_SAME_COLOUR:
            return "SAME COLOUR";
        default:
            return "Colour UNKOWN";
    }
};


const char* ledEventToString(LedEvent event)
{
    switch (event)
    {
        case POWER_ON:
            return "Power On";
        case POWER_ON_SELF_TEST:
            return "Power On Self Test";
        case TEMPERATURE_OUT_OF_RANGE:
            return "Temperature Out Of Range";
        case FAP_ERROR:
            return "Fap Error";
        case CONNECT_TO_SERVER:
            return "Connect To Server";
        case NO_CONNECTION_TO_SERVER:
            return "No Connection to Server";
        case NOT_OPERATIONAL:
            return "Not Operational";
        case OPERATIONAL_ERROR:
            return "Operational Error";
        case OPERATIONAL:
            return "Operational";
    /* without GPS */
        case REM_IN_PROGRESS:
            return "Rem In Progress";
        case HMS_ACCEPTS_REM_RESULTS:
            return "HMS Accept Rem Results";
        case HNB_IS_LOCATION_LOCKED:
            return "HNB is Location Locked";
        case HNB_HAS_NOT_STARTED_REM:
            return "HNB Has Not Started REM";
    /* with GPS */
        case LOCATION_ACQUISITION_NOT_STARTED:
            return "Location Acquisition Not Started";
        case DETERMINING_LOCATION:
            return "Determining Location";
        case WAITING_FOR_LOCATION_ACCEPTANCE:
            return "Waiting For Location Acceptance";
        case LOCATION_ACCEPTED:
            return "Location Accepted";
        case UNABLE_TO_DETERMINE_LOCATION:
            return "Unable To Determine Location";
        default:
            return "UNKOWN event";
    }
};



