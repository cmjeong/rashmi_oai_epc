///////////////////////////////////////////////////////////////////////////////
//
// AlarmEventType.h
//
// Enum of Alarm Event Type.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#if (!defined(__AlarmEventType_h_) || defined(ENUM_GENERATE_STRINGS) || defined(ENUM_GENERATE_TABLE) || defined(ENUM_GENERATE_THE_FROM_STRING_FUNCTION))

#if (!defined(ENUM_GENERATE_STRINGS) && !defined(ENUM_GENERATE_TABLE) && !defined(ENUM_GENERATE_THE_FROM_STRING_FUNCTION))
    #define __AlarmEventType_h_
#endif

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/EnumToString.h>

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////


ENUM_START(AlarmEventType)
{
    ENUM_ELEMENT_DUPLICATE(    ALARM_EVENT_TYPE_BEGIN, 0)
    ENUM_ELEMENT_VALUE_STRING( ALARM_EVENT_TYPE_COMMUNICATION_FAULURE,  0,  "CommunicationFailure")
    ENUM_ELEMENT_VALUE_STRING( ALARM_EVENT_TYPE_QUALITY_OF_SERVICE,     1,  "QualityOfService")
    ENUM_ELEMENT_VALUE_STRING( ALARM_EVENT_TYPE_PROCESSING_FAILURE,     2,  "ProcessingFailure")
    ENUM_ELEMENT_VALUE_STRING( ALARM_EVENT_TYPE_EQUIPMENT_FAILURE,      3,  "EquipmentFailure")
    ENUM_ELEMENT_VALUE_STRING( ALARM_EVENT_TYPE_ENVIRONMENT_FAILURE,    4,  "EnvironmentFailure")
    ENUM_ELEMENT(              ALARM_EVENT_TYPE_END )
}
ENUM_END(AlarmEventType)


#endif
