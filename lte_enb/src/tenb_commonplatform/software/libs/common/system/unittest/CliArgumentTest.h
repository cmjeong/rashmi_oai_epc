///////////////////////////////////////////////////////////////////////////////
//
// CliArgumentTest.h
//
// Unit tests for CliArgument class.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CliArgumentTest_h_
#define __CliArgumentTest_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include <cppunit/TestCase.h>

#include <system/Trace.h>
#include <system/CliArgument.h>

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Test Cases
///////////////////////////////////////////////////////////////////////////////

class CliArgumentTest : public CppUnit::TestCase
{
public:
    void runTest()
    {
        cout << endl << endl
             << "*****************" << endl
             << "CliArgument tests" << endl
             << "*****************" << endl << endl;

        TRACE_MSG("Constructing instance of CliArgument and testing a bunch of different values...");

        CliArgument cliArgument("33");
        CPPUNIT_ASSERT(cliArgument.IsBool() == false);
        CPPUNIT_ASSERT(cliArgument.GetBool() == false);
        CPPUNIT_ASSERT(cliArgument.IsU32() == true);
        CPPUNIT_ASSERT(cliArgument.GetU32() == 33);
        CPPUNIT_ASSERT(cliArgument.IsS32() == true);
        CPPUNIT_ASSERT(cliArgument.GetS32() == 33);

        cliArgument.assign("0x12345678");
        CPPUNIT_ASSERT(cliArgument.IsU32() == true);
        CPPUNIT_ASSERT(cliArgument.GetU32() == 0x12345678);

        cliArgument.assign("-123");
        CPPUNIT_ASSERT(cliArgument.IsU32() == false);
        CPPUNIT_ASSERT(cliArgument.IsBool() == false);
        CPPUNIT_ASSERT(cliArgument.IsS32() == true);
        CPPUNIT_ASSERT(cliArgument.GetS32() == -123);

        cliArgument.assign("trUE");
        CPPUNIT_ASSERT(cliArgument.IsBool() == true);
        CPPUNIT_ASSERT(cliArgument.IsU32() == false);
        CPPUNIT_ASSERT(cliArgument.IsS32() == false);
        CPPUNIT_ASSERT(cliArgument.GetBool() == true);

        cliArgument.assign("1");
        CPPUNIT_ASSERT(cliArgument.IsBool() == true);
        CPPUNIT_ASSERT(cliArgument.IsU32() == true);
        CPPUNIT_ASSERT(cliArgument.IsS32() == true);
        CPPUNIT_ASSERT(cliArgument.GetBool() == true);
        CPPUNIT_ASSERT(cliArgument.GetU32() == 1);
        CPPUNIT_ASSERT(cliArgument.GetS32() == 1);

        cliArgument.assign("oN");
        CPPUNIT_ASSERT(cliArgument.IsBool() == true);
        CPPUNIT_ASSERT(cliArgument.IsU32() == false);
        CPPUNIT_ASSERT(cliArgument.IsS32() == false);
        CPPUNIT_ASSERT(cliArgument.GetBool() == true);

        cliArgument.assign("False");
        CPPUNIT_ASSERT(cliArgument.IsBool() == true);
        CPPUNIT_ASSERT(cliArgument.IsU32() == false);
        CPPUNIT_ASSERT(cliArgument.IsS32() == false);
        CPPUNIT_ASSERT(cliArgument.GetBool() == false);

        cliArgument.assign("0");
        CPPUNIT_ASSERT(cliArgument.IsBool() == true);
        CPPUNIT_ASSERT(cliArgument.IsU32() == true);
        CPPUNIT_ASSERT(cliArgument.IsS32() == true);
        CPPUNIT_ASSERT(cliArgument.GetBool() == false);
        CPPUNIT_ASSERT(cliArgument.GetU32() == 0);
        CPPUNIT_ASSERT(cliArgument.GetS32() == 0);

        cliArgument.assign("OFF");
        CPPUNIT_ASSERT(cliArgument.IsBool() == true);
        CPPUNIT_ASSERT(cliArgument.IsU32() == false);
        CPPUNIT_ASSERT(cliArgument.IsS32() == false);
        CPPUNIT_ASSERT(cliArgument.GetBool() == false);

        cliArgument.assign("somecrap");
        CPPUNIT_ASSERT(cliArgument.IsBool() == false);
        CPPUNIT_ASSERT(cliArgument.IsU32() == false);
        CPPUNIT_ASSERT(cliArgument.IsS32() == false);

        fflush(stdout);
    }

protected:

private:

};

#endif
