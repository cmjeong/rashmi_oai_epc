///////////////////////////////////////////////////////////////////////////////
//
// BinaryFile.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <unistd.h>
#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "BinaryFile.h"

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

BinaryFile::BinaryFile(const char * fileName) :
    m_fileName(fileName),
    m_fileHandle(NULL)
{
    ENTER();

    EXIT();
}

BinaryFile::~BinaryFile()
{
    ENTER();

    Close();

    EXIT();
}

bool BinaryFile::Open()
{
    ENTER();

    // Preconditions.
    RSYS_ASSERT(m_fileHandle == NULL);

    TRACE_PRINTF("Opening %s", m_fileName.c_str());

    // Open file for reading (start of file) and appending (end of file).
    m_fileHandle = fopen(m_fileName.c_str(), "a+b");
    if(m_fileHandle == NULL)
    {
        // Don't assert here.  It is not necessarily a coding bug.
        TRACE_PRINTF_LEV(TRACE_CRITICAL, "BinaryFile::Open(): Failed to open file %s.", m_fileName.c_str());
    }

    RETURN(m_fileHandle != NULL);
}

void BinaryFile::Close()
{
    if(m_fileHandle)
    {
        TRACE_PRINTF("Closing %s", m_fileName.c_str());

        fclose(m_fileHandle);
        m_fileHandle = NULL;
    }
}

bool BinaryFile::Delete()
{
    ENTER();

    // Preconditions.
    RSYS_ASSERT(m_fileHandle == NULL);

    RETURN(remove(m_fileName.c_str()) == 0);
}

void BinaryFile::Rewind()
{
    ENTER();

    // Preconditions.
    RSYS_ASSERT(m_fileHandle != NULL);

    rewind(m_fileHandle);

    EXIT();
}

s32 BinaryFile::GetFilePos()
{
    ENTER();

    // Preconditions.
    RSYS_ASSERT(m_fileHandle != NULL);

    long int pos = ftell(m_fileHandle);
    if(pos < 0)
    {
        TRACE_PRINTF_LEV(TRACE_CRITICAL, "ftell() failed on %s", m_fileName.c_str());
    }

    RETURN((s32)pos);
}

bool BinaryFile::GetEof()
{
    ENTER();

    // Preconditions.
    RSYS_ASSERT(m_fileHandle != NULL);

    RETURN(feof(m_fileHandle) != 0);
}

bool BinaryFile::AppendData(const u8* writeBuffer, u32 writeBufferLen, bool flushAndSync)
{
    ENTER();

    // Preconditions.
    RSYS_ASSERT(m_fileHandle != NULL);

    size_t numBytes = fwrite((const void*)writeBuffer, 1, writeBufferLen, m_fileHandle);

    if(numBytes == (size_t)writeBufferLen)
    {
        if(flushAndSync)
        {
            fflush(m_fileHandle);
            fsync(fileno(m_fileHandle));
        }
        RETURN(true);
    }

    RETURN(false);
}

u32 BinaryFile::ReadData(u8* readBuffer, u32 readBufferLen)
{
    ENTER();

    // Preconditions.
    RSYS_ASSERT(m_fileHandle != NULL);

    size_t numBytes = fread((void*)readBuffer, 1, readBufferLen, m_fileHandle);

    RETURN(numBytes);
}

}
