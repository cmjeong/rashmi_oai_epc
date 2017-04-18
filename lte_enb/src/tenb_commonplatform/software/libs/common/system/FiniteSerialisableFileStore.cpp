///////////////////////////////////////////////////////////////////////////////
//
// FiniteSerialisableFileStore.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>

#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "FiniteSerialisableFileStore.h"

using namespace std;
using namespace threeway;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

FiniteSerialisableFileStore::FiniteSerialisableFileStore(const char * logFileNameStem, u32 minNumObjects) :
    m_logFileNameStem(logFileNameStem),
    m_objectsPerFile(minNumObjects),
    m_currentFileStoreIndex(0),
    m_objectCountCurrentFile(0)
{
    ENTER();

    TRACE_PRINTF("FiniteSerialisableFileStore(logFileNameStem=%s, minNumObjects=%"PRIu32")", logFileNameStem, minNumObjects);

    EXIT();
}

FiniteSerialisableFileStore::~FiniteSerialisableFileStore()
{
    ENTER();

    // Files will be closed as shared pointers go out of scope.

    EXIT();
}

void FiniteSerialisableFileStore::WriteObject(const Serialisable& object)
{
    ENTER();

    if(m_objectFileStore != NULL)
    {
        // Write to current event store.
        m_objectFileStore->WriteObject(object);

        // Increase count of alarm events.
        m_objectCountCurrentFile++;

        // See if we need to change file.
        if((m_objectCountCurrentFile % m_objectsPerFile) == 0)
        {
            // Move to next file.
            m_currentFileStoreIndex = (m_currentFileStoreIndex + 1) % NUM_STORE_FILES;

            // Close current file and create object for new one then delete it to
            // ensure we start with an empty file.
            // reset() will destroy old object which will close the file.
            string storeFileName = GenerateStoreFileName(m_currentFileStoreIndex);
            m_objectFileStore.reset(new SerialisableFileStore(storeFileName.c_str(), *this, true /* flush and sync each write */));

            // Delete the current version.
            m_objectFileStore->Delete();

            // And now open the new one.
            if(!m_objectFileStore->Open())
            {
                TRACE_PRINTF_LEV(TRACE_CRITICAL, "FiniteSerialisableFileStore::WriteObject(): Failed to open %s", storeFileName.c_str());
                m_objectFileStore.reset();
            }
        }
    }

    EXIT();
}

void FiniteSerialisableFileStore::StartLogging()
{
    ENTER();

    // Preconditions.
    // Check we're not already logging.
    RSYS_ASSERT(m_objectFileStore == NULL);

    TRACE_MSG("FiniteSerialisableFileStore::StartLogging()");

    // Assume we'll start logging to the first file until we find out otherwise.
    m_currentFileStoreIndex = 0;

    // Start with the first file... we're going to cycle through them 'til we find
    // one that is not full.  That's the one we start appending to.
    u8 fileStoreIndex = 0;

    // We're going to look for the file that we should start appending new objects
    // to i.e. the 'current' file.
    bool foundCurrentFile = false;

    // Now start reading in all objects from each file in turn.
    string fileName;
    for(u8 i = 0; i < NUM_STORE_FILES; i++)
    {
        // Open each file in turn and read all the objects from it.
        // Stop on first file that has fewer than expected number of objects
        // including being empty.  We'll start appending new objects to that file.

        // Create object for managing file with current index.
        fileName = GenerateStoreFileName(fileStoreIndex);
        m_objectFileStore.reset(new SerialisableFileStore(fileName.c_str(), *this, true /* flush and sync each write */));

        // Try opening it.
        if(m_objectFileStore->Open())
        {
            // Count objects in this file.
            SerialisableFileStore::ReadResult readResult;
            u32 numObjectsInFile = CountObjectsInFile(m_objectFileStore, readResult);

            // Who knows what happened... Close and delete all files and
            // start from scratch with a fresh file.
            if(readResult != SerialisableFileStore::READ_EOF)
            {
                TRACE_PRINTF_LEV(TRACE_WARNING,
                                 "%s(): Failed to count objects in file %s, readResult=%" PRIu32,
                                 __FUNCTION__, fileName.c_str(), (u32)readResult);

                StartLoggingFromScratch();
                RETURN_VOID();
            }

            // If num objects in this file is less that the max we expect then
            // we've found the one we want.  There should always be a file that
            // matches this criteria - once a file gets full we always start a
            // new (empty) one.  There is a possibility that we fill one file
            // then can't open the next one... this is handled below.
            if(numObjectsInFile < m_objectsPerFile)
            {
                foundCurrentFile = true;
                m_objectCountCurrentFile = numObjectsInFile;
                m_currentFileStoreIndex = fileStoreIndex;
                break;
            }
        }
        else
        {
            // TODO: Decide on recovery action?  Probably shouldn't assert
            // as this is probably not a coding bug.  Could raise an alarm but
            // for some uses we won't be in a position to raise an alarm unless
            // we queue alarms for reporting when we get a management connection.
            // Also the alarm log is stored using this class!  Perhaps we
            // return a result bool/enum?
            TRACE_PRINTF_LEV(TRACE_CRITICAL, "FiniteSerialisableFileStore::StartLogging(): Failed to open %s", fileName.c_str());
        }

        // Move to the next file, wrapping if necessary.
        fileStoreIndex = (fileStoreIndex + 1) % NUM_STORE_FILES;
    }

    if(!foundCurrentFile)
    {
        // Hmm, disaster recovery attempt required... let's just start with the
        // first index and try opening a new file.
        TRACE_PRINTF_LEV(TRACE_WARNING,
                         "%s(): Failed to find a file to start appending objects to... attempting recovery...",
                         __FUNCTION__);

        m_objectCountCurrentFile = 0;
        m_currentFileStoreIndex = 0;
        fileName = GenerateStoreFileName(m_currentFileStoreIndex);
        m_objectFileStore.reset(new SerialisableFileStore(fileName.c_str(), *this, true /* flush and sync each write */));

        // Delete it first to give ourselves the best chance of success.
        m_objectFileStore->Delete();

        // Try opening it...
        if(!m_objectFileStore->Open())
        {
            TRACE_PRINTF_LEV(TRACE_WARNING,
                             "%s(): Failed to find a file to start appending objects to... recovery attempt failed.",
                             __FUNCTION__);

            // Last gasp disaster recovery.
            StartLoggingFromScratch();
            RETURN_VOID();
        }
    }

    EXIT();
}

void FiniteSerialisableFileStore::StopLogging()
{
    ENTER();

    TRACE_MSG("FiniteSerialisableFileStore::StopLogging()");

    // Close the current log file.
    if(m_objectFileStore != NULL)
    {
        m_objectFileStore.reset(); // Will delete the object and therefore close the file and set pointer to NULL.
    }

    EXIT();
}

void FiniteSerialisableFileStore::ReadAllObjects()
{
    ENTER();

    // Preconditions.
    // Check we're not currently logging.
    RSYS_ASSERT(m_objectFileStore == NULL);

    TRACE_PRINTF("Reading all objects for file stem %s", m_logFileNameStem.c_str());

    // Start with the first file... we're going to cycle through them 'til we find
    // one that is not full.  The oldest is then the next one that has something in it.
    u8 newestFileIndex = 0;

    // Now start reading in all objects from each file in turn.
    string fileName;
    bool foundNewestFile = false;
    for(u8 i = 0; i < NUM_STORE_FILES; i++)
    {
        // Open each file in turn and read all the objects from it.

        // Create object for managing file with current index.
        fileName = GenerateStoreFileName(newestFileIndex);
        shared_ptr<SerialisableFileStore> searchFileStore(new SerialisableFileStore(fileName.c_str(), *this, true /* flush and sync each write */));

        // Try opening it.
        if(searchFileStore->Open())
        {
            // Count objects in this file.
            SerialisableFileStore::ReadResult readResult;
            u32 numObjectsInFile = CountObjectsInFile(searchFileStore, readResult);

            // As we are only reading objects at this point there is no
            // real benefit in taking drastic action if a read failed.
            // We'll log it and carry on.  When the client calls StartLogging()
            // we'll discover any problems and do some disaster recovery.
            if(readResult != SerialisableFileStore::READ_EOF)
            {
                TRACE_PRINTF_LEV(TRACE_WARNING,
                                 "%s(): Unexpected readResult=%" PRIu32 " when reading %s",
                                 __FUNCTION__, (u32)readResult, fileName.c_str());
            }

            // If num objects in this file is less that the max we expect then
            // we've found the newest one.  There should always be a file that
            // matches this criteria - once a file gets full we always start a
            // new (empty) one.  There is a possibility that we fill one file
            // then can't open the next one... this is handled below.
            if(numObjectsInFile < m_objectsPerFile)
            {
                foundNewestFile = true;
                break;
            }
        }
        else
        {
            TRACE_PRINTF_LEV(TRACE_CRITICAL, "FiniteSerialisableFileStore::ReadAllObjects(): Failed to open %s", fileName.c_str());
        }

        // Move to the next file, wrapping if necessary.
        newestFileIndex = (newestFileIndex + 1) % NUM_STORE_FILES;
    }


    if(foundNewestFile)
    {
        TRACE_PRINTF("  Found newest file index %u", newestFileIndex);

        // newestFileIndex now points at the latest log file.
        // But we want to start reading from the oldest log file...
        // Search through starting with the file after the newest
        // until we find our first full file (must be the oldest) or
        // wrap back to the newest one (which must then be the only one).
        u8 oldestFileIndex = (newestFileIndex + 1) % NUM_STORE_FILES;
        while(oldestFileIndex != newestFileIndex)
        {
            fileName = GenerateStoreFileName(oldestFileIndex);
            shared_ptr<SerialisableFileStore> searchFileStore(new SerialisableFileStore(fileName.c_str(), *this, true /* flush and sync each write */));

            // Try opening it.
            if(searchFileStore->Open())
            {
                // Count objects in this file.
                SerialisableFileStore::ReadResult readResult;
                u32 numObjectsInFile = CountObjectsInFile(searchFileStore, readResult);

                // As we are only reading objects at this point there is no
                // real benefit in taking drastic action if a read failed.
                // We'll log it and carry on.  When the client calls StartLogging()
                // we'll discover any problems and do some disaster recovery.
                if(readResult != SerialisableFileStore::READ_EOF)
                {
                    TRACE_PRINTF_LEV(TRACE_WARNING,
                                     "%s(): Unexpected readResult=%" PRIu32 " when reading %s",
                                     __FUNCTION__, (u32)readResult, fileName.c_str());
                }

                if(numObjectsInFile == m_objectsPerFile)
                {
                    // We've found our first full one... must be oldest.
                    break;
                }
            }

            // Move to next file.
            oldestFileIndex = (oldestFileIndex + 1) % NUM_STORE_FILES;
        }

        TRACE_PRINTF("  Oldest file index %u", oldestFileIndex);

        // Either we've found the first full file or we've wrapped round
        // and are now pointing at the newest file.  Either way, it's the
        // oldest and we should start reading objects until we read from
        // a file that has fewer than the max expected or, as a safety
        // check, we wrap around.
        while(1)
        {
            fileName = GenerateStoreFileName(oldestFileIndex);
            shared_ptr<SerialisableFileStore> readFileStore(new SerialisableFileStore(fileName.c_str(), *this, true /* flush and sync each write */));

            TRACE_PRINTF("  Reading objects from %s", fileName.c_str());

            // Try opening it.
            u32 numObjects = 0;

            if(readFileStore->Open())
            {
                shared_ptr<Serialisable> object;
                bool finishedReading = false;

                while(!finishedReading)
                {
                    SerialisableFileStore::ReadResult readObjectResult;
                    object = readFileStore->ReadObject(readObjectResult);

                    // object could be NULL if is valid but not understood by this software.
                    if((object != NULL) && (readObjectResult == SerialisableFileStore::READ_OK))
                    {
                        numObjects++;
                        TRACE_PRINTF_LEV(TRACE_VERBOSE,"Read object %d from file: %s", numObjects, object->ToString().c_str());
                        HandleObjectRead(object);
                    }

                    if(readObjectResult != SerialisableFileStore::READ_OK)
                    {
                        // As we are only reading objects at this point there is no
                        // real benefit in taking drastic action if a read failed.
                        // We'll log it and carry on.  When the client calls StartLogging()
                        // we'll discover any problems and do some disaster recovery.
                        if(readObjectResult != SerialisableFileStore::READ_EOF)
                        {
                            TRACE_PRINTF_LEV(TRACE_WARNING,
                                             "%s(): Unexpected readResult=%" PRIu32 " when reading %s",
                                             __FUNCTION__, (u32)readObjectResult, fileName.c_str());
                        }

                        finishedReading = true;
                    }
                }
            }
            else
            {
                TRACE_PRINTF_LEV(TRACE_CRITICAL, "FiniteSerialisableFileStore::ReadAllObjects(): Failed to open %s", fileName.c_str());
                break;
            }

            if((numObjects < m_objectsPerFile) || (oldestFileIndex == newestFileIndex))
            {
                // We're done.
                break;
            }

            // Move to next file.
            oldestFileIndex = (oldestFileIndex + 1) % NUM_STORE_FILES;
        }
    }
    else
    {
        // Hmmm...
        TRACE_PRINTF_LEV(TRACE_CRITICAL, "FiniteSerialisableFileStore::ReadAllObjects(): Failed to find newest file.");
    }

    EXIT();
}

u32 FiniteSerialisableFileStore::CountObjectsInFile(shared_ptr<SerialisableFileStore> objectFileStore,
                                                    SerialisableFileStore::ReadResult& readResult)
{
    ENTER();

    // Preconditions.
    // File must be open.
    RSYS_ASSERT(objectFileStore != NULL);

    // Start off pessimistic...
    readResult = SerialisableFileStore::READ_ERROR;

    // Rewind to start of file.
    objectFileStore->Rewind();

    shared_ptr<Serialisable> object;
    bool finishedReading = false;
    u32 numObjects = 0;

    while(!finishedReading)
    {
        object = objectFileStore->ReadObject(readResult);

        // object could be NULL if is valid but not understood by this software.
        if((object != NULL) && (readResult == SerialisableFileStore::READ_OK))
        {
            numObjects++;
        }

        if(readResult != SerialisableFileStore::READ_OK)
        {
            finishedReading = true;
        }
    }

    RETURN(numObjects);
}

string FiniteSerialisableFileStore::GenerateStoreFileName(u8 fileIndex) const
{
    ENTER();

    Filename fileName(m_logFileNameStem);

    fileName.append("-");
    fileName.append(1, (char)('0' + fileIndex));

    RETURN(fileName);
}

void FiniteSerialisableFileStore::DeleteAll()
{
    ENTER();

    TRACE_PRINTF_LEV(TRACE_WARNING, "%s(): Deleting all files: %s*", __FUNCTION__, m_logFileNameStem.c_str());

    // Close any open file.
    if(m_objectFileStore != NULL)
    {
        m_objectFileStore.reset();
    }

    // Delete all possible files.
    for(u8 i = 0; i < NUM_STORE_FILES; i++)
    {
        // Create object for managing file with current index.
        string fileName = GenerateStoreFileName(i);
        BinaryFile fileToDelete(fileName.c_str());
        fileToDelete.Delete();
    }

    EXIT();
}

void FiniteSerialisableFileStore::StartLoggingFromScratch()
{
    ENTER();

    // Delete all files.
    DeleteAll();

    // Set up member vars to indicate starting from scratch.
    m_currentFileStoreIndex = 0;
    m_objectCountCurrentFile = 0;

    // Create a new file store at first index.
    string fileName = GenerateStoreFileName(0);
    m_objectFileStore.reset(new SerialisableFileStore(fileName.c_str(), *this, true /* flush and sync each write */));
    if(!m_objectFileStore->Open())
    {
        TRACE_PRINTF_LEV(TRACE_CRITICAL,
                         "%s(): Failed to open %s after disaster recovery",
                         __FUNCTION__, fileName.c_str());
        m_objectFileStore.reset();
    }

    EXIT();
}

}
