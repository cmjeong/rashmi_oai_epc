///////////////////////////////////////////////////////////////////////////////
//
// UdpSocketUsingSelectorTest.h
//
// Unit tests for UdpSocket class.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __UdpSocketUsingSelectorTest_h_
#define __UdpSocketUsingSelectorTest_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <ctype.h>
#include <cppunit/TestCase.h>

#include <system/Trace.h>
#include <system/Exception.h>
#include <system/Selector.h>
#include <comms/UdpSocketWithSelect.h>

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class UdpSocketUsingSelectorTest : public CppUnit::TestCase, public UdpRxInterface
{
public:
    void HandleUdpRx(s32 fd)
    {
        u8 packet[2048];
        int rxdPacketLen = recv(fd, packet, sizeof(packet), 0);
        rxdPacketLengths.push_back(rxdPacketLen);
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
             << "****************************" << endl
             << "UdpSocketUsingSelector tests" << endl
             << "****************************" << endl << endl;
        
        //
        // Normal cases.
        //
        Selector selector;

        TRACE_MSG("Create UDP sockets between ports 1234 and 2345 on localhost");
        UdpSocketWithSelect udpSocket1(selector,
                                       *this,
                                       1234, "127.0.0.1", 2345);
        UdpSocketWithSelect udpSocket2(selector,
                                       *this,
                                       2345, "127.0.0.1", 1234);
        udpSocket1.StartReceiving();
        udpSocket2.StartReceiving();

        TRACE_MSG("Send something 1->2");
        u8 data[] = {'l', 'i', 'v', 'e', 'r', 'p', 'o', 'o', 'l', ' ', 'r', 'u', 'l', 'e'};
        s32 sendResult = udpSocket1.UdpSend(data, sizeof(data));
        TRACE("Send result", sendResult);
        CPPUNIT_ASSERT_MESSAGE("Check packet sent OK", sendResult == sizeof(data));
        
        TRACE_MSG("Send something 2->1");
        u8 data2[] = {'o', 'k'};
        sendResult = udpSocket2.UdpSend(data2, sizeof(data2));
        TRACE("Send result", sendResult);
        CPPUNIT_ASSERT_MESSAGE("Check packet sent OK", sendResult == sizeof(data2));
        
        // Kick to receive messages.
        selector.DoSelect(1000);
        
        // Check rxd messages.
        TRACE_PRINTF("Check received packet 1, len=%i", rxdPacketLengths.at(0));
        CPPUNIT_ASSERT(rxdPacketLengths.at(0) == sizeof(data2));
        TRACE_PRINTF("Check received packet 2, len=%i", rxdPacketLengths.at(1));
        CPPUNIT_ASSERT(rxdPacketLengths.at(1) == sizeof(data));
        TRACE_PRINTF("Check received packet count,%i", rxdPacketLengths.size());
        CPPUNIT_ASSERT(rxdPacketLengths.size() == 2);

        // Stop receiving.
        udpSocket1.StopReceiving();
        udpSocket2.StopReceiving();
        
        //
        // Error cases.
        //
        
        fflush(stdout);
    }

private:
    std::vector<int> rxdPacketLengths;
};

#endif
