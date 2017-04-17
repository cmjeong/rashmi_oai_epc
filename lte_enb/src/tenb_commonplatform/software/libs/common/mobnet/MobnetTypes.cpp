///////////////////////////////////////////////////////////////////////////////
//
// MobnetTypes.cpp
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

#include "MobnetTypes.h"

///////////////////////////////////////////////////////////////////////////////
// Functions
///////////////////////////////////////////////////////////////////////////////

namespace rsysmob
{

const char *TrafficVolumeEventTypeToString (TrafficVolumeEventType eventType)
{
    switch (eventType)
    {
    case FACH_ABOVE_THRESHOLD:
        return "FACH ABOVE THRESHOLD";
    case FACH_BELOW_THRESHOLD:
        return "FACH BELOW THRESHOLD";
    case DCH_ABOVE_THRESHOLD:
        return "DCH ABOVE THRESHOLD";
    case DCH_BELOW_THRESHOLD:
        return "DCH BELOW THRESHOLD";
    case FACH_IDLE:
        return "FACH IDLE";
    default:
        return "Unknown";
    }
}

const char *TrafficVolumeEventDirectionToString (TrafficVolumeEventDirection eventDirection)
{
    switch (eventDirection)
    {
    case THRESHOLD_EXCEEDED_IN_UPLINK:
        return "UPLINK THRESHOLD EXCEEDED";
    case THRESHOLD_EXCEEDED_IN_DOWNLINK:
        return "DOWNLINK THRESHOLD EXCEEDED";
    default:
        return "Unknown";
    }
}

const char * accessStratumReleaseToString(AccessStratumRelease asRel)
{
    switch(asRel)
    {
    case AS_R99: return "R99"; break;
    case AS_R4: return "R4"; break;
    case AS_R5: return "R5"; break;
    case AS_R6: return "R6"; break;
    case AS_R7: return "R7"; break;
    case AS_R8: return "R8"; break;
    case AS_UNKNOWN: return "UNKNOWN"; break;
    // No default, let compiler tell us about missing elements.
    }

    RSYS_ASSERT(false);
    return "";
}

const char * ueCsgCapabilityToString(UeCsgCapability ueCsg)
{
    switch(ueCsg)
    {
    case UE_CSG_CAPABLE: return "CsgCapable"; break;
    case UE_NOT_CSG_CAPABLE: return "NotCsgCapable"; break;
    // No default, let compiler tell us about missing elements.
    }

    RSYS_ASSERT(false);
    return "";
}

const char * ueRegistrationCauseToString(UeRegistrationCause regCause)
{
    switch(regCause)
    {
    case UE_REG_CAUSE_EMERGENCY_CALL: return "EmergencyCall"; break;
    case UE_REG_CAUSE_NORMAL: return "NormalCall"; break;
    // No default, let compiler tell us about missing elements.
    }

    RSYS_ASSERT(false);
    return "";
}

const char * r99DlCapabilityHsdpaToString(R99DlCapabilityHsdpa dlCapWithHs)
{
    switch(dlCapWithHs)
    {
    case R99DL_32k: return "32k"; break;
    case R99DL_64k: return "64k"; break;
    case R99DL_128k: return "128k"; break;
    case R99DL_384k: return "384k"; break;
    // No default, let compiler tell us about missing elements.
    }

    RSYS_ASSERT(false);
    return "";
}

}

const char * MobnetTypes::DomainToString(DomainIdent domain)
{
    switch(domain)
    {
    case CS_DOMAIN:
        return("CS");
        break;
    case PS_DOMAIN:
        return("PS");
        break;
    default:
        return("UnknownDomain");
        break;
    }
}


static const u8 static_maximumEstablishmentCauseValue = 31;
static const char * static_establishmentCauseString [] =
{
    "originatingConversationalCall",
    "originatingStreamingCall",
    "originatingInteractiveCall",
    "originatingBackgroundCall",
    "originatingSubscribedTrafficCall",
    "terminatingConversationalCall",
    "terminatingStreamingCall",
    "terminatingInteractiveCall",
    "terminatingBackgroundCall",
    "emergencyCall",
    "interRAT_CellReselection",
    "interRAT_CellChangeOrder",
    "registration",
    "detach",
    "originatingHighPrioritySignalling",
    "originatingLowPrioritySignalling",
    "callRe_establishment",
    "terminatingHighPrioritySignalling",
    "terminatingLowPrioritySignalling",
    "terminatingCauseUnknown",
    "EstablishmentCause_spare12",
    "EstablishmentCause_spare11",
    "EstablishmentCause_spare10",
    "EstablishmentCause_spare9",
    "EstablishmentCause_spare8",
    "EstablishmentCause_spare7",
    "EstablishmentCause_spare6",
    "EstablishmentCause_spare5",
    "EstablishmentCause_spare4",
    "EstablishmentCause_spare3",
    "EstablishmentCause_spare2",
    "EstablishmentCause_spare1"
};

const char * MobnetTypes::EstCauseToString(u8 establishmentCause)
{
    if (establishmentCause < static_maximumEstablishmentCauseValue)
    {
        return static_establishmentCauseString[establishmentCause];
    }
    else
    {
        return "EstablishmentCause_Invalid";

    }
}


