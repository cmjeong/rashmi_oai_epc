///////////////////////////////////////////////////////////////////////////////
//
// MobnetTypes.h
//
// Mobile networks type definitions and ToString functions.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MobnetTypes_h_
#define __MobnetTypes_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <Radisys.h>
#include <system/UarfcnTypes.h>
#include <system/ArfcnTypes.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

typedef enum
{
    CS_DOMAIN = 0,
    PS_DOMAIN = 1,
    TOTAL_NUM_OF_DOMAIN = 2 // Used for invalid also
} DomainIdent;

typedef enum
{   
    HO_TYPE_INTRA_RAT_INTRA_FREQ = 0,   // Intra-Rat (Intra Freq 3G to 3G HO).
    HO_TYPE_INTRA_RAT_INTER_FREQ,   // Intra-Rat (Inter Freq 3G to 3G HO).
    HO_TYPE_INTER_RAT,              // Inter-Rat (3G to 2G).
    HO_TYPE_UNDEFINED               // Undefined (invalid) HO type.
} HandoverType;

// Power Margin Selection Type
typedef enum
{
	POWER_MARGIN_TOTAL_ECNO_BASED = 0,
	POWER_MARGIN_RSSI_BASED
}PowerMarginSelectionType;

typedef u16 ScramblingCode;

#ifdef __cplusplus

// These are so common that there is a strong likelihood of conflict with
// 3rd party or ASN1 compiled headers so bung them in their own namespace.
// Don't really wanna bung them in threeway namespace as we'll then have
// to remove "using namespace threeway" from a lot of code.
// TODO: Move all basic mobnet types into this namespace?
namespace rsysmob
{

typedef u16 Mnc;            // 0-999?
typedef u16 Mcc;            // 0-999?
typedef u16 Lac;            // 0-0xffff
typedef u8  Rac;            // 0-0xff
typedef u32 CellIdentity;   // 0-0x0fffffff
typedef u16 Sac;            // 0-0xffff
typedef u16 RncId;          // 0-0xffff
typedef u32 ExtendedRncId;  // 0-0x????????

typedef enum
{
    AS_UNKNOWN,
    AS_R99,
    AS_R4,
    AS_R5,
    AS_R6,
    AS_R7,
    AS_R8
} AccessStratumRelease;

typedef enum
{
    UE_CSG_CAPABLE,
    UE_NOT_CSG_CAPABLE
} UeCsgCapability;

typedef enum
{
    UE_REG_CAUSE_EMERGENCY_CALL,
    UE_REG_CAUSE_NORMAL
} UeRegistrationCause;

typedef enum
{
    R99DL_32k,
    R99DL_64k,
    R99DL_128k,
    R99DL_384k

} R99DlCapabilityHsdpa;

typedef enum
{
    DL_SPREADING_FACTOR_4,
    DL_SPREADING_FACTOR_8,
    DL_SPREADING_FACTOR_16,
    DL_SPREADING_FACTOR_32,
    DL_SPREADING_FACTOR_64,
    DL_SPREADING_FACTOR_128,
    DL_SPREADING_FACTOR_256,
    DL_SPREADING_FACTOR_512,

    // Bearers on FACH do not require a DL SF
    DL_SPREADING_FACTOR_NONE,

} DlSpreadingFactor;

// Traffic Volume Event Type
typedef enum TrafficVolumeEventType_tag
{
    FACH_ABOVE_THRESHOLD,
    FACH_BELOW_THRESHOLD,
    DCH_ABOVE_THRESHOLD,
    DCH_BELOW_THRESHOLD,
    FACH_IDLE

}TrafficVolumeEventType;

// traffic Volume Event Direction Type
typedef enum TrafficVolumeEventDirection_tag
{
    THRESHOLD_EXCEEDED_IN_UPLINK,
    THRESHOLD_EXCEEDED_IN_DOWNLINK,
    THRESHOLD_NOT_EXCEEDED

}TrafficVolumeEventDirection;


const char *TrafficVolumeEventTypeToString (TrafficVolumeEventType eventType);
const char *TrafficVolumeEventDirectionToString (TrafficVolumeEventDirection eventDirection);

// lifted from 25.413
static const u8 Ranap_PriorityLevel_highest = 1;
static const u8 Ranap_PriorityLevel_lowest = 14;
static const u8 Ranap_PriorityLevel_none = 15;


const char * accessStratumReleaseToString(AccessStratumRelease asRel);
const char * ueCsgCapabilityToString(UeCsgCapability ueCsg);
const char * ueRegistrationCauseToString(UeRegistrationCause regCause);
const char * r99DlCapabilityHsdpaToString(R99DlCapabilityHsdpa dlCapWithHs);

}

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class MobnetTypes
{
public:
    static const char * DomainToString(DomainIdent domain);
    static const char * EstCauseToString(u8 establishmentCause);
};
#else

#endif

#endif

