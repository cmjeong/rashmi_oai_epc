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

#include "CliArgumentTest.h"
#include "BinaryFileTest.h"
#include "BitReaderTest.h"
#include "SerialisableFileStoreTest.h"
#include "AlarmTests.h"
#include "KpiTests.h"
#include "TimerEngineTest.h"
#include "TimeWrapTest.h"
#include "SerialisationUtilsTest.h"
#include "TraceTest.h"
#include "StringUtilsTest.h"
#include "HexStringTest.h"
#include "SoftwareReleaseTest.h"
#include "RegexTest.h"

///////////////////////////////////////////////////////////////////////////////
// Functions
///////////////////////////////////////////////////////////////////////////////

extern "C" CppUnit::Test* GetTests();
CppUnit::Test* GetTests()
{
    CppUnit::TestSuite* suite = new CppUnit::TestSuite("Common system library unit tests");

    suite->addTest( new TraceTest() );
    suite->addTest( new StringUtilsTest() );
    suite->addTest( new BitReaderTest() );
    suite->addTest( new CliArgumentTest() );
    suite->addTest( new BinaryFileTest() );
    suite->addTest( new SerialisableFileStoreTest() );
    suite->addTest( new FiniteSerialisableFileStoreTest() );
    suite->addTest( new AlarmEventTest() );
    suite->addTest( new AlarmEventLogTest() );
    suite->addTest( new ActiveAlarmsTest() );
    suite->addTest( new TimerEngineTest() );
    suite->addTest( new TimeWrapTest() );
    suite->addTest( new SerialisationUtilsTest() );
    suite->addTest( new KpiGroupTest() );
    suite->addTest( new KpiLogFileMgrTest() );
    suite->addTest( new HexStringTest() );
    suite->addTest( new SoftwareReleaseTest() );
    suite->addTest( new RegexTest() );

    return suite;
}
