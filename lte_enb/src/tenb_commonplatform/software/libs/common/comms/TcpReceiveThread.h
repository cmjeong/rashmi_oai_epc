///////////////////////////////////////////////////////////////////////////////
//
// TcpReceiveThread.h
//
// Receives TCP packets from specified port and calls a callback
// for each one.
//
// Copyright � 3 Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __TcpReceiveThread_h_
#define __TcpReceiveThread_h_

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
class TcpRxInterface
{
public:
    /**
     * Handle a packet received from a FIFO.
     * To read the data, use:
     *   packetLen = recv(fd, packet, sizeof(packet), 0);
     *
     * \param fd File descriptor to read from
     * \return 0 if more than 0 bytes were read; -1 otherwise
     */
    virtual s32 HandleTcpRx(s32 fd) = 0;

    /**
     * Handle a disconnection.
     *
     * \param fd File descriptor that disconnected.
     */
    virtual void HandleTcpDisconnect(s32 fd) = 0;

    /**
     * Make destructor virtual to remove compiler warnings.
     */
    virtual ~TcpRxInterface () {}
};

/**
 * Added Callback to set new created sockets.
 */
class TcpServerRxInterface : public TcpRxInterface
{
public:
    /**
     * Handle the new created socket.
     * \param fd File descriptor for the new socket
     */
    virtual void HandleNewTcpSock(s32 fd) = 0;
};

/**
 * Thread for listening for TCP packets.
 */

class TcpReceiveThread : public Thread
{
public:
    /**
     * Constructor.
     *
     * \param remoteSockFd   File descriptor for the connection
     * \param tcpRxInterface Callback for received packets
     * \param threadName Thread name
     */
    TcpReceiveThread(int remoteSockFd, const char * threadName);

    /**
     * Abstract method implemented by derived servers/clients threads.
     */
    virtual u32 ThreadProcedure() = 0;

    virtual void StopThread();

protected:
    int m_localSockFd;
    int m_stopPipe[2];
};

/**
 * Client Thread for listening for TCP packets.
 */
class TcpClientReceiveThread : public TcpReceiveThread
{
public:
    /**
     * Constructor.
     *
     * \param remoteSockFd   File descriptor for the connection
     * \param udpRxInterface Callback for received packets
     */
    TcpClientReceiveThread(int remoteSockFd, TcpRxInterface *tcpRxInterface);

    /**
     * Implement Thread method.
     * Listen to tcp socket, call tcpRxInterface for each packet.
     */
    virtual u32 ThreadProcedure();

protected:
    TcpRxInterface *m_tcpRxInterface;
};

/**
 * Server Thread for listening new connections and for TCP packets.
 */
class TcpServerReceiveThread : public TcpReceiveThread
{
public:
    /**
     * Constructor.
     *
     * \param remoteSockFd   File descriptor for the connection
     * \param udpRxInterface Callback for received packets
     */
    TcpServerReceiveThread(int remoteSockFd, TcpServerRxInterface *tcpRxInterface);

    /**
     * Implement Thread method.
     * Listen to tcp socket for data and new connections, call tcpRxInterface for each packet.
     */
    virtual u32 ThreadProcedure();
protected:
    TcpServerRxInterface *m_tcpRxInterface;

};

}

#endif
