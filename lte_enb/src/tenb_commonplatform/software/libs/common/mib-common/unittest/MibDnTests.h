///////////////////////////////////////////////////////////////////////////////
//
// MibDnTests.h
//
// Unit tests for MIB DN validators.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MibDnTests_h_
#define __MibDnTests_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include <cppunit/TestCase.h>

#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MibDN.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Test Cases
///////////////////////////////////////////////////////////////////////////////

class MibDnTests : public CppUnit::TestCase
{
public:
    void runTest()
    {
        cout << endl << endl
             << "***************" << endl
             << "MibDN tests" << endl
             << "***************" << endl << endl;

        TRACE_MSG("Testing MibDN");

        MibDN fap0 = MibDN::GenerateMibDN("FAP.0");
        cout << fap0.ToString();
        CPPUNIT_ASSERT_MESSAGE("Checking MibDN::GenerateMibDN(string) #1", fap0.ToString() == "FAP.0");

        MibDN fap0Commissioning = MibDN::GenerateMibDN("FAP.0.COMMISSIONING.0");
        cout << fap0Commissioning.ToString();
        CPPUNIT_ASSERT_MESSAGE("Checking MibDN::GenerateMibDN(string) #2", fap0Commissioning.ToString() == "FAP.0.COMMISSIONING.0");

        MibDN fap0InterRatNeighbours = MibDN::GenerateMibDN("FAP.0.INTER_RAT_NEIGHBOURS.31");
        cout << fap0InterRatNeighbours.ToString();
        CPPUNIT_ASSERT_MESSAGE("Checking MibDN::GenerateMibDN(string) #3", fap0InterRatNeighbours.ToString() == "FAP.0.INTER_RAT_NEIGHBOURS.31");

        fflush(stdout);
    }

protected:

private:

};

#endif
