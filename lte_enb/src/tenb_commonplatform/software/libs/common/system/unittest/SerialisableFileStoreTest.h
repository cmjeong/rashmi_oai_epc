///////////////////////////////////////////////////////////////////////////////
//
// SerialisableFileStoreTest.h
//
// Unit tests for SerialisableFileStore class.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __SerialisableFileStoreTest_h_
#define __SerialisableFileStoreTest_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include <cppunit/TestCase.h>

#include <3waytypes.h>
#include <system/Trace.h>
#include <system/SerialisableFileStore.h>
#include <system/FiniteSerialisableFileStore.h>

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class TestSerialisableObject : public Serialisable
{
public:
    virtual u32 GetSerialisationId() const { return 0x1234; };
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const
    {
        *data++ = 7;
        *data++ = 6;
        *data++ = 5;
        return 3;
    }

    virtual bool DeSerialise(const u8* data, u32 dataLen)
    {
        RSYS_ASSERT(data[0] == 7);
        RSYS_ASSERT(data[1] == 6);
        RSYS_ASSERT(data[2] == 5);
        return true;
    }

    virtual std::string ToString() const
    {
        return "test object";
    }
};

class TestSerialisableObject2 : public Serialisable
{
public:
    virtual u32 GetSerialisationId() const { return 0x12341234; };
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const
    {
        RSYS_ASSERT(dataMaxBytes >= 2048);

        data[0] = 8;
        data[1] = 9;
        data[2] = 10;
        data[2047] = 243;

        return 2048;
    }

    virtual bool DeSerialise(const u8* data, u32 dataLen)
    {
        RSYS_ASSERT(data[0] == 8);
        RSYS_ASSERT(data[1] == 9);
        RSYS_ASSERT(data[2] == 10);
        RSYS_ASSERT(data[2047] == 243);
        return true;
    }

    virtual std::string ToString() const
    {
        return "test object";
    }
};

class TestSerialisableFactory : public SerialisableFactory
{
    virtual shared_ptr<Serialisable> GetSerialisable(u32 serialisationId,
                                                     const u8* serialisedData,
                                                     u32 serialisedDataLen)
    {
        shared_ptr<Serialisable> object;
        switch(serialisationId)
        {
            case 0x1234:
                object.reset(new TestSerialisableObject);
                break;
            case 0x12341234:
                object.reset(new TestSerialisableObject2);
                break;
        }
        return object;
    }

};

class SerialisableFileStoreTest : public CppUnit::TestCase
{
public:
    void runTest()
    {
        cout << endl << endl
             << "***************************" << endl
             << "SerialisableFileStore tests" << endl
             << "***************************" << endl << endl;

        TRACE_MSG("Constructing SerialisableFileStore.");

        TestSerialisableFactory factory;
        SerialisableFileStore fileStore("./testserialisablestore", factory, false /* no need to flush and sync each write */);

        // Make sure we start with fresh file.
        fileStore.Delete();

        TRACE_MSG("Opening file.");
        bool success = fileStore.Open();
        CPPUNIT_ASSERT_MESSAGE("Check file opens OK", success == true);

        // Write a serialisable object.
        TRACE_MSG("Writing 1st serialised object.");
        TestSerialisableObject objectToWrite;
        success = fileStore.WriteObject(objectToWrite);
        CPPUNIT_ASSERT_MESSAGE("Check 1st WriteObject worked", success == true);

        // Write another serialisable object.
        TRACE_MSG("Writing 2nd serialised object.");
        TestSerialisableObject2 objectToWrite2;
        success = fileStore.WriteObject(objectToWrite2);
        CPPUNIT_ASSERT_MESSAGE("Check 2nd WriteObject worked", success == true);

        // Close and re-open file.
        TRACE_MSG("Closing and reopening file.");
        fileStore.Close();
        success = fileStore.Open();
        CPPUNIT_ASSERT_MESSAGE("Check file closed then re-opened OK", success == true);

        // Read object.
        TRACE_MSG("Reading 1st object.");
        shared_ptr<Serialisable> objectRead;
        SerialisableFileStore::ReadResult readObjectResult;
        objectRead = fileStore.ReadObject(readObjectResult);
        CPPUNIT_ASSERT_MESSAGE("Check for successful read", readObjectResult == SerialisableFileStore::READ_OK);
        CPPUNIT_ASSERT_MESSAGE("Check read object ptr non-NULL", objectRead != NULL);
        CPPUNIT_ASSERT_MESSAGE("Check read object serialisation ID", objectRead->GetSerialisationId() == 0x1234);

        shared_ptr<TestSerialisableObject> testSerialisableObject = dynamic_pointer_cast<TestSerialisableObject>(objectRead);
        CPPUNIT_ASSERT_MESSAGE("Check object casts to TestSerialisableObject", testSerialisableObject != NULL);

        TRACE_MSG("Reading 2nd object.");
        objectRead = fileStore.ReadObject(readObjectResult);
        CPPUNIT_ASSERT_MESSAGE("Check for successful read", readObjectResult == SerialisableFileStore::READ_OK);
        CPPUNIT_ASSERT_MESSAGE("Check read object ptr non-NULL", objectRead != NULL);
        CPPUNIT_ASSERT_MESSAGE("Check read object serialisation ID", objectRead->GetSerialisationId() == 0x12341234);

        shared_ptr<TestSerialisableObject2> testSerialisableObject2 = dynamic_pointer_cast<TestSerialisableObject2>(objectRead);
        CPPUNIT_ASSERT_MESSAGE("Check object casts to TestSerialisableObject2", testSerialisableObject2 != NULL);

        TRACE_MSG("Reading 3rd object.  Should be EOF");
        objectRead = fileStore.ReadObject(readObjectResult);
        CPPUNIT_ASSERT_MESSAGE("Check for EOF read", readObjectResult == SerialisableFileStore::READ_EOF);
        CPPUNIT_ASSERT_MESSAGE("Check read object ptr NULL", objectRead == NULL);

        TRACE_MSG("Closing file.");
        fileStore.Close();

        TRACE_MSG("Deleting file.");
        fileStore.Delete();

        fflush(stdout);
    }

private:
};


/*
 * FiniteSerialisableFileStore tests
 */

class TestSerialisableObject3 : public Serialisable
{
public:
    virtual u32 GetSerialisationId() const { return 0x1235; };
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const
    {
        *data++ = 1;
        *data++ = 2;
        *data++ = 3;
        return 3;
    }

    virtual bool DeSerialise(const u8* data, u32 dataLen)
    {
        RSYS_ASSERT(data[0] == 1);
        RSYS_ASSERT(data[1] == 2);
        RSYS_ASSERT(data[2] == 3);
        return true;
    }

    virtual std::string ToString() const
    {
        return "test object 3";
    }
};

#define TEST_FINITE_STORE_STEM "./test-finite-store"
class TestFiniteSerialisableFileStore : public FiniteSerialisableFileStore
{
public:
    TestFiniteSerialisableFileStore() :
        FiniteSerialisableFileStore(TEST_FINITE_STORE_STEM, 2),
        m_numObjectsRead(0)
    {
    }

    virtual ~TestFiniteSerialisableFileStore() {};

    virtual boost::shared_ptr<Serialisable> GetSerialisable(
                                                u32 serialisationId,
                                                const u8* serialisedData,
                                                u32 serialisedDataLen
                                                           )
    {
        shared_ptr<Serialisable> object;
        switch(serialisationId)
        {
            case 0x1235:
                object.reset(new TestSerialisableObject3);
                break;
        }
        return object;
    }

    virtual void HandleObjectRead(const shared_ptr<Serialisable> object)
    {
        TRACE("Object", object->ToString());
        m_numObjectsRead++;
    }

    u32 GetNumObjectsRead() const { return m_numObjectsRead; }

    u32 m_numObjectsRead;
};

class FiniteSerialisableFileStoreTest : public CppUnit::TestCase
{
public:

    void runTest()
    {
        cout << endl << endl
             << "*********************************" << endl
             << "FiniteSerialisableFileStore tests" << endl
             << "*********************************" << endl << endl;

        TRACE_MSG("Constructing TestFiniteSerialisableFileStore.");

        // Make sure we start afresh.
        remove(TEST_FINITE_STORE_STEM "-0");
        remove(TEST_FINITE_STORE_STEM "-1");

        TestFiniteSerialisableFileStore finiteStore;
        finiteStore.StartLogging();

        // Write 7 serialisable objects.
        TestSerialisableObject3 objectToWrite;
        for(u32 i = 0; i < 7; i++)
        {
            TRACE_PRINTF("Writing serialised object num %" PRIu32 ".", i+1);
            finiteStore.WriteObject(objectToWrite);
        }

        // Close and re-open file.
        TRACE_MSG("Stopping logging.");
        finiteStore.StopLogging();

        // Read objects.
        TRACE_MSG("Read all objects.");
        finiteStore.ReadAllObjects();

        // We stored 7 objects but the max is 2 to 4.  In this case
        // we should have ended up with 1 full file (2 objects) and
        // 1 file with 1 object i.e. 3 total.
        CPPUNIT_ASSERT_MESSAGE("Check the correct number of objects were read", finiteStore.GetNumObjectsRead() == 3);

        // Now firkle with the file so it will fail to read.
        FILE* firstFile = fopen(TEST_FINITE_STORE_STEM "-0", "rb");
        u8 fileData[100];
        fread((void *)fileData, 1, 26 /* expected size */, firstFile);
        fclose(firstFile);

        firstFile = fopen(TEST_FINITE_STORE_STEM "-0", "wb");
        fileData[13] = 0; // Bugger up the 2nd object's magic delimiter.
        fwrite((const void *)&fileData, 1, 26, firstFile);
        fclose(firstFile);

        // Read objects.
        TRACE_MSG("Read all objects after firkling with first file.");
        finiteStore.ReadAllObjects();

        // We would expect to read a further 1 object before the dodgy
        // magic delimiter is read.
        CPPUNIT_ASSERT_MESSAGE("Check the correct number of objects were read", finiteStore.GetNumObjectsRead() == 4);

        // Now start logging again, we expect our files to be scrubbed and end up
        // with a single open file with no objects in it.
        finiteStore.StartLogging();
        finiteStore.WriteObject(objectToWrite);
        finiteStore.StopLogging();
        finiteStore.ReadAllObjects();
        CPPUNIT_ASSERT_MESSAGE("Check the correct number of objects were read", finiteStore.GetNumObjectsRead() == 5);


        fflush(stdout);
    }

private:
};

#endif
