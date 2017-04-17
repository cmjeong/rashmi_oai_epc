///////////////////////////////////////////////////////////////////////////////
//
// MibAttributeDescriptorsTest.h
//
// Test common MIB attribute descriptor stuff.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MibAttributeDescriptorsTest_h_
#define __MibAttributeDescriptorsTest_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include <iostream>

#include <cppunit/TestCase.h>

#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MibAttributeDescriptors.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Test Cases
///////////////////////////////////////////////////////////////////////////////

class MibAttributeDescriptorsTest : public CppUnit::TestCase
{
public:
    void runTest()
    {
        cout << endl << endl
             << "*****************************" << endl
             << "MibAttributeDescriptors tests" << endl
             << "*****************************" << endl << endl;

        TRACE_MSG("Checking a couple of MIB attribute names");
        CPPUNIT_ASSERT_MESSAGE("MNC", strcmp(getMibAttributeName(PARAM_ID_MNC), "MNC") == 0);
        TRACE("TEST_STRING_ARRAY as string: ", getMibAttributeName(PARAM_ID_TEST_STRING_ARRAY));
        CPPUNIT_ASSERT_MESSAGE("TEST_STRING_ARRAY", strcmp(getMibAttributeName(PARAM_ID_TEST_STRING_ARRAY), "TEST_STRING_ARRAY") == 0);

        fflush(stdout);
    }

protected:

private:

};

#endif
