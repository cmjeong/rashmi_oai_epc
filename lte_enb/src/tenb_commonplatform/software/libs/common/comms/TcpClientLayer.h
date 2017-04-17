///////////////////////////////////////////////////////////////////////////////
//
// TcpClientLayer.h
//
// Protocol layer that manages a set of TCP client connections.
//
// The upper edge interface uses two types of PDU:
//
//      TcpMgmtPDU - Contains CONNECT-REQ/CNF, DISCONNECT-REQ and
//                   DISCONNECT-IND for establishing/maintaining connections.
//
//      SimplePDU  - Contains packet to transmit (d/l) or received (u/l).
//
// The lower edge access sockets directly using the TcpSocket class (which
// wraps up standard unix socket calls).
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __TcpClientLayer_h_
#define __TcpClientLayer_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <map>
#include <boost/shared_ptr.hpp>
#include <comms/ProtocolLayer.h>
#include <comms/TcpSocket.h>
#include <comms/TcpMgmtPDU.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

using namespace boost;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

typedef shared_ptr<TcpSocket> TcpSocketPtr;
typedef std::map<s32, TcpSocketPtr> TcpClients; // Indexed by socket FD.

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class TcpClientLayer : public ProtocolLayer, public TcpRxInterface
{
public:
    /**
     * Construction / destruction.
     */
    TcpClientLayer();
    virtual ~TcpClientLayer();

    /**
     * Implement ProtocolLayer pure virtual.
     * Receive packet from the layer above.  This should be a TcpMgmtPDU for
     * setting up / clearing down the TCP connection or a SimplePDU for
     * transferring packets.
     * This layer reports a connection identifier in the CONNECT-CNF and this
     * ID must be used in the SimplePDU.
     */
    virtual void ReceiveFromHigherLayer(shared_ptr<PDU> pdu);

    /**
     * Implement ProtocolLayer pure virtual.
     * Receive packet from the layer below.  I guess this wouldn't
     * normally happen but just pass it through in case someone has
     * thought of a clever reason for doing this.
     */
    virtual void ReceiveFromLowerLayer(shared_ptr<PDU> pdu);

    /**
     * Implement TcpRxInterface pure virtual.
     * Handle a received TCP packet.
     */
    virtual s32 HandleTcpRx(s32 fd);

    /**
     * Implement TcpRxInterface pure virtual.
     * Handle a TCP disconnection.
     */
    virtual void HandleTcpDisconnect(s32 fd);

    /**
     * Get info about the state of this layer.  E.g. list of connections.
     */
    virtual std::string ToString() const;

private:
    /**
     * Send a DISCONNECT-IND to higher layer to indicate the TCP connection
     * identified by connectionId has disconnected.
     */
    void SendDisconnectInd(u32 connectionId) const;

    /**
     * Send a CONNECT-CNF to higher layer to indicate the TCP connection
     * identified by connectionId has successfully connected or failed to
     * connect.
     */
    void SendConnectCnf(const IPv4Address& remoteIpAddress, u16 remotePort,
                        u32 connectionId, TcpMgmtPDU::TcpMgmtResult result) const;

    // Default timeout when trying to do TCP connect.
    // This will block so don't make it too long.
    static const u32 DEFAULT_TCP_CONNECT_TIMEOUT_SECS = 5;

    // The current set of TCP clients, indexed by connection ID.
    TcpClients m_tcpClients;
};

}

#endif
