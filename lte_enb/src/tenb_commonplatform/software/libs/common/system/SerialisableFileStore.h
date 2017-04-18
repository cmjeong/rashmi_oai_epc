///////////////////////////////////////////////////////////////////////////////
//
// SerialisableFileStore.h
//
// Read and write serialisable objects from/to a binary file.
// Objects are written to file with the following format:
//    Bytes 0-3: Magic delimiter 0x5E1A115A (a bit like SErIALISAtion)
//    Bytes 4-7: Serialisation ID (be sure this doesn't change between s/w releases!)
//    Bytes 8-9: Serialised data len in bytes.
//    Bytes 10+: Serialised data as written by Serialise() function.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __SerialisableFileStore_h_
#define __SerialisableFileStore_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>

#include <boost/shared_ptr.hpp>
#include <system/BinaryFile.h>
#include <system/SerialisableFactory.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

using namespace boost;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class SerialisableFileStore : public BinaryFile
{
public:
    // Constants
    static const u32 MAX_SERIALISED_DATA_LEN = 4096;
    static const u32 MAGIC_DELIMITER = 0x5E1A115A;  // SErIALISAtion;
    static const u32 OBJECT_HEADER_LEN = 10; // 4 bytes magic number delimiter, 4 bytes serialisation id, 2 bytes length

    // Typedefs
    typedef enum
    {
        READ_OK = 0,
        READ_EOF,
        READ_ERROR // E.g. invalid header, wrong length serialised data, failed to deserialise...
    } ReadResult;

    /**
     * Construct with file path and name.
     * Doesn't open the file at this point.
     *
     * \param fileName File path and name.
     */
    SerialisableFileStore(const char * fileName, SerialisableFactory& serialisableFactory, bool flushAndSyncEveryWrite);
    virtual ~SerialisableFileStore();

    /**
     * Write object to the end of the file.
     */
    bool WriteObject(const Serialisable& objectToWrite);

    /**
     * Read object from the file at the current read position.
     *
     * \param readResult Returns the result of the read.  READ_OK and READ_EOF
     *                   are normal but READ_EOF occurs after a previous read
     *                   of the last object so the returned object pointer will
     *                   be NULL in this case.
     * \return Pointer to deserialised object read from file.  NULL if no object
     *         available due to read error or EOF.
     */
    shared_ptr<Serialisable> ReadObject(ReadResult& readResult);

private:
    /**
     * Factory for creating a Serialisable object from file data.
     */
    SerialisableFactory& m_serialisableFactory;

    /**
     * If true then we'll flush and sync on every object write to file.
     */
    bool m_flushAndSyncEveryWrite;

};

}

#endif
