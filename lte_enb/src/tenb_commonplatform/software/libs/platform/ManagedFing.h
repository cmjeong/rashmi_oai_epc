///////////////////////////////////////////////////////////////////////////////
//
// ManagedFing.h
//
// Enum of "managed fings" i.e. blocks of code, protocol layers, modules etc
// that conform to the MF API of being able to set admin state and report op
// state internally to the FAP.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#if (!defined(__ManagedFing_h_) || defined(ENUM_GENERATE_STRINGS) || defined(ENUM_GENERATE_TABLE))

#if (!defined(ENUM_GENERATE_STRINGS) && !defined(ENUM_GENERATE_TABLE))
    #define __ManagedFing_h_
#endif

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/EnumToString.h>

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

ENUM_START(ManagedFing)
{
    ENUM_ELEMENT_VAL(MF_RADIO, 0) // Leave as first element as some code loops over this enum
    ENUM_ELEMENT(MF_UMTS_STACK)
    ENUM_ELEMENT(MF_IPSEC_TUNNEL)
    ENUM_ELEMENT(MF_ETH0)
    ENUM_ELEMENT(MF_SW_UPDATE)
    ENUM_ELEMENT(MF_REM_SCAN)
    ENUM_ELEMENT(MF_TEMPERATURE_MONITOR)
    ENUM_ELEMENT(MF_FREQUENCY_OFFSET)
    ENUM_ELEMENT(MF_HW_CONFIG)
    ENUM_ELEMENT(MF_TR069)
    ENUM_ELEMENT(MF_IKE)
    ENUM_ELEMENT(MF_SCTP)
    ENUM_ELEMENT(MF_HNBAP_RUA)
    ENUM_ELEMENT(MF_RANAP)
    ENUM_ELEMENT(MF_CS_USER_PLANE)
    ENUM_ELEMENT(MF_RRC)
    ENUM_ELEMENT(MF_RRM)
    ENUM_ELEMENT(MF_SM)

    ENUM_ELEMENT(MF_INVALID) // Leave as last as some code loops over this enum
}
ENUM_END(ManagedFing)

#endif
