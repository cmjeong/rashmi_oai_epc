///////////////////////////////////////////////////////////////////////////////
//
// Tr196AlarmEnums.h
//
// IDs of all possible GSM Bands.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#if (!defined(__Tr196AlarmEnums_h_) || defined(ENUM_GENERATE_STRINGS) || defined(ENUM_GENERATE_TABLE) || defined(ENUM_GENERATE_THE_FROM_STRING_FUNCTION))

#if (!defined(ENUM_GENERATE_STRINGS) && !defined(ENUM_GENERATE_TABLE) && !defined(ENUM_GENERATE_THE_FROM_STRING_FUNCTION))
    #define __Tr196AlarmEnums_h_
#endif

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/EnumToString.h>

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

ENUM_START(NotificationTypeId)
{
    ENUM_ELEMENT_DUPLICATE(    NOTIFICATION_TYPE_FIRST,         0 )
    ENUM_ELEMENT_VALUE_STRING( NOTIFICATION_TYPE_NEW_ALARM,     0,  "NewAlarm")
    ENUM_ELEMENT_VALUE_STRING( NOTIFICATION_TYPE_CHANGED_ALARM, 1,  "ChangedAlarm")
    ENUM_ELEMENT_VALUE_STRING( NOTIFICATION_TYPE_CLEARED_ALARM, 2,  "ClearedAlarm")
    ENUM_ELEMENT_DUPLICATE(    NOTIFICATION_TYPE_LAST,          2 )
}
ENUM_END(NotificationTypeId)




#endif
