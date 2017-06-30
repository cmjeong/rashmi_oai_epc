///////////////////////////////////////////////////////////////////////////////
//
// UdpSocket.h
//
// Send and receive UDP packets.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __UdpSocket_h_
#define __UdpSocket_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <netinet/ip.h>
#include <unistd.h>
#include <3waytypes.h>

#include <boost/shared_ptr.hpp>
#include <comms/IPv4Address.h>

#include <comms/TOSValues.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "UdpReceiveThread.h"

using namespace boost;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

/**
 * Class for sending and receiving UDP packets.
 */
class UdpSocket : public GetFdInterface
{
public:

    /**
     * Constructor for transmit and receive.
     *
     * \param localIpAddress    Interface to bind to.
     * \param localPort         Port to listen on.
     * \param remoteIpAddress   IP address to send packets to.
     * \param remotePort        Port to send packets to.
     * \param tosValue          TOS Value for the socket
     * \param udpRxInterface    Callback for received packets.
     */
    UdpSocket( const IPv4Address& localIpAddress, u16 localPort, const IPv4Address& remoteIpAddress, u16 remotePort,
               UdpRxInterface& udpRxInterface, TOSVal tosValue = QOS_NONE, bool reentrantUdpSend = false);

    /**
     * Constructor for transmit and receive.
     *
     * \param localPort         Port to listen on.
     * \param remoteIpAddress   IP address to send packets to.
     * \param remotePort        Port to send packets to.
     * \param udpRxInterface    Callback for received packets.
     */
    UdpSocket(u16 localPort, const IPv4Address& remoteIpAddress, u16 remotePort, UdpRxInterface& udpRxInterface,
                bool reentrantUdpSend = false);

    /**
     * Constructor for transmit only.
     *
     * \param localIpAddress    Interface to bind to.
     * \param remoteIpAddress   IP address to send packets to.
     * \param remotePort        Port to send packets to.
     * \param tosValue          TOS Value for the socket
     */
    UdpSocket( const IPv4Address& localIpAddress, const IPv4Address& remoteIpAddress, u16 remotePort,
               TOSVal tosValue = QOS_NONE, bool reentrantUdpSend = false);

    /**
     * Constructor for transmit only.
     *
     * \param localIpAddress    Interface to bind to.
     * \param localPort         Local port to send from.
     * \param remoteIpAddress   IP address to send packets to.
     * \param remotePort        Port to send packets to.
     * \param tosValue          TOS Value for the socket
     */
    UdpSocket( const IPv4Address& localIpAddress, u16 localPort, const IPv4Address& remoteIpAddress, u16 remotePort,
               TOSVal tosValue = QOS_NONE, bool reentrantUdpSend = false);

    /**
     * Constructor for transmit only.
     *
     * \param remoteIpAddress   IP address to send packets to.
     * \param remotePort        Port to send packets to.
     */
    UdpSocket(const IPv4Address& remoteIpAddress, u16 remotePort, bool reentrantUdpSend = false);

    /**
     * Constructor for receive only (can still use UdpSendTo though as remote IP/port is provided at that point).
     *
     * \param localPort         Port to listen on.
     * \param udpRxInterface    Callback for received packets.
     */
    UdpSocket(u16 localPort, UdpRxInterface& udpRxInterface);

    virtual ~UdpSocket();

    /**
     * Start/stop the UDP receive thread.
     */
    void StartReceiving();
    void StopReceiving();

    /**
     * Send a UDP packet.
     *
     * \param packet Packet to send
     * \param packetLen Length of packet in bytes
     */
    s32 UdpSend(const u8* packet, u32 packetLen) const;

    /**
     * Send a UDP packet to the given IP Address and port.
     *
     * \param packet Packet to send
     * \param packetLen Length of packet in bytes
     */
    s32 UdpSendTo(const IPv4Address& remoteIpAddress, u16 remotePort, const u8* packet, u32 packetLen) const;

    /**
     * Set the underlying file descriptor to close-on-exec.
     */
    void CloseOnExec();

    /**
     * Get as string for debug.
     */
    virtual std::string ToString() const;

    /* Accessor for use of NTP*/
    int GetFd();

private:
    // Initialise the transmit section.
    void InitialiseTransmit();

    // Initialise the receive section including constructing the receive thread.
    void InitialiseReceive(UdpRxInterface& udpRxInterface);

    // Receive thread - only constructed if required.
    shared_ptr<UdpReceiveThread> m_udpReceiveThread;

    IPv4Address         m_localIpAddress;
    u16                 m_localPort;

    // Remote IP/port for sending.
    IPv4Address         m_remoteIpAddress;
    u16                 m_remotePort;

    // TOS value associated with socket
    TOSVal              m_tosValue;

    // File descriptor - can be just transmit, receive or both depending on constructor called.
    int                 m_fd;

    // Transmit sockaddr.
    struct sockaddr_in  m_txSockAddr;

    // Are we providing a re-entrant UdpSend?
    bool                m_reentrantUdpSend;

    // UdpSend mutex.
    mutable Mutex       m_udpSendMutex;
};

}

#endif
