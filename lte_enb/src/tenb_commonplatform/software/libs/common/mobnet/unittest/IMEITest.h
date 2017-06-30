///////////////////////////////////////////////////////////////////////////////
//
// IMEITest.h
//
// Unit tests for IMEI class.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __IMEITest_h_
#define __IMEITest_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include <cppunit/TestCase.h>

#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "mobnet/IMEI.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Test Cases
///////////////////////////////////////////////////////////////////////////////

class IMEITest : public CppUnit::TestCase
{
public:
    void runTest()
    {
        cout << endl << endl
             << "**********" << endl
             << "IMEI tests" << endl
             << "**********" << endl << endl;

        u8 imeiArray[] = {0,1,2,3,4,5,6,7,8,9,0,1,2,3};
        threeway::IMEI imei(imeiArray);

        TRACE("IMEI", imei.ToString());
        CPPUNIT_ASSERT_MESSAGE("Checking IMEI ToString()", imei.ToString() == "01234567890123");

        u8 expectedPackedImei[] = {0x01, 0x23, 0x45, 0x67, 0x89, 0x01, 0x23, 0x00};
        u8 packedImei[8];
        imei.GetImeiPacked(packedImei, sizeof(packedImei));
        CPPUNIT_ASSERT_MESSAGE("Checking packed IMEI", memcmp(expectedPackedImei, packedImei, sizeof(packedImei)) == 0);

        u8 newPackedImei[] = { 0x76, 0x82, 0x19, 0x44, 0x37, 0x14, 0x23 };
        imei.SetImeiPacked(newPackedImei);
        TRACE("IMEI", imei.ToString());
        CPPUNIT_ASSERT_MESSAGE("Checking IMEI ToString()", imei.ToString() == "76821944371423");

        threeway::IMEI imeiEqual("76821944371423");
        CPPUNIT_ASSERT_MESSAGE("Compare equal IMEIs", imei == imeiEqual);
        CPPUNIT_ASSERT_MESSAGE("Compare equal IMEIs", !(imei != imeiEqual));

        threeway::IMEI imeiNotEqual("76821944371421");
        CPPUNIT_ASSERT_MESSAGE("Compare equal IMEIs", imei != imeiNotEqual);
        CPPUNIT_ASSERT_MESSAGE("Compare equal IMEIs", !(imei == imeiNotEqual));

        fflush(stdout);
    }

protected:

private:

};

#endif
