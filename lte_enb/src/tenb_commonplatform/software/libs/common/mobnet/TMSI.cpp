///////////////////////////////////////////////////////////////////////////////
//
// TMSI.cpp
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

#include "TMSI.h"

using namespace std;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

TMSI::TMSI() :
    HexString(TMSI_NUM_HEX_DIGITS, TMSI_NUM_HEX_DIGITS)
{
    ENTER();

    EXIT();
}

TMSI::TMSI(const u8 * hexArray) :
    HexString(TMSI_NUM_HEX_DIGITS, TMSI_NUM_HEX_DIGITS)
{
    ENTER();

    SetHexArray(hexArray, TMSI_NUM_HEX_DIGITS);

    EXIT();
}

TMSI::~TMSI()
{
    ENTER();

    EXIT();
}

void TMSI::SetTmsiFromAsnStyle(const u8 *tmsiValue)
{
   ENTER();

   // This is actually BCD encoded digits...
   u8 expandedTmsi[TMSI_NUM_HEX_DIGITS+1]; // +1 for padding
   u8 digitCount = 0;
   for (u8 i=0; i<4; i++)
   {
      if(TMSI_NUM_HEX_DIGITS < digitCount)
      {
         expandedTmsi[digitCount++] = tmsiValue[i] & 0x0f;
         expandedTmsi[digitCount++] = (tmsiValue[i] & 0xf0) >> 4;
      }
   }
   SetHexArray (expandedTmsi, TMSI_NUM_HEX_DIGITS);

   EXIT();
}

void TMSI::SetTmsiFromULongArray(const unsigned long *tmsiValue)
{
    u8 tmsiDigits[4];
    tmsiDigits[0] = (u8)tmsiValue[0];
    tmsiDigits[1] = (u8)tmsiValue[1];
    tmsiDigits[2] = (u8)tmsiValue[2];
    tmsiDigits[3] = (u8)tmsiValue[3];
    SetTmsiFromAsnStyle(tmsiDigits);
}

u8 TMSI::GetTmsiAsAsnStyle(u8 *tmsiValue, u32 tmsiValueSize) const
{
    ENTER();

    RSYS_ASSERT(tmsiValueSize >= 4);

    u8 expandedTmsi[TMSI_NUM_HEX_DIGITS+1]; // +1 for padding
    u32 digitCount = 0;
    u8 tmsiLength = 0;
    
    if (GetByteArray(expandedTmsi, TMSI_NUM_HEX_DIGITS))
    {
        tmsiLength = 4;
        for (u8 i=0; i<4; i++, digitCount+=2)
        {
            tmsiValue[i] =  (expandedTmsi[digitCount] & 0x0f);
            tmsiValue[i] |= ((expandedTmsi[digitCount+1] & 0x0f) << 4);
        }
    }

    RETURN(tmsiLength);
}
