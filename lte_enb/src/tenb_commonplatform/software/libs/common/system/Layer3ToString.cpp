///////////////////////////////////////////////////////////////////////////////
//
// Layer3ToString.cpp
//
// Simple PD + MT to string helpers.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#include "3waytypes.h"
#include "nas/include/Layer3Constants.h"

namespace threeway
{

const char *Layer3PD_To_String (unsigned char  x)
{
	switch (x & M0408_PROTOCOL_DISCRIMINATOR_MASK)
	{
	case PD_CC: return "CC";
	case PD_MM: return "MM";
	case PD_RR: return "RR";
	case PD_GMM: return "GMM";
	case PD_SMS: return "SMS";
	case PD_SM: return "SM";
	case PD_SS: return "SS";
	case PD_TEST: return "TEST";
	case PD_NON: return "NON";
	default: return "??";
	}
}

const char *Layer3MT_To_String (unsigned char x, unsigned char y)
{
	switch (x & M0408_PROTOCOL_DISCRIMINATOR_MASK)
	{
	case PD_CC:
		switch (y & M0408_BASIC_MSG_TYPE_MASK)
		{
		case ALERTING: return "ALERTING";
		case CALL_CONFIRMED: return "CALL_CONFIRMED";
		case CALL_PROCEEDING: return "CALL_PROCEEDING";
		case CONNECT: return "CONNECT";
		case CONNECT_ACK: return "CONNECT_ACK";
		case EMERGENCY_SETUP: return "EMERGENCY_SETUP";
		case PROGRESS: return "PROGRESS";
		case SETUP: return "SETUP";
		case MODIFY: return "MODIFY";
		case MODIFY_COMPLETE: return "MODIFY_COMPLETE";
		case MODIFY_REJECT: return "MODIFY_REJECT";
		case USER_INFORMATION: return "USER_INFORMATION";
		case HOLD: return "HOLD";
		case HOLD_ACK: return "HOLD_ACK";
		case HOLD_REJECT: return "HOLD_REJECT";
		case RETRIEVE: return "RETRIEVE";
		case RETRIEVE_ACK: return "RETRIEVE_ACK";
		case RETRIEVE_REJECT: return "RETRIEVE_REJECT";
		case DISCONNECT: return "DISCONNECT";
		case RELEASE: return "RELEASE";
		case RELEASE_COMPLETE: return "RELEASE_COMPLETE";
		case CONGESTION_CONTROL: return "CONGESTION_CONTROL";
		case NOTIFY: return "NOTIFY";
		case CC_STATUS: return "CC_STATUS";
		case STATUS_ENQUIRY: return "STATUS_ENQUIRY";
		case START_DTMF: return "START_DTMF";
		case STOP_DTMF: return "STOP_DTMF";
		case STOP_DTMF_ACK: return "STOP_DTMF_ACK";
		case START_DTMF_ACK: return "START_DTMF_ACK";
		case START_DTMF_REJECT: return "START_DTMF_REJECT";
		case FACILITY: return "FACILITY";
		default: return "CC (not decoded)";
		}
	case PD_MM:
		switch (y & M0408_BASIC_MSG_TYPE_MASK)
		{
		case IMSI_DETACH_INDICATION: return "IMSI_DETACH_INDICATION";
		case LOCATION_UPDATING_ACCEPT: return "LOCATION_UPDATING_ACCEPT";
		case LOCATION_UPDATING_REJECT: return "LOCATION_UPDATING_REJECT";
		case LOCATION_UPDATING_REQUEST: return "LOCATION_UPDATING_REQUEST";
		case AUTHENTICATION_REJECT: return "AUTHENTICATION_REJECT";
		case AUTHENTICATION_REQUEST: return "AUTHENTICATION_REQUEST";
		case AUTHENTICATION_RESPONSE: return "AUTHENTICATION_RESPONSE";
		case AUTHENTICATION_FAILURE: return "AUTHENTICATION_FAILURE";
		case IDENTITY_REQUEST: return "IDENTITY_REQUEST";
		case IDENTITY_RESPONSE: return "IDENTITY_RESPONSE";
		case TMSI_REALLOCATION_COMMAND: return "TMSI_REALLOCATION_COMMAND";
		case TMSI_REALLOCATION_COMPLETE: return "TMSI_REALLOCATION_COMPLETE";
		case CM_SERVICE_ACCEPT: return "CM_SERVICE_ACCEPT";
		case CM_SERVICE_REJECT: return "CM_SERVICE_REJECT";
		case CM_SERVICE_ABORT: return "CM_SERVICE_ABORT";
		case CM_SERVICE_REQUEST: return "CM_SERVICE_REQUEST";
		case CM_REESTABLISHMENT_REQUEST: return "CM_REESTABLISHMENT_REQUEST";
		case ABORT: return "ABORT";
        case MM_NULL: return "MM_NULL";
        case MM_STATUS: return "MM_STATUS";
		case MM_INFORMATION: return "MM_INFORMATION";
		default: return "MM (not decoded)";
		}
	case PD_RR:
		return (y & M0408_BASIC_MSG_TYPE_MASK) == PAGING_RESPONSE ? "PAGING_RESPONSE" : "RR (not decoded)";
	case PD_GMM:
		switch (y)
		{
		case ATTACH_REQUEST: return "ATTACH_REQUEST";
		case ATTACH_ACCEPT: return "ATTACH_ACCEPT";
		case ATTACH_COMPLETE: return "ATTACH_COMPLETE";
		case ATTACH_REJECT: return "ATTACH_REJECT";
		case DETACH_REQUEST: return "DETACH_REQUEST";
		case DETACH_ACCEPT: return "DETACH_ACCEPT";
		case ROUTING_AREA_UPDATE_REQUEST: return "ROUTING_AREA_UPDATE_REQUEST";
		case ROUTING_AREA_UPDATE_ACCEPT: return "ROUTING_AREA_UPDATE_ACCEPT";
		case ROUTING_AREA_UPDATE_COMPLETE: return "ROUTING_AREA_UPDATE_COMPLETE";
		case ROUTING_AREA_UPDATE_REJECT: return "ROUTING_AREA_UPDATE_REJECT";
		case SERVICE_REQUEST: return "SERVICE_REQUEST";
		case SERVICE_ACCEPT: return "SERVICE_ACCEPT";
		case SERVICE_REJECT: return "SERVICE_REJECT";
		case PTMSI_REALLOCATION_COMMAND: return "PTMSI_REALLOCATION_COMMAND";
		case PTMSI_REALLOCATION_COMPLETE: return "PTMSI_REALLOCATION_COMPLETE";
		case AUTHENT_AND_CYPH_REQUEST: return "AUTHENT_AND_CYPH_REQUEST";
		case AUTHENT_AND_CYPH_RESPONSE: return "AUTHENT_AND_CYPH_RESPONSE";
		case AUTHENT_AND_CYPH_REJECT: return "AUTHENT_AND_CYPH_REJECT";
		case AUTHENT_AND_CYPH_FAILURE: return "AUTHENT_AND_CYPH_FAILURE";
		case GMM_IDENTITY_REQUEST: return "GMM_IDENTITY_REQUEST";
		case GMM_IDENTITY_RESPONSE: return "GMM_IDENTITY_RESPONSE";
		case GMM_STATUS: return "GMM_STATUS";
		case GMM_INFORMATION: return "GMM_INFORMATION";
		default: return "GMM (not decoded)";
		}
	case PD_SM:
        switch (y)
        {
        case ACTIVATE_PDP_CONTEXT_REQUEST_UP: return "ACT_PDP_CONTEXT_REQ_UP";
        case ACTIVATE_PDP_CONTEXT_ACCEPT_DN: return "ACT_PDP_CONTEXT_ACC_DN";
        case ACTIVATE_PDP_CONTEXT_REJECT_DN: return "ACT_PDP_CONTEXT_REJ_DN";
        case REQUEST_PDP_CONTEXT_ACTIVATION_DN: return "REQ_PDP_CONTEXT_ACT_DN";
        case REQUEST_PDP_CONTEXT_ACTIVATION_REJECT_UP: return "REQ_PDP_CONTEXT_ACT_REJECT_UP";
        case DEACTIVATE_PDP_CONTEXT_REQUEST: return "DEACT_PDP_CONTEXT_REQUEST";
        case DEACTIVATE_PDP_CONTEXT_ACCEPT: return "DEACT_PDP_CONTEXT_ACCEPT";
        case MODIFY_PDP_CONTEXT_REQUEST_DN: return "MOD_PDP_CONTEXT_REQUEST_DN";
        case MODIFY_PDP_CONTEXT_ACCEPT_UP: return "MOD_PDP_CONTEXT_ACCEPT_UP";
        case MODIFY_PDP_CONTEXT_REQUEST_UP: return "MOD_PDP_CONTEXT_REQUEST_UP";
        case MODIFY_PDP_CONTEXT_ACCEPT_DN: return "MOD_PDP_CONTEXT_ACCEPT_DN";
        case MODIFY_PDP_CONTEXT_REJECT_DN: return "MOD_PDP_CONTEXT_REJECT_DN";
        case ACTIVATE_SECONDARY_PDP_CONTEXT_REQUEST_UP: return "ACT_2ND_PDP_CONTEXT_REQUEST_UP";
        case ACTIVATE_SECONDARY_PDP_CONTEXT_ACCEPT_DN: return "ACT_2ND_PDP_CONTEXT_ACCEPT_DN";
        case ACTIVATE_SECONDARY_PDP_CONTEXT_REJECT_DN: return "ACT_2ND_PDP_CONTEXT_REJECT_DN";
        case SM_STATUS: return "SM_STATUS";
        default: return "SM (not decoded)";
        }
	case PD_SMS:
		return "SMS (not decoded)";
	case PD_SS:
		return "SS (not decoded)";
	case PD_TEST:
		return "TEST (not decoded)";
	case PD_NON:
		return "NON (not decoded)";
	default:
		return "L3 (unknown PD)";
	}
}

}


