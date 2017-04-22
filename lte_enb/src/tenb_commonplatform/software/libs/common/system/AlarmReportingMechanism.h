///////////////////////////////////////////////////////////////////////////////
//
// AlarmReportingMechanism.h
//
// Enum of Alarm Severity (percieved).
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#if (!defined(__AlarmReportingMechanism_h_) || defined(ENUM_GENERATE_STRINGS) || defined(ENUM_GENERATE_TABLE) || defined(ENUM_GENERATE_THE_FROM_STRING_FUNCTION))

#if (!defined(ENUM_GENERATE_STRINGS) && !defined(ENUM_GENERATE_TABLE) && !defined(ENUM_GENERATE_THE_FROM_STRING_FUNCTION))
    #define __AlarmReportingMechanism_h_
#endif

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/EnumToString.h>

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////


ENUM_START(AlarmReportingMechanism)
{
    ENUM_ELEMENT_DUPLICATE(    ALARM_REPORTING_MECHANISM_BEGIN, 0)
    ENUM_ELEMENT_VALUE_STRING( ALARM_REPORTING_MECHANISM_EXPEDITED,      0,  "0 Expedited")
    ENUM_ELEMENT_VALUE_STRING( ALARM_REPORTING_MECHANISM_QUEUED,         1,  "1 Queued")
    ENUM_ELEMENT_VALUE_STRING( ALARM_REPORTING_MECHANISM_LOGGED,         2,  "2 Logged")
    ENUM_ELEMENT_VALUE_STRING( ALARM_REPORTING_MECHANISM_DISABLED,       3,  "3 Disabled")
    ENUM_ELEMENT(              ALARM_REPORTING_MECHANISM_END)
}
ENUM_END(AlarmReportingMechanism)


#endif
