///////////////////////////////////////////////////////////////////////////////
//
// MobileIdentity.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MobileIdentity.h"

using namespace std;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

std::string MobileIdentity::GetMobileIdentityAsString(
        MobileIdentityType identityType,
        const u32* identityDigits,
        u32 identityLength)
{
    ENTER();

    ostringstream mobileIdString;
    char identityTypeStr[16], identityStr[32];

    switch (identityType)
    {
    case IMSI:
    case IMEI:
        snprintf (identityTypeStr, sizeof(identityTypeStr),
                  "%s", identityType == IMSI ? "IMSI" : "IMEI");

        for (u32 i = 0; i < identityLength; i++)
        {
            snprintf (identityStr + i, sizeof(identityStr) - i,
                      "%" PRIX32, identityDigits[i]);
        }//end for
        break;

    case TMSI_P_TMSI:
        snprintf (identityTypeStr, sizeof(identityTypeStr), "TMSI");

        for (u32 i = 0, digitIndex = 0; i < identityLength; i++)
        {
            u8 nextDigit = (u8) ((identityDigits[i] & 0xf0) >> 4);
            identityStr[digitIndex++] = nextDigit <= 9 ? nextDigit + 48 : nextDigit + 55;
            nextDigit = (u8) (identityDigits[i] & 0x0f);
            identityStr[digitIndex++] = nextDigit <= 9 ? nextDigit + 48 : nextDigit + 55;
        }//end for
        break;

    }//end switch

    mobileIdString << identityTypeStr << ":" << identityStr;

    RETURN(mobileIdString.str());
}

}
