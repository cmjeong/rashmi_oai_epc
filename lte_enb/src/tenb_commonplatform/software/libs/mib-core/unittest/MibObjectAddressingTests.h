///////////////////////////////////////////////////////////////////////////////
//
// MibObjectAddressingTests.h
//
// Unit tests for DN and RDN.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MibObjectAddressingTests_h_
#define __MibObjectAddressingTests_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <sstream>

#include <cppunit/TestCase.h>

#include <system/Trace.h>
#include <mib-common/MibDN.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MibManagedObjects.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Test Cases
///////////////////////////////////////////////////////////////////////////////

class MibObjectAddressingTests : public CppUnit::TestCase
{
public:
    void runTest()
    {
        cout << endl << endl
             << "***************************" << endl
             << "MIB object addressing tests" << endl
             << "***************************" << endl << endl;

        TRACE_MSG("Construct a couple of RDNs");
        MibRDN rdn1(MIB_OBJECT_CLASS_FAP, 0);
        TRACE("rdn1", rdn1.ToString());
        CPPUNIT_ASSERT(rdn1.ToString().compare("FAP.0") == 0);

        MibRDN rdn2(MIB_OBJECT_CLASS_RADIO, 0);
        TRACE("rdn2", rdn2.ToString());
        CPPUNIT_ASSERT(rdn2.ToString().compare("RADIO.0") == 0);

        TRACE_MSG("Validate 2 RDNs don't match.");
        CPPUNIT_ASSERT(rdn1 != rdn2);

        TRACE_MSG("Validate first RDN is 'less than' second.");
        CPPUNIT_ASSERT(rdn1 < rdn2);
        CPPUNIT_ASSERT(!(rdn1 > rdn2)); // Check both operators!

        TRACE_MSG("Validate == for 2 RDNs that are the same.");
        MibRDN rdn3(MIB_OBJECT_CLASS_FAP, 0);
        CPPUNIT_ASSERT(rdn1 == rdn3);

        TRACE_MSG("Build up a DN and check it.");
        MibDN dn1;
        dn1.push_back(rdn1);
        dn1.push_back(rdn2);

        TRACE("dn1", dn1.ToString());
        CPPUNIT_ASSERT(dn1.ToString().compare("FAP.0.RADIO.0") == 0);

        fflush(stdout);
    }

protected:

private:

};

#endif
