///////////////////////////////////////////////////////////////////////////////
//
// UdpReceiveThread.h
//
// Thread for receiving UDP packets.  Actual reading from the socket is
// done by callback function (class implementing UdpRxInterface).
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __UdpReceiveThread_h_
#define __UdpReceiveThread_h_

///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////

#include <3waytypes.h>

#include <system/Thread.h>

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

/**
 * Callback for received packets.
 */
class UdpRxInterface
{
public:
    /**
     * Handle a packet received from a UDP socket.
     * To read the data, use:
     *   packetLen = recvfrom(fd, packet, sizeof(packet), 0, NULL, NULL);
     *
     * \param fd File descriptor to read from
     */
    virtual void HandleUdpRx(s32 fd) = 0;

    /**
     * Make destructor virtual to remove compiler warnings.
     */
    virtual ~UdpRxInterface () {}
};

/**
 * UdpSocket owns the file descriptor but this class needs it for receiving on the same socket.
 * Need to do via interface to avoid circular dependencies.
 */
class GetFdInterface
{
public:
    /**
     * Get file descriptor.
     */
    virtual int GetFd() = 0;

    /**
     * Make destructor virtual to remove compiler warnings.
     */
    virtual ~GetFdInterface () {}
};

/**
 * Thread for listening for UDP packets.
 */
class UdpReceiveThread : public Thread
{
public:
    /**
     * Constructor.
     *
     * \param localPort      Port to listen on
     * \param udpRxInterface Callback for received packets
     */
    UdpReceiveThread(GetFdInterface& associatedSocket, UdpRxInterface& udpRxInterface);

    /**
     * Override Thread method.
     * Listen to UDP socket, call udpRxInterface for each packet.
     */
    virtual u32 ThreadProcedure();

    /**
     * After calling StartThread() you can poll to see if the thread is
     * ready to receive packets i.e. has bound to socket.
     */
    bool IsReadyToReceive() const { return m_readyToReceive; };

    void StopThread();

private:
    GetFdInterface&  m_associatedSocket;
    UdpRxInterface& m_udpRxInterface;
    bool        m_readyToReceive;
    int         m_stopPipe[2];
};

}

#endif
