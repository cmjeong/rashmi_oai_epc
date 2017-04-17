///////////////////////////////////////////////////////////////////////////////
//
// SerialisableFileStore.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Trace.h>
#include <system/NumberConversions.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "SerialisableFileStore.h"

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

SerialisableFileStore::SerialisableFileStore(const char * fileName, SerialisableFactory& serialisableFactory, bool flushAndSyncEveryWrite) :
    BinaryFile(fileName),
    m_serialisableFactory(serialisableFactory),
    m_flushAndSyncEveryWrite(flushAndSyncEveryWrite)
{
    ENTER();

    EXIT();
}

SerialisableFileStore::~SerialisableFileStore()
{
    ENTER();

    EXIT();
}

bool SerialisableFileStore::WriteObject(const Serialisable& objectToWrite)
{
    ENTER();

    TRACE("SerialisableFileStore::WriteObject()", objectToWrite.ToString().c_str());

    // Serialise the object into a local store, skipping the header we'll fill in later.
    u8 writeBuffer[MAX_SERIALISED_DATA_LEN + OBJECT_HEADER_LEN];
    s32 serialisedDataLen = objectToWrite.Serialise(&(writeBuffer[OBJECT_HEADER_LEN]), sizeof(writeBuffer) - OBJECT_HEADER_LEN);

    // Check length of serialised data.
    RSYS_ASSERT_PRINTF(serialisedDataLen >= 0, "%s", objectToWrite.ToString().c_str()); // Picks up any failure to serialise.
    RSYS_ASSERT_PRINTF(serialisedDataLen <= (s32)MAX_SERIALISED_DATA_LEN, "%s", objectToWrite.ToString().c_str());

    // Fill in header.
    U32ToBigEndianByteArray(MAGIC_DELIMITER, writeBuffer);
    U32ToBigEndianByteArray(objectToWrite.GetSerialisationId(), &(writeBuffer[4]));
    U16ToBigEndianByteArray(serialisedDataLen, &(writeBuffer[8]));

    // Append to file.
    bool success = AppendData(writeBuffer, OBJECT_HEADER_LEN + serialisedDataLen, m_flushAndSyncEveryWrite);

    RETURN(success);
}

shared_ptr<Serialisable> SerialisableFileStore::ReadObject(ReadResult& readResult)
{
    ENTER();

    shared_ptr<Serialisable> object;
    u8 header[OBJECT_HEADER_LEN];
    u8 serialisedData[MAX_SERIALISED_DATA_LEN];

    // Assume error for now.
    readResult = READ_ERROR;

    // Read the header so we know what we are dealing with.
    u32 bytesRead = ReadData(header, OBJECT_HEADER_LEN);
    if(GetEof())
    {
        // This is probably normal so don't display an error message, just return.
        readResult = READ_EOF;
        RETURN(object);
    }

    // Check header otherwise read OK.
    if(bytesRead != OBJECT_HEADER_LEN)
    {
        // Failed to read header.
        TRACE_PRINTF_LEV(TRACE_CRITICAL, "SerialisableFileStore::ReadObject(): Failed to read header - length mismatch (read %" PRIu32 " bytes, expected %" PRIu32 ").", bytesRead, OBJECT_HEADER_LEN);
        readResult = READ_ERROR;
        RETURN(object);
    }

    // Check magic number.
    u32 magicDelimiter = BigEndianByteArrayToU32(header);
    if(magicDelimiter != MAGIC_DELIMITER)
    {
        // Header invalid.
        TRACE_PRINTF_LEV(TRACE_CRITICAL, "SerialisableFileStore::ReadObject(): Failed to read header - magic delimiter invalid (read 0x%08" PRIX32 ", expected 0x%08" PRIX32 ").", magicDelimiter, MAGIC_DELIMITER);
        readResult = READ_ERROR;
        RETURN(object);
    }

    // Check we've got enough room for the data we are about to read.
    u16 serialisedDataLen = BigEndianByteArrayToU16(&(header[8]));
    if(serialisedDataLen > sizeof(serialisedData))
    {
        // Header invalid.
        TRACE_PRINTF_LEV(TRACE_CRITICAL, "SerialisableFileStore::ReadObject(): Serialised data length too long %" PRIu32, serialisedDataLen);
        readResult = READ_ERROR;
        RETURN(object);
    }

    // Grab the serialised data.
    bytesRead = ReadData(serialisedData, (u32)serialisedDataLen);
    if(bytesRead != (u32)serialisedDataLen)
    {
        // Wrong amount of serialised data.
        TRACE_PRINTF_LEV(TRACE_CRITICAL, "SerialisableFileStore::ReadObject(): Failed to read serialised data - length mismatch (read %" PRIu32 " bytes, expected %" PRIu16 " bytes).", bytesRead, serialisedDataLen);
        readResult = READ_ERROR;
        RETURN(object);
    }

    // Call serialisable object factory.
    u32 serialisationId = BigEndianByteArrayToU32(&(header[4]));
    object = m_serialisableFactory.GetSerialisable(serialisationId, serialisedData, serialisedDataLen);

    if(object == NULL)
    {
        // This may or may not be expected.  Perhaps the file contains data that this build of s/w
        // cannot de-serialise, or maybe it's corrupt.  Either way, we'll return NULL for this object
        // but we won't consider it an error.  We'll end up finishing readin the file through
        // other mechanisms (end of file, error in serialisable header).
        TRACE_PRINTF_LEV(TRACE_WARNING, "SerialisableFileStore::ReadObject(): Failed to create Serialisable object.");
    }

    readResult = READ_OK;
    RETURN(object)
}

}
