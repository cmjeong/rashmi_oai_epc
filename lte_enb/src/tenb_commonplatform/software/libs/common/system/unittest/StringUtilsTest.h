///////////////////////////////////////////////////////////////////////////////
//
// StringUtilsTest.h
//
// Unit tests for StringUtils module.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __StringUtilsTest_h_
#define __StringUtilsTest_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include <cppunit/TestCase.h>

#include <system/Trace.h>
#include <system/StringUtils.h>
#include <system/Exception.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////


using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Test Cases
///////////////////////////////////////////////////////////////////////////////

class StringUtilsTest : public CppUnit::TestCase
{
public:
    void runTest()
    {
        cout << endl << endl
             << "*********************" << endl
             << "StringUtilsTest tests" << endl
             << "*********************" << endl << endl;

        string u32ArrayAsString("0,1,2,3..9,10,11,12..20,21,22");
        vector<u32> u32Vector;
        TRACE_MSG("Check for u32 csv conversion." );

        try {
            StringUtils::ConvertStringToInteger(u32ArrayAsString, u32Vector);

            stringstream result;
            result << "Vector length ==" << u32Vector.size();
            TRACE_MSG( result.str().c_str() );
        } catch(const Exception& e) {
            TRACE_MSG("Exception");
            TRACE_MSG(e.what());
        }

        for(u32 i = 0; i < 23; i++)
        {
            TRACE_MSG( "Check result exists for i" );
            CPPUNIT_ASSERT( u32Vector.size() >= i);

            stringstream result;
            result << "U32 csv conversion result...(" << i << "==" << u32Vector.at(i) << ")";
            TRACE_MSG( result.str().c_str() );
            CPPUNIT_ASSERT_MESSAGE( result.str().c_str(), i == u32Vector.at(i));
        }

        string s32ArrayAsString("-6,-5..3,4..6");
        vector<s32> s32Vector;
        TRACE_MSG("Check for s32 csv conversion." );

        try {
            StringUtils::ConvertStringToInteger(s32ArrayAsString, s32Vector);

            stringstream result;
            result << "Vector length ==" << s32Vector.size();
            TRACE_MSG( result.str().c_str() );
        } catch(const Exception& e) {
            TRACE_MSG("Exception");
            TRACE_MSG(e.what());
        }

        for(s32 i = -6; i < 7; i++)
        {
            size_t index = i + 6;

            TRACE_MSG( "Check result exists for i" );
            CPPUNIT_ASSERT( s32Vector.size() >= index);

            stringstream result;
            result << "S32 csv conversion result...(" << i << "==" << s32Vector.at(index) << ")";
            TRACE_MSG( result.str().c_str() );
            CPPUNIT_ASSERT_MESSAGE( result.str().c_str(), i == s32Vector.at(index));
        }

        TRACE_MSG("Creating a string and copying 'hello' into it and checking.");
        char testStr[10];
        memset(testStr, 0x12, sizeof(testStr));

        char * retStr = strncpysafe(testStr, "hello", 6);

        CPPUNIT_ASSERT(retStr == testStr);
        CPPUNIT_ASSERT(testStr[0] == 'h');
        CPPUNIT_ASSERT(testStr[1] == 'e');
        CPPUNIT_ASSERT(testStr[2] == 'l');
        CPPUNIT_ASSERT(testStr[3] == 'l');
        CPPUNIT_ASSERT(testStr[4] == 'o');
        CPPUNIT_ASSERT(testStr[5] == '\0');
        CPPUNIT_ASSERT(testStr[6] == 0x12);
        CPPUNIT_ASSERT(testStr[7] == 0x12);
        CPPUNIT_ASSERT(testStr[8] == 0x12);
        CPPUNIT_ASSERT(testStr[9] == 0x12);

        TRACE_MSG("Now copying 'blah' into it and checking.");
        retStr = strncpysafe(testStr, "blah", 6);

        CPPUNIT_ASSERT(retStr == testStr);
        CPPUNIT_ASSERT(testStr[0] == 'b');
        CPPUNIT_ASSERT(testStr[1] == 'l');
        CPPUNIT_ASSERT(testStr[2] == 'a');
        CPPUNIT_ASSERT(testStr[3] == 'h');
        CPPUNIT_ASSERT(testStr[4] == '\0');
        CPPUNIT_ASSERT(testStr[5] == '\0');
        CPPUNIT_ASSERT(testStr[6] == 0x12);
        CPPUNIT_ASSERT(testStr[7] == 0x12);
        CPPUNIT_ASSERT(testStr[8] == 0x12);
        CPPUNIT_ASSERT(testStr[9] == 0x12);

        // Now do some edge case tests.
        Trace_SetAssertAbortDisabled(true);

//        CPPUNIT_CHECK_ASSERT(
//                (strncpysafe(testStr, "hello", 5);)
//                "srcLen < n"
//                            );

        bool asserted = false;
        try {
            strncpysafe(testStr, "hello", 5);
        } catch(const Exception& e) {
//            CPPUNIT_ASSERT_MESSAGE("Check for correct assert condition.", strcmp(e.what(), "srcLen < n") == 0);
            asserted = true;
        }
        CPPUNIT_ASSERT_MESSAGE("Check that we spot that the destination is just too small.", asserted == true);

        asserted = false;
        try {
            strncpysafe(testStr, testStr, 10);
        } catch(const Exception& e) {
//            CPPUNIT_ASSERT_MESSAGE("Check for correct assert condition.", strcmp(e.what(), "srcLen < n") == 0);
            asserted = true;
        }
        //CPPUNIT_ASSERT_MESSAGE("Check for overlapping strings.", asserted == true);

        // Go back to normal asserts.
        Trace_SetAssertAbortDisabled(false);

        fflush(stdout);

    }

protected:

private:

};

#endif
