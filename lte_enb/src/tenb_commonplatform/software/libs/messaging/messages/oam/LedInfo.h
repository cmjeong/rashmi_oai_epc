///////////////////////////////////////////////////////////////////////////////
//
// LedInfo.h
//
// LED states and patterns
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __LedInfo_h_
#define __LedInfo_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <Radisys.h>

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////
/* 4 in HW 4.x, 3 in HW 3.5 (although only 2 are used) */
#ifdef HARDWARE_hbs2_3_5
static const u8 LED_MAX_NUMBER = 3;
#else
static const u8 LED_MAX_NUMBER = 4;
#endif

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

/* States for a LED */

typedef enum
{
    LED_SET_OFF = 0,
    LED_SET_ON,
    LED_SET_FLASHING,
    LED_SET_BLINKING,
    LED_SET_FADING,
    LED_SAME_PATTERN,

    LED_MAX_PATTERN
} LedPattern;


/* Colours for a LED*/
typedef enum
{
    LED_NONE  = 0,
    LED_GREEN,
    LED_RED,
    LED_YELLOW,
    LED_SAME_COLOUR,

    LED_MAX_COLOUR
} LedColour;

/* Entry Map for LEDs */
typedef struct {
    LedColour    colour;
    LedPattern   pattern;
} LedMapEntry;

/* Map for LEDs */
typedef struct {
    // HW 4.x: Power, Internet, Location, Service
    // HW 3.5: Alarm, Service
    LedMapEntry l[LED_MAX_NUMBER];
} LedMap;


/* Event Scenarios for LED */
typedef enum
{
    POWER_ON = 0,
    POWER_ON_SELF_TEST,
    TEMPERATURE_OUT_OF_RANGE,
    FAP_ERROR,
    CONNECT_TO_SERVER,
    NO_CONNECTION_TO_SERVER,
    NOT_OPERATIONAL,
    OPERATIONAL_ERROR,
    OPERATIONAL,
    /* without GPS */
    REM_IN_PROGRESS,
    HMS_ACCEPTS_REM_RESULTS,
    HNB_IS_LOCATION_LOCKED,         // Not used at the moment
    HNB_HAS_NOT_STARTED_REM,
    /* with GPS */
    LOCATION_ACQUISITION_NOT_STARTED,
    DETERMINING_LOCATION,
    WAITING_FOR_LOCATION_ACCEPTANCE,
    LOCATION_ACCEPTED,
    UNABLE_TO_DETERMINE_LOCATION,

    MAX_EVENT_SCENARIOS_NUMBER
} LedEvent;


const char* ledPatternToString(LedPattern);
const char* ledColourToString(LedColour);
const char* ledEventToString(LedEvent);


#endif
