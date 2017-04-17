///////////////////////////////////////////////////////////////////////////////
//
// MessagingEntity.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MessagingEntity.h"

///////////////////////////////////////////////////////////////////////////////
// Functions
///////////////////////////////////////////////////////////////////////////////

const char * MessagingEntityToString(MessagingEntity entity)
{
    switch(entity)
    {
        case ENTITY_INVALID:                    return "<out-of-bounds-low>";       break;
        case ENTITY_POSTOFFICE:                 return "POSTOFFICE";                break;
        case ENTITY_IU:                         return "IU";                        break;
        case ENTITY_RRC:                        return "RRC";                       break;
        case ENTITY_OAM:                        return "OAM";                       break;
        case ENTITY_MIB:                        return "MIB";                       break;
        case ENTITY_CPHY:                       return "CPHY";                      break;
        case ENTITY_CRLC:                       return "CRLC";                      break;
        case ENTITY_CMAC:                       return "CMAC";                      break;
        case ENTITY_OAM_HW:                     return "OAM_HW";                    break;
        case ENTITY_OAM_REM:                    return "OAM-REM";                   break;
        case ENTITY_SNMP:                       return "SNMP";                      break;
        case ENTITY_TR069:                      return "TR069";                     break;
        case ENTITY_CS_USER_PLANE:              return "CS_USER_PLANE";             break;
        case ENTITY_PS_USER_PLANE:              return "PS_USER_PLANE";             break;
        case ENTITY_HLR:                        return "HLR";                       break;
        case ENTITY_NTP_CLIENT:                 return "NTP_CLIENT";                break;
        case ENTITY_RLC:                        return "RLC";                       break;
        case ENTITY_FREQ_SYNC:                  return "FREQ_SYNC";                 break;
        case ENTITY_SIP_RELAY:                  return "SIP_RELAY";                 break;
        case ENTITY_NAS_CORE:                   return "NAS_CORE";                  break;
        case ENTITY_SMSC:                       return "SMSC";                      break;
        case ENTITY_GGSN:                       return "GGSN";                      break;
        case ENTITY_CATS:                       return "CATS";                      break;
        case ENTITY_CLI:                        return "CLI";                       break;
        case ENTITY_CARB:                       return "CARB";                      break;
        case ENTITY_TENPIN:                     return "TENPIN";                    break;
        case ENTITY_WATCHDOG:                   return "WATCHDOG";                  break;
        case ENTITY_GSM_REM:                    return "GSM-REM";                   break;
        case ENTITY_QOS:                        return "QOS";                       break;
        case ENTITY_TPM:                        return "TPM";                       break;
        case ENTITY_X509:                       return "X509";                      break;
        case ENTITY_RRM:                        return "RRM";                       break;
        case ENTITY_SERVICE_API:                return "SERVICE_API";               break;
        case ENTITY_TRIGGER_PACKET_RECEIVER:    return "TRIGGER_PACKET_RECEIVER";	break;
        case ENTITY_SW_UPDATE:					return "SW_UPDATE";					break;
        case ENTITY_FTP:						return "FTP";						break;
        case ENTITY_IPSEC_TUNNEL_DB:            return "IPSEC_TUNNEL_DB";           break;
        case ENTITY_IKE:                        return "IKE";                       break;
        case ENTITY_GPS:                        return "GPS";                       break;
        case ENTITY_SIBS:                       return "SIBS";                      break;
        case ENTITY_SM:                         return "SM";                        break;
        case ENTITY_NUM_ENTITIES:               return "<out-of-bounds-high>";      break;
    }

    if (MessagingEntityIsEphemeral(entity))
    {
        return "<ephemeral>";
    }

    return "<unknown-entity>";
}

bool MessagingEntityIsEphemeral(
    MessagingEntity entity
)
{
    if (entity & 0xFFFF0000)
    {
        return true;
    }

    return false;
}

bool MessagingEntityIsBoundEphemeral(
    MessagingEntity entity
)
{
    if (    MessagingEntityIsEphemeral(entity)
         && (entity & 0x0000FFFF)
       )
    {
        return true;
    }

    return false;
}

MessagingEntity MessagingEntityBindEphemeral(
    MessagingEntity entity,
    u16             port
)
{
    if (MessagingEntityIsEphemeral(entity))
    {
        entity &= 0xFFFF0000;
        entity |= (0x0000FFFF & port);
    }

    return entity;
}

u16 MessagingEntityGetBoundPort(
    MessagingEntity entity
)
{
    if (MessagingEntityIsEphemeral(entity))
    {
        return (entity & 0x0000FFFF);
    }

    return 0;
}

MessagingEntity MessagingEntityNextUnboundEphemeral(
    u16 * counter
)
{
    if (0 == ++(*counter))
    {
        return ENTITY_INVALID;
    }

    return ((*counter) << 16);
}

/*
 * Generate the function that lets us dump the whole enum as value / string pairs.
 */

#define ENUM_GENERATE_TABLE

#include "MessagingEntity.h"

#undef ENUM_GENERATE_TABLE
