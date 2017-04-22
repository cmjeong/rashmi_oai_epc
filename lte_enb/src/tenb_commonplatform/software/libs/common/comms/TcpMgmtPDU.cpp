///////////////////////////////////////////////////////////////////////////////
//
// TcpMgmtPDU.cpp
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

#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "TcpMgmtPDU.h"


namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

TcpMgmtPDU::TcpMgmtPDU(TcpMgmtMessageType messageType, u32 connectionId) :
    m_messageType(messageType),
    m_remotePort(0),
    m_result(NO_RESULT)
{
    SetConnectionId(connectionId);
    TRACE_PRINTF("TcpMgmtPDU instantiated, messageType=%s, connectionId=%" PRIu32,
                  GetMessageTypeStr(), connectionId);
}

// CONNECT-REQ
TcpMgmtPDU::TcpMgmtPDU(const IPv4Address& remoteIpAddress, u16 remotePort) :
    m_messageType(CONNECT_REQ),
    m_remoteIpAddress(remoteIpAddress),
    m_remotePort(remotePort),
    m_result(NO_RESULT)
{
    TRACE_PRINTF("TcpMgmtPDU instantiated, messageType=%s, remoteIpAddress=%s, remotePort=%u",
                  GetMessageTypeStr(), remoteIpAddress.ToString(), remotePort);
}

// CONNECT-CNF
TcpMgmtPDU::TcpMgmtPDU(const IPv4Address& remoteIpAddress, u16 remotePort, u32 connectionId, TcpMgmtResult result) :
    m_messageType(CONNECT_CNF),
    m_remoteIpAddress(remoteIpAddress),
    m_remotePort(remotePort),
    m_result(result)
{
    SetConnectionId(connectionId);
    TRACE_PRINTF("TcpMgmtPDU instantiated, messageType=%s, remoteIpAddress=%s, remotePort=%u, result=%" PRIu32,
                  GetMessageTypeStr(), remoteIpAddress.ToString(), remotePort, (u32)result);
}

TcpMgmtPDU::~TcpMgmtPDU()
{
}

std::string TcpMgmtPDU::ToString() const
{
    std::ostringstream stream;

    stream << PDU::ToString() << ", messageType=" << GetMessageTypeStr();

    if(m_remoteIpAddress.IsSet())
    {
        stream << ", remoteIpAddress=" << m_remoteIpAddress.ToString();
    }

    if(m_remotePort != 0)
    {
        stream << ", remotePort=" << m_remotePort;
    }

    switch(m_result)
    {
        case CONNECTED:
            stream << ", CONNECTED";
            break;
        case FAILED_TO_CONNECT:
            stream << ", FAILED_TO_CONNECT";
            break;
        case NO_RESULT:
            break;
    }

    return (stream.str());
}

const char * TcpMgmtPDU::GetMessageTypeStr() const
{
    switch(m_messageType)
    {
        case CONNECT_REQ:
            return "CONNECT-REQ";
            break;
        case CONNECT_CNF:
            return "CONNECT-CNF";
            break;
        case DISCONNECT_REQ:
            return "DISCONNECT-REQ";
            break;
        case DISCONNECT_IND:
            return "DISCONNECT-IND";
            break;
    }

    return "Unknown Message Type";
}

}
