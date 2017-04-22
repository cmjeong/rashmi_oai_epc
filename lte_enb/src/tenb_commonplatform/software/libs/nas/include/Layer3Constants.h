///////////////////////////////////////////////////////////////////////////////
//
// 3 Way Networks Source File
//
///////////////////////////////////////////////////////////////////////////////
//
// Layer3Constants.h
//
// Various defines lifted from the GSM 04.08 spec.  Just to aid readability
// in the implementation code.
//
// Copyright � 3 Way Networks, Ltd.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Layer3Constants_h_
#define __Layer3Constants_h_

typedef enum GSM0408ProtocolDiscrimTag
{
    PD_CC                           =   0x03,
    PD_MM                           =   0x05,
    PD_RR                           =   0x06,
    PD_GMM                          =   0x08,
    PD_SMS                          =   0x09,
    PD_SM                           =   0x0A,
    PD_SS                           =   0x0B,
    PD_TEST                         =   0x0F,
    PD_NON                          =   0x7F
}GSM0408ProtocolDiscrim;

// Mask to isolate the protcol discrimiator
#define M0408_PROTOCOL_DISCRIMINATOR_MASK 0x0F

/***** 04.08 Message types *****/

// Masks to isolate the message type
#define M0408_BASIC_MSG_TYPE_MASK      0x3f

/* RR MESSAGES */
typedef enum GSM0408RrMessageTypeTag
{
    ADDITIONAL_ASSIGNMENT            = 0x3B,
    IMMEDIATE_ASSIGNMENT             = 0x3F,
    IMMEDIATE_ASSIGNMENT_EXT         = 0x39,
    IMMEDIATE_ASSIGNMENT_REJ         = 0x3A,

    CIPHERING_MODE_COMMAND           = 0x35,
    CIPHERING_MODE_COMPLETE          = 0x32,

    ASSIGNMENT_COMMAND               = 0x2E,
    ASSIGNMENT_COMPLETE              = 0x29,
    ASSIGNMENT_FAILURE               = 0x2F,
    HANDOVER_COMMAND                 = 0x2B,
    HANDOVER_COMPLETE                = 0x2C,
    HANDOVER_FAILURE                 = 0x28,
    PHYSICAL_INFORMATION             = 0x2D,

    CHANNEL_RELEASE                  = 0x0D,
    PARTIAL_RELEASE                  = 0x0A,
    PARTIAL_RELEASE_COMPLETE         = 0x0F,

    PAGING_REQUEST_TYPE1             = 0x21,
    PAGING_REQUEST_TYPE2             = 0x22,
    PAGING_REQUEST_TYPE3             = 0x24,
    PAGING_RESPONSE                  = 0x27,

    SYSTEM_INFORMATION_TYPE8         = 0x18,
    SYSTEM_INFORMATION_TYPE1         = 0x19,
    SYSTEM_INFORMATION_TYPE2         = 0x1A,
    SYSTEM_INFORMATION_TYPE3         = 0x1B,
    SYSTEM_INFORMATION_TYPE4         = 0x1C,
    SYSTEM_INFORMATION_TYPE5         = 0x1D,
    SYSTEM_INFORMATION_TYPE6         = 0x1E,
    SYSTEM_INFORMATION_TYPE7         = 0x1F,

    SYSTEM_INFORMATION_TYPE2BIS      = 0x02,
    SYSTEM_INFORMATION_TYPE5BIS      = 0x05,

    SYSTEM_INFORMATION_TYPE2TER      = 0x03,
    SYSTEM_INFORMATION_TYPE5TER      = 0x06,
    SYSTEM_INFORMATION_TYPE9         = 0x04,
    SYSTEM_INFORMATION_TYPE13        = 0x00,

    CHANNEL_MODE_MODIFY              = 0x10,
    RR_STATUS                        = 0x12,
    CHANNEL_MODE_MODIFY_ACK          = 0x17,
    FREQUENCY_REDEFINITION           = 0x14,
    CLASSMARK_CHANGE                 = 0x16,
    MEASUREMENT_REPORT               = 0x15,
    CLASSMARK_ENQUIRY                = 0x13,
    EXTENDED_MEASUREMENT_ORDER       = 0x37,
    EXTENDED_MEASUREMENT_REPORT      = 0x36,
    RR_INITIALISATION                = 0x3c,
    RR_CELL_CHANGE_ORDER             = 0x08,
    PDCH_ASSIGNMENT_COMMAND          = 0x23,
    GPRS_SUSPENSION_REQUEST          = 0x34
} GSM0408RrMessageType;


/* MM MESSAGES */
typedef enum GSM0408MmMessageTypeTag
{
    IMSI_DETACH_INDICATION           = 0x01,
    LOCATION_UPDATING_ACCEPT         = 0x02,
    LOCATION_UPDATING_REJECT         = 0x04,
    LOCATION_UPDATING_REQUEST        = 0x08,

    AUTHENTICATION_REJECT            = 0x11,
    AUTHENTICATION_REQUEST           = 0x12,
    AUTHENTICATION_RESPONSE          = 0x14,
	AUTHENTICATION_FAILURE           = 0x1C,
    IDENTITY_REQUEST                 = 0x18,
    IDENTITY_RESPONSE                = 0x19,
    TMSI_REALLOCATION_COMMAND        = 0x1A,
    TMSI_REALLOCATION_COMPLETE       = 0x1B,

    CM_SERVICE_ACCEPT                = 0x21,
    CM_SERVICE_REJECT                = 0x22,
    CM_SERVICE_ABORT                 = 0x23,
    CM_SERVICE_REQUEST               = 0x24,
    CM_REESTABLISHMENT_REQUEST       = 0x28,

    ABORT                            = 0x29,
    MM_NULL                          = 0x30,
    MM_STATUS                        = 0x31,
    MM_INFORMATION                   = 0x32
} GSM0408MmMessageType;

/* CC (and call related SS) MESSAGES */
typedef enum GSM0408CcMessageTypeTag
{
    ALERTING                         = 0x01,
    CALL_CONFIRMED                   = 0x08,
    CALL_PROCEEDING                  = 0x02,
    CONNECT                          = 0x07,
    CONNECT_ACK                      = 0x0F,
    EMERGENCY_SETUP                  = 0x0E,
    PROGRESS                         = 0x03,
    SETUP                            = 0x05,

    MODIFY                           = 0x17,
    MODIFY_COMPLETE                  = 0x1F,
    MODIFY_REJECT                    = 0x13,
    USER_INFORMATION                 = 0x10,
    HOLD                             = 0x18,
    HOLD_ACK                         = 0x19,
    HOLD_REJECT                      = 0x1A,
    RETRIEVE                         = 0x1C,
    RETRIEVE_ACK                     = 0x1D,
    RETRIEVE_REJECT                  = 0x1E,

    DISCONNECT                       = 0x25,
    RELEASE                          = 0x2D,
    RELEASE_COMPLETE                 = 0x2A,
    CONGESTION_CONTROL               = 0x39,
    NOTIFY                           = 0x3E,
    CC_STATUS                        = 0x3D,
    STATUS_ENQUIRY                   = 0x34,
    START_DTMF                       = 0x35,
    STOP_DTMF                        = 0x31,
    STOP_DTMF_ACK                    = 0x32,
    START_DTMF_ACK                   = 0x36,
    START_DTMF_REJECT                = 0x37,
    FACILITY                         = 0x3A
} GSM0408CcMessageType;

/* SS MESSAGES */
typedef enum GSM0408SsMessageTypeTag
{
    SS_REGISTER                      = 0x3B,
    SS_FACILITY                      = 0x3A,
    SS_RELEASE_COMPLETE              = 0x2A
} GSM0408SsMessageType;

/* SMS MESSAGES */
typedef enum GSM0408SmsMessageTypeTag
{
    _CP_DATA                         = 0x01,
    _CP_ACK                          = 0x04,
    _CP_ERROR                        = 0x10
} GSM0408SmsMessageType;

/* GMM MESSAGES */
typedef enum GSM0408GmmMessageTypeTag
{
	ATTACH_REQUEST					= 0x01,
	ATTACH_ACCEPT					= 0x02,
	ATTACH_COMPLETE					= 0x03,
	ATTACH_REJECT					= 0x04,
	DETACH_REQUEST					= 0x05,
	DETACH_ACCEPT					= 0x06,

	ROUTING_AREA_UPDATE_REQUEST		= 0x08,
	ROUTING_AREA_UPDATE_ACCEPT		= 0x09,
	ROUTING_AREA_UPDATE_COMPLETE	= 0x0A,
	ROUTING_AREA_UPDATE_REJECT		= 0x0B,

	SERVICE_REQUEST					= 0x0C,
	SERVICE_ACCEPT					= 0x0D,
	SERVICE_REJECT					= 0x0E,

	PTMSI_REALLOCATION_COMMAND		= 0x10,
	PTMSI_REALLOCATION_COMPLETE		= 0x11,
	AUTHENT_AND_CYPH_REQUEST		= 0x12,
	AUTHENT_AND_CYPH_RESPONSE		= 0x13,
	AUTHENT_AND_CYPH_REJECT			= 0x14,
	AUTHENT_AND_CYPH_FAILURE		= 0x1C,
	GMM_IDENTITY_REQUEST			= 0x15,
	GMM_IDENTITY_RESPONSE			= 0x16,
	GMM_STATUS						= 0x20,
	GMM_INFORMATION					= 0x21

} GSM0408GmmMessageType;

/* SM MESSAGES */
typedef enum GSM0408SmMessageTypeTag
{
    ACTIVATE_PDP_CONTEXT_REQUEST_UP             = 0x41,
    ACTIVATE_PDP_CONTEXT_ACCEPT_DN              = 0x42,
    ACTIVATE_PDP_CONTEXT_REJECT_DN              = 0x43,
    REQUEST_PDP_CONTEXT_ACTIVATION_DN           = 0x44,
    REQUEST_PDP_CONTEXT_ACTIVATION_REJECT_UP    = 0x45,
    DEACTIVATE_PDP_CONTEXT_REQUEST              = 0x46, 
    DEACTIVATE_PDP_CONTEXT_ACCEPT               = 0x47,
    MODIFY_PDP_CONTEXT_REQUEST_DN               = 0x48,
    MODIFY_PDP_CONTEXT_ACCEPT_UP                = 0x49,
    MODIFY_PDP_CONTEXT_REQUEST_UP               = 0x4A,
    MODIFY_PDP_CONTEXT_ACCEPT_DN                = 0x4B,
    MODIFY_PDP_CONTEXT_REJECT_DN                = 0x4C,
    ACTIVATE_SECONDARY_PDP_CONTEXT_REQUEST_UP   = 0x4D,
    ACTIVATE_SECONDARY_PDP_CONTEXT_ACCEPT_DN    = 0x4E,
    ACTIVATE_SECONDARY_PDP_CONTEXT_REJECT_DN    = 0x4F,
    SM_STATUS                                   = 0x55
} GSM0408SmMessageType;


/* Values for the 04.08 Cause information element. These are defined */
/* using #define's because the cause field can apply to a number of  */
/* alternative coding schemes - we don't want loads of casts all over*/
/* the place.                                                        */

/* This first one is not in the 04.08 spec, but is useful for when we*/
/* wish to return a IE0408Cause and indicate all's OK.               */
#define IE0408_CAUSE_OK                                                                 0

#define IE0408_CAUSE_UNASSIGNED_NUMBER                                                  1
#define IE0408_CAUSE_IMSI_UNKNOWN_IN_HLR                                                2
#define IE0408_CAUSE_NO_ROUTE_TO_DESTINATION                                            3
#define IE0408_CAUSE_CHANNEL_UNACCEPTABLE                                               6
#define IE0408_CAUSE_OPERATOR_DETERMINED_BARRING                                        8
#define IE0408_CAUSE_NORMAL_CALL_CLEARING                                               16
#define IE0408_CAUSE_USER_BUSY                                                          17
#define IE0408_CAUSE_NO_USER_RESPONDING                                                 18
#define IE0408_CAUSE_USER_ALERTING_NO_ANSWER                                            19
#define IE0408_CAUSE_CALL_REJECTED                                                      21
#define IE0408_CAUSE_NUMBER_CHANGED                                                     22
#define IE0408_CAUSE_NON_SELECTED_USER_CLEARING                                         26
#define IE0408_CAUSE_DESTINATION_OUT_OF_ORDER                                           27
#define IE0408_CAUSE_INVALID_NUMBER_FORMAT                                              28
#define IE0408_CAUSE_FACILITY_REJECTED                                                  29
#define IE0408_CAUSE_RESPONSE_TO_STATUS_ENQUIRY                                         30
#define IE0408_CAUSE_NORMAL_UNSPECIFIED                                                 31
#define IE0408_CAUSE_NO_CIRCUIT_OR_CHANNEL_AVAILABLE                                    34
#define IE0408_CAUSE_NETWORK_OUT_OF_ORDER                                               38
#define IE0408_CAUSE_TEMPORARY_FAILURE                                                  41
#define IE0408_CAUSE_SWITCHING_EQUIPMENT_CONGESTION                                     42
#define IE0408_CAUSE_ACCESS_INFORMATION_DISCARDED                                       43
#define IE0408_CAUSE_REQUESTED_CIRCUIT_OR_CHANNEL_NOT_AVAILABLE                         44
#define IE0408_CAUSE_RESOURCES_UNAVAILABLE                                              47
#define IE0408_CAUSE_QUALITY_OF_SERVICE_UNAVAILABLE                                     49
#define IE0408_CAUSE_REQUESTED_FACILITY_NOT_SUBSCRIBED                                  50
#define IE0408_CAUSE_INCOMING_CALLS_BARRED_WITHIN_THE_CUG                               55
#define IE0408_CAUSE_BEARER_CAPABILITY_NOT_AUTHORIZED                                   57
#define IE0408_CAUSE_BEARER_CAPABILITY_NOT_PRESENTLY_AVAILABLE                          58
#define IE0408_CAUSE_SERVICE_OR_OPTION_NOT_AVAILABLE                                    63
#define IE0408_CAUSE_BEARER_SERVICE_NOT_IMPLEMENTED                                     65
#define IE0408_CAUSE_ACM_EQUAL_TO_OR_GREATER_THAN_ACMMAX                                68
#define IE0408_CAUSE_REQUESTED_FACILITY_NOT_IMPLEMENTED                                 69
#define IE0408_CAUSE_ONLY_RESTRICTED_DIGITAL_INFORMATION_BEARER_CAPABILITY_IS_AVAILABLE 70
#define IE0408_CAUSE_SERVICE_OR_OPTION_NOT_IMPLEMENTED                                  79
#define IE0408_CAUSE_INVALID_TRANSACTION_IDENTIFIER_VALUE                               81
#define IE0408_CAUSE_USER_NOT_MEMBER_OF_CUG                                             87
#define IE0408_CAUSE_INCOMPATIBLE_DESTINATION                                           88
#define IE0408_CAUSE_INVALID_TRANSIT_NETWORK_SELECTION                                  91
#define IE0408_CAUSE_SEMANTICALLY_INCORRECT_MESSAGE                                     95
#define IE0408_CAUSE_INVALID_MANDATORY_INFORMATION                                      96
#define IE0408_CAUSE_MESSAGE_TYPE_NON_EXISTENT_OR_NOT_IMPLEMENTED                       97
#define IE0408_CAUSE_MESSAGE_TYPE_NOT_COMPATIBLE                                        98
#define IE0408_CAUSE_IE_NON_EXISTENT_OR_NOT_IMPLEMENTED                                 99
#define IE0408_CAUSE_CONDITIONAL_IE_ERROR                                               100
#define IE0408_CAUSE_MESSAGE_NOT_COMPATIBLE_WITH_PROTOCOL_STATE                         101
#define IE0408_CAUSE_RECOVERY_ON_TIMER_EXPIRY                                           102
#define IE0408_CAUSE_PROTOCOL_ERROR                                                     111
#define IE0408_CAUSE_INTERWORKING                                                       127

// Session Management 'Cause' IE values.
#define IE24008_SM_CAUSE_OPERATOR_DETERMINED_BARRING                        (0x08)
#define IE24008_SM_CAUSE_LLC_OR_SNDCP_FAILURE                               (0x19)
#define IE24008_SM_CAUSE_INSUFFICIENT_RESOURCES                             (0x1a)
#define IE24008_SM_CAUSE_MISSING_OR_UNKNOWN_APN                             (0x1b)
#define IE24008_SM_CAUSE_UNKNOWN_PDP_ADDRESS_OR_PDP_TYPE                    (0x1c)
#define IE24008_SM_CAUSE_USER_AUTHENTICATION_FAILED                         (0x1d)
#define IE24008_SM_CAUSE_ACTIVATION_REJECTED_BY_GGSN                        (0x1e)
#define IE24008_SM_CAUSE_ACTIVATION_REJECTED_UNSPECIFIED                    (0x1f)
#define IE24008_SM_CAUSE_SERVICE_OPTION_NOT_SUPPORTED                       (0x20)
#define IE24008_SM_CAUSE_REQUESTED_SERVICE_OPTION_NOT_SUBSCRIBED            (0x21)
#define IE24008_SM_CAUSE_SERVICE_OPTION_TEMPORARILY_OUT_OF_ORDER            (0x22)
#define IE24008_SM_CAUSE_NSAPI_ALREADY_USED                                 (0x23)
#define IE24008_SM_CAUSE_REGULAR_DEACTIVATION                               (0x24)
#define IE24008_SM_CAUSE_QOS_NOT_ACCEPTED                                   (0x25)
#define IE24008_SM_CAUSE_NETWORK_FAILURE                                    (0x26)
#define IE24008_SM_CAUSE_REACTIVATION_REQUIRED                              (0x27)
#define IE24008_SM_CAUSE_FEATURE_NOT_SUPPORTED                              (0x28)
#define IE24008_SM_CAUSE_SEMANTIC_ERROR_IN_THE_TFT_OPERATION                (0x29)
#define IE24008_SM_CAUSE_SYNTACTICAL_ERROR_IN_THE_TFT_OPERATION             (0x2a)
#define IE24008_SM_CAUSE_UNKNOWN_PDP_CONTEXT                                (0x2b)
#define IE24008_SM_CAUSE_SEMANTIC_ERRORS_IN_PACKET_FILTER                   (0x2c)
#define IE24008_SM_CAUSE_SYNTACTICAL_ERRORS_IN_PACKET_FILTER                (0x2d)
#define IE24008_SM_CAUSE_PDP_CONTEXT_WITHOUT_TFT_ALREADY_ACTIVATED          (0x2e) 
#define IE24008_SM_CAUSE_INVALID_TRANSACTION_IDENTIFIER_VALUE               (0x51)
#define IE24008_SM_CAUSE_SEMANTICALLY_INCORRECT_MESSAGE                     (0x5f)
#define IE24008_SM_CAUSE_INVALID_MANDATORY_INFORMATION                      (0x60)
#define IE24008_SM_CAUSE_MESSAGE_TYPE_NONEXISTENT_OR_NOT_IMPLEMENTED        (0x61)
#define IE24008_SM_CAUSE_MESSAGE_TYPE_NOT_COMPATIBLE_WITH_PROTOCOL_STATE    (0x62)
#define IE24008_SM_CAUSE_INFORMATION_ELEMENT_NONEXISTENT_OR_NOT_IMPLEMENTED (0x63)
#define IE24008_SM_CAUSE_CONDITIONAL_IE_ERROR                               (0x64)
#define IE24008_SM_CAUSE_MESSAGE_NOT_COMPATIBLE_WITH_PROTOCOL_STATE         (0x65)
#define IE24008_SM_CAUSE_PROTOCOL_ERROR_UNSPECIFIED                         (0x6f)

/* Call States - see GSM04.08 10.5.4.6 */
typedef enum GSM0408CodingStandardTag
{
    GSM_0408_CODING_STD_Q931        = 0x00,
    GSM_0408_CODING_STD_RESERVED    = 0x40,
    GSM_0408_CODING_STD_NATIONAL    = 0x80,
    GSM_0408_CODING_STD_GSM         = 0xc0
}GSM0408CodingStandard;

#define GSM_0408_CODING_STD_MASK    0xC0


/* call priority - defined in GSM04.08, 10.5.1.9 but used by others */
/* (e.g. GSM 08.58, 9.3.49)                                         */
typedef enum IE0408CallPriorityTag
{
    CPRI_NO_PRIORITY_APPLIED        = 0x00,
    CPRI_LEVEL_4                    = 0x01,
    CPRI_LEVEL_3                    = 0x02,
    CPRI_LEVEL_2                    = 0x03,
    CPRI_LEVEL_1                    = 0x04,
    CPRI_LEVEL_0                    = 0x05,
    CPRI_LEVEL_B                    = 0x06,
    CPRI_LEVEL_A                    = 0x07
}IE0408CallPriority;

/* Type of identity - defined in GSM04.08, 10.5.3.4 but used by others */
/* (e.g. GSM 08.58, 9.3.12)                                            */
typedef enum IE0408MobileIdentityType_Tag
{
    NO_IDENTITY     = 0x00,
    MI_IMSI         = 0x01,
    MI_IMEI         = 0x02,
    MI_IMEISV       = 0x03,
    MI_TMSI_P_TMSI  = 0x04,

    INVALID_IDENTITY
}IE0408MobileIdentityType;

/*****************************************************************************/
/* Bearer Capability - GSM 04.08 10.5.4.5                                    */

typedef enum Gsm0408BearerCapInfoTransfer_Tag
{
    GSM0408_BC_IT_SPEECH                                        = 0x00,
    GSM0408_BC_IT_UNRESTRICTED_DIGITAL_INFORMATION              = 0x01,
    GSM0408_BC_IT_PLMN_3_1_KHZ_AUDIO                            = 0x02,
    GSM0408_BC_IT_FACSIMILE_GROUP_3                             = 0x03,
    GSM0408_BC_IT_OTHER_ITC                                     = 0x05,
    GSM0408_BC_IT_RESERVED                                      = 0x07,

    GSM0408_BC_IT_INVALID
} Gsm0408BearerCapInfoTransfer;

typedef enum Gsm0408BearerCapTransferMode_Tag
{
    GSM0408_BC_TM_CIRCUIT_MODE                                  = 0x00,
    GSM0408_BC_TM_PACKET_MODE                                   = 0x08,

    GSM0408_BC_TM_INVALID
} Gsm0408BearerCapTransferMode;

typedef enum Gsm0408BearerCapCodingStandard_Tag
{
    GSM0408_BC_CS_GSM_STANDARDIZED_CODING                       = 0x00,
    GSM0408_BC_CS_RESERVED                                      = 0x10,

    GSM0408_BC_CS_INVALID
} Gsm0408BearerCapCodingStandard;

typedef enum Gsm0408BearerCapRadioChannel_Tag
{
    GSM0408_BC_RC_MS_FULL_RATE_SUPPORT_ONLY                     = 0x20,
    GSM0408_BC_RC_MS_DUAL_RATE_SUPPORT_PREF_HALF_RATE           = 0x40,
    GSM0408_BC_RC_MS_DUAL_RATE_SUPPORT_PREF_FULL_RATE           = 0x60,

    GSM0408_BC_RC_INVALID
} Gsm0408BearerCapRadioChannel;

typedef enum Gsm0408BearerCapSpeechCoding_Tag
{
    GSM0408_BC_SC_GSM_FULL_RATE_SPEECH_VERSION_1                = 0x00,
    GSM0408_BC_SC_GSM_FULL_RATE_SPEECH_VERSION_2                = 0x02,
    GSM0408_BC_SC_GSM_FULL_RATE_SPEECH_VERSION_3                = 0x04,
    GSM0408_BC_SC_GSM_HALF_RATE_SPEECH_VERSION_1                = 0x01,
    GSM0408_BC_SC_GSM_HALF_RATE_SPEECH_VERSION_3                = 0x05,

    GSM0408_BC_SC_INVALID
} Gsm0408BearerCapSpeechCoding;

/* user rate for data calls */
typedef enum Gsm0408BearerCapUserRateTag
{
    GSM0408_BC_UR_0_3_KBPS                                      = 0x01,
    GSM0408_BC_UR_1_2_KBPS                                      = 0x02,
    GSM0408_BC_UR_2_4_KBPS                                      = 0x03,
    GSM0408_BC_UR_4_8_KBPS                                      = 0x04,
    GSM0408_BC_UR_9_6_KBPS                                      = 0x05,
    GSM0408_BC_UR_12_0_KBPS                                     = 0x06,
    GSM0408_BC_UR_1_2_KBPS_75_BPS                               = 0x07,

    GSM0408_BC_UR_INVALID
} Gsm0408BearerCapUserRate;

/* mask to isolate the user (data) rate in octet 6a of the raw BC data call bytes */
#define GSM0408_BC_USER_RATE_MASK               0x0f

/* The Ciphering Algorithm identifier - (bits aligned for use in
** 04.08 Cipher Mode Setting IE)
*/
typedef enum IE0408CipherModeSettingAlgorithm
{
    CMSA_ALGORITHM_A5_1             = 0x00,
    CMSA_ALGORITHM_A5_2             = 0x02,
    CMSA_ALGORITHM_A5_3             = 0x04,
    CMSA_ALGORITHM_A5_4             = 0x06,
    CMSA_ALGORITHM_A5_5             = 0x08,
    CMSA_ALGORITHM_A5_6             = 0x0A,
    CMSA_ALGORITHM_A5_7             = 0x0C,

    CMSA_INVALID
} IE0408CipherModeSettingAlgorithm;


typedef enum IE0408CmServiceTypeValue_Tag
{
    CMST_MOBILE_ORIGINATING_CALL_ESTABLISHMENT   = 0x01,
    CMST_EMERGENCY_CALL_ESTABLISHMENT            = 0x02,
    CMST_SHORT_MESSAGE_SERVICE                   = 0x04,
    CMST_SUPPLEMENTARY_SERVICE_ACTIVATION        = 0x08,
    CMST_VOICE_GROUP_CALL_ESTABLISHMENT          = 0x09,
    CMST_VOICE_BROADCAST_CALL_ESTABLISHMENT      = 0x0A,
    CMST_LOCATION_SERVICES                       = 0x0B,
    
    CMST_INVALID_CM_SERVICE_VALUE
} IE0408CmServiceTypeValue;

// Enum maps directly onto bits in IE
typedef enum IE0408RejectCauseValueTag
{
    RC_IMSI_UNKNOWN_IN_HLR                                  = 0x02,
    RC_ILLEGAL_MS                                           = 0x03,
    RC_IMSI_UNKNOWN_IN_VLR                                  = 0x04,
    RC_IMEI_NOT_ACCEPTED                                    = 0x05,
    RC_ILLEGAL_ME                                           = 0x06,
    RC_PLMN_NOT_ALLOWED                                     = 0x0B,
    RC_LOCATION_AREA_NOT_ALLOWED                            = 0x0C,
    RC_ROAMING_NOT_ALLOWED_IN_THIS_LOCATION_AREA            = 0x0D,
    RC_NO_SUITABLE_CELLS_AVAILABLE                          = 0x0F,
    RC_NETWORK_FAILURE                                      = 0x11,
    RC_CONGESTION                                           = 0x16,
    RC_SERVICE_OPTION_NOT_SUPPORTED                         = 0x20,
    RC_REQUESTED_SERVICE_OPTION_NOT_SUBSCRIBED              = 0x21,
    RC_SERVICE_OPTION_TEMPORARILY_OUT_OF_ORDER              = 0x22,
    RC_CALL_CANNOT_BE_IDENTIFIED                            = 0x26,

    // There's a range for the following
    RC_RETRY_UPON_ENTRY_INTO_A_NEW_CALL                     = 0x30,
    RC_RETRY_UPON_ENTRY_INTO_A_NEW_CALL_MAX_VALUE           = 0x3F,

    RC_SEMANTICALLY_INCORRECT_MESSAGE                       = 0x5F,
    RC_INVALID_MANDATORY_INFORMATION                        = 0x60,
    RC_MESSAGE_TYPE_NON_EXISTANT_OR_NOT_IMPLEMENTED         = 0x61,
    RC_MESSAGE_TYPE_NOT_COMPATIBLE_WITH_THE_PROTOCOL_STATE  = 0x62,
    RC_INFORMATION_ELEMENT_NON_EXISTANT_OR_NOT_IMPLEMENTED  = 0x63,
    RC_CONDITIONAL_IE_ERROR                                 = 0x64,
    RC_MESSAGE_NOT_COMPATIBLE_WITH_THE_PROTOCOL_STATE       = 0x65,
    RC_PROTOCOL_ERROR_UNSPECIFIED                           = 0x6F,

    RC_INVALID
}
IE0408RejectCauseValue;

typedef enum enum24008BCDNumberType
{
    CPBN_TYPE_UNKNOWN                       = 0x00,
    CPBN_TYPE_INTERNATIONAL_NUMBER          = 0x10,
    CPBN_TYPE_NATIONAL_NUMBER               = 0x20,
    CPBN_TYPE_NETWORK_SPECIFIC_NUMBER       = 0x30,
    CPBN_TYPE_DEDICATED_ACCESS_SHORT_CODE   = 0x40,

    CPBN_TYPE_INVALID
} BCDNumberType;

typedef enum enum24008BCDNumberPlan
{
    CPBN_PLAN_UNKNOWN                       = 0x00,
    CPBN_PLAN_ISDN_TELEPHONY_NUMBERING_PLAN = 0x01,
    CPBN_PLAN_DATA_NUMBERING_PLAN           = 0x03,
    CPBN_PLAN_TELEX_NUMBERING_PLAN          = 0x04,
    CPBN_PLAN_NATIONAL_NUMBERING_PLAN       = 0x08,
    CPBN_PLAN_PRIVATE_NUMBERING_PLAN        = 0x09,
    CPBN_PLAN_RESERVED_FOR_CTS              = 0x0B,
    CPBN_PLAN_RESERVED_FOR_EXTENSION        = 0x0F,

    CPBN_PLAN_INVALID
} BCDNumberPlan;

typedef enum enum24008EstablishmentCause {
    EST_CAUSE_ORIGINATING_CONVERSATIONAL_CALL = 0,
    EST_CAUSE_ORIGINATING_STREAMING_CALL = 1,
    EST_CAUSE_ORIGINATING_INTERACTIVE_CALL = 2,
    EST_CAUSE_ORIGINATING_BACKGROUND_CALL = 3,
    EST_CAUSE_ORIGINATING_SUBSCRIBED_TRAFFIC_CALL = 4,
    EST_CAUSE_TERMINATING_CONVERSATIONAL_CALL = 5,
    EST_CAUSE_TERMINATING_STREAMING_CALL = 6,
    EST_CAUSE_TERMINATING_INTERACTIVE_CALL = 7,
    EST_CAUSE_TERMINATING_BACKGROUND_CALL = 8,
    EST_CAUSE_EMERGENCY_CALL = 9,
    EST_CAUSE_INTERRAT_CELL_RESELECTION = 10,
    EST_CAUSE_INTERRAT_CELL_CHANGE_ORDER = 11,
    EST_CAUSE_REGISTRATION = 12,
    EST_CAUSE_DETACH = 13,
    EST_CAUSE_ORIGINATING_HIGH_PRIORITY_SIGNALLING = 14,
    EST_CAUSE_ORIGINATING_LOW_PRIORITY_SIGNALLING = 15,
    EST_CAUSE_CALLRE_ESTABLISHMENT = 16,
    EST_CAUSE_TERMINATING_HIGH_PRIORITY_SIGNALLING = 17,
    EST_CAUSE_TERMINATING_LOW_PRIORITY_SIGNALLING = 18,
    EST_CAUSE_TERMINATING_CAUSE_UNKNOWN = 19,
    EST_CAUSE_SPARE12 = 20,
    EST_CAUSE_SPARE11 = 21,
    EST_CAUSE_SPARE10 = 22,
    EST_CAUSE_SPARE9 = 23,
    EST_CAUSE_SPARE8 = 24,
    EST_CAUSE_SPARE7 = 25,
    EST_CAUSE_SPARE6 = 26,
    EST_CAUSE_SPARE5 = 27,
    EST_CAUSE_SPARE4 = 28,
    EST_CAUSE_SPARE3 = 29,
    EST_CAUSE_SPARE2 = 30,
    EST_CAUSE_SPARE1 = 31
} IE0408EstablishmentCause;

#endif
