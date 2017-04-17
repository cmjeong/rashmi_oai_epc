///////////////////////////////////////////////////////////////////////////////
//
// UdpMessengerTest.h
//
// Unit tests for UdpMessenger class.
//
// Copyright radisys Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __UdpMessengerTest_h_
#define __UdpMessengerTest_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <ctype.h>
#include <cppunit/TestCase.h>

#include <3waytypes.h>
#include <system/Trace.h>
#include <system/Exception.h>
#include <system/Serialisable.h>
#include <messaging/transport/UdpMessenger.h>

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class TestMessage : public Serialisable
{
public:
    TestMessage() :
        m_someData(0)
    {
    }

    TestMessage(u8 someData) :
        m_someData(someData)
    {
    }

    virtual ~TestMessage()
    {
    }

    u32 GetSerialisationId() const
    {
        return 0x12345678;
    }

    s32 Serialise(u8* data, u32 dataMaxBytes) const
    {
        *data = m_someData;
        return 1;
    }

    bool DeSerialise(const u8* data, u32 dataLen)
    {
        m_someData = data[0];
        return true;
    }

    string ToString() const
    {
        string str;

        if(isprint((char)m_someData))
        {
            str = (char)m_someData;
        }
        else
        {
            str = '.';
        }

        return str;
    }

private:
    u8 m_someData;
};

class UdpMessengerTest : public CppUnit::TestCase, public MessageRxRawInterface
{
public:

    void ReceiveMessage(MessagingEntity fromEntity, MessagingEntity toEntity, u32 serialisationId, const u8* serialisedData, u32 serialisedDataLen)
    {
        TRACE_PRINTF("Received message, from =%d, to=%d, serialisationId=0x%08" PRIX32 ", serialisedDataLen=%" PRIu32 ":",
                      fromEntity, toEntity, serialisationId, serialisedDataLen);

        TestMessage testMessage;
        testMessage.DeSerialise(serialisedData, serialisedDataLen);
        TRACE("Received message", testMessage.ToString().c_str());
    }

    void runTest()
    {
        cout << endl << endl
             << "******************" << endl
             << "UdpMessenger tests" << endl
             << "******************" << endl << endl;

        //
        // Normal cases.
        //
        TRACE_MSG("Create messengers between ports 3456 and 4567 on localhost");
        IPv4Address loopback = IPv4Address(127,0,0,1);
        UdpMessenger udpMessenger1(3456, loopback, 4567);
        UdpMessenger udpMessenger2(4567, loopback, 3456);

        udpMessenger1.StartReceiving();
        udpMessenger2.StartReceiving();

        TestMessage testMessage1('A');
        TRACE("Send message 1->2", testMessage1.ToString().c_str());
        bool sendOK = udpMessenger1.SendMessage(testMessage1, ENTITY_POSTOFFICE, ENTITY_POSTOFFICE);
        TRACE("Send result", sendOK);
        CPPUNIT_ASSERT_MESSAGE("Check packet sent OK", sendOK == true);

        sleep(1);

        TestMessage testMessage2('B');
        TRACE("Send message 1->2", testMessage2.ToString().c_str());
        sendOK = udpMessenger2.SendMessage(testMessage2, ENTITY_POSTOFFICE, ENTITY_POSTOFFICE);
        TRACE("Send result", sendOK);
        CPPUNIT_ASSERT_MESSAGE("Check packet sent OK", sendOK == true);

        // Wait for messages to be received.
        sleep(1);

        //
        // Error cases.
        //

        fflush(stdout);
    }

private:

};

#endif
