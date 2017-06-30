///////////////////////////////////////////////////////////////////////////////
//
// IPv4AddressTest.h
//
// Unit tests for IPv4Address class.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __IPv4AddressTest_h_
#define __IPv4AddressTest_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <unistd.h>
#include <string.h>

#include <cppunit/TestFixture.h>
#include <cppunit/Test.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <iostream>

#include <3waytypes.h>
#include <system/Trace.h>
#include <comms/IPv4Address.h>

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class IPv4AddressTest : public CppUnit::TestFixture
{
public:
    static CppUnit::Test *GetSuite()
    {
        CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite( "IPv4AddressTest" );
        suiteOfTests->addTest( new CppUnit::TestCaller<IPv4AddressTest>(
                                   "Test1",
                                   &IPv4AddressTest::Test1 ) );
        return suiteOfTests;
    }

    void setUp()
    {
        cout << endl << endl
             << "*****************" << endl
             << "IPv4Address tests" << endl
             << "*****************" << endl << endl;

        cout << "setUp(): Construct IPv4AddressTest" << endl;
    }

    void tearDown()
    {
        cout << "tearDown(): Delete IPv4AddressTest" << endl;
    }

    void Test1()
    {
        IPv4Address ipAddress;
        ipAddress.Set("10.1.2.3");

        u32 ipAddressU32 = ipAddress.Get();
        u32 calcIpAddressU32;
        u8* pCalcIpAddress = (u8*)&calcIpAddressU32;

        // Calculate the IP address we expect - should be NBO.
        pCalcIpAddress[0] = 10;
        pCalcIpAddress[1] = 1;
        pCalcIpAddress[2] = 2;
        pCalcIpAddress[3] = 3;

        cout.flags( ios_base::right | ios_base::showbase );
        cout.width(10);
        cout << "10.1.2.3 as int = " << hex << ipAddressU32 << endl;
        cout << "10.1.2.3 calculated as int = " << hex << calcIpAddressU32 << endl;
        CPPUNIT_ASSERT_MESSAGE("Check Get() u32", ipAddressU32 == calcIpAddressU32);

        cout << "ToString(): " << ipAddress.ToString() << endl;
        CPPUNIT_ASSERT_MESSAGE("Check ToString()", strcmp(ipAddress.ToString(), "10.1.2.3") == 0);

        ipAddress.Set(calcIpAddressU32);
        CPPUNIT_ASSERT_MESSAGE("Check Set(u32)", strcmp(ipAddress.ToString(), "10.1.2.3") == 0);

        u8 digit0, digit1, digit2, digit3;
        ipAddress.GetDigits(digit0, digit1, digit2, digit3);
        CPPUNIT_ASSERT_MESSAGE("Check GetDigits()", (digit0 == 10) && (digit1 == 1) && (digit2 == 2) && (digit3 == 3));

        ipAddress.SetDigits(10, 1, 2, 3);
        cout << "ToString(): " << ipAddress.ToString() << endl;
        CPPUNIT_ASSERT_MESSAGE("Check SetDigits()", strcmp(ipAddress.ToString(), "10.1.2.3") == 0);

        ipAddress.GetDigits(digit0, digit1, digit2, digit3);
        CPPUNIT_ASSERT_MESSAGE("Check GetDigits()", (digit0 == 10) && (digit1 == 1) && (digit2 == 2) && (digit3 == 3));

        // Check operators.
        cout << "Checking operators..." << endl;
        IPv4Address ipAddressLow;
        ipAddressLow.Set("0.0.0.1");
        IPv4Address ipAddressHigh;
        ipAddressHigh.Set("255.255.255.254");
        ipAddress.Set("0.0.0.1");
        CPPUNIT_ASSERT_MESSAGE("Check ==", ipAddress == ipAddressLow);
        CPPUNIT_ASSERT_MESSAGE("Check !=", ipAddress != ipAddressHigh);
        CPPUNIT_ASSERT_MESSAGE("Check <", ipAddress < ipAddressHigh);
        CPPUNIT_ASSERT_MESSAGE("Check >", ipAddressHigh > ipAddress);

        fflush(stdout);
    }

private:
};

#endif
