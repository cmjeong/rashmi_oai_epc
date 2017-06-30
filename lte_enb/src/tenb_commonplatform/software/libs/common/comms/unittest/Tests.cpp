///////////////////////////////////////////////////////////////////////////////
//
// Tests.cpp
//
// Contains the function that exposes the set of unit tests contained in this
// shared library to the unit test runner application.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <cppunit/TestSuite.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "IPv4AddressTest.h"
#include "SimplePDUTest.h"
#include "ProtocolStackTest.h"
#include "TcpSocketTest.h"
#include "UdpSocketTest.h"
#include "UdpSocketUsingSelectorTest.h"
#include "TcpClientLayerTest.h"

///////////////////////////////////////////////////////////////////////////////
// Functions
///////////////////////////////////////////////////////////////////////////////

extern "C" CppUnit::Test* GetTests();
CppUnit::Test* GetTests()
{
    CppUnit::TestSuite* suite = new CppUnit::TestSuite("Common comms library unit tests");

    suite->addTest( IPv4AddressTest::GetSuite() );
    suite->addTest( new SimplePDUTest() );
    suite->addTest( new ProtocolStackTest() );
    suite->addTest( new TcpSocketTest() );
    suite->addTest( new TcpClientLayerTest() );
    suite->addTest( new UdpSocketTest() );
    suite->addTest( new UdpSocketUsingSelectorTest() );

    return suite;
}
