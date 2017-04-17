///////////////////////////////////////////////////////////////////////////////
//
// RemScanStatusId.h
//
// Enum of Alarm Severity (percieved).
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#if (!defined(__RemScanStatusId_h_) || defined(ENUM_GENERATE_STRINGS) || defined(ENUM_GENERATE_TABLE) || defined(ENUM_GENERATE_THE_FROM_STRING_FUNCTION))

#if (!defined(ENUM_GENERATE_STRINGS) && !defined(ENUM_GENERATE_TABLE) && !defined(ENUM_GENERATE_THE_FROM_STRING_FUNCTION))
    #define __RemScanStatusId_h_
#endif

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/EnumToString.h>

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

ENUM_START(RemScanStatusId)
{
    ENUM_ELEMENT_VALUE_STRING( REM_SCAN_STATUS_INDETERMINATE,        0,  "Indeterminate")
    ENUM_ELEMENT_VALUE_STRING( REM_SCAN_STATUS_IN_PROGRESS,          1,  "InProgress")
    ENUM_ELEMENT_VALUE_STRING( REM_SCAN_STATUS_SUCCESS,              2,  "Success")
    ENUM_ELEMENT_VALUE_STRING( REM_SCAN_STATUS_ERROR,                3,  "Error")
    ENUM_ELEMENT_VALUE_STRING( REM_SCAN_STATUS_ERROR_TIMEOUT,        4,  "Error_TIMEOUT")
}
ENUM_END(RemScanStatusId)


#endif
