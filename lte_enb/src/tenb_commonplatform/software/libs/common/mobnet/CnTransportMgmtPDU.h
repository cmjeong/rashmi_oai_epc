///////////////////////////////////////////////////////////////////////////////
//
// CnTransportMgmtPDU.h
//
// Concrete PDU class for managing core network connections.
// This is the control interface for the top edge of Iu (SCCP) or Iuh (HNBAP/RUA).
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CnTransportMgmtPDU_h_
#define __CnTransportMgmtPDU_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <boost/shared_ptr.hpp>
#include <comms/PDU.h>
#include <comms/SimplePDU.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MobnetTypes.h"
#include "IDNNS.h"
#include "IMSI.h"
#include "IMEI.h"
#include "TMSI.h"

using namespace boost;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class CnTransportMgmtPDU : public PDU
{
public:
    // Maximum length of user data field in an CN transport message.
    static const u32 CN_TRANSPORT_USER_DATA_FIELD_MAX_LEN_BYTES = 1000; // TODO - where's this defined?

    enum CnTransportMgmtMessageType
    {
        CONNECT_REQ = 0,
        CONNECT_CNF,
        DISCONNECT_REQ,
        DISCONNECT_IND,
        LOCAL_RELEASE,
		LOCAL_RESET,
		CN_SIG_CONN_ID_REQ,
		CN_SIG_CONN_ID_CNF
    };
    
    enum CnTransportMgmtResult
    {
        NO_RESULT = 0,
        CONNECTED,
        FAILED,                 // e.g. timeout or local reset
        REFUSED,                // Refused but may include a payload to send on to UE
        REFUSED_UE_NOT_ALLOWED, // Refused and UE is not allowed on this cell
        REFUSED_TEMPORARILY     // Refused and UE may retry on this cell
    };
    
    /**
     * Construction / destruction.
     * cnTransportConnId is allocated by client.
     */
    // General purpose constructors.
    CnTransportMgmtPDU(DomainIdent domain, u32 cnTransportConnId, CnTransportMgmtMessageType messageType);
    // Constructor taking a result code.
    CnTransportMgmtPDU(DomainIdent domain, u32 cnTransportConnId, CnTransportMgmtMessageType messageType,
                       CnTransportMgmtResult result);
    // Constructor taking a CN transport user message.
    CnTransportMgmtPDU(DomainIdent domain, u32 cnTransportConnId, CnTransportMgmtMessageType messageType,
                       shared_ptr<SimplePDU> userMessage);
    // Constructor taking a result code for CNF/RSP and CN transport user message.
    CnTransportMgmtPDU(DomainIdent domain, u32 cnTransportConnId, CnTransportMgmtMessageType messageType,
                       CnTransportMgmtResult result, shared_ptr<SimplePDU> userMessage);
    virtual ~CnTransportMgmtPDU();
    
    /**
     * Accessors
     */
    CnTransportMgmtMessageType  GetMessageType() const;
    const char *                GetMessageTypeStr() const;
    CnTransportMgmtResult       GetResult() const;
    const char *                GetResultStr() const;
    shared_ptr<SimplePDU>       GetUserMessage () const { return m_userMessage; }
    DomainIdent                 GetDomain() const { return m_domain; }

    /**
     * Optional info. as required for certain CN protocols e.g. Iuh/HNBAP
     */
    void SetUeImsi(const threeway::IMSI& ueImsi);
    bool GetUeImsi(threeway::IMSI& ueImsi);
    void SetUeTmsi(const threeway::TMSI& ueTmsi);
    bool GetUeTmsi(threeway::TMSI& ueTmsi);
    void SetUeImei(const threeway::IMEI& ueImei);
    bool GetUeImei(threeway::IMEI& ueImei);
    void SetUeCapabilities(rsysmob::AccessStratumRelease ueAsRelease, rsysmob::UeCsgCapability ueCsgCapability);
    bool GetUeCapabilities(rsysmob::AccessStratumRelease& ueAsRelease, rsysmob::UeCsgCapability& ueCsgCapability);
    void SetUeRegistrationCause(rsysmob::UeRegistrationCause cause);
    bool GetUeRegistrationCause(rsysmob::UeRegistrationCause& cause);
    void SetCnSigConnId(u32 cnSigConnId) { m_cnSigConnId = cnSigConnId; };
    u32  GetCnSigConnId() const { return m_cnSigConnId; };
	bool IsIDNNSPresent() const { return m_isIdnnsPresent;};
    const rsysmob::RadisysIntraDomainNASNodeSelector& GetIDNNS() const { return m_IDNNS;}
	void SetIDNNS(const rsysmob::RadisysIntraDomainNASNodeSelector& nodeSelector);
	bool IsIuReleaseDueToReloc() const             { return m_isIuRelDueToReloc; }
	void SetIuReleaseDueToReloc (bool isReloc)     { m_isIuRelDueToReloc = isReloc; }


    /**
     * Implement PDU virtual.
     */
    virtual std::string ToString() const;
    
private:
    // Set initial message for connect request - provided at construction
    // for CONNECT-REQ messages.
    void                SetCnTransportUserMessage(shared_ptr<SimplePDU> userMessage);
    
    DomainIdent                 m_domain;
    CnTransportMgmtMessageType  m_messageType;
    CnTransportMgmtResult       m_result;
    
    // Optional initial message to be sent with the CR or CC.
    shared_ptr<SimplePDU>       m_userMessage;

    // Optional UE info.
    threeway::IMSI                  m_ueImsi;
    threeway::TMSI                  m_ueTmsi;
    threeway::IMEI                  m_ueImei;
    bool                            m_ueCapabilityInfoPresent;
    rsysmob::AccessStratumRelease   m_ueAsRelease;
    rsysmob::UeCsgCapability        m_ueCsgCapability;
    bool                            m_ueRegistrationCausePresent;
    rsysmob::UeRegistrationCause    m_ueRegistrationCause;
    u32                             m_cnSigConnId;

	rsysmob::RadisysIntraDomainNASNodeSelector m_IDNNS;
	bool m_isIdnnsPresent;

	bool m_isIuRelDueToReloc;
};

}

#endif
