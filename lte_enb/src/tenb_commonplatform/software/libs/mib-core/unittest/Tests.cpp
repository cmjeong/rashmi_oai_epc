///////////////////////////////////////////////////////////////////////////////
//
// Tests.cpp
//
// Contains the function that exposes the set of unit tests contained in this
// shared library to the unit test runner application.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <cppunit/TestSuite.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MibAttributeTests.h"
#include "MibObjectAddressingTests.h"
#include "IniFormatNvStoreTests.h"
#include "UpgradeNvStoreTests.h"
#include "MibObjectTests.h"
#include "MibManagerTests.h"
#include "MibSubscriptionManagerTests.h"

///////////////////////////////////////////////////////////////////////////////
// Functions
///////////////////////////////////////////////////////////////////////////////

extern "C" CppUnit::Test* GetTests();
CppUnit::Test* GetTests()
{
    CppUnit::TestSuite* suite = new CppUnit::TestSuite("MIB library unit tests");

    suite->addTest( new BasicMibAttributeTest() );
    suite->addTest( new MibObjectAddressingTests() );
    suite->addTest( new IniFormatNvStoreTests() );
    suite->addTest( new UpgradeNvStoreTests() );
    suite->addTest( new MibObjectTests() );
    suite->addTest( new MibManagerTests() );
    suite->addTest( new MibSubscriptionManagerTests() );

    return suite;
}
