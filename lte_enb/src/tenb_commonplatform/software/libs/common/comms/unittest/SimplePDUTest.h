///////////////////////////////////////////////////////////////////////////////
//
// SimplePDUTest.h
//
// Unit tests for ProtocolStack class.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __SimplePDUTest_h_
#define __SimplePDUTest_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cppunit/TestCase.h>

#include <3waytypes.h>
#include <system/Trace.h>
#include <system/Exception.h>
#include <comms/SimplePDU.h>

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class SimplePDUTest : public CppUnit::TestCase
{
public:
    void runTest()
    {
        cout << endl << endl
             << "***************" << endl
             << "SimplePdu tests" << endl
             << "***************" << endl << endl;

        SimplePDU pdu;

        //
        // Normal cases.
        //

        cout << "Check initial conditions" << endl;
        CPPUNIT_ASSERT_MESSAGE("Initial PDU empty", pdu.GetPacketLength() == 0);

        cout << "Add some data to the tail" << endl;
        u8 tailData[] = {1,'2','3','4',5};
        pdu.AddToTail(tailData, sizeof(tailData));
        cout << pdu.ToString() << endl;
        CPPUNIT_ASSERT_MESSAGE("PDU length after adding tail data", pdu.GetPacketLength() == 5);
        const u8* packet = pdu.GetPacket();
        CPPUNIT_ASSERT_MESSAGE("PDU data values", packet[0] == 1);
        CPPUNIT_ASSERT_MESSAGE("PDU data values", packet[4] == 5);

        cout << "Add some data to the head" << endl;
        u8 headData[] = {255,254,253};
        pdu.AddToHead(headData, sizeof(headData));
        CPPUNIT_ASSERT_MESSAGE("PDU length after adding head data", pdu.GetPacketLength() == 8);
        packet = pdu.GetPacket();
        CPPUNIT_ASSERT_MESSAGE("PDU data values", packet[0] == 255);
        CPPUNIT_ASSERT_MESSAGE("PDU data values", packet[2] == 253);
        CPPUNIT_ASSERT_MESSAGE("PDU data values", packet[3] == 1);
        CPPUNIT_ASSERT_MESSAGE("PDU data values", packet[7] == 5);

        cout << "Add some more data to the head" << endl;
        u8 moreHeadData[] = {11};
        pdu.AddToHead(moreHeadData, sizeof(moreHeadData));
        CPPUNIT_ASSERT_MESSAGE("PDU length after adding more head data", pdu.GetPacketLength() == 9);
        packet = pdu.GetPacket();
        CPPUNIT_ASSERT_MESSAGE("PDU data values", packet[0] == 11);
        CPPUNIT_ASSERT_MESSAGE("PDU data values", packet[1] == 255);
        CPPUNIT_ASSERT_MESSAGE("PDU data values", packet[8] == 5);

        cout << "Trim the head" << endl;
        pdu.TrimHead(8);
        CPPUNIT_ASSERT_MESSAGE("PDU length after trimming head", pdu.GetPacketLength() == 1);
        packet = pdu.GetPacket();
        CPPUNIT_ASSERT_MESSAGE("PDU data values", packet[0] == 5);

        cout << "Trim the tail back to an empty PDU" << endl;
        pdu.TrimTail(1);
        CPPUNIT_ASSERT_MESSAGE("PDU length after trimming tail", pdu.GetPacketLength() == 0);

        cout << "Pad the head" << endl;
        pdu.PadHead('H', 10);
        CPPUNIT_ASSERT_MESSAGE("PDU length after padding head", pdu.GetPacketLength() == 10);

        cout << "Pad the tail" << endl;
        pdu.PadTail('T', 5);
        CPPUNIT_ASSERT_MESSAGE("PDU length after padding tail", pdu.GetPacketLength() == 15);

        //
        // Error cases.
        // These used to throw exceptions but now assert instead so can't test them.
        // TODO: Look at adding assert test mode so we can test them...
        //

//        cout << "Try trimming an empty PDU" << endl;
//        pdu.Reset();
//        pdu.TrimTail(1);
//
//        cout << "Try adding too much data to the head of the PDU" << endl;
//        pdu.AddToHead(headData, PDU_DEFAULT_START_OFFSET*2);
//
//        cout << "Try adding too much data to the tail of the PDU" << endl;
//        pdu.AddToTail(tailData, PDU_MAX_LENGTH);

        fflush(stdout);
    }

private:
};

#endif
