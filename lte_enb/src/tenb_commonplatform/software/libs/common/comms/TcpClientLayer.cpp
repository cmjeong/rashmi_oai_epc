///////////////////////////////////////////////////////////////////////////////
//
// TcpClientLayer.cpp
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
#include <3waytypes.h>
#include <system/Trace.h>
#include <comms/PDU.h>
#include <comms/TcpMgmtPDU.h>
#include <comms/SimplePDU.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "TcpClientLayer.h"

using namespace std;
using namespace boost;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// TcpClientLayer Class Functions
///////////////////////////////////////////////////////////////////////////////

TcpClientLayer::TcpClientLayer() :
    ProtocolLayer("TCP Client Layer")
{
    ENTER();
    EXIT();
}

TcpClientLayer::~TcpClientLayer()
{
    ENTER();
    EXIT();
}

void TcpClientLayer::ReceiveFromHigherLayer(shared_ptr<PDU> pdu)
{
    ENTER();

    // Check for a SimplePDU
    shared_ptr<SimplePDU> tcpPacketPDU = dynamic_pointer_cast<SimplePDU>(pdu);
    if(tcpPacketPDU)
    {
        // Lookup the TCP connection and if present, try to send the packet.
        // If sending fails, delete the socket and inform higher layer.
        u32 connectionId = tcpPacketPDU->GetConnectionId();
        TcpClients::iterator iter = m_tcpClients.find((s32)connectionId);
        if(iter != m_tcpClients.end())
        {
            // Found it.
            s32 sendResult = iter->second->TcpSend(tcpPacketPDU->GetPacket(),
                                                   tcpPacketPDU->GetPacketLength());
            if(sendResult < 0)
            {
                // Send failed.
                TRACE_PRINTF("TcpClientLayer: Failed to send PDU on connection %" PRIu32 ".  PDU: %s", connectionId, pdu->ToString().c_str());

                // Remove this connection and send disconnect ind.
                m_tcpClients.erase(iter);
                SendDisconnectInd(connectionId);
            }

        }
        else
        {
            TRACE_PRINTF("TcpClientLayer: Failed to find connection (%" PRIu32 ") to send PDU on.  PDU: %s", connectionId, pdu->ToString().c_str());
        }

        RETURN_VOID();
    }

    // Check for a TcpMgmtPDU
    shared_ptr<TcpMgmtPDU> tcpMgmtPDU = dynamic_pointer_cast<TcpMgmtPDU>(pdu);
    if(tcpMgmtPDU)
    {
        // Check for CONNECT-REQ or DISCONNECT-REQ.
        TcpMgmtPDU::TcpMgmtMessageType messageType = tcpMgmtPDU->GetMessageType();
        switch(messageType)
        {
            case TcpMgmtPDU::CONNECT_REQ:
                {
                // Create a new TCP client.
                shared_ptr<TcpSocket> newTcpClient( new TcpSocket(this) );
                // Try to connect.
                if(newTcpClient->Connect(tcpMgmtPDU->GetRemoteIpAddress(),
                                         tcpMgmtPDU->GetRemotePort(),
                                         DEFAULT_TCP_CONNECT_TIMEOUT_SECS))
                {
                    // Connected successfully.

                    // Add it to the set of clients.
                    int fd = newTcpClient->GetSocketFd();

                    // Double check we haven't already got this one.
                    // Just replace it if we have but make sure we log this.
                    TcpClients::iterator iter = m_tcpClients.find(fd);
                    if(iter != m_tcpClients.end())
                    {
                        // Hmmm...
                        TRACE("TcpClientLayer: Found duplicate TcpSocket, replacing.  FD", (s32)fd);
                        m_tcpClients.erase(iter);
                    }
                    m_tcpClients[(s32)fd] = newTcpClient;

                    // Send CONNECT-CNF (success).
                    SendConnectCnf(tcpMgmtPDU->GetRemoteIpAddress(), tcpMgmtPDU->GetRemotePort(),
                                   (u32)fd, TcpMgmtPDU::CONNECTED);

                    // Start receiving.
                    newTcpClient->StartReceiving();
                }
                else
                {
                    // Failed to connect.
                    // Send CONNECT-CNF (failed).
                    SendConnectCnf(tcpMgmtPDU->GetRemoteIpAddress(), tcpMgmtPDU->GetRemotePort(),
                                   PDU::PDU_CONNECTION_ID_UNDEFINED, TcpMgmtPDU::FAILED_TO_CONNECT);
                }
                }
                break;

            case TcpMgmtPDU::DISCONNECT_REQ:
                {
                // Find the connection and erase it.
                u32 connectionId = tcpMgmtPDU->GetConnectionId();
                TcpClients::iterator iter = m_tcpClients.find((s32)connectionId);
                if(iter != m_tcpClients.end())
                {
                    // Found it - remove it from map, TcpSocket destructor closes socket.
                    m_tcpClients.erase(iter);
                }
                else
                {
                    TRACE("TcpClientLayer: Received DISCONNECT-REQ but couldn't find socket, connectionId", connectionId);
                }
                }
                break;

            default:
                TRACE("Unrecognised TcpMgmtPDU message type", (u32)messageType);
                break;
        }

        RETURN_VOID();
    }


    EXIT();
}

void TcpClientLayer::ReceiveFromLowerLayer(shared_ptr<PDU> pdu)
{
    ENTER();

    // Not sure why someone might want to send a packet into the bottom of
    // this layer but just send it on anyway.
    SendToHigherLayer(pdu);

    EXIT();
}

s32 TcpClientLayer::HandleTcpRx(s32 fd)
{
    ENTER();

    u8 packet[PDU_MAX_LENGTH];
    int packetLen;

    // Receive the data locally.
    packetLen = recv(fd, packet, sizeof(packet), 0);

    // Check we know about this FD.
    TcpClients::iterator iter = m_tcpClients.find(fd);
    if(iter != m_tcpClients.end())
    {
        if(packetLen >= 0)
        {
            // All looks good, send it up.
            //TRACE("TcpClientLayer: Recv from FD", fd);
            shared_ptr<SimplePDU> tcpPacketPDU( new SimplePDU() );
            tcpPacketPDU->SetPacket(packet, packetLen);
            tcpPacketPDU->SetConnectionId((u32)fd);
            SendToHigherLayer(tcpPacketPDU);
            RETURN (0);
        }
        else
        {
            TRACE("TcpClientLayer: Failed to recv from FD", fd);
            RETURN (-1);
        }
    }
    else
    {
        TRACE("TcpClientLayer: Received a packet but can't find related socket, FD", fd);
        RETURN (-1);
    }

    RETURN(0);
}

void TcpClientLayer::HandleTcpDisconnect(s32 fd)
{
    ENTER();

    // Check we know about this FD.
    TcpClients::iterator iter = m_tcpClients.find(fd);
    if(iter != m_tcpClients.end())
    {
        // Found it, remove it and send DISCONNECT-IND.
        m_tcpClients.erase(iter);
        SendDisconnectInd((u32)fd);
    }
    else
    {
        // If not found it's probably because this is the call back to notify us
        // when the socket is destroyed - so if we've erased the socket from
        // our map because we got a DISCONNECT_REQ then this is what we expect.
        //TRACE("TcpClientLayer: Received disconnect notification but can't find socket for FD", fd);
    }

    EXIT();
}

std::string TcpClientLayer::ToString() const
{
    ENTER ();

    std::ostringstream stream;

    TcpClients::const_iterator iter = m_tcpClients.begin();
    u32 connIndex = 0;
    while(iter != m_tcpClients.end())
    {
        stream << connIndex++ << ": " << iter->second->ToString() << endl;
        ++iter;
    }

    RETURN (stream.str());
}

void TcpClientLayer::SendDisconnectInd(u32 connectionId) const
{
    ENTER();

    shared_ptr<TcpMgmtPDU> disconnectInd( new TcpMgmtPDU(TcpMgmtPDU::DISCONNECT_IND, connectionId) );
    SendToHigherLayer(disconnectInd);

    EXIT();
}

void TcpClientLayer::SendConnectCnf(const IPv4Address& remoteIpAddress, u16 remotePort, u32 connectionId, TcpMgmtPDU::TcpMgmtResult result) const
{
    ENTER();

    shared_ptr<TcpMgmtPDU> connectCnf( new TcpMgmtPDU(remoteIpAddress, remotePort, connectionId, result) );
    SendToHigherLayer(connectCnf);

    EXIT();
}

}
