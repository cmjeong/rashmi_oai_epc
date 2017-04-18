///////////////////////////////////////////////////////////////////////////////
//
// PlmnIdTest.h
//
// Unit tests for PlmnId class.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __PlmnIdTest_h_
#define __PlmnIdTest_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <sstream>

#include <cppunit/TestCase.h>

#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "mobnet/PlmnId.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Test Cases
///////////////////////////////////////////////////////////////////////////////

class PlmnIdTest : public CppUnit::TestCase
{
public:
    void runTest()
    {
        cout << endl << endl
             << "************" << endl
             << "PlmnId tests" << endl
             << "************" << endl << endl;

        // MCC = 123, MNC = 456
        rsysmob::PlmnId plmnId(123, 456);
        u8 encodedPlmnId[3];

        TRACE_MSG("Checking encoded PLMN ID with 3 digit MNC");
        plmnId.GetAsBcdEncoded(encodedPlmnId);
        TRACE_PRINTF("  0x%02X 0x%02X 0x%02X", encodedPlmnId[0], encodedPlmnId[1], encodedPlmnId[2]);
        CPPUNIT_ASSERT_MESSAGE("Check encoded PLMN ID byte 0", encodedPlmnId[0] == ((2 << 4) + 1));
        CPPUNIT_ASSERT_MESSAGE("Check encoded PLMN ID byte 1", encodedPlmnId[1] == ((6 << 4) + 3));
        CPPUNIT_ASSERT_MESSAGE("Check encoded PLMN ID byte 2", encodedPlmnId[2] == ((5 << 4) + 4));

        TRACE_MSG("Checking 25.469 encoded PLMN ID with 3 digit MNC");
        plmnId.GetAs25469BcdEncoded(encodedPlmnId);
        TRACE_PRINTF("  0x%02X 0x%02X 0x%02X", encodedPlmnId[0], encodedPlmnId[1], encodedPlmnId[2]);
        CPPUNIT_ASSERT_MESSAGE("Check encoded PLMN ID byte 0", encodedPlmnId[0] == ((2 << 4) + 1));
        CPPUNIT_ASSERT_MESSAGE("Check encoded PLMN ID byte 1", encodedPlmnId[1] == ((4 << 4) + 3));
        CPPUNIT_ASSERT_MESSAGE("Check encoded PLMN ID byte 2", encodedPlmnId[2] == ((6 << 4) + 5));


        TRACE_MSG("Checking encoded PLMN ID with 2 digit MNC - should see a warning but get 3 digit MNC");
        rsysmob::PlmnId plmnId2(123, 456, true);
        plmnId2.GetAsBcdEncoded(encodedPlmnId);
        TRACE_PRINTF("  0x%02X 0x%02X 0x%02X", encodedPlmnId[0], encodedPlmnId[1], encodedPlmnId[2]);
        CPPUNIT_ASSERT_MESSAGE("Check encoded PLMN ID byte 0", encodedPlmnId[0] == ((2 << 4) + 1));
        CPPUNIT_ASSERT_MESSAGE("Check encoded PLMN ID byte 1", encodedPlmnId[1] == ((6 << 4) + 3));
        CPPUNIT_ASSERT_MESSAGE("Check encoded PLMN ID byte 2", encodedPlmnId[2] == ((5 << 4) + 4));

        TRACE_MSG("Checking 25.469 encoded PLMN ID with 2 digit MNC - should see a warning but get 3 digit MNC");
        plmnId2.GetAs25469BcdEncoded(encodedPlmnId);
        TRACE_PRINTF("  0x%02X 0x%02X 0x%02X", encodedPlmnId[0], encodedPlmnId[1], encodedPlmnId[2]);
        CPPUNIT_ASSERT_MESSAGE("Check encoded PLMN ID byte 0", encodedPlmnId[0] == ((2 << 4) + 1));
        CPPUNIT_ASSERT_MESSAGE("Check encoded PLMN ID byte 1", encodedPlmnId[1] == ((4 << 4) + 3));
        CPPUNIT_ASSERT_MESSAGE("Check encoded PLMN ID byte 2", encodedPlmnId[2] == ((6 << 4) + 5));


        TRACE_MSG("Checking encoded PLMN ID with 2 digit MNC");
        rsysmob::PlmnId plmnId3(123, 78, true);
        plmnId3.GetAsBcdEncoded(encodedPlmnId);
        TRACE_PRINTF("  0x%02X 0x%02X 0x%02X", encodedPlmnId[0], encodedPlmnId[1], encodedPlmnId[2]);
        CPPUNIT_ASSERT_MESSAGE("Check encoded PLMN ID byte 0", encodedPlmnId[0] == ((2 << 4) + 1));
        CPPUNIT_ASSERT_MESSAGE("Check encoded PLMN ID byte 1", encodedPlmnId[1] == ((0x0f << 4) + 3));
        CPPUNIT_ASSERT_MESSAGE("Check encoded PLMN ID byte 2", encodedPlmnId[2] == ((8 << 4) + 7));

        TRACE_MSG("Checking 25.469 encoded PLMN ID with 2 digit MNC");
        plmnId3.GetAs25469BcdEncoded(encodedPlmnId);
        TRACE_PRINTF("  0x%02X 0x%02X 0x%02X", encodedPlmnId[0], encodedPlmnId[1], encodedPlmnId[2]);
        CPPUNIT_ASSERT_MESSAGE("Check encoded PLMN ID byte 0", encodedPlmnId[0] == ((2 << 4) + 1));
        CPPUNIT_ASSERT_MESSAGE("Check encoded PLMN ID byte 1", encodedPlmnId[1] == ((0x0f << 4) + 3));
        CPPUNIT_ASSERT_MESSAGE("Check encoded PLMN ID byte 2", encodedPlmnId[2] == ((8 << 4) + 7));

        TRACE_MSG("Checking PLMN ID from string validation");
        CPPUNIT_ASSERT_MESSAGE("Check 2 digit MNC", rsysmob::PlmnId::Validate("12345") );
        CPPUNIT_ASSERT_MESSAGE("Check 3 digit MNC", rsysmob::PlmnId::Validate("123456") );
        CPPUNIT_ASSERT_MESSAGE("Check non-digits fails", !rsysmob::PlmnId::Validate("12345A") );
        CPPUNIT_ASSERT_MESSAGE("Check too many digits fails", !rsysmob::PlmnId::Validate("1234567") );
        CPPUNIT_ASSERT_MESSAGE("Check too few digits fails", !rsysmob::PlmnId::Validate("1234") );

        TRACE_MSG("Checking PLMN ID from string setting");
        rsysmob::PlmnId plmnId4;

        plmnId4.Set("12345");
        ostringstream msg1;
        msg1 << "Check 2 digit MNC (" << plmnId4.ToString() << ")";
        cout << msg1.str() << endl;
        bool isTwoDigits = false;
        CPPUNIT_ASSERT_MESSAGE(msg1.str().c_str(),
                (u16(123) == plmnId4.GetMcc())
                && (u16(45) == plmnId4.GetMnc(&isTwoDigits))
                && isTwoDigits );

        plmnId4.Set("004006");
        ostringstream msg2;
        msg2 << "Check 3 digit MNC, leading zero (" << plmnId4.ToString() << ")";
        cout << msg2.str() << endl;
        CPPUNIT_ASSERT_MESSAGE(msg2.str().c_str(),
                (u16(4) == plmnId4.GetMcc())
                && (u16(6) == plmnId4.GetMnc(&isTwoDigits))
                && (!isTwoDigits) );

        plmnId4.Set("345678");
        ostringstream msg3;
        msg3 << "Check 3 digit MNC, (" << plmnId4.ToString() << ")";
        cout << msg3.str() << endl;
        CPPUNIT_ASSERT_MESSAGE(msg3.str().c_str(),
                (u16(345) == plmnId4.GetMcc())
                && (u16(678) == plmnId4.GetMnc(&isTwoDigits))
                && (!isTwoDigits));


		// Check PLMN Encoding and Decoding for 25.469

		// Following two scenarios are based on the assumption that,
		// plmnid will always be created as 3 digit MNC if MNC is greater than 99. 
		// Else it will be created as 2 digit MNC

		// 3 Digit MNC
		// Since value is greater than 99, create it as 3 digit MNC
        rsysmob::PlmnId plmnId7(123, 456, false);

        TRACE_MSG("Checking encoded PLMN ID with 3 digit MNC");
        TRACE_PRINTF("%s", plmnId7.ToString().c_str());
        plmnId7.GetAs25469BcdEncoded(encodedPlmnId);
        TRACE_PRINTF("  0x%02X 0x%02X 0x%02X", encodedPlmnId[0], encodedPlmnId[1], encodedPlmnId[2]);
        CPPUNIT_ASSERT_MESSAGE("Check encoded PLMN ID byte 0", encodedPlmnId[0] == ((2 << 4) + 1));
        CPPUNIT_ASSERT_MESSAGE("Check encoded PLMN ID byte 1", encodedPlmnId[1] == ((4 << 4) + 3));
        CPPUNIT_ASSERT_MESSAGE("Check encoded PLMN ID byte 2", encodedPlmnId[2] == ((6 << 4) + 5));


        TRACE_MSG("Checking 25.469 decoded PLMN ID with 3 digit MNC");
		rsysmob::PlmnId plmnId8;
		plmnId8.SetFrom25469BcdEncoded(encodedPlmnId);
        TRACE_PRINTF("%s", plmnId8.ToString().c_str());
        CPPUNIT_ASSERT_MESSAGE("Check encoded PLMN and Decoded PLMN", (plmnId7 == plmnId8));


		// 2 Digit MNC
		// Since value is not greater than 99, create it as 2 digit MNC
        rsysmob::PlmnId plmnId9(123, 78, true);
        TRACE_MSG("Checking 25.469 encoded PLMN ID with 2 digit MNC");
        TRACE_PRINTF("%s", plmnId9.ToString().c_str());
        plmnId9.GetAs25469BcdEncoded(encodedPlmnId);
        TRACE_PRINTF("  0x%02X 0x%02X 0x%02X", encodedPlmnId[0], encodedPlmnId[1], encodedPlmnId[2]);
        CPPUNIT_ASSERT_MESSAGE("Check encoded PLMN ID byte 0", encodedPlmnId[0] == ((2 << 4) + 1));
        CPPUNIT_ASSERT_MESSAGE("Check encoded PLMN ID byte 1", encodedPlmnId[1] == ((0x0f << 4) + 3));
        CPPUNIT_ASSERT_MESSAGE("Check encoded PLMN ID byte 2", encodedPlmnId[2] == ((8 << 4) + 7));
        
        TRACE_MSG("Checking 25.469 decoded PLMN ID with 2 digit MNC");
		rsysmob::PlmnId plmnId10;
		plmnId10.SetFrom25469BcdEncoded(encodedPlmnId);
        TRACE_PRINTF("%s", plmnId10.ToString().c_str());
        CPPUNIT_ASSERT_MESSAGE("Check encoded PLMN and Decoded PLMN", (plmnId9 == plmnId10));

		// Failure Scenarios

		// Failure Scenario #1
		// 3 Digit MNC
		// Since value is greater than 99, create it as 3 digit MNC, but here we will create it as 2 Digit
        rsysmob::PlmnId plmnId11(123, 456, true);

        TRACE_MSG("Checking encoded PLMN ID with 3 digit MNC");
        TRACE_PRINTF("%s", plmnId11.ToString().c_str());
        plmnId11.GetAs25469BcdEncoded(encodedPlmnId);
        TRACE_PRINTF("  0x%02X 0x%02X 0x%02X", encodedPlmnId[0], encodedPlmnId[1], encodedPlmnId[2]);
        CPPUNIT_ASSERT_MESSAGE("Check encoded PLMN ID byte 0", encodedPlmnId[0] == ((2 << 4) + 1));
        CPPUNIT_ASSERT_MESSAGE("Check encoded PLMN ID byte 1", encodedPlmnId[1] == ((4 << 4) + 3));
        CPPUNIT_ASSERT_MESSAGE("Check encoded PLMN ID byte 2", encodedPlmnId[2] == ((6 << 4) + 5));


        TRACE_MSG("Checking 25.469 decoded PLMN ID with 3 digit MNC");
		rsysmob::PlmnId plmnId12;
		plmnId12.SetFrom25469BcdEncoded(encodedPlmnId);
        TRACE_PRINTF("%s", plmnId12.ToString().c_str());
        CPPUNIT_ASSERT_MESSAGE("Check encoded PLMN and Decoded PLMN fails", !(plmnId11 == plmnId12));


		// Failure Scenario #2
		
		// 2 Digit MNC
		// Since value is not greater than 99, create it as 2 digit MNC, But here we will create it as 3 digit
        rsysmob::PlmnId plmnId13(123, 78, false);
        TRACE_MSG("Checking 25.469 encoded PLMN ID with 2 digit MNC");
        TRACE_PRINTF("%s", plmnId13.ToString().c_str());
        plmnId13.GetAs25469BcdEncoded(encodedPlmnId);
        TRACE_PRINTF("  0x%02X 0x%02X 0x%02X", encodedPlmnId[0], encodedPlmnId[1], encodedPlmnId[2]);
        CPPUNIT_ASSERT_MESSAGE("Check encoded PLMN ID byte 0", encodedPlmnId[0] == ((2 << 4) + 1));
        CPPUNIT_ASSERT_MESSAGE("Check encoded PLMN ID byte 1 fails", !(encodedPlmnId[1] == ((0x0f << 4) + 3)));
        CPPUNIT_ASSERT_MESSAGE("Check encoded PLMN ID byte 2", encodedPlmnId[2] == ((8 << 4) + 7));
        
        TRACE_MSG("Checking 25.469 decoded PLMN ID with 2 digit MNC");
		rsysmob::PlmnId plmnId14;
		plmnId14.SetFrom25469BcdEncoded(encodedPlmnId);
        TRACE_PRINTF("%s", plmnId14.ToString().c_str());
        CPPUNIT_ASSERT_MESSAGE("Check encoded PLMN and Decoded PLMN", (plmnId13 == plmnId14));

		
		fflush(stdout);
    }

protected:

private:

};

#endif
