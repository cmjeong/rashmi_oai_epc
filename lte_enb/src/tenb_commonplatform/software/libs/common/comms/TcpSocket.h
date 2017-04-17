///////////////////////////////////////////////////////////////////////////////
//
// TcpSocket.h
//
// Send and receive TCP packets.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __TcpSocket_h_
#define __TcpSocket_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <3waytypes.h>
#include <boost/shared_ptr.hpp>
#include <comms/IPv4Address.h>
#include <comms/networking.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "TcpReceiveThread.h"

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

/**
 * Class for sending and receiving TCP packets as TCP client.
 */
class TcpSocket
{
public:
    /**
     * Constructor for Client.
     *
     * \param tcpRxInterface Callback for received packets
     */
    TcpSocket(TcpRxInterface *tcpRxInterface);
    /**
     * Constructor for Server.
     *
     * \param localPort Port to bind the socket on
     * \param tcpRxInterface Callback for received packets
     */
    TcpSocket(u16 localPort, TcpServerRxInterface *tcpRxInterface, IPv4Address localIpAddress = INADDR_ANY);

    virtual ~TcpSocket();

    /**
     * Get file descriptor.
     */
    int GetSocketFd() const;

    /**
     * Connect to server.
     * \param remoteIpAddress IP address to send packets to
     * \param remotePort Port to send packets to
     * Second form will put socket into non-blocking and use select to wait
     * for successful connect - this allows us to specify a timeout.
     *
     * \return true if connect succeeded, false otherwise
     */
    bool Connect(IPv4Address remoteIpAddress, u16 remotePort);
    bool Connect(IPv4Address remoteIpAddress, u16 remotePort, u32 timeoutSecs);

    /**
     * Check connection status.
     */
    bool IsConnected();

    /**
     * Start/stop the TCP receive thread.
     */
    void StartReceiving();
    void StopReceiving();

    /**
     * Send a TCP packet.
     *
     * \param packet Packet to send
     * \param packetLen Length of packet in bytes
     * \param socket Id (> -1) in case it is not the already created one
     * \return Result of call to sendto i.e. -1 on failure or num chars sent
     */
    s32 TcpSend(const u8* packet, u32 packetLen, const int sockId = -1);

    /**
     * Get debug string.
     */
    virtual std::string ToString() const;

private:
    // Ensure objects of this type can't be copied.
    TcpSocket(const TcpSocket&);
    TcpSocket& operator=(const TcpSocket&);

    // Receive thread.
    boost::shared_ptr<TcpReceiveThread> m_tcpReceiveThread;

    // File descriptors for sending packets.
    int                 m_sockFd;
    struct sockaddr_in  m_sockAddr;

    // Connection state.
    bool                m_connected;

};

}

#endif
