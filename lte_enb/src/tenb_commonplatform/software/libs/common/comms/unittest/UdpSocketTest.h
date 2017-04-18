///////////////////////////////////////////////////////////////////////////////
//
// UdpSocketTest.h
//
// Unit tests for UdpSocket class.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __UdpSocketTest_h_
#define __UdpSocketTest_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <ctype.h>
#include <cppunit/TestCase.h>

#include <3waytypes.h>
#include <system/Trace.h>
#include <system/Exception.h>
#include <comms/UdpSocket.h>

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class UdpSocketTest : public CppUnit::TestCase, public UdpRxInterface
{
public:
    void HandleUdpRx(s32 fd)
    {
        u8 packet[2048];
        rxdPacketLen = recv(fd, packet, sizeof(packet), 0);
        rxdPacketCount++;
        cout << "Received UDP packet on FD=" << fd << ", packet length=" << rxdPacketLen << ": ";
        if(rxdPacketLen > 0)
        {
            s32 i = 0;
            while(i < rxdPacketLen)
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
    }
    
    void runTest()
    {
        cout << endl << endl
             << "***************" << endl
             << "UdpSocket tests" << endl
             << "***************" << endl << endl;
        
        //
        // Normal cases.
        //

        rxdPacketLen = 0;
        rxdPacketCount = 0;
        
        TRACE_MSG("Create UDP sockets between ports 1234 and 2345 on localhost");
        UdpSocket udpSocket1(1234, "127.0.0.1", 2345, *this);
        UdpSocket udpSocket2(2345, "127.0.0.1", 1234, *this);
        udpSocket1.StartReceiving();
        udpSocket2.StartReceiving();

        TRACE_MSG("Send something 1->2");
        u8 data[] = {'l', 'i', 'v', 'e', 'r', 'p', 'o', 'o', 'l', ' ', 'r', 'u', 'l', 'e'};
        s32 sendResult = udpSocket1.UdpSend(data, sizeof(data));
        TRACE("Send result", sendResult);
        CPPUNIT_ASSERT_MESSAGE("Check packet sent OK", sendResult == sizeof(data));
        
        sleep(1);
        
        TRACE_MSG("Send something 2->1");
        u8 data2[] = {'o', 'k'};
        sendResult = udpSocket2.UdpSend(data2, sizeof(data2));
        TRACE("Send result", sendResult);
        CPPUNIT_ASSERT_MESSAGE("Check packet sent OK", sendResult == sizeof(data2));
        
        // Wait for messages to be received.
        sleep(1);
        
        // Check rxd messages.
        TRACE_PRINTF("Check received packet, len=%i, count=%i", rxdPacketLen, rxdPacketCount);
        CPPUNIT_ASSERT_MESSAGE("Check packet received length", rxdPacketLen == sizeof(data2));
        CPPUNIT_ASSERT_MESSAGE("Check packet received count", rxdPacketCount == 2);

        // Create another 'send only' socket.
        UdpSocket udpSocket3("127.0.0.1", 1234);

        TRACE_MSG("Send something 3->1");
        u8 data3[] = {'i', 'n', 't', 'e', 'r', 'l', 'o', 'p', 'e', 'r'};
        sendResult = udpSocket3.UdpSend(data3, sizeof(data3));
        TRACE("Send result", sendResult);
        CPPUNIT_ASSERT_MESSAGE("Check packet sent OK", sendResult == sizeof(data3));
        
        // Wait for messages to be received.
        sleep(1);
        
        // Check rxd message.
        TRACE_PRINTF("Check received packet, len=%i, count=%i", rxdPacketLen, rxdPacketCount);
        CPPUNIT_ASSERT_MESSAGE("Check packet received length", rxdPacketLen == sizeof(data3));
        CPPUNIT_ASSERT_MESSAGE("Check packet received count", rxdPacketCount == 3);

        // Stop threads (this would happen in the UdpSocket destructor anyway...).
        udpSocket1.StopReceiving();
        udpSocket2.StopReceiving();
        
        //
        // Error cases.
        //
        
        fflush(stdout);
    }

private:
    int rxdPacketLen;
    int rxdPacketCount;
};

#endif
