///////////////////////////////////////////////////////////////////////////////
//
// RegexTest.h
//
// Unit tests for Regex class.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __RegexTest_h_
#define __RegexTest_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <ctype.h>
#include <unistd.h>

#include <cppunit/TestCase.h>

#include <3waytypes.h>
#include <system/Trace.h>
#include <system/Regex.h>

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////


class RegexTest : public CppUnit::TestCase
{
public:

    void runTest()
    {
        cout << endl << endl
             << "*****************" << endl
             << "Regex tests" << endl
             << "*****************" << endl << endl;

        //
        // Normal cases.
        //
        threeway::Regex rdnRegex("[a-zA-Z_]+[.][0-9]+[.]?");

        TRACE_MSG("Validation of regex: [a-zA-Z_]+[.][0-9]+[.]?")
        u16 matchedLength = 0;

        fflush(stdout);
    }

private:
    TimerHandle m_expiredTimer;
};

#endif
