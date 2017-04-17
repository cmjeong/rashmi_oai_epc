///////////////////////////////////////////////////////////////////////////////
//
// TcpMgmtPDU.h
//
// Concrete PDU class for managing TCP client connections.
// This is the control interface for the top edge of TcpClientLayer.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __TcpMgmtPDU_h_
#define __TcpMgmtPDU_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <comms/PDU.h>
#include <comms/IPv4Address.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class TcpMgmtPDU : public PDU
{
public:
    enum TcpMgmtMessageType
    {
        CONNECT_REQ = 0,
        CONNECT_CNF,
        DISCONNECT_REQ,
        DISCONNECT_IND
    };
    
    enum TcpMgmtResult
    {
        CONNECTED = 0,
        FAILED_TO_CONNECT,
        NO_RESULT
    };
    
    /**
     * Construction / destruction.
     */
    // General purpose constructor.
    TcpMgmtPDU(TcpMgmtMessageType messageType, u32 connectionId);
    // CONNECT-REQ
    TcpMgmtPDU(const IPv4Address& remoteIpAddress, u16 remotePort);
    // CONNECT-CNF
    TcpMgmtPDU(const IPv4Address& remoteIpAddress, u16 remotePort, u32 connectionId, TcpMgmtResult result);
    virtual ~TcpMgmtPDU();
    
    /**
     * Accessors
     */
    TcpMgmtMessageType  GetMessageType() const      { return m_messageType; };
    const IPv4Address&  GetRemoteIpAddress() const  { return m_remoteIpAddress; };
    u16                 GetRemotePort() const       { return m_remotePort; };
    TcpMgmtResult       GetResult() const           { return m_result; };
    
    virtual std::string ToString() const;
    const char *        GetMessageTypeStr() const;
    
private:
    TcpMgmtMessageType m_messageType;

    // Following only applicable for CONNECT-REQ/CNF.
    IPv4Address     m_remoteIpAddress;
    u16             m_remotePort;
    TcpMgmtResult   m_result;
};

}

#endif
