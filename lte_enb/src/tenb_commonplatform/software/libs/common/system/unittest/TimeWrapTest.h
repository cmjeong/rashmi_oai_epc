///////////////////////////////////////////////////////////////////////////////
//
// TimeWrapTest.h
//
// Unit tests for TimeWrap class.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __TimeWrapTest_h_
#define __TimeWrapTest_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <ctype.h>
#include <unistd.h>

#include <cppunit/TestCase.h>

#include <3waytypes.h>
#include <system/Trace.h>
#include <system/Exception.h>
#include <system/TimeWrap.h>

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class TimeWrapTest : public CppUnit::TestCase
{
public:
    void runTest()
    {
        cout << endl << endl
             << "**************" << endl
             << "TimeWrap tests" << endl
             << "**************" << endl << endl;

        struct tm timeStruct;
        memset((void*)&timeStruct, 0, sizeof(timeStruct));
        timeStruct.tm_year = 2008 - 1900;
        timeStruct.tm_mon = 3; // April
        timeStruct.tm_mday = 12; // 12th
        timeStruct.tm_hour = 21; // 0-23
        timeStruct.tm_min = 33;
        timeStruct.tm_sec = 12;
        time_t unixTime = timegm(&timeStruct); // Should be 1208034000 according to online calculator: http://www.7is7.com/otto/datediff.html
                                               // But we get 1208035992.

        cout << "After timegm: timeStruct time = " << (u32)timeStruct.tm_hour << ":"  << (u32)timeStruct.tm_min << ":"  << (u32)timeStruct.tm_sec << endl;
        cout << "unixTime=" << unixTime << endl;

        struct tm * pTimeStruct = gmtime(&unixTime);
        cout << "After gmtime: time = " << (u32)pTimeStruct->tm_hour << ":"  << (u32)pTimeStruct->tm_min << ":"  << (u32)pTimeStruct->tm_sec << endl;

        TimeWrap myTime(unixTime);

        cout << "myTime.GetUnixTime()=" << myTime.GetUnixTime() << endl;
        cout << "myTime.ToString()=" << myTime.ToString() << endl;

        CPPUNIT_ASSERT_MESSAGE("Check unix time", unixTime == (time_t)myTime.GetUnixTime());
        CPPUNIT_ASSERT_MESSAGE("Check micro secs are zero", 0 == myTime.GetMicroSecs());
        cout << myTime.ToString() << endl;
        CPPUNIT_ASSERT_MESSAGE("Check ToString()", "2008-04-12T21:33:12" == myTime.ToString());

        unixTime += 24*60*60;
        myTime.Set(unixTime, 123);

        CPPUNIT_ASSERT_MESSAGE("Check unix time", unixTime == (time_t)myTime.GetUnixTime());
        CPPUNIT_ASSERT_MESSAGE("Check micro secs are 123", 123 == myTime.GetMicroSecs());
        CPPUNIT_ASSERT_MESSAGE("Check ToString()", "2008-04-13T21:33:12" == myTime.ToString());

        cout << "Test elapsed time calc (2s sleep)" << endl;

        TimeWrap timeBeforeSleep;

        sleep(2);

        CPPUNIT_ASSERT_MESSAGE("Check elapsed seconds", timeBeforeSleep.GetSecondsElapsed() == 2);

        fflush(stdout);
    }

private:
};

#endif
