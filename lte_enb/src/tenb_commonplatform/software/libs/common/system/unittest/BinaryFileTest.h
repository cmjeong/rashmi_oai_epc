///////////////////////////////////////////////////////////////////////////////
//
// BinaryFileTest.h
//
// Unit tests for BinaryFile class.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __BinaryFileTest_h_
#define __BinaryFileTest_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include <cppunit/TestCase.h>

#include <3waytypes.h>
#include <system/Trace.h>
#include <system/BinaryFile.h>

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class BinaryFileTest : public CppUnit::TestCase
{
public:
    void runTest()
    {
        cout << endl << endl
             << "****************" << endl
             << "BinaryFile tests" << endl
             << "****************" << endl << endl;

        TRACE_MSG("Constructing binaryFile.");

        BinaryFile binaryFile("./testbinaryfile");

        // Make sure we start with fresh file.
        binaryFile.Delete();

        TRACE_MSG("Opening file.");
        bool success = binaryFile.Open();
        CPPUNIT_ASSERT_MESSAGE("Check file opens OK", success == true);

        // Write some data.
        TRACE_MSG("Writing data.");
        TRACE("  File pos before append", binaryFile.GetFilePos());
        u8 buff[] = { 1,2,3,4,5,6,7,8,9 };
        success = binaryFile.AppendData(buff, sizeof(buff));
        TRACE("  File pos after append", binaryFile.GetFilePos());
        CPPUNIT_ASSERT_MESSAGE("Check 1st AppendData worked", success == true);

        // Write some more data.
        TRACE_MSG("Writing more data.");
        TRACE("  File pos before append", binaryFile.GetFilePos());
        u8 buff2[] = { 10,11,12 };
        success = binaryFile.AppendData(buff2, sizeof(buff2));
        CPPUNIT_ASSERT_MESSAGE("Check 2nd AppendData worked", success == true);
        TRACE("  File pos after append", binaryFile.GetFilePos());

        // Close and re-open file.
        TRACE_MSG("Closing and reopening.");
        TRACE("  File pos before", binaryFile.GetFilePos());
        binaryFile.Close();
        success = binaryFile.Open();
        TRACE("  File pos after", binaryFile.GetFilePos());
        CPPUNIT_ASSERT_MESSAGE("Check file closed then re-opened OK", success == true);

        // Read data.
        TRACE_MSG("Reading data.");
        TRACE("  File pos before read", binaryFile.GetFilePos());
        u8 readBuffer[1024];
        u32 bytesRead = binaryFile.ReadData(readBuffer, 5);
        CPPUNIT_ASSERT_MESSAGE("Check num bytes read", bytesRead == 5);
        CPPUNIT_ASSERT_MESSAGE("Check byte value [0] read OK", readBuffer[0] == 1);
        CPPUNIT_ASSERT_MESSAGE("Check byte value [1] read OK", readBuffer[1] == 2);
        CPPUNIT_ASSERT_MESSAGE("Check byte value [2] read OK", readBuffer[2] == 3);
        CPPUNIT_ASSERT_MESSAGE("Check byte value [3] read OK", readBuffer[3] == 4);
        CPPUNIT_ASSERT_MESSAGE("Check byte value [4] read OK", readBuffer[4] == 5);
        TRACE("  File pos after 1st read", binaryFile.GetFilePos());

        bytesRead = binaryFile.ReadData(readBuffer, 7);
        CPPUNIT_ASSERT_MESSAGE("Check num bytes read", bytesRead == 7);
        CPPUNIT_ASSERT_MESSAGE("Check byte value [0] read OK", readBuffer[0] == 6);
        CPPUNIT_ASSERT_MESSAGE("Check byte value [1] read OK", readBuffer[1] == 7);
        CPPUNIT_ASSERT_MESSAGE("Check byte value [2] read OK", readBuffer[2] == 8);
        CPPUNIT_ASSERT_MESSAGE("Check byte value [3] read OK", readBuffer[3] == 9);
        CPPUNIT_ASSERT_MESSAGE("Check byte value [4] read OK", readBuffer[4] == 10);
        CPPUNIT_ASSERT_MESSAGE("Check byte value [5] read OK", readBuffer[5] == 11);
        CPPUNIT_ASSERT_MESSAGE("Check byte value [6] read OK", readBuffer[6] == 12);
        TRACE("  File pos after 2nd read", binaryFile.GetFilePos());

        // Rewind and read first one again.
        TRACE_MSG("Rewinding and reading again.");
        TRACE("  File pos before rewind", binaryFile.GetFilePos());
        binaryFile.Rewind();
        TRACE("  File pos after rewind", binaryFile.GetFilePos());
        bytesRead = binaryFile.ReadData(readBuffer, 5);
        CPPUNIT_ASSERT_MESSAGE("Check num bytes read", bytesRead == 5);
        CPPUNIT_ASSERT_MESSAGE("Check byte value [0] read OK", readBuffer[0] == 1);
        CPPUNIT_ASSERT_MESSAGE("Check byte value [1] read OK", readBuffer[1] == 2);
        CPPUNIT_ASSERT_MESSAGE("Check byte value [2] read OK", readBuffer[2] == 3);
        CPPUNIT_ASSERT_MESSAGE("Check byte value [3] read OK", readBuffer[3] == 4);
        CPPUNIT_ASSERT_MESSAGE("Check byte value [4] read OK", readBuffer[4] == 5);
        TRACE("  File pos after read", binaryFile.GetFilePos());

        // Append some more data - our file pointer is mid-file but this will move it to the end.
        TRACE_MSG("Appending more data with read position mid-file.");
        TRACE("  File pos before append", binaryFile.GetFilePos());
        u8 buff3[] = { 13,14,15 };
        success = binaryFile.AppendData(buff3, sizeof(buff3));
        CPPUNIT_ASSERT_MESSAGE("Check 3rd AppendData worked", success == true);
        TRACE("  File pos after append", binaryFile.GetFilePos());

        TRACE_MSG("Now rewind and read all the data and check OK.");
        binaryFile.Rewind();
        CPPUNIT_ASSERT_MESSAGE("Check EOF not set", binaryFile.GetEof() == false);
        TRACE("  File pos after rewind", binaryFile.GetFilePos());
        bytesRead = binaryFile.ReadData(readBuffer, 15);
        CPPUNIT_ASSERT_MESSAGE("Check num bytes read", bytesRead == 15);
        CPPUNIT_ASSERT_MESSAGE("Check byte value [0] read OK", readBuffer[0] == 1);
        CPPUNIT_ASSERT_MESSAGE("Check byte value [1] read OK", readBuffer[1] == 2);
        CPPUNIT_ASSERT_MESSAGE("Check byte value [2] read OK", readBuffer[2] == 3);
        CPPUNIT_ASSERT_MESSAGE("Check byte value [3] read OK", readBuffer[3] == 4);
        CPPUNIT_ASSERT_MESSAGE("Check byte value [4] read OK", readBuffer[4] == 5);
        CPPUNIT_ASSERT_MESSAGE("Check byte value [5] read OK", readBuffer[5] == 6);
        CPPUNIT_ASSERT_MESSAGE("Check byte value [6] read OK", readBuffer[6] == 7);
        CPPUNIT_ASSERT_MESSAGE("Check byte value [7] read OK", readBuffer[7] == 8);
        CPPUNIT_ASSERT_MESSAGE("Check byte value [8] read OK", readBuffer[8] == 9);
        CPPUNIT_ASSERT_MESSAGE("Check byte value [9] read OK", readBuffer[9] == 10);
        CPPUNIT_ASSERT_MESSAGE("Check byte value [10] read OK", readBuffer[10] == 11);
        CPPUNIT_ASSERT_MESSAGE("Check byte value [11] read OK", readBuffer[11] == 12);
        CPPUNIT_ASSERT_MESSAGE("Check byte value [12] read OK", readBuffer[12] == 13);
        CPPUNIT_ASSERT_MESSAGE("Check byte value [13] read OK", readBuffer[13] == 14);
        CPPUNIT_ASSERT_MESSAGE("Check byte value [14] read OK", readBuffer[14] == 15);
        TRACE("  File pos after read", binaryFile.GetFilePos());

        // EOF checks.
        TRACE_MSG("EOF checks.");
        binaryFile.ReadData(readBuffer, 1);
        CPPUNIT_ASSERT_MESSAGE("Check EOF set", binaryFile.GetEof() == true);
        binaryFile.Rewind();
        CPPUNIT_ASSERT_MESSAGE("Check EOF not set", binaryFile.GetEof() == false);

        TRACE_MSG("Closing file.");
        binaryFile.Close();

        TRACE_MSG("Deleting file.");
        binaryFile.Delete();

        fflush(stdout);
    }

private:
};

#endif
