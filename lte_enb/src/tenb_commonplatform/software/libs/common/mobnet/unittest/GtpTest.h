///////////////////////////////////////////////////////////////////////////////
//
// GtpTest.h
//
// Unit tests for GTP encode/decode.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __GtpTest_h_
#define __GtpTest_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include <cppunit/TestCase.h>

#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "mobnet/Gtp.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Test Cases
///////////////////////////////////////////////////////////////////////////////

class GtpTest : public CppUnit::TestCase
{
public:
    void runTest()
    {
        cout << endl << endl
             << "*********" << endl
             << "GTP tests" << endl
             << "*********" << endl << endl;

        TRACE_MSG("Testing decode of GTP Error Indication");

        u8 errorIndBytes[] = {/* 0x32, 0x1a, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, */ 0x10, 0x12, 0x34, 0x56, 0x78, 0x85, 0x00, 0x04, 1, 2, 3, 4};

        SimplePDU errorIndPdu;
        errorIndPdu.SetPacket(errorIndBytes, sizeof(errorIndBytes));
        u32 teIdDataI;
        IPv4Address gsnAddress;
        Gtp::DecodeErrorInd(errorIndPdu, teIdDataI, gsnAddress);

        CPPUNIT_ASSERT_MESSAGE("Checking TEID decoded", teIdDataI == 0x12345678);
        CPPUNIT_ASSERT_MESSAGE("Checking GSN address decoded", strcmp(gsnAddress.ToString(), "1.2.3.4") == 0);

        fflush(stdout);
    }

protected:

private:

};

#endif
