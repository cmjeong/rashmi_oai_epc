///////////////////////////////////////////////////////////////////////////////
//
// UmtsBandId.cpp
//
// Implementation of EnumToString.h functions.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "UmtsBandId.h"

/*
 * Generate the function that lets us get the string equivalent of an enum value.
 */

#define ENUM_GENERATE_STRINGS

#include "UmtsBandId.h"

#undef ENUM_GENERATE_STRINGS

#define ENUM_GENERATE_THE_FROM_STRING_FUNCTION

#include "UmtsBandId.h"

#undef ENUM_GENERATE_THE_FROM_STRING_FUNCTION

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////
static const char * m_umtsBandId_DetailedString[UBAND_NUMBER_OF] = {
        "{invalid}",
        "I (fdd2100)",
        "II (fdd1900)",
        "III (fdd1800)",
        "IV (1700-aws)",
        "V (fdd850)",
        "VI (fdd800-japan)",
        "VII (2600-imtE)",
        "VIII (fdd900)",
        "IX (fdd1700-japan)",
        "X (fdd1700)",
        "XI (fdd1500-japan)",
        "XII (700smh-A/B/lowerC)",
        "XIII (700smh-upperC)",
        "XIV (700smh-D)",
};

const char * UmtsBandIdToDetailedString(UmtsBandId umtsBandID)
{
    if(umtsBandID > UBAND_LAST)
    {
        // This is possible - given that more bands are supported in
        // rel 6 than in this Uband list!
        return "unknown band";
    }

    return m_umtsBandId_DetailedString[umtsBandID];
}
