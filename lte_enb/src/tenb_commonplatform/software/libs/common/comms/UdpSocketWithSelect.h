///////////////////////////////////////////////////////////////////////////////
//
// UdpSocketWithSelect.h
//
// Send and receive UDP packets.  Use Selector to implement the select() to
// reduce number of threads compared to standard UdpSocket implementation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __UdpSocketWithSelect_h_
#define __UdpSocketWithSelect_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <netinet/ip.h>
#include <unistd.h>

#include <boost/shared_ptr.hpp>
#include <system/SelectorInterfaces.h>
#include <comms/IPv4Address.h>
#include <comms/UdpReceiveThread.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

using namespace boost;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

/**
 * Class for sending and receiving UDP packets.
 */
class UdpSocketWithSelect : public SelectorCallBackInterface
{
public:

    /**
     * Constructor for transmit and receive.
     *
     * \param selector          Interface for registering our FD.
     * \param udpRxInterface    Interface to callback to with received UDP packets.
     * \param localPort         Port to listen on.
     * \param remoteIpAddress   IP address to send packets to.
     * \param remotePort        Port to send packets to.
     */
    UdpSocketWithSelect(SelectorRegisterInterface& selector,
                        UdpRxInterface& udpRxInterface,
                        u16 localPort,
                        const IPv4Address& remoteIpAddress,
                        u16 remotePort);

    virtual ~UdpSocketWithSelect();

    /**
     * Implement SelectorCallBackInterface.
     */
    virtual void SelectCallBack();

    /**
     * Start/stop the UDP receive thread.
     */
    void StartReceiving();
    void StopReceiving();

    // TODO: this is bad.
    int GetFd() const { return m_fd; };

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
     * Get as string for debug.
     */
    virtual std::string ToString() const;

private:
    /**
     * Set the underlying file descriptor to close-on-exec.
     */
    void CloseOnExec();

    // Initialise the transmit section.
    void InitialiseTransmit();

    // Selector for registering select callbacks.
    SelectorRegisterInterface&  m_selector;

    // Callback on received UDP packets.
    UdpRxInterface&             m_udpRxInterface;

    IPv4Address         m_localIpAddress;
    u16                 m_localPort;

    // Remote IP/port for sending.
    IPv4Address         m_remoteIpAddress;
    u16                 m_remotePort;

    // File descriptor - can be just transmit, receive or both depending on constructor called.
    int                 m_fd;

    // Transmit sockaddr.
    struct sockaddr_in  m_txSockAddr;

};

}

#endif
