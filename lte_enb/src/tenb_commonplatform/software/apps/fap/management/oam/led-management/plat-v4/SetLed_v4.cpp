///////////////////////////////////////////////////////////////////////////////
//
// SetLed_v4.cpp
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
#include <stdio.h>
#include <messaging/messages/oam/OamLedStateInformInd.h>
#include <messaging/transport/MessagingEntity.h>


///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "SetLed_v4.h"
#include "LedTypes_v4.h"
#include "OamUserApplication.h"

using namespace std;
using namespace boost;
using namespace threeway;



void SetLed_v4::SetLed(u32 id, LedColour colour, LedPattern pattern)
{
    RSYS_ASSERT(id < LED_MAX_NUMBER );

    string ledStr;

    switch (id)
    {
        case LED_POWER:
            ledStr.assign("power");
            break;
        case LED_INTERNET:
            ledStr.assign("internet");
            break;
        case LED_LOCATION:
            ledStr.assign("location");
            break;
        case LED_SERVICE:
            ledStr.assign("service");
            break;
        default:
        {
            RSYS_ASSERT_FAIL("LED status for HW v4 not supported (value is: id->%"PRIu32", pattern->%s)",
							 (u32)id, ledPatternToString(pattern) );
            break;
        }
    }

    // Performs also a LED_SET_OFF
    ResetLed(ledStr);


    if (pattern == LED_SET_ON)
    {
        if (colour == LED_GREEN)
        {
            WriteLed(ledStr.c_str(), "green", "trigger", "default-on" );
        }
        else if (colour == LED_RED)
        {
            WriteLed(ledStr.c_str(), "red", "trigger", "default-on" );
        }
        else if (colour == LED_YELLOW)
        {
            WriteLed(ledStr.c_str(), "green", "trigger", "default-on" );
            WriteLed(ledStr.c_str(), "red", "trigger", "default-on" );
        }
    }
    else if (pattern == LED_SET_FLASHING)
    {
        if (colour == LED_GREEN)
        {
            WriteLed(ledStr.c_str(), "green", "trigger", "timer");
            WriteLed(ledStr.c_str(), "green", "delay_on", "500");
            WriteLed(ledStr.c_str(), "green", "delay_off", "500");
        }
        else if (colour == LED_RED)
        {
            WriteLed(ledStr.c_str(), "red", "trigger", "timer");
            WriteLed(ledStr.c_str(), "red", "delay_on", "500");
            WriteLed(ledStr.c_str(), "red", "delay_off", "500");
        }
        else if (colour == LED_YELLOW)
        {
            WriteLed(ledStr.c_str(), "green", "trigger", "timer");
            WriteLed(ledStr.c_str(), "green", "delay_on", "500");
            WriteLed(ledStr.c_str(), "green", "delay_off", "500");

            WriteLed(ledStr.c_str(), "red", "trigger", "timer");
            WriteLed(ledStr.c_str(), "red", "delay_on", "500");
            WriteLed(ledStr.c_str(), "red", "delay_off", "500");
        }
    }
    else if (pattern != LED_SET_OFF)
    {
    	/* LED_SET_OFF has already been performed by ResetLed() call */
        TRACE_PRINTF_LEV(TRACE_INFO, "SetLed V4: pattern %s not supported", ledPatternToString(pattern) );
        return;
    }

    OamLedStateInformInd ledStateInformInd( id, colour, pattern );
    OamUserApplication::GetInstance().SendMessage(ledStateInformInd, ENTITY_SERVICE_API, ENTITY_OAM);
}


/* ensures blinking and colours are reset */
void SetLed_v4::ResetLed(string &ledStr)
{
    WriteLed(ledStr.c_str(), "green", "trigger", "none");

    WriteLed(ledStr.c_str(), "red", "trigger", "none");
}


void SetLed_v4::WriteLed(const char *ledName, const char *colour,
                         const char *file, const char *value)
{
    char  buf[64];
    FILE *f;

    snprintf(buf, sizeof(buf), "/sys/class/leds/v4es:%s:%s/%s",
             colour, ledName, file);
    f = fopen(buf, "w");
    if(f)
    {
       //fprintf(f, value);
       fclose(f);
    }
}

