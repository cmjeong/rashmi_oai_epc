///////////////////////////////////////////////////////////////////////////////
//
// FiniteSerialisableFileStore.h
//
// Manage a set of files for storing and retrieving serialisable objects in
// a way that allows us to limit the number that are stored to at least
// the past N while maintaining file integrity at all times.
//
// If any problems are encountered reading existing files then they will be
// deleted and recreated empty.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __FiniteSerialisableFileStore_h_
#define __FiniteSerialisableFileStore_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <system/SerialisableFileStore.h>
#include <system/Filename.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class FiniteSerialisableFileStore : public SerialisableFactory // Derived class has to implement this for the object types that are stored.
{
public:

    //friend class FiniteSerialisableFileStoreTest;

    // Constants

    /**
     * The number of files to use.
     */
    static const u8 NUM_STORE_FILES = 2;

    /**
     * Constructor.
     *
     * \param logFileNameStem Path and file name stem to log file.
     * \param minNumObjects   Minimum number of objects to be stored.
     */
    FiniteSerialisableFileStore(const char * logFileNameStem, u32 minNumObjects);

    virtual ~FiniteSerialisableFileStore();

    /**
     * Write object to file.
     */
    virtual void WriteObject(const Serialisable& object);

    /**
     * Open log file, read any existing objects so we know how many
     * there are and can initialise count of objects and next sequence number.
     */
    virtual void StartLogging();

    /**
     * Close the file(s).
     */
    virtual void StopLogging();

    /**
     * Read all objects, oldest first, and call HandleObjectRead().
     */
    virtual void ReadAllObjects();

protected:
    /**
     * Hook for handling objects read from file(s) e.g. when ReadAllObjects() is called.
     */
    virtual void HandleObjectRead(const shared_ptr<Serialisable> object) {};

private:

    /**
     * Count objects in (open) file.  Will only count objects that
     * are successfully deserialised.  On failing to deserialise
     * it will assume that the end-of-file has been reached.
     *
     * \param objectFileStore File store to count objects in.
     * \param readResult      Returns result of last object read.
     *                        Should be READ_EOF if all is well.
     * \return Number of objects read from file.
     */
    u32 CountObjectsInFile(shared_ptr<SerialisableFileStore> objectFileStore,
                           SerialisableFileStore::ReadResult& readResult);

    /**
     * Get a file name based on the current file store index.
     * e.g. if current file is 1, file stem is mystore then file name
     * will be "mystore-1"
     */
    std::string GenerateStoreFileName(u8 fileIndex) const;

    /**
     * Close any open file and delete all possible files.
     * I.e. start from scratch!  Leaves all files closed.
     */
    void DeleteAll();

    /**
     * Delete all files and set object up to start logging
     * with empty files.
     */
    void StartLoggingFromScratch();

    /**
     * Log file name stem.  This will be appended with -0, -1 etc as we cycle
     * through files.
     */
    const Filename m_logFileNameStem;

    /**
     * The max number of objects stored in each file.
     */
    const u32 m_objectsPerFile;

    /**
     * File stores for events.
     * We maintain two files... when the first is full, we start on the other,
     * when that's full, we delete the first and start writing to that again.
     * On reading, we try both files and read the one with the lowest sequence
     * number in the first entry first then read the other file.
     */
    shared_ptr<SerialisableFileStore> m_objectFileStore;

    /**
     * Which file are we currently writing to?
     */
    u8 m_currentFileStoreIndex;

    /**
     * Number of objects stored in the current log file.
     */
    u32 m_objectCountCurrentFile;

};

}

#endif
