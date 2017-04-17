///////////////////////////////////////////////////////////////////////////////
//
// SoftwareReleaseTest.h
//
// Test our software release conversion function.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __SoftwareReleaseTest_h_
#define __SoftwareReleaseTest_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include <cppunit/TestCase.h>

#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "system/SoftwareRelease.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Test Cases
///////////////////////////////////////////////////////////////////////////////

class SoftwareReleaseTest : public CppUnit::TestCase
{
public:
    void runTest()
    {
        cout << endl << endl
             << "*********************" << endl
             << "SoftwareRelease tests" << endl
             << "*********************" << endl << endl;

        u32 swRel1 = 0x01020304;
        CPPUNIT_ASSERT_MESSAGE("Check 4 digit release", SoftwareReleaseToString(swRel1, 4) == "SW1.2.3.4");
        CPPUNIT_ASSERT_MESSAGE("Check 3 digit release", SoftwareReleaseToString(swRel1, 3) == "SW1.2.3");
        CPPUNIT_ASSERT_MESSAGE("Check 2 digit release", SoftwareReleaseToString(swRel1, 2) == "SW1.2");
        CPPUNIT_ASSERT_MESSAGE("Check 1 digit release", SoftwareReleaseToString(swRel1, 1) == "SW1");

        fflush(stdout);
    }

protected:

private:

};

#endif
