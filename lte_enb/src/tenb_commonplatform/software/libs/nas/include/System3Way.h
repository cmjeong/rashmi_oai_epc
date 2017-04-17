///////////////////////////////////////////////////////////////////////////////
//
// System3Way.h
//
// Contains various NAS types, structures, etc.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __System3Way_h_
#define __System3Way_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <Radisys.h>
#include <ConnectionIdentifier.h>
#include <mobnet/MobnetTypes.h>
//#include <lib-system/BCDAddress.h>

// So the way this works: if you define __NAS_FUNCTION__ to be __PRETTY_FUNCTION__
// you are including debug information about MUTEX locking in the applications.
// There is a LOT if this: so only do it if you are intentionally debugging
// the MUTEX logic.  For 'vanilla' builds, define it to be NULL.

//#define __NAS_FUNCTION__ __PRETTY_FUNCTION__
#define __NAS_FUNCTION__ NULL

///////////////////////////////////////////////////////////////////////////////
// System Wide Application Constants.
///////////////////////////////////////////////////////////////////////////////

// First 4 digit pattern in our allocated TMSI's.
static const u8 NAS_3WAY_TMSI_OCTET_1 = 0x6F;

// The phone number that is dialled to contact this subscriber.  I'm
// taking the digit limit from 24.008, although I could be wrong: ever
// seen a phone number with more than 26 digits??
static const u8 MAX_E164_DIGITS = 26;

// The maximum length of a string containing a dotted IPv4 address.  Includes
// space for the NULL terminator (xxx.xxx.xxx.xxx\0).
static const u8 MAX_IP_ADDRESS = 16;

// HLR Database Version Identification
// Version 1 [CS Only Implementation]
static const u32 HLR_DATABASE_VERSION_1 = 0x12233221;

// Version 2 [CS + PS Implementation]
static const u32 HLR_DATABASE_VERSION_2 = 0x23344332;

///////////////////////////////////////////////////////////////////////////////
// NAS Application Includes
///////////////////////////////////////////////////////////////////////////////

// GSM 04.08 Types.
#include "Layer3Constants.h"

///////////////////////////////////////////////////////////////////////////////
// Application Files: these are constant, and unchangeable.  The applications
// will abort startup if they do not exist.
// We use different names for each OS to aviod confusion when running
// the apps.
///////////////////////////////////////////////////////////////////////////////

static const char NAS_SYSTEM_CONFIGURATION [] = "nas-system-configuration";
static const char NAS_STATUS_LOG [] = "nas-system-status";
static const char NAS_NUMBERING_PLAN_CONFIGURATION [] = "nas-numbering-plan";
static const char NAS_SMSC_CONFIGURATION [] = "nas-smsc-configuration";
static const char NAS_GGSN_IP_TUNNEL_CONFIGURATION [] = "nas-ggsn-iptunnel-configuration";
static const char NAS_UE_IP_CONFIGURATION [] = "nas-ue-ip-configuration";
static const char NAS_ACCESS_CONTROL_CONFIGURATION [] = "nas-access-control";
static const char NAS_IU_CONFIGURATION [] = "nas-iu-configuration";

// Maximum number of timers allowed in the system.  Not sure we actually need
// this, but we can use it to detect TimerHandle leaks (TimerEngine will
// signal overload when there are none left).
static const u32 MAX_NAS_TIMERS = 0x0000ffff;   // 65536

// Identifier attached to each CORE_Connection instance in the Core app.
// Used for L3 message routing between the core + rrc link layer.
typedef u32 CORE_ConnectionIdentifier;

// Identifier used in the NAS_Core + NAS_Hlr to identify an MM / CC session.
typedef u32 MobileControlBlockNumber;

// Just used to clarify type declarations in NAS_Core when 'talking'
// about GSM call legs.
typedef u32 CallCentreCallNumber;

///////////////////////////////////////////////////////////////////////////////
// Number ranges for the identifiers above: Range constant is +1
// because the link number range is inclusive.
// Currently the ranges are allow for 256 concurrent sessions: so that
// would be 256 concurrent location update procedures, and 128 concurrent
// calls (as each call has two legs, ya dig).
///////////////////////////////////////////////////////////////////////////////

// Normalised by MJA to try and help with debugging links: isn't it easier if
// for instance, all of the applications agree that a UE is on the same
// link number?

#define NAS_LINK_FIRST_ID       1
#define NAS_LINK_LAST_ID        256
#define NUMBER_OF_NAS_LINKS     NAS_LINK_LAST_ID - NAS_LINK_FIRST_ID + 1

// Does it make sense to everyone, that the number of links on each
// side of the RRC <-> CORE <-> HLR interface must be the same?  The library
// will ASSERT + CLOSE if you don't match the two sides.

///////////////////////////////////////////////////////////////////////////////
// Application Numbering Scheme, used for Inter App Messaging.
///////////////////////////////////////////////////////////////////////////////
typedef u16 NASApp;

static const NASApp NAS_CORE            = 0x0001;
static const char   NAS_CORE_APPNAME[]  = "nas-core";
static const NASApp NAS_HLR             = 0x0002;
static const char   NAS_HLR_APPNAME[]   = "nas-hlr";
static const NASApp NAS_RRCLINKLAYER    = 0x0003;
static const char   NAS_RRC_APPNAME[]   = "rrc";
static const NASApp NAS_SMSC            = 0x0005;
static const char   NAS_SMSC_APPNAME[]  = "nas-smsc";
static const NASApp NAS_GGSN            = 0x0006;
static const char   NAS_GGSN_APPNAME[]  = "nas-ggsn";
static const NASApp NAS_GGSN_IP_TUNNEL  = 0x0008;
static const char   NAS_GGSN_IP_TUNNEL_APPNAME[]  = "nas-ggsn-iptunnel";
static const NASApp NAS_IU              = 0x000a;
static const char   NAS_IU_APPNAME[]    = "iu";

static const NASApp NAS_BROADCAST       = 0xffff;
static const NASApp NAS_UNKNOWN         = 0x0000;

///////////////////////////////////////////////////////////////////////////////
// Application Message Types, used for Inter App Messaging.  These codes,
// in conjunction with the application id above, identifies the payload
// of the NASMessageStructure that is used to transport messages between
// the various applications in the system.
///////////////////////////////////////////////////////////////////////////////

typedef u32 NASAppMessage;

// Base IDs for messages.
#define NAS_GGSN_BASE           0x00007000
#define NAS_RABM_BASE           0x00008000
#define NAS_SMSC_BASE           0x00009000
#define NAS_DBX_MSG_BASE        0x0000a000
#define NAS_CORE_MSG_BASE       0x0000b000
#define NAS_PORTAL_BASE         0x0000c000
#define NAS_HLR_MSG_BASE        0x0000d000
#define NAS_RRCLINKLAYER_BASE   0x0000e000
#define NAS_TRANSPORT_MSG_BASE  0x0000f000


static const NASAppMessage NAS_DBX_ULCCCH_MSG   = NAS_DBX_MSG_BASE + 0x001;
static const NASAppMessage NAS_DBX_ULDCCH_MSG   = NAS_DBX_MSG_BASE + 0x002;


// Private messages used to implement the cyphering procedure.
static const NASAppMessage NAS_COREAPP_CYPHER_MODE_COMMAND  = NAS_CORE_MSG_BASE + 0x001;
static const NASAppMessage NAS_COREAPP_CYPHER_MODE_COMPLETE = NAS_CORE_MSG_BASE + 0x002;
static const NASAppMessage NAS_COREAPP_CYPHER_MODE_FAILURE  = NAS_CORE_MSG_BASE + 0x003;

static const NASAppMessage NAS_COREAPP_CYPHER_MODE_COMMAND_PS  = NAS_CORE_MSG_BASE + 0x00b;
static const NASAppMessage NAS_COREAPP_CYPHER_MODE_COMPLETE_PS = NAS_CORE_MSG_BASE + 0x00c;
static const NASAppMessage NAS_COREAPP_CYPHER_MODE_FAILURE_PS  = NAS_CORE_MSG_BASE + 0x00d;

// Private messages used to implement the radio bearer setup procedure.
static const NASAppMessage NAS_COREAPP_REQUEST_TRAFFIC_CHAN = NAS_CORE_MSG_BASE + 0x004;
static const NASAppMessage NAS_COREAPP_TRAFFIC_CHAN_ACCEPT  = NAS_CORE_MSG_BASE + 0x005;
static const NASAppMessage NAS_COREAPP_TRAFFIC_CHAN_FAIL    = NAS_CORE_MSG_BASE + 0x006;

// Private messages used to implement the radio bearer release procedure.
static const NASAppMessage NAS_COREAPP_RELEASE_TRAFFIC_CHAN = NAS_CORE_MSG_BASE + 0x007;
static const NASAppMessage NAS_COREAPP_TRAFFIC_CHAN_RELCOMP = NAS_CORE_MSG_BASE + 0x008;
static const NASAppMessage NAS_COREAPP_TRAFFIC_CHAN_RELFAIL = NAS_CORE_MSG_BASE + 0x009;

static const NASAppMessage NAS_COREAPP_L3MESSAGE            = NAS_CORE_MSG_BASE + 0x00a;

// Private messages to support interaction with CN (via RANAP, Iu, or whatever).
static const NASAppMessage NAS_RRC_RESET_CS                 = NAS_CORE_MSG_BASE + 0xf00;
static const NASAppMessage NAS_RRC_RESET_PS                 = NAS_CORE_MSG_BASE + 0xf01;
static const NASAppMessage NAS_SIGNALLING_CONNECTION_REL    = NAS_CORE_MSG_BASE + 0xf02;
static const NASAppMessage NAS_HANDOVER_TRIGGER             = NAS_CORE_MSG_BASE + 0xf03;
static const NASAppMessage NAS_HANDOVER_COMMAND             = NAS_CORE_MSG_BASE + 0xf04;
static const NASAppMessage NAS_HANDOVER_CANCEL              = NAS_CORE_MSG_BASE + 0xf05;
static const NASAppMessage NAS_HANDOVER_FAILED              = NAS_CORE_MSG_BASE + 0xf06;

// When a new radio bearer is requested, identify the type of that bearer.
typedef enum enumRadioBearerRequest
{
    SpeechRadioBearer,
    VideoRadioBearer,
    DataRadioBearer,
    UnknownRadioBearer
}RadioBearerRequest;

typedef enum enumRrcRabFailureCause
{
    RRC_BEARER_EST_CAUSE_SUCCESS,   // Obviously; no problem!
    RRC_BEARER_EST_CAUSE_FAILURE,   // RLF - probably bearer coding error in Rrc.
    RRC_BEARER_EST_CAUSE_NO_RAB,     // Invalid combined Rab combination.
    RRC_RELOCATION_ON_GOING         // When Relocation is active no RAB changes are allowed

}RrcRabFailureCause;

typedef enum enumRrcConnectionReleaseCause
{
    RRC_RADIO_LINK_FAILURE,
    RRC_UE_CONNECTION_RELEASE_IND,     // Signalling Connection Release from UE
    RRC_RAB_PRE_EMPTED,                // RRM Preemption reason
    RRC_FACH_INACTIVITY,               // UE in Cell Fach is doing nothing
    RRC_CAUSE_NOT_SPECIFIED

}RrcConnectionReleaseCause;

typedef struct structRABMessageStructure
{
    // This will be populated with the Radio Bearer Identity of
    // the transport channel we are creating / reconfing / deleting.
    u8 rbIdentity;

    // Also when requesting a RadioBearer operation, this field will indicate which
    // of our canned RRC messages to send (are we requesting a Speech, Video or Data bearer?).
    RadioBearerRequest requestedRadioBearer;

    // This pair of values only used when establishing SIP calls to
    // external networks; they convey the address/port pair on the
    // media gateway for traffic routing.
    u16 mediaDestinationPort;
    char mediaDestinationAddress [MAX_IP_ADDRESS];

    // The user number, starting from 0.  Only filled in for certain messages from rrc.
    // Allows cs-user-plane to know which audio streams (e.g. FIFOs) to connect up.
    u8 allocatedDchNumber;

    // What was the result of the bearer configuration attempt?  We will
    // use this to return a meaningful Ranap Cause in the IU build.
    RrcRabFailureCause rrcCause;

    RrcConnectionReleaseCause rrcReleaseCause;

    // Priority & Pre-emption parameters from CN
    bool mayTriggerPreemption;
    bool mayBePreempted;
    u16  priorityLevel;

}RABMessageStructure;

// NOTE: the following two enums reflect the "struct Cause" in the asn-derived file ranap_25413_6a0.h.
// "Cause" has not been used here in order not to pull in the above file.
typedef enum enumRrrcSecurityModeProcedureFailureCause
{
    // To be sued with CAUSE_RADIO_NETWORK
    CONFLICT_WITH_ALREADY_EXISTING_INT_PROT_AND_OR_CIPHER_INFO,
    REQUESTED_CYPHERING_AND_OR_INTEGRITY_PROTECTION_ALGORITHMS_NOT_SUPPORTED,
    FAILURE_IN_THE_RADIO_INTERFACE_PROCEDURE,

    // To be used with CAUSE_PROTOCOL
    SEMANTIC_ERROR,

    // To be used with CAUSE_MISC
    UNSPECIFIED_FAILURE
} RrrcSecurityModeProcedureFailureCause;

typedef enum enumRrrcSecurityModeProcedureFailureCauseType
{
    CAUSE_RADIO_NETWORK,
    CAUSE_PROTOCOL,
    CAUSE_MISC
} RrrcSecurityModeProcedureFailureCauseType;

typedef struct tagRrrcSecurityModeProcedureFailureInfo
{
    RrrcSecurityModeProcedureFailureCauseType type;
    RrrcSecurityModeProcedureFailureCause cause;

} RrrcSecurityModeProcedureFailureInfo;



// The following types describe the cyphering and integrity algos.
typedef enum CipherAlgoChoiceTag {
    UEA0 = 0x00, // UEA0 - No Ciphering
    UEA1 = 0x01, // Kasumi
//    UEA2 = 0x02  // Snow 3G    REL 7
    NO_CIPHER_ALGO = 0x7f
} CypherAlgoChoice;

typedef enum IntegrityAlgoChoiceTag {
    UIA1 = 0x01, // Kasumi
//    UIA2 = 0x02  // Snow 3G    REL 7
    NO_INT_PROT_ALGO = 0x7f
} IntegrityAlgoChoice;

// The following "typedef"s describe the cyphering and integrity protection preferences
// received from the CN.
// The CN sends a list of algos. It is assumed the following:
// 1) first element in the list <----> most preferred algo
// 2) last element in the list <----> least preferred algo.
// This is an assumption since this is stated nowhere in the standards.
// Note also, that in the arrays below, the following applies:
// A) array [0]                  <----> most preferred algo
// B) array [max number of ....] <----> least preferred algo
static const u8 MAX_NUMBER_OF_CYPHER_ALGOS = 16;  // Does take UEA0 (ie, no cyphering) into account
typedef struct tagCypheringAlgosInfo {
    CypherAlgoChoice chyperAlgosArray [MAX_NUMBER_OF_CYPHER_ALGOS];
    u8               numberOfAlgos;
} CypheringAlgosInfo;

static const u8 MAX_NUMBER_OF_INTEGR_PROT_ALGOS = 16;
typedef struct tagIntegrProtectionAlgosInfo {
    IntegrityAlgoChoice intProtAlgosArray [MAX_NUMBER_OF_INTEGR_PROT_ALGOS];
    u8                  numberOfAlgos;
} IntegrProtectionAlgosInfo;


// The following structure is used for messages both from RRC to IU and viceversa.
// Hence, some fields may or may not be relevant, depending on the direction.
// See the messages in which it is used for info on the semantics.

typedef struct tagCypherMessageStructure
{
    // DIRECTION: IU -> RRC
    // IK as obtained during Authentication.  This is required for the F9
    // function used to implement message integrity protection.
    u8 IK[16];

    // DIRECTION: IU -> RRC
    // CK as obtained during Authentication.  This is required for the F8
    // function used to implement cyphering.
    u8 CK[16];

    // DIRECTION: IU -> RRC
    // Has the Authentication Centre allocated new keys?
    bool keyStatusIsNew;

    // DIRECTION: IU -> RRC
    // Passed between IU + RRC to indicate whether cyphering information is present or not.
    bool encryptionInformationIePresent;

    // DIRECTION: IU -> RRC
    // a) IU -> RRC: contains the cyphering algorithms preferred by the CN.
    // b) RRC -> IU: Element "chyperAlgosArray [0]" contains the cyphering algorithm selected by the FAP.
    CypheringAlgosInfo cypheringAlgorithms;

    // DIRECTION:
    // a) IU -> RRC: contains the algorithms preferred by the CN.
    // b) RRC -> IU: element "intProtAlgosArray [0]" contains the Int. Prot. algorithm selected by the FAP.
    IntegrProtectionAlgosInfo integrProtectionAlgorithms;

    // DIRECTION: RRC -> IU
    RrrcSecurityModeProcedureFailureInfo causeInfo;

}CypherMessageStructure;

typedef struct tagL3MessageStructure
{
    // Should the layer 3 message be sent to CS or PS domain?
    DomainIdent domain;

    // Length of the low level payload.
    u32 payloadLength;

    // And the L3 NAS message itself.
    u8 payloadMessage[1024];

}L3MessageStructure;

// Small enumeration used to differentiate between SRB3 and SRB4.  Better than just using
// a bool >:-)
typedef enum enumRRC_SRBIdent
{
    RRC_USE_SRB_1,
    RRC_USE_SRB_2,
    RRC_USE_SRB_3,
    RRC_USE_SRB_4,
    RRC_USE_DCCH_1
}RRC_SRBIdent;

static const NASAppMessage NAS_CCCH_PDU_FOR_DBX = NAS_RRCLINKLAYER_BASE + 0x001;

static const NASAppMessage NAS_DCH_SRB_1_UM = NAS_RRCLINKLAYER_BASE + 0x002;
static const NASAppMessage NAS_DCH_SRB_2_AM = NAS_RRCLINKLAYER_BASE + 0x003;
static const NASAppMessage NAS_DCH_SRB_3_AM = NAS_RRCLINKLAYER_BASE + 0x004;
static const NASAppMessage NAS_DCH_SRB_4_AM = NAS_RRCLINKLAYER_BASE + 0x005;



static const NASAppMessage NAS_HLR_LUREQ_MSG        = NAS_HLR_MSG_BASE + 0x001;
static const NASAppMessage NAS_HLR_LUACC_MSG        = NAS_HLR_MSG_BASE + 0x002;
static const NASAppMessage NAS_HLR_LUREJ_MSG        = NAS_HLR_MSG_BASE + 0x003;
static const NASAppMessage NAS_HLR_IMSIDETACH_MSG   = NAS_HLR_MSG_BASE + 0x004;
static const NASAppMessage NAS_HLR_PTMSI_DETACH     = NAS_HLR_MSG_BASE + 0x015;

static const NASAppMessage NAS_REGISTER_OBTAIN_VECTORS      = NAS_HLR_MSG_BASE + 0x005;
static const NASAppMessage NAS_REGISTER_OBTAIN_VECTORS_PS   = NAS_HLR_MSG_BASE + 0x00F;
static const NASAppMessage NAS_REGISTER_VECTORS_RESPONSE    = NAS_HLR_MSG_BASE + 0x006;
static const NASAppMessage NAS_REGISTER_VECTORS_RESPONSE_PS = NAS_HLR_MSG_BASE + 0x010;
static const NASAppMessage NAS_REGISTER_VECTORS_FAILURE     = NAS_HLR_MSG_BASE + 0x007;
static const NASAppMessage NAS_REGISTER_VECTORS_FAILURE_PS  = NAS_HLR_MSG_BASE + 0x011;

static const NASAppMessage NAS_REGISTER_SUBSCRIBER      = NAS_HLR_MSG_BASE + 0x008;
static const NASAppMessage NAS_REGISTER_SUBSCRIBER_PS   = NAS_HLR_MSG_BASE + 0x012;
static const NASAppMessage NAS_REGISTER_SUCCESS         = NAS_HLR_MSG_BASE + 0x009;
static const NASAppMessage NAS_REGISTER_SUCCESS_PS      = NAS_HLR_MSG_BASE + 0x013;
static const NASAppMessage NAS_REGISTER_FAILURE         = NAS_HLR_MSG_BASE + 0x00A;
static const NASAppMessage NAS_REGISTER_FAILURE_PS      = NAS_HLR_MSG_BASE + 0x014;

static const u8 PTMSI_NOT_FOUND = 0xff;
static const u8 IMSI_NOT_FOUND = 0xfe;

static const NASAppMessage NAS_PAGING_MSG_CS        = NAS_HLR_MSG_BASE + 0x00B;
static const NASAppMessage NAS_PAGING_MSG_PS        = NAS_HLR_MSG_BASE + 0x018;
static const NASAppMessage NAS_IMSI_IND             = NAS_HLR_MSG_BASE + 0x019;

static const NASAppMessage NAS_CALL_ATTEMPT_MSG     = NAS_HLR_MSG_BASE + 0x00C;
static const NASAppMessage NAS_CALL_REJECTED_MSG    = NAS_HLR_MSG_BASE + 0x00D;
static const NASAppMessage NAS_CALL_ACCEPTED_MSG    = NAS_HLR_MSG_BASE + 0x00E;
static const NASAppMessage NAS_CALL_FORWARDED_MSG   = NAS_HLR_MSG_BASE + 0x016;
static const NASAppMessage SIP_CALL_ACCEPTED_MSG    = NAS_HLR_MSG_BASE + 0x017;

///////////////////////////////////////////////////////////////////////////////
// SIP RELAY Transport Mechanism.
///////////////////////////////////////////////////////////////////////////////

static const NASAppMessage NAS_PORTAL_CALL_SETUP        = NAS_PORTAL_BASE + 0x001;
static const NASAppMessage NAS_PORTAL_CALL_REJECT       = NAS_PORTAL_BASE + 0x002;
static const NASAppMessage NAS_PORTAL_CALL_ACCEPT       = NAS_PORTAL_BASE + 0x003;
static const NASAppMessage NAS_PORTAL_CALL_ALERTING     = NAS_PORTAL_BASE + 0x004;
static const NASAppMessage NAS_PORTAL_CALL_CONNECT      = NAS_PORTAL_BASE + 0x005;
static const NASAppMessage NAS_PORTAL_CALL_CONNECT_ACK  = NAS_PORTAL_BASE + 0x006;
static const NASAppMessage NAS_PORTAL_CALL_DISCONNECT   = NAS_PORTAL_BASE + 0x007;
static const NASAppMessage NAS_PORTAL_CALL_RELEASE      = NAS_PORTAL_BASE + 0x008;
static const NASAppMessage NAS_PORTAL_CALL_RELCOMP      = NAS_PORTAL_BASE + 0x009;
static const NASAppMessage NAS_PORTAL_CALL_USER_NO_IND  = NAS_PORTAL_BASE + 0x00A;


static const NASAppMessage NAS_PORTAL_IDENT_REQUEST     = NAS_PORTAL_BASE + 0x00B;
static const NASAppMessage NAS_PORTAL_IDENT_RESPONSE    = NAS_PORTAL_BASE + 0x00C;
static const NASAppMessage NAS_PORTAL_IDENT_FAILURE     = NAS_PORTAL_BASE + 0x00D;

static const NASAppMessage NAS_PORTAL_SS_REGISTER       = NAS_PORTAL_BASE + 0x00E;
static const NASAppMessage NAS_PORTAL_SS_FACILITY       = NAS_PORTAL_BASE + 0x00F;
static const NASAppMessage NAS_PORTAL_SS_RELCOMP        = NAS_PORTAL_BASE + 0x010;
static const NASAppMessage NAS_PORTAL_SS_REGISTER_RESP  = NAS_PORTAL_BASE + 0x011;
static const NASAppMessage NAS_PORTAL_SS_FACILITY_RESP  = NAS_PORTAL_BASE + 0x012;
static const NASAppMessage NAS_PORTAL_SS_RELCOMP_RESP   = NAS_PORTAL_BASE + 0x013;

///////////////////////////////////////////////////////////////////////////////
// SMSC Transport Mechanism.
///////////////////////////////////////////////////////////////////////////////

static const NASAppMessage NAS_SMSC_PAGE_REQUEST        = NAS_SMSC_BASE + 0x001;
static const NASAppMessage NAS_SMSC_PAGE_REJECT         = NAS_SMSC_BASE + 0x002;
static const NASAppMessage NAS_SMSC_PAGE_FAILURE        = NAS_SMSC_BASE + 0x003;
static const NASAppMessage NAS_SMSC_RP_MESSAGE          = NAS_SMSC_BASE + 0x004;
static const NASAppMessage NAS_SMSC_MSISDN_ALERT        = NAS_SMSC_BASE + 0x005;

static const NASAppMessage NAS_SMSC_IDENT_REQUEST       = NAS_SMSC_BASE + 0x006;
static const NASAppMessage NAS_SMSC_IDENT_RESPONSE      = NAS_SMSC_BASE + 0x007;
static const NASAppMessage NAS_SMSC_IDENT_FAILURE       = NAS_SMSC_BASE + 0x008;

static const NASAppMessage NAS_SMSC_SIP_DELIVERY_REQUEST        = NAS_SMSC_BASE + 0x009;
static const NASAppMessage NAS_SMSC_SIP_DELIVERY_COMPLETE       = NAS_SMSC_BASE + 0x00A;
static const NASAppMessage NAS_SMSC_SIP_DELIVERY_FAILED         = NAS_SMSC_BASE + 0x00B;

///////////////////////////////////////////////////////////////////////////////
// RABM Transport Mechanism.
///////////////////////////////////////////////////////////////////////////////

static const NASAppMessage NAS_RABM_ACTIVATE_IND        = NAS_RABM_BASE + 0x001;
static const NASAppMessage NAS_RABM_DEACTIVATE_IND      = NAS_RABM_BASE + 0x002;
static const NASAppMessage NAS_RABM_MODIFY_IND          = NAS_RABM_BASE + 0x003;
static const NASAppMessage NAS_RABM_ACTIVATE_RESP       = NAS_RABM_BASE + 0x004;
static const NASAppMessage NAS_RABM_DEACTIVATE_RESP     = NAS_RABM_BASE + 0x005;
static const NASAppMessage NAS_RABM_MODIFY_RESP         = NAS_RABM_BASE + 0x006;
static const NASAppMessage NAS_RABM_SUSPEND_IND         = NAS_RABM_BASE + 0x007;
static const NASAppMessage NAS_RABM_RESUME_REQ          = NAS_RABM_BASE + 0x008;
static const NASAppMessage NAS_RABM_RESUME_CNF          = NAS_RABM_BASE + 0x009;
static const NASAppMessage NAS_RABM_RESUME_IND          = NAS_RABM_BASE + 0x00A;

static const u8 RABM_CAUSE_SUCCESS                      = 0x00;
static const u8 RABM_CAUSE_NO_LINK_AVAILABLE            = 0x01;
static const u8 RABM_CAUSE_NO_GGSN                      = 0x02;
static const u8 RABM_CAUSE_NO_RADIO_BEARER              = 0x03;
static const u8 RABM_CAUSE_RELOCATION_ON_GOING          = 0x04;
static const u8 RABM_CAUSE_RB_FAILURE                   = 0x05;

static const u8 NSAPI_UNUSED                            = 0xff;

typedef enum enumPsBearerType
{
    RABM_PS_BEARER_LOW_RATE  = 1,
    RABM_PS_BEARER_HIGH_RATE = 2
}PsBearerType;

typedef struct tagRABMMessageStructure
{
    // For all messages.
    // NSAPI (becomes Radio Access Bearer Id for PS radio bearer).
    u8 nsapi;

    // PS user plane index
    u32 psUserPlaneNumber;

    // This identifier is allocated by RRC and allows the RNC to
    // communicate with and track a subscriber connected to our cell.
    u32 uRnti;

    // if true, a PS Streaming bearer is required, else interactive.
    bool isPsStreaming;

    // For ActivateInd/ModifyInd.
    // QoS to be achieved on radio bearer.  Only pass down the information
    // required rather than a full SM QoS structure.
    // For now this is simply whether to use ack'd or unack'd on RLC.
    // All else is best efforts.
    bool rlcAcknowledgedMode;

    // For StatusReq/ActivateRsp.
    u8 cause;

    u32 maxUlBitRate;
    u32 maxDlBitRate;
    bool asymmetricBearer;

    // Priority & Pre-emption parameters from CN
    bool mayTriggerPreemption;
    bool mayBePreempted;
    u16  priorityLevel;

}RABMMessageStructure;

///////////////////////////////////////////////////////////////////////////////
// SM<->GGSN Transport Mechanism.
///////////////////////////////////////////////////////////////////////////////

static const NASAppMessage NAS_GGSN_PDP_CONTEXT_ACTIVATE_IND   = NAS_GGSN_BASE + 0x001;
static const NASAppMessage NAS_GGSN_PDP_CONTEXT_ACTIVATE_RSP   = NAS_GGSN_BASE + 0x002;
static const NASAppMessage NAS_GGSN_PDP_CONTEXT_DEACTIVATE_IND = NAS_GGSN_BASE + 0x003;
static const NASAppMessage NAS_GGSN_PDP_CONTEXT_DEACTIVATE_RSP = NAS_GGSN_BASE + 0x004;

typedef struct tagGGSNMessageStructure
{
    // For Activate/DeactivateInd. Data stream ID and IP address assigned to UE.
    u32 psDataStreamId;
    u32 ueIpAddress;
    u32 bearerType;

} GGSNMessageStructure;

///////////////////////////////////////////////////////////////////////////////
// RRC<>IU/CORE Handover Transport Mechanism.
///////////////////////////////////////////////////////////////////////////////

#define MaxNumberOfRABs 256
#define MaxRABSubFlows  7
#define MaxNumberOfSRBs 8

typedef enum tagTrafficChannelType
{
    // Dedicated downlink channel...
    DCH_Channel,

    // Downlink shared channel...
    DSCH_Channel,

    // Uplink shared channel...
    USCH_Channel

}TrafficChannelType;

typedef struct tagTrafficChannelId
{
    // Which if the RAB channel types is this?
    TrafficChannelType chanType;

    // And the associated RB ID.
    u8 radioBearerId;

}TrafficChannelId;


static const u16 ENCODED_RRC_MAX_LENGTH            = 512;
static const u16 ENCODED_NAS_HO_COMMAND_MAX_LENGTH = 256;

typedef struct tagHandoverMessageStructure_3G_elements
{
    // ** 3G Only Structures (NAS_HANDOVER_COMMAND only) ** /

    // Our Target neighbour cell details.
    u16 targetCellCid;
    u16 targetCellLac;
    u16 targetCellMcc;
    u16 targetCellMnc;
    u8  targetCellRac;
    u16 targetCellRncId;

    // Is this a cyphered cell?  If so, provide CK.
    bool cellIsCyphered;

    // Check cnDomain to know if this is CKcs or CKps.
    u8 cypheringKey [16];

    // This will be the serving IK, so currently it will bk IKcs.
    u8 integrityKey [16];

    // How many Iu connection we have to CN?
    u8 numberOfDomains;
    // Currently only supporting one RAB ID for handover.
    // TODO Multiple bearers (i.e. concurrent CS + PS handover)
    u8 rabId;

    // Encoded RRC Container information: either an SRNS RELOCATION INFORMATION in a
    // Relocation Required, or <something else> in a Relocation Command.
    u16 encodedRRCLength;
    u8 encodedRRC [ENCODED_RRC_MAX_LENGTH];
} HandoverMessageStructure_3G_elements;

typedef struct tagHandoverMessageStructure_2G_elements
{
    // ** 2G Only Structures (NAS_HANDOVER_COMMAND only) ** /
    u32 targetCellId;
    u16 targetCellLac;
    u16 targetCellMcc;
    u16 targetCellMnc;

    u8 classmark2_length;
    u8 classmark2_data[5];

    u8 classmark3_length;
    u8 classmark3_data[32];

    u16 nasHOCommand_messageLength;
    u8  nasHOCommand_message[ENCODED_NAS_HO_COMMAND_MAX_LENGTH]; // L3 NAS message will be much smaller than RRC HO SRNS RelReq or RRC Ho Command.

} HandoverMessageStructure_2G_elements;

typedef struct tagHandoverMessageStructure
{
    DomainIdent cnDomain;      // We have to know the domain for the Iu signalling.
    u32 relocationCancelCause; // If we have a failure message, the reason for the failure is here.

    HandoverType handOverType;

    union
    {
        HandoverMessageStructure_3G_elements handover_3g;
        HandoverMessageStructure_2G_elements handover_2g;
    } u; // Follow same pattern as ASN.1 generated code.

}HandoverMessageStructure;

// High(er) level message types, used to manage creation, deletion and message
// transfer using the NASTransport mechanism.
static const NASAppMessage NAS_CORE_CNXN_REQ        = NAS_TRANSPORT_MSG_BASE + 0x001;
static const NASAppMessage NAS_CORE_CNXN_CONF       = NAS_TRANSPORT_MSG_BASE + 0x002;
static const NASAppMessage NAS_CORE_CNXN_REF        = NAS_TRANSPORT_MSG_BASE + 0x003;
static const NASAppMessage NAS_CORE_CNXN_DATA       = NAS_TRANSPORT_MSG_BASE + 0x004;
static const NASAppMessage NAS_CORE_CNXN_REL        = NAS_TRANSPORT_MSG_BASE + 0x005;
static const NASAppMessage NAS_CORE_CNXN_RELCOMP    = NAS_TRANSPORT_MSG_BASE + 0x006;
static const NASAppMessage NAS_CORE_CNXNLESS_MSG    = NAS_TRANSPORT_MSG_BASE + 0x007;

// This is a 'special' message type, indicating there is no associated payload.
// We would use this, for example, when sending a CNXN-REF message denying access
// to the a remote application for some reason.
static const NASAppMessage NAS_PAYLOAD_EMPTY        = NAS_TRANSPORT_MSG_BASE + 0xfff;

// Linux doesn't have GetTickCount() so we have implemented our own.
unsigned GetTickCount ();

#endif
