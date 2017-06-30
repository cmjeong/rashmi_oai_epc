///////////////////////////////////////////////////////////////////////////////
//
// IMSITest.h
//
// Unit tests for IMSI class.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __IMSITest_h_
#define __IMSITest_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <mobnet/IMSI.h>

#include <string.h>
#include <iostream>
#include <cppunit/TestCase.h>

#include <3waytypes.h>
#include <system/Trace.h>
#include <system/Exception.h>

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class IMSITest : public CppUnit::TestCase
{
public:
    void runTest()
    {
        cout << endl << endl
             << "**********" << endl
             << "IMSI tests" << endl
             << "**********" << endl << endl;

        //
        // Normal cases.
        //

        // Different constructors.
        IMSI imsi1;
        cout << "Checking different constructors" << endl;
        cout << "  IMSI1=" << imsi1.ToString() << endl;
        CPPUNIT_ASSERT_MESSAGE("Check default constructor means IMSI not set", imsi1.IsSet() == false);
        CPPUNIT_ASSERT_MESSAGE("Check default constructor means IMSI is empty string", strcmp(imsi1.ToString(), "<undefined>") == 0);

        IMSI imsi2("0123456789ABCDE");
        cout << "  IMSI2=" << imsi2.ToString() << endl;
        CPPUNIT_ASSERT_MESSAGE("Check new IMSI set", imsi2.IsSet() == true);
        CPPUNIT_ASSERT_MESSAGE("Check new IMSI set correctly", strcmp(imsi2.ToString(), "0123456789ABCDE") == 0);

        u8 data[] = {14,13,12,11,10,9,8,7,6,5,4,3,2,1,0};
        IMSI imsi3(data, (u8)sizeof(data));
        cout << "  IMSI3=" << imsi3.ToString() << endl;
        CPPUNIT_ASSERT_MESSAGE("Check new IMSI set", imsi3.IsSet() == true);
        CPPUNIT_ASSERT_MESSAGE("Check new IMSI set correctly", strcmp(imsi3.ToString(), "EDCBA9876543210") == 0);

        unsigned long dataUL[] = {13,12,11,10,9,8,7,6,5,4,3,2,1,0,14};
        IMSI imsi4(dataUL,(int)( (sizeof(dataUL))/(sizeof(dataUL[0]) ) ) );
        cout << "  IMSI4=" << imsi4.ToString() << endl;
        CPPUNIT_ASSERT_MESSAGE("Check new IMSI set", imsi4.IsSet() == true);
        CPPUNIT_ASSERT_MESSAGE("Check new IMSI set correctly", strcmp(imsi4.ToString(), "DCBA9876543210E") == 0);

        // Different setters.
        IMSI imsi5;
        imsi5.SetIMSI("0123456789ABCDE");
        cout << "  IMSI5=" << imsi5.ToString() << endl;
        CPPUNIT_ASSERT_MESSAGE("Check IMSI set", imsi5.IsSet() == true);
        CPPUNIT_ASSERT_MESSAGE("Check IMSI set correctly", strcmp(imsi5.ToString(), "0123456789ABCDE") == 0);
        imsi5.SetIMSI("123456789ABCDE0");
        cout << "  IMSI5=" << imsi5.ToString() << endl;
        CPPUNIT_ASSERT_MESSAGE("Check IMSI set", imsi5.IsSet() == true);
        CPPUNIT_ASSERT_MESSAGE("Check IMSI set correctly", strcmp(imsi5.ToString(), "123456789ABCDE0") == 0);

        IMSI imsi6;
        imsi6.SetIMSI(data,(u8)sizeof(data));
        cout << "  IMSI6=" << imsi6.ToString() << endl;
        CPPUNIT_ASSERT_MESSAGE("Check IMSI set", imsi6.IsSet() == true);
        CPPUNIT_ASSERT_MESSAGE("Check IMSI set correctly", strcmp(imsi6.ToString(), "EDCBA9876543210") == 0);
        imsi6.SetIMSI(dataUL,(int)( (sizeof(dataUL))/ (sizeof(dataUL[0]) )) );
        cout << "  IMSI6=" << imsi6.ToString() << endl;
        CPPUNIT_ASSERT_MESSAGE("Check IMSI set", imsi6.IsSet() == true);
        CPPUNIT_ASSERT_MESSAGE("Check IMSI set correctly", strcmp(imsi6.ToString(), "DCBA9876543210E") == 0);

        IMSI imsi7;
        imsi7.SetIMSI(data,(u8)sizeof(data));
        cout << "  IMSI7=" << imsi7.ToString() << endl;
        CPPUNIT_ASSERT_MESSAGE("Check IMSI set", imsi7.IsSet() == true);
        CPPUNIT_ASSERT_MESSAGE("Check IMSI set correctly", strcmp(imsi7.ToString(), "EDCBA9876543210") == 0);
        IMSI imsi8(imsi7);
        cout << "  IMSI8=" << imsi8.ToString() << endl;
        CPPUNIT_ASSERT_MESSAGE("Check IMSI set", imsi8.IsSet() == true);
        CPPUNIT_ASSERT_MESSAGE("Check IMSI set correctly", strcmp(imsi8.ToString(), "EDCBA9876543210") == 0);
        CPPUNIT_ASSERT_MESSAGE("IMSIs are equivalent", imsi7 == imsi8);

        //
        // Error cases.
        //

        fflush(stdout);
    }

private:
};

#endif
