///////////////////////////////////////////////////////////////////////////////
//
// SerialisationUtilsTest.h
//
// Unit tests for KPI classes.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __SerialisationUtilsTest_h_
#define __SerialisationUtilsTest_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include <cppunit/TestCase.h>

#include <3waytypes.h>
#include <system/Trace.h>
#include <system/SerialisationUtils.h>

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

typedef enum
{
    SOME_ENUM_1,
    SOME_ENUM_2,
    SOME_ENUM_3
} SomeEnum;

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class SerialisationUtilsTest : public CppUnit::TestCase
{
public:
    void runTest()
    {
        cout << endl << endl
             << "************************" << endl
             << "SerialisationUtils tests" << endl
             << "************************" << endl << endl;

        u8 dataIn[100];
        u8* pDataIn = dataIn;

        const u8 myU8In = 123;
        const u16 myU16In = 12345;
        const u32 myU32In = 123456789;
        const string myStrIn("Think of some words... pub, beer, ..."); // 37 chars
        const bool myBoolIn = true;
        set<SomeEnum> myEnumIn;
        myEnumIn.insert(SOME_ENUM_1);
        myEnumIn.insert(SOME_ENUM_3);

        u8 myU8Out;
        u16 myU16Out;
        u32 myU32Out;
        string myStrOut;
        bool myBoolOut;
        set<SomeEnum> myEnumOut;

        TRACE_MSG("Serialise a bunch of stuff.");
        SerialiseIt(myU8In, pDataIn); // 1
        SerialiseIt(myU16In, pDataIn); // 2
        SerialiseIt(myU32In, pDataIn); // 4
        SerialiseIt(myStrIn, pDataIn); // 39
        SerialiseIt(myBoolIn, pDataIn); // 1
        SerialiseItU32Set(myEnumIn, pDataIn, sizeof(dataIn) - (pDataIn - dataIn)); // 10

        TRACE("Check it serialised OK, length", (u32)(pDataIn - dataIn));
        CPPUNIT_ASSERT_MESSAGE("Check serialisation length", (pDataIn - dataIn) == 57);

        TRACE_MSG("DeSerialise it.");
        const u8* pDataOut = dataIn;
        DeSerialiseIt(myU8Out, pDataOut);
        DeSerialiseIt(myU16Out, pDataOut);
        DeSerialiseIt(myU32Out, pDataOut);
        DeSerialiseIt(myStrOut, pDataOut, 100);
        DeSerialiseIt(myBoolOut, pDataOut);
        DeSerialiseItU32Set(myEnumOut, pDataOut, (u16)10);

        TRACE_MSG("Check it deserialised OK.");

        CPPUNIT_ASSERT_MESSAGE("Check deserialisation length", (pDataOut - dataIn) == 57);

        CPPUNIT_ASSERT_MESSAGE("Check U8", myU8In == myU8Out);
        CPPUNIT_ASSERT_MESSAGE("Check U16", myU16In == myU16Out);
        CPPUNIT_ASSERT_MESSAGE("Check U32", myU32In == myU32Out);
        CPPUNIT_ASSERT_MESSAGE("Check string", myStrIn == myStrOut);
        CPPUNIT_ASSERT_MESSAGE("Check bool", myBoolIn == myBoolOut);

        CPPUNIT_ASSERT_MESSAGE("Check set length", myEnumOut.size() == 2);
        CPPUNIT_ASSERT_MESSAGE("Check set values", myEnumIn == myEnumOut);

        fflush(stdout);
    }

private:
};

#endif
