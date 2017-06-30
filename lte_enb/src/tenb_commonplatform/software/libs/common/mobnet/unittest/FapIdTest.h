///////////////////////////////////////////////////////////////////////////////
//
// FapIdTest.h
//
// Unit tests for FapId class.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __FapIdTest_h_
#define __FapIdTest_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include <cppunit/TestCase.h>

#include <system/Trace.h>
#include <mobnet/FapId.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Test Cases
///////////////////////////////////////////////////////////////////////////////

class FapIdTest : public CppUnit::TestCase
{
public:
    void runTest()
    {
        cout << endl << endl
             << "***************" << endl
             << "FapIdTest tests" << endl
             << "***************" << endl << endl;

        // Now do some edge case tests.
        Trace_SetAssertAbortDisabled(true);

        TRACE_MSG("Check FAP ID length validation.");

        bool asserted = false;
        try {
            string tooShortFapId("12345678901234");
            FapId fapIdWrongLength(tooShortFapId);
        } catch(const Exception& e) {
            asserted = true;
        }

        CPPUNIT_ASSERT_MESSAGE("Check that we assert on too short FAP ID.", asserted == true);

        asserted = false;
        try {
            string tooLongShortFapId("1234567890123456");
            FapId fapIdWrongLength(tooLongShortFapId);
        } catch(const Exception& e) {
            asserted = true;
        }

        CPPUNIT_ASSERT_MESSAGE("Check that we assert on too long FAP ID.", asserted == true);

        // Go back to normal asserts.
        Trace_SetAssertAbortDisabled(false);

        string shortFapId("012345678912345");
        FapId fapId(shortFapId);

        TRACE_MSG("Check FAP ID is set");
        CPPUNIT_ASSERT(fapId.IsSet());

        TRACE("Check getting short FAP ID", fapId.GetShortFapId());
        CPPUNIT_ASSERT(fapId.GetShortFapId() == "012345678912345");

        TRACE("Check getting full FAP ID", fapId.GetFullFapId());
        CPPUNIT_ASSERT(fapId.GetFullFapId() == "012345678912345.Radisys.com");

        TRACE_MSG("Serialise");
        u8 buffer[100];
        s32 serialisationLength = fapId.Serialise(buffer, sizeof(buffer));
        FapId newFapId;
        TRACE_MSG("Check new FAP ID is not set");
        CPPUNIT_ASSERT(!newFapId.IsSet());
        TRACE_MSG("Check new FAP ID not same as old FAP ID");
        CPPUNIT_ASSERT(newFapId != fapId);

        TRACE_MSG("Deserialise");
        newFapId.DeSerialise(buffer, serialisationLength);

        TRACE_MSG("Check new FAP ID same as old FAP ID");
        CPPUNIT_ASSERT(newFapId == fapId);

        TRACE_MSG("Check the IsEquivalentTo() function");
        FapId normalFapId(             "0005B9-12345678");
        FapId longerEquivFapId(      "0005B9-9812345678");
        FapId longerButNotEquivFapId("0005B9-9822345678");

        // They are all different...
        CPPUNIT_ASSERT(normalFapId != longerEquivFapId);
        CPPUNIT_ASSERT(normalFapId != longerButNotEquivFapId);
        CPPUNIT_ASSERT(longerEquivFapId != longerButNotEquivFapId);

        // But normalFapId and longerEquivFapId are equivalent.
        CPPUNIT_ASSERT(normalFapId.IsEquivalentTo(longerEquivFapId));
        CPPUNIT_ASSERT(longerEquivFapId.IsEquivalentTo(normalFapId));

        // And longerEquivFapId and longerButNotEquivFapId are not equivalent.
        CPPUNIT_ASSERT(!longerEquivFapId.IsEquivalentTo(longerButNotEquivFapId));
        CPPUNIT_ASSERT(!longerButNotEquivFapId.IsEquivalentTo(longerEquivFapId));

        // And normalFapId and longerButNotEquivFapId are not equivalent either.
        CPPUNIT_ASSERT(!normalFapId.IsEquivalentTo(longerButNotEquivFapId));
        CPPUNIT_ASSERT(!longerButNotEquivFapId.IsEquivalentTo(normalFapId));

        fflush(stdout);
    }

protected:

private:

};

#endif
