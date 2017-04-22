///////////////////////////////////////////////////////////////////////////////
//
// SetLed_v3_5.cpp
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

#include <messaging/messages/carb/CarbLedSetReq.h>
#include <messaging/messages/oam/OamLedStateInformInd.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "SetLed_v3_5.h"
#include "OamUserApplication.h"


using namespace std;
using namespace boost;
using namespace threeway;


SetLed_v3_5::SetLed_v3_5():
    m_ledStateMap()
{};


void SetLed_v3_5::SetLed(u32 id, LedColour colour, LedPattern pattern)
{
   RSYS_ASSERT(id < LED_MAX_NUMBER );

#if 0
   if(id >= LED_MAX_NUMBER)
   {
      switch (pattern)
      {
         case LED_SET_OFF:
            m_ledStateMap.intensity[id] = LED_OFF;
            break;
         case LED_SET_ON:
            m_ledStateMap.intensity[id] = LED_ON;
            break;
         case LED_SET_FLASHING:
            m_ledStateMap.intensity[id] = LED_FLASH_1_2;
            break;
         case LED_SET_BLINKING:
         case LED_SET_FADING:
         default:
            RSYS_ASSERT_FAIL("LED status for HW 3.5 not supported (value is %s)", ledPatternToString(pattern) );
            break;
      }
   }
#endif
   /* LEDs in 3.5 HW are:
    * 0 = Alarm
    * 2 = Access
    * 1 = Spare LED / not all boards have it */
   if ( id == LED_ALARM || id == LED_ACCESS )
   {
      CarbLedSetReq carbLedSetReq( m_ledStateMap.intensity, m_ledStateMap.pulsate );
      OamUserApplication::GetInstance().SendMessage(carbLedSetReq, ENTITY_CARB, ENTITY_OAM);

      OamLedStateInformInd ledStateInformInd( id, colour, pattern );
      OamUserApplication::GetInstance().SendMessage(ledStateInformInd, ENTITY_SERVICE_API, ENTITY_OAM);
   }
}
