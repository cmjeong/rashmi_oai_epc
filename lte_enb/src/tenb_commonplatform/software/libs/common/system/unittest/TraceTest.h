///////////////////////////////////////////////////////////////////////////////
//
// TraceTest.h
//
// Tracing tests.  Generates a file that is then compared to the expected
// output.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __TraceTest_h_
#define __TraceTest_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include <cppunit/TestCase.h>

#include <system/Trace.h>
#include <system/Exception.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Test Cases
///////////////////////////////////////////////////////////////////////////////

class TraceTest : public CppUnit::TestCase
{
public:
    void runTest()
    {
        ENTER();

        cout << endl << endl
             << "***********" << endl
             << "Trace tests" << endl
             << "***********" << endl << endl;

        // These should already be disabled.  Other unit tests should
        // not have enabled them.
        Trace::GetInstance().SetApplicationInfo("Some old guff about this app.");
        Trace::GetInstance().SetFileLoggingParams("./", "TraceTest");
        Trace::GetInstance().EnableFileLogging(128*1024);
        Trace::GetInstance().DisableUDPLogging();
        Trace::GetInstance().SetTraceLevelsMask(TRACE_VERBOSE | TRACE_INFO | TRACE_WARNING | TRACE_CRITICAL | TRACE_FATAL);
        static u32 TRACE_CAT_TEST = 0x00000001;
        Trace::GetInstance().RegisterTraceCategory(TRACE_CAT_TEST, "TESTCAT");
        Trace::GetInstance().SetTraceCategoriesOn(TRACE_CAT_TEST);

        TRACE_PRINTF("Some simple %" PRIu32 " TRACE_PRINTF", 123);
        TRACE_PRINTF_LEV(TRACE_VERBOSE,  "Some VERBOSE %" PRIu32 " TRACE_PRINTF", 123);
        TRACE_PRINTF_LEV(TRACE_INFO,     "Some INFO %" PRIu32 " TRACE_PRINTF", 123);
        TRACE_PRINTF_LEV(TRACE_WARNING,  "Some WARNING %" PRIu32 " TRACE_PRINTF", 123);
        TRACE_PRINTF_LEV(TRACE_CRITICAL, "Some CRITICAL %" PRIu32 " TRACE_PRINTF", 123);
        TRACE_PRINTF_LEV(TRACE_FATAL,    "Some FATAL %" PRIu32 " TRACE_PRINTF", 123);

        TRACE_PRINTF_CAT(TRACE_CAT_TEST, TRACE_VERBOSE, "Some VERBOSE TESTCAT %" PRIu32 " TRACE_PRINTF", 123);
        TRACE_PRINTF_CAT(TRACE_CAT_TEST, TRACE_WARNING, "Some WARNING TESTCAT %" PRIu32 " TRACE_PRINTF", 123);

        TRACE_MSG("Some message");
        TRACE_MSG_LEV(TRACE_WARNING, "Some WARNING message");
        TRACE_MSG_CAT(TRACE_CAT_TEST, TRACE_WARNING, "Some WARNING TESCAT message");

        TRACE("Trace a u32", (u32)1234);
        TRACE("Trace a s32", (s32)-1234);
        TRACE("Trace a const char *", "hello");
        string str = "hello!";
        TRACE("Trace a string", str);
        TRACE("Trace a bool", true);
        Exception e("file", 1, "some message %s", "blah");
        TRACE_EXCEPTION(e);
        u8 arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17 };
        TRACE_X("Trace a X array", arr, sizeof(arr));
        TRACE_HEX_MSG("Trace a hex array", arr, sizeof(arr));
        TRACE_HEX("Trace a hex number", 123);


        TRACE_MSG(
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                "Trace a very large message indeed.  Trace a very large message indeed.  Trace a very large message indeed.  "
                 );

        Trace::GetInstance().SetTraceLevelOff(TRACE_VERBOSE);
        const char * logFileName = Trace::GetInstance().GetTraceFilename();
        Trace::GetInstance().DisableFileLogging();

        // TODO: Read file and add tests here to check it's formatted correctly.

        remove(logFileName);

        //RSYS_ASSERT_PRINTF(1==0, "argh!");

        fflush(stdout);

        EXIT();
    }

protected:

private:

};

#endif
