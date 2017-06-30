///////////////////////////////////////////////////////////////////////////////
//
// MessagingEntity.h
//
// List of all entities in system that can send/receive messages.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#if (!defined(__MessagingEntity_h_) || defined(ENUM_GENERATE_STRINGS) || defined(ENUM_GENERATE_TABLE))

#if (!defined(ENUM_GENERATE_STRINGS) && !defined(ENUM_GENERATE_TABLE))
    #define __MessagingEntity_h_
#endif

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <Radisys.h>
#include <system/EnumToString.h>

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

ENUM_START(StaticMessagingEntity)
{
    ENUM_ELEMENT_VAL(ENTITY_INVALID, 0)     /**< Maintain value of zero so that code which needs to iterate across entire set of tags can use it as a starting point */
    ENUM_ELEMENT_VAL(ENTITY_POSTOFFICE, 1)  /**< Maintain value of 1 for specials customers. */
    ENUM_ELEMENT_VAL(ENTITY_IU, 2)          /**< Maintain value of 2 for specials customers. */
    ENUM_ELEMENT_VAL(ENTITY_RRC, 3)         /**< Maintain value of 3 for specials customers. */
    ENUM_ELEMENT_VAL(ENTITY_OAM, 4)         /**< Maintain value of 4 for specials customers. */
    ENUM_ELEMENT(ENTITY_MIB)
    ENUM_ELEMENT(ENTITY_CPHY)            /**< Physical Layer Control. */
    ENUM_ELEMENT(ENTITY_CRLC)
    ENUM_ELEMENT(ENTITY_CMAC)
    ENUM_ELEMENT(ENTITY_OAM_HW)
    ENUM_ELEMENT(ENTITY_OAM_REM)
    ENUM_ELEMENT(ENTITY_SNMP)
    ENUM_ELEMENT(ENTITY_TR069)
    ENUM_ELEMENT(ENTITY_CS_USER_PLANE)
    ENUM_ELEMENT(ENTITY_PS_USER_PLANE)
    ENUM_ELEMENT(ENTITY_HLR)
    ENUM_ELEMENT(ENTITY_NTP_CLIENT)
    ENUM_ELEMENT(ENTITY_RLC)
    ENUM_ELEMENT(ENTITY_FREQ_SYNC)
    ENUM_ELEMENT(ENTITY_SIP_RELAY)
    ENUM_ELEMENT(ENTITY_NAS_CORE)
    ENUM_ELEMENT(ENTITY_SMSC)
    ENUM_ELEMENT(ENTITY_GGSN)
    ENUM_ELEMENT(ENTITY_CATS)             /**< Calibration And Test Services. */
    ENUM_ELEMENT(ENTITY_CLI)
    ENUM_ELEMENT(ENTITY_CARB)             /**< Control of Arbitrary Board functions. */
    ENUM_ELEMENT(ENTITY_TENPIN)
    ENUM_ELEMENT(ENTITY_WATCHDOG)         /**< Watchdog kicking daemon. */
    ENUM_ELEMENT(ENTITY_GSM_REM)
    ENUM_ELEMENT(ENTITY_QOS)
    ENUM_ELEMENT(ENTITY_TPM)
    ENUM_ELEMENT(ENTITY_X509)
    ENUM_ELEMENT(ENTITY_RRM)
    ENUM_ELEMENT(ENTITY_SERVICE_API)
    ENUM_ELEMENT(ENTITY_TRIGGER_PACKET_RECEIVER)
    ENUM_ELEMENT(ENTITY_SW_UPDATE)
    ENUM_ELEMENT(ENTITY_FTP)
    ENUM_ELEMENT(ENTITY_IPSEC_TUNNEL_DB)
    ENUM_ELEMENT(ENTITY_IKE)
    ENUM_ELEMENT(ENTITY_GPS)
    ENUM_ELEMENT(ENTITY_SIBS)
    ENUM_ELEMENT(ENTITY_SM)
    ENUM_ELEMENT(ENTITY_REM)       // Rohit : Adding for REM
    ENUM_ELEMENT(ENTITY_NUM_ENTITIES)    // Insert new entities *before* here please!
}
ENUM_END(StaticMessagingEntity)

ENUM_START(StaticMessagingPort)
{
    ENUM_ELEMENT_VAL(PORT_POSTOFFICE, 6000)
}
ENUM_END(StaticMessagingPort)

typedef u32 MessagingEntity;

extern const char *     MessagingEntityToString             (MessagingEntity entity);
extern bool             MessagingEntityIsEphemeral          (MessagingEntity entity);
extern bool             MessagingEntityIsBoundEphemeral     (MessagingEntity entity);
extern MessagingEntity  MessagingEntityBindEphemeral        (MessagingEntity entity, u16 port);
extern u16              MessagingEntityGetBoundPort         (MessagingEntity entity);
extern MessagingEntity  MessagingEntityNextUnboundEphemeral (u16 * counter);

#endif
