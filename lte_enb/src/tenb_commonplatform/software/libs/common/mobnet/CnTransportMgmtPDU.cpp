///////////////////////////////////////////////////////////////////////////////
//
// CnTransportMgmtPDU.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <iomanip>
#include <string.h>
#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "CnTransportMgmtPDU.h"

using namespace boost;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

CnTransportMgmtPDU::CnTransportMgmtPDU(DomainIdent domain, u32 cnTransportConnId, CnTransportMgmtMessageType messageType) :
    m_domain(domain),
    m_messageType(messageType),
    m_result(NO_RESULT),
    m_ueCapabilityInfoPresent(false),
    m_ueAsRelease(rsysmob::AS_R99),
    m_ueCsgCapability(rsysmob::UE_NOT_CSG_CAPABLE),
    m_ueRegistrationCausePresent(false),
    m_ueRegistrationCause(rsysmob::UE_REG_CAUSE_NORMAL),
    m_cnSigConnId(PDU_CONNECTION_ID_UNDEFINED),
	m_isIdnnsPresent(false),
	m_isIuRelDueToReloc(false)
{

    RSYS_ASSERT(messageType != CnTransportMgmtPDU::CN_SIG_CONN_ID_CNF); // Must have a result associated with it.
    SetConnectionId(cnTransportConnId);
	memset(&m_IDNNS, 0, sizeof(m_IDNNS));
    
}

CnTransportMgmtPDU::CnTransportMgmtPDU(DomainIdent domain, u32 cnTransportConnId, CnTransportMgmtMessageType messageType, CnTransportMgmtResult result) :
    m_domain(domain),
    m_messageType(messageType),
    m_result(result),
    m_ueCapabilityInfoPresent(false),
    m_ueAsRelease(rsysmob::AS_R99),
    m_ueCsgCapability(rsysmob::UE_NOT_CSG_CAPABLE),
    m_ueRegistrationCausePresent(false),
    m_ueRegistrationCause(rsysmob::UE_REG_CAUSE_NORMAL),
    m_cnSigConnId(PDU_CONNECTION_ID_UNDEFINED),
	m_isIdnnsPresent(false),
	m_isIuRelDueToReloc(false)
{
    
    SetConnectionId(cnTransportConnId);
	memset(&m_IDNNS, 0, sizeof(m_IDNNS));
    
}

CnTransportMgmtPDU::CnTransportMgmtPDU(DomainIdent domain, u32 cnTransportConnId, CnTransportMgmtMessageType messageType, shared_ptr<SimplePDU> userMessage) :
    m_domain(domain),
    m_messageType(messageType),
    m_result(NO_RESULT),
    m_ueCapabilityInfoPresent(false),
    m_ueAsRelease(rsysmob::AS_R99),
    m_ueCsgCapability(rsysmob::UE_NOT_CSG_CAPABLE),
    m_ueRegistrationCausePresent(false),
    m_ueRegistrationCause(rsysmob::UE_REG_CAUSE_NORMAL),
    m_cnSigConnId(PDU_CONNECTION_ID_UNDEFINED),
	m_isIdnnsPresent(false),
	m_isIuRelDueToReloc(false)
{

    RSYS_ASSERT(messageType != CnTransportMgmtPDU::CN_SIG_CONN_ID_CNF); // Must have a result associated with it.

    SetConnectionId(cnTransportConnId);
    SetCnTransportUserMessage(userMessage);
	memset(&m_IDNNS, 0, sizeof(m_IDNNS));

}

CnTransportMgmtPDU::CnTransportMgmtPDU(DomainIdent domain, u32 cnTransportConnId, CnTransportMgmtMessageType messageType, CnTransportMgmtResult result, shared_ptr<SimplePDU> userMessage) :
    m_domain(domain),
    m_messageType(messageType),
    m_result(result),
    m_ueCapabilityInfoPresent(false),
    m_ueAsRelease(rsysmob::AS_R99),
    m_ueCsgCapability(rsysmob::UE_NOT_CSG_CAPABLE),
    m_ueRegistrationCausePresent(false),
    m_ueRegistrationCause(rsysmob::UE_REG_CAUSE_NORMAL),
    m_cnSigConnId(PDU_CONNECTION_ID_UNDEFINED),
	m_isIdnnsPresent(false),
	m_isIuRelDueToReloc(false)
{

    RSYS_ASSERT(messageType != CnTransportMgmtPDU::CN_SIG_CONN_ID_CNF); // Doesn't require user message.

    SetConnectionId(cnTransportConnId);
    SetCnTransportUserMessage(userMessage);
	memset(&m_IDNNS, 0, sizeof(m_IDNNS));

}

CnTransportMgmtPDU::~CnTransportMgmtPDU()
{
}

CnTransportMgmtPDU::CnTransportMgmtMessageType CnTransportMgmtPDU::GetMessageType() const
{
    return m_messageType;
}

const char * CnTransportMgmtPDU::GetMessageTypeStr() const
{
    
    switch(m_messageType)
    {
        case CONNECT_REQ:
            return("CONNECT-REQ");
            break;
        case CONNECT_CNF:
            return("CONNECT-CNF");
            break;
        case DISCONNECT_REQ:
            return("DISCONNECT-REQ");
            break;
        case DISCONNECT_IND:
            return("DISCONNECT-IND");
            break;
        case LOCAL_RELEASE:
            return("LOCAL-REL");
            break;
        case LOCAL_RESET:
            return("LOCAL-RESET");
            break;
        case CN_SIG_CONN_ID_REQ:
            return("CN-SIG-CONN-ID-REQ");
            break;
        case CN_SIG_CONN_ID_CNF:
            return("CN-SIG-CONN-ID-CNF");
            break;
    }
    
    return("Unknown Message Type");
}

CnTransportMgmtPDU::CnTransportMgmtResult CnTransportMgmtPDU::GetResult() const
{
    return m_result;
}

const char * CnTransportMgmtPDU::GetResultStr() const
{
    switch(m_result)
    {
        case NO_RESULT:
            return "NoResult";
            break;
        case CONNECTED:
            return "Connected";
            break;
        case FAILED:
            return "Failed";
            break;
        case REFUSED:
            return "Refused";
            break;
        case REFUSED_UE_NOT_ALLOWED:
            return "RefusedUeNotAllowed";
            break;
        case REFUSED_TEMPORARILY:
            return "RefusedTemporarily";
            break;
    }
    
    return "";
}

void CnTransportMgmtPDU::SetUeImsi(const threeway::IMSI& ueImsi)
{

    m_ueImsi = ueImsi;

}

bool CnTransportMgmtPDU::GetUeImsi(threeway::IMSI& ueImsi)
{

    ueImsi = m_ueImsi;

    return(m_ueImsi.IsSet());
}

void CnTransportMgmtPDU::SetUeTmsi(const threeway::TMSI& ueTmsi)
{

    m_ueTmsi = ueTmsi;

}

bool CnTransportMgmtPDU::GetUeTmsi(threeway::TMSI& ueTmsi)
{

    ueTmsi = m_ueTmsi;

    return(m_ueTmsi.IsSet());
}

void CnTransportMgmtPDU::SetUeImei(const threeway::IMEI& ueImei)
{

    m_ueImei = ueImei;

}

bool CnTransportMgmtPDU::GetUeImei(threeway::IMEI& ueImei)
{

    ueImei = m_ueImei;

    return(m_ueImei.IsSet());
}

void CnTransportMgmtPDU::SetUeCapabilities(rsysmob::AccessStratumRelease ueAsRelease, rsysmob::UeCsgCapability ueCsgCapability)
{

    m_ueCapabilityInfoPresent = true;
    m_ueAsRelease = ueAsRelease;
    m_ueCsgCapability = ueCsgCapability;

}

bool CnTransportMgmtPDU::GetUeCapabilities(rsysmob::AccessStratumRelease& ueAsRelease, rsysmob::UeCsgCapability& ueCsgCapability)
{

    ueAsRelease = m_ueAsRelease;
    ueCsgCapability = m_ueCsgCapability;

    return(m_ueCapabilityInfoPresent);
}

void CnTransportMgmtPDU::SetUeRegistrationCause(rsysmob::UeRegistrationCause cause)
{

    m_ueRegistrationCause = cause;
    m_ueRegistrationCausePresent = true;

}

bool CnTransportMgmtPDU::GetUeRegistrationCause(rsysmob::UeRegistrationCause& cause)
{

    cause = m_ueRegistrationCause;

    return(m_ueRegistrationCausePresent);
}

void CnTransportMgmtPDU::SetIDNNS(const rsysmob::RadisysIntraDomainNASNodeSelector& nodeSelector) 
{ 
	m_IDNNS = nodeSelector; 
	m_isIdnnsPresent=true;
}

std::string CnTransportMgmtPDU::ToString() const
{

    std::ostringstream stream;

    stream << GetMessageTypeStr();

    stream << ", " << MobnetTypes::DomainToString(m_domain);

    if(GetSourceId() != PDU_SOURCE_ID_UNDEFINED)
    {
        stream << ", sourceId=" << GetSourceId();
    }

    if(GetConnectionId() != PDU_CONNECTION_ID_UNDEFINED)
    {
        stream << ", connectionId=" << GetConnectionId();
    }

    if(m_ueRegistrationCausePresent)
    {
        stream << ", " << ueRegistrationCauseToString(m_ueRegistrationCause);
    }

    if(m_userMessage != NULL)
    {
        stream << ", WithPayload";
    }

    if(m_ueImsi.IsSet())
    {
        stream << ", imsi=" << m_ueImsi.ToString();
    }

    if(m_ueImei.IsSet())
    {
        stream << ", imei=" << m_ueImei.ToString();
    }

    if(m_cnSigConnId != PDU_CONNECTION_ID_UNDEFINED)
    {
        stream << ", sigConnId=0x" << std::setw(8) << std::setfill('0') << std::hex << m_cnSigConnId << std::dec;
    }

    if(m_result != NO_RESULT)
    {
        stream << ", " << GetResultStr();
    }

    if(m_isIdnnsPresent)
    {
        stream << ", IDNNS=" << IDNNSToString(m_IDNNS);
    }

    return(stream.str());
}

void CnTransportMgmtPDU::SetCnTransportUserMessage(shared_ptr<SimplePDU> userMessage)
{
    
    u32 pduLen = userMessage->GetPacketLength();
    RSYS_ASSERT_PRINTF(pduLen < CN_TRANSPORT_USER_DATA_FIELD_MAX_LEN_BYTES, "CnTransportMgmtPDU: CN transport user message length of %" PRIu32 " exceeds user data field limit of %" PRIu32,
                       pduLen, CN_TRANSPORT_USER_DATA_FIELD_MAX_LEN_BYTES);

    m_userMessage = userMessage;
    
}

}
