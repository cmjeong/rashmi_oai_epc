///////////////////////////////////////////////////////////////////////////////
//
// HexStringTest.h
//
// TODO: Describe unit tests...
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __HexStringTest_h_
#define __HexStringTest_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include <cppunit/TestCase.h>

#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "system/HexString.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Test Cases
///////////////////////////////////////////////////////////////////////////////

class HexStringTest : public CppUnit::TestCase
{
public:
    void runTest()
    {
        cout << endl << endl
             << "***************" << endl
             << "HexString tests" << endl
             << "***************" << endl << endl;

        HexString hs1("1AB");
        HexString hs2("1AB");
        HexString hs3("1ABC8");
        HexString hs4("2");
        HexString hs5;

        TRACE_MSG("Checking (in)equality operators");

        CPPUNIT_ASSERT(hs1 == hs2);
        CPPUNIT_ASSERT(!(hs1 != hs2));

        CPPUNIT_ASSERT(hs1 != hs3);
        CPPUNIT_ASSERT(!(hs1 == hs3));

        CPPUNIT_ASSERT(hs1 != hs4);
        CPPUNIT_ASSERT(!(hs1 == hs4));

        CPPUNIT_ASSERT(hs1 != hs5);
        CPPUNIT_ASSERT(!(hs1 == hs5));

        TRACE_MSG("Checking < operator");

        CPPUNIT_ASSERT(!(hs1 < hs2));
        CPPUNIT_ASSERT(hs1 < hs3);
        CPPUNIT_ASSERT(hs1 < hs4);
        CPPUNIT_ASSERT(!(hs1 < hs5));

        fflush(stdout);
    }

protected:

private:

};

#endif
