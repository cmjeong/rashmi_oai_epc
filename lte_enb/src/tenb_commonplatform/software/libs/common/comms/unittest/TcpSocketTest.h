///////////////////////////////////////////////////////////////////////////////
//
// TcpSocketTest.h
//
// Unit tests for TcpSocket class.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __TcpSocketTest_h_
#define __TcpSocketTest_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <ctype.h>
#include <cppunit/TestCase.h>

#include <3waytypes.h>
#include <system/Trace.h>
#include <system/Exception.h>
#include <comms/TcpSocket.h>

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////
class TcpClientSocketListener : public TcpRxInterface
{
public:
    s32 HandleTcpRx(s32 fd)
    {
        u8 packet[2048];
        int packetLen = recv(fd, packet, sizeof(packet), 0);
        cout << "Client received TCP packet on FD=" << fd << ", packet length=" << packetLen << ": ";
        if(packetLen > 0)
        {
            s32 i = 0;
            while(i < packetLen)
            {
                if(isprint(packet[i]))
                {
                    cout << (char)packet[i];
                }
                else
                {
                    cout << '.';
                }
                i++;
            }
        }
        cout << endl;
        return (packetLen > 0 ? 0 : -1);
    }

    void HandleTcpDisconnect(s32 fd)
    {
        cout << "TCP disconnect on FD=" << fd << endl;
    }
};

class TcpSocketTest : public CppUnit::TestCase, public TcpServerRxInterface
    {
public:
    s32 HandleTcpRx(s32 fd)
    {
        u8 packet[2048];
        int packetLen = recv(fd, packet, sizeof(packet), 0);
        cout << "Server received TCP packet on FD=" << fd << ", packet length=" << packetLen << ": ";
        if(packetLen > 0)
        {
            s32 i = 0;
            while(i < packetLen)
            {
                if(isprint(packet[i]))
                {
                    cout << (char)packet[i];
                }
                else
                {
                cout << '.';
                }
                i++;
            }
        }
        cout << endl;
        return (packetLen > 0 ? 0 : -1);
    }

    void HandleTcpDisconnect(s32 fd)
    {
        cout << "TCP disconnect on FD=" << fd << endl;
    }

    void HandleNewTcpSock(s32 fd)
    {
        m_sendFd = fd;
    }

    void runTest()
    {
        cout << endl << endl
             << "***************" << endl
             << "TcpSocket tests" << endl
             << "***************" << endl << endl;
        //
        // Normal cases.
        //
        //Start server
        TRACE_MSG("Create server socket on 18100 and wait for connections");

        u16 testPort = 18100;
        std::string localHost = "127.0.0.1";
        TcpSocket tcpServerSocket(testPort, this);

        tcpServerSocket.StartReceiving();
        // TODO: Fix these tests. Currently the server socket can start listening and then the client socket sends repeatedly before
        // server socket accepts the client connection. The server socket is then closed down before anything has been pulled out of
        // the socket. We need to be able to queue up data and ensure that the socket has connected. This requires more invesigation
        // but it is also worthwhile considering that in the future the Boost Asio library might be a better way forward for our needs.
        sleep(1);
        // Create Client
        TcpClientSocketListener clientSocketListener;
        // Connect TCP client to local ssh server.
        TRACE_MSG("Create socket and try to connect to localhost:18100");
        TcpSocket tcpClientSocket(&clientSocketListener);

        u32 timeoutSeconds = 5;
        bool connected = tcpClientSocket.Connect(localHost.c_str(), testPort, timeoutSeconds);
        TRACE_MSG("Connect has returned");

        cout << "Check connected" << endl;
        CPPUNIT_ASSERT_MESSAGE("Check connected", connected == true);

        if(connected)
        {
            cout << "Client : " << tcpClientSocket.ToString() << endl;

            tcpClientSocket.StartReceiving();
            sleep(1);
            cout << "Send something" << endl;
            u8 data[] = {'e', 'c', 'h', 'o', ' ', 'h', 'i', 10};
            s32 sendResult;

            //send the same message 10 times
            for (int i = 0; i < 10; i++)
            {
                sendResult = tcpClientSocket.TcpSend(data, sizeof(data));
                TRACE_PRINTF("sendResult: %"PRId32" %s", sendResult, sendResult < 0 ? strerror(errno) : "OK" );
                CPPUNIT_ASSERT_MESSAGE("Check packet sent OK", sendResult > 0);
            }


            //and now one back
            for (int i = 0; i < 10; i++)
            {
                sendResult = tcpServerSocket.TcpSend(data, sizeof(data), m_sendFd);
                TRACE_PRINTF("sendResult: %"PRId32" %s", sendResult, sendResult < 0 ? strerror(errno) : "OK" );
                CPPUNIT_ASSERT_MESSAGE("Check packet sent OK", sendResult > 0);
            }

            tcpClientSocket.StopReceiving();
        }

        sleep(1);
        tcpServerSocket.StopReceiving();

        //
        // Error cases.
        //

        // Try connecting to a non-existent host.
        TRACE_MSG("Create socket for 192.168.100.100:22 and try to connect");
        TcpSocket tcpSocket2(this);
        connected = tcpSocket2.Connect("192.168.100.100", 22, 3);
        TRACE_MSG("Connect has returned");

        cout << "Check not connected" << endl;
        CPPUNIT_ASSERT_MESSAGE("Check not connected", connected == false);

        fflush(stdout);
    }

private:
    int m_sendFd;
};

#endif
