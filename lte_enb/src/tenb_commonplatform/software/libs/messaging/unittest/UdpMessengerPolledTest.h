///////////////////////////////////////////////////////////////////////////////
//
// UdpMessengerPolledTest.h
//
// Unit tests for UdpMessenger class.
//
// Copyright radisys Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __UdpMessengerPolledTest_h_
#define __UdpMessengerPolledTest_h_

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
#include <system/SerialisableFactory.h>
#include <messaging/transport/UdpMessenger.h>

using namespace threeway;
using namespace std;
using namespace boost;

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class MessageFactory : public threeway::SerialisableFactory
{
public:
    MessageFactory() {};
    virtual ~MessageFactory() {};

    virtual shared_ptr<Serialisable> GetSerialisable(
                                                u32 serialisationId,
                                                const u8* serialisedData,
                                                u32 serialisedDataLen
                                                     )
    {
        shared_ptr<Serialisable> message;
        if(serialisationId == 0x12345678)
        {
            message.reset(new TestMessage);
            message->DeSerialise(serialisedData, serialisedDataLen);
        }

        return message;
    }
};

class UdpMessengerPolledTest : public CppUnit::TestCase
{
public:
    void runTest()
    {
        cout << endl << endl
             << "************************" << endl
             << "UdpMessengerPolled tests" << endl
             << "************************" << endl << endl;

        //
        // Normal cases.
        //
        TRACE_MSG("Create factory + polled mode messengers between ports 3456 and 4567 on localhost");
        shared_ptr<MessageFactory> messageFactory(new MessageFactory);

        IPv4Address loopback = IPv4Address(127,0,0,1);
        UdpMessenger udpMessenger1(3456, loopback, 4567);
        UdpMessenger udpMessenger2(4567, loopback, 3456);

        /*
        UdpMessenger udpMessenger1(3456, "127.0.0.1", 4567,
                                   messageFactory,
                                   0x12345678 );

        UdpMessenger udpMessenger2(4567, "127.0.0.1", 3456,
                                   messageFactory,
                                   0x87654321 );
        */

        udpMessenger1.StartReceiving();
        udpMessenger2.StartReceiving();

        TestMessage testMessage1('A');
        TRACE("Send message 1->2", testMessage1.ToString().c_str());
        bool sendOK = udpMessenger1.SendMessage(testMessage1, ENTITY_POSTOFFICE, ENTITY_POSTOFFICE);
        TRACE("Send result", sendOK);
        CPPUNIT_ASSERT_MESSAGE("Check packet sent OK", sendOK == true);

        MessagingEntity fromEntity;
        MessagingEntity toEntity;
        /* shared_ptr<Serialisable> rxdMessage1; */
        shared_ptr<SerialisedData> rxdMessage1;
        rxdMessage1 = udpMessenger2.BlockingReceiveMessage(1000, fromEntity, toEntity);

        if(rxdMessage1 != NULL)
        {
            TRACE("Received message, serialisationId", rxdMessage1->GetSerialisationId());
        }

        CPPUNIT_ASSERT_MESSAGE("Check message received OK 1", rxdMessage1 != NULL);
        CPPUNIT_ASSERT_MESSAGE("Check message tag is correct 1", fromEntity == ENTITY_POSTOFFICE);

        TestMessage testMessage2('B');
        TRACE("Send message 1->2", testMessage2.ToString().c_str());
        sendOK = udpMessenger2.SendMessage(testMessage2, ENTITY_POSTOFFICE, ENTITY_POSTOFFICE);
        TRACE("Send result", sendOK);
        CPPUNIT_ASSERT_MESSAGE("Check packet sent OK", sendOK == true);

        shared_ptr<SerialisedData> rxdMessage2;
        rxdMessage2 = udpMessenger1.BlockingReceiveMessage(1000, fromEntity, toEntity);
        if(rxdMessage2 != NULL)
        {
            TRACE("Received message, serialisationId", rxdMessage2->GetSerialisationId());
        }

        CPPUNIT_ASSERT_MESSAGE("Check message received OK 2", rxdMessage2 != NULL);
        CPPUNIT_ASSERT_MESSAGE("Check message tag is correct 2", fromEntity == ENTITY_POSTOFFICE);

        // Wait for a non-existent message.
        TRACE_MSG("Wait 1 sec for non-existent message ...");

        /* shared_ptr<Serialisable> rxdMessage3; */
        shared_ptr<SerialisedData> rxdMessage3;
        rxdMessage3 = udpMessenger1.BlockingReceiveMessage(1000, fromEntity, toEntity);

        TRACE_MSG("  ...returned");
        CPPUNIT_ASSERT_MESSAGE("Check no message received", rxdMessage3 == NULL);

        //
        // Error cases.
        //

        fflush(stdout);
    }

private:

};

#endif
