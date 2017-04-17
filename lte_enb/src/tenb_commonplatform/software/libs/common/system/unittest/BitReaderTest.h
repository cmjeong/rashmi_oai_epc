///////////////////////////////////////////////////////////////////////////////
//
// BitReaderTest.h
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __BitReaderTest_h_
#define __BitReaderTest_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include <cppunit/TestCase.h>

#include <system/Trace.h>

#include <system/BitReader.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Test Cases
///////////////////////////////////////////////////////////////////////////////

class BitReaderTest : public CppUnit::TestCase
{
public:
    void runTest()
    {
        cout << endl << endl
             << "**********************" << endl
             << "BitReaderTest tests" << endl
             << "**********************" << endl << endl;

        TRACE_MSG("Starting BitReader tests");

        // Test data array
        u8 data[8] = { 0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0 };

        BitReader bits(data, 7, (sizeof(data) << 3));
        u32 thirty2;

        CPPUNIT_ASSERT_MESSAGE("Checking read of 5 bits...", bits.ReadBits(5, thirty2));
        CPPUNIT_ASSERT_MESSAGE("Checking 5 bit contents...", thirty2 == 0x2);
        CPPUNIT_ASSERT_MESSAGE("Checking bits remaining...", bits.BitsRemaining() == ((sizeof(data) << 3)-5));
        CPPUNIT_ASSERT_MESSAGE("Checking read of 4 bits...", bits.ReadBits(4, thirty2));
        CPPUNIT_ASSERT_MESSAGE("Checking 4 bit contents...", thirty2 == 0x4);
        CPPUNIT_ASSERT_MESSAGE("Checking bits remaining...", bits.BitsRemaining() == ((sizeof(data) << 3)-9));
        CPPUNIT_ASSERT_MESSAGE("Checking read of 25 bits...", bits.ReadBits(25, thirty2));
        CPPUNIT_ASSERT_MESSAGE("Checking 25 bit contents...", thirty2 == 0x0d159e2);
        CPPUNIT_ASSERT_MESSAGE("Checking bits remaining...", bits.BitsRemaining() == ((sizeof(data) << 3)-34));
        CPPUNIT_ASSERT_MESSAGE("Checking read of 1 bit...", bits.ReadBits(1, thirty2));
        CPPUNIT_ASSERT_MESSAGE("Checking 1 bit contents...", thirty2 == 0x0);
        CPPUNIT_ASSERT_MESSAGE("Checking bits remaining...", bits.BitsRemaining() == ((sizeof(data) << 3)-35));
        CPPUNIT_ASSERT_MESSAGE("Checking read of 1 bit...", bits.ReadBits(1, thirty2));
        CPPUNIT_ASSERT_MESSAGE("Checking 1 bit contents...", thirty2 == 0x1);
        CPPUNIT_ASSERT_MESSAGE("Checking bits remaining...", bits.BitsRemaining() == ((sizeof(data) << 3)-36));
        CPPUNIT_ASSERT_MESSAGE("Checking read of 1 bit...", bits.ReadBits(1, thirty2));
        CPPUNIT_ASSERT_MESSAGE("Checking 1 bit contents...", thirty2 == 0x1);
        CPPUNIT_ASSERT_MESSAGE("Checking bits remaining...", bits.BitsRemaining() == ((sizeof(data) << 3)-37));

        // Rewind
        bits.ResetReader();
        CPPUNIT_ASSERT_MESSAGE("Checking bits remaining...", bits.BitsRemaining() == (sizeof(data) << 3));
        CPPUNIT_ASSERT_MESSAGE("Checking read of 8 bits...", bits.ReadBits(8, thirty2));
        CPPUNIT_ASSERT_MESSAGE("Checking 8 bit contents...", thirty2 == 0x12);
        CPPUNIT_ASSERT_MESSAGE("Checking bits remaining...", bits.BitsRemaining() == ((sizeof(data) << 3)-8));

        // Check skipping forward
        bits.ResetReader();
        CPPUNIT_ASSERT_MESSAGE("Checking bits remaining...", bits.BitsRemaining() == (sizeof(data) << 3));
        bits.SkipBits(35);
        CPPUNIT_ASSERT_MESSAGE("Checking bits remaining...", bits.BitsRemaining() == ((sizeof(data) << 3)-35));
        CPPUNIT_ASSERT_MESSAGE("Checking read of 11 bits...", bits.ReadBits(11, thirty2));
        CPPUNIT_ASSERT_MESSAGE("Checking 11 bit contents...", thirty2 == 0x6af);
        CPPUNIT_ASSERT_MESSAGE("Checking bits remaining...", bits.BitsRemaining() == ((sizeof(data) << 3)-46));
        bits.ResetReader();
        bits.SkipBits(6);
        CPPUNIT_ASSERT_MESSAGE("Checking read of 3 bits...", bits.ReadBits(3, thirty2));
        CPPUNIT_ASSERT_MESSAGE("Checking 3 bit contents...", thirty2 == 0x4);
        CPPUNIT_ASSERT_MESSAGE("Checking bits remaining...", bits.BitsRemaining() == ((sizeof(data) << 3)-9));

        // Check starting from not bit 7
        BitReader bits2(data, 3, ((sizeof(data) << 3) - 4));
        CPPUNIT_ASSERT_MESSAGE("Checking read of 9 bits...", bits2.ReadBits(9, thirty2));
        CPPUNIT_ASSERT_MESSAGE("Checking 9 bit contents...", thirty2 == 0x046);
        CPPUNIT_ASSERT_MESSAGE("Checking bits remaining...", bits2.BitsRemaining() == ((sizeof(data) << 3)-13));

        // Check 8 bit read
        u8 eight;
        bits.ResetReader();
        CPPUNIT_ASSERT_MESSAGE("Checking bits remaining...", bits.BitsRemaining() == (sizeof(data) << 3));
        CPPUNIT_ASSERT_MESSAGE("Checking read of 8 bits...", bits.ReadBits(8, eight));
        CPPUNIT_ASSERT_MESSAGE("Checking 8 bit contents...", eight == 0x12);
        CPPUNIT_ASSERT_MESSAGE("Checking bits remaining...", bits.BitsRemaining() == ((sizeof(data) << 3)-8));
        CPPUNIT_ASSERT_MESSAGE("Checking read of 8 bits...", bits.ReadBits(3, eight));
        CPPUNIT_ASSERT_MESSAGE("Checking 8 bit contents...", eight == 0x01);
        CPPUNIT_ASSERT_MESSAGE("Checking bits remaining...", bits.BitsRemaining() == ((sizeof(data) << 3)-11));

        // Check boolean bit test.
        bool bitTest;
        bits.ResetReader();
        CPPUNIT_ASSERT_MESSAGE("Checking bits remaining...", bits.BitsRemaining() == (sizeof(data) << 3));
        bits.SkipBits(3);
        CPPUNIT_ASSERT_MESSAGE("Checking read of bool  ...", bits.ReadBit(bitTest));
        CPPUNIT_ASSERT_MESSAGE("Checking 1 bit contents...", bitTest == true);
        CPPUNIT_ASSERT_MESSAGE("Checking read of bool  ...", bits.ReadBit(bitTest));
        CPPUNIT_ASSERT_MESSAGE("Checking 1 bit contents...", bitTest == false);

        // Check 32 bit peak
        bits.ResetReader();
        CPPUNIT_ASSERT_MESSAGE("Checking bits remaining...",  bits.BitsRemaining() == (sizeof(data) << 3));
        CPPUNIT_ASSERT_MESSAGE("Checking read of 12 bits...", bits.ReadBits(12, thirty2));
        CPPUNIT_ASSERT_MESSAGE("Checking 12 bit contents...", thirty2 == 0x123);
        CPPUNIT_ASSERT_MESSAGE("Checking bits remaining...",  bits.BitsRemaining() == ((sizeof(data) << 3)-12));
        CPPUNIT_ASSERT_MESSAGE("Checking peak of 11 bits...", bits.PeakBits(11, thirty2));
        CPPUNIT_ASSERT_MESSAGE("Checking 11 bit contents...", thirty2 == 0x22b);
        CPPUNIT_ASSERT_MESSAGE("Checking bits remaining...",  bits.BitsRemaining() == ((sizeof(data) << 3)-12));
        CPPUNIT_ASSERT_MESSAGE("Checking read of 7 bits...",  bits.ReadBits(7, thirty2));
        CPPUNIT_ASSERT_MESSAGE("Checking 11 bit contents...", thirty2 == 0x22);
        CPPUNIT_ASSERT_MESSAGE("Checking bits remaining...",  bits.BitsRemaining() == ((sizeof(data) << 3)-19));

        TRACE_MSG("BitReader tests completed");

        fflush(stdout);
    }

protected:

private:

};

#endif
