///////////////////////////////////////////////////////////////////////////////
//
// AlarmPerceivedSeverity.h
//
// Enum of Alarm Severity (percieved).
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#if (!defined(__AlarmPerceivedSeverity_h_) || defined(ENUM_GENERATE_STRINGS) || defined(ENUM_GENERATE_TABLE) || defined(ENUM_GENERATE_THE_FROM_STRING_FUNCTION))

#if (!defined(ENUM_GENERATE_STRINGS) && !defined(ENUM_GENERATE_TABLE) && !defined(ENUM_GENERATE_THE_FROM_STRING_FUNCTION))
    #define __AlarmPerceivedSeverity_h_
#endif

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/EnumToString.h>

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////


ENUM_START(AlarmPerceivedSeverity)
{
    ENUM_ELEMENT_DUPLICATE(    ALARM_PERCEIVED_SEVERITY_BEGIN, 0)
    ENUM_ELEMENT_VALUE_STRING( ALARM_PERCEIVED_SEVERITY_CLEARED,        0,  "Cleared")
    ENUM_ELEMENT_VALUE_STRING( ALARM_PERCEIVED_SEVERITY_WARNING,        1,  "Warning")
    ENUM_ELEMENT_VALUE_STRING( ALARM_PERCEIVED_SEVERITY_MINOR,          2,  "Minor")
    ENUM_ELEMENT_VALUE_STRING( ALARM_PERCEIVED_SEVERITY_MAJOR,          3,  "Major")
    ENUM_ELEMENT_VALUE_STRING( ALARM_PERCEIVED_SEVERITY_CRITICAL,       4,  "Critical")
    ENUM_ELEMENT(              ALARM_PERCEIVED_SEVERITY_END)
}
ENUM_END(AlarmPerceivedSeverity)


#endif
