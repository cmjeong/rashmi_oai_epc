///////////////////////////////////////////////////////////////////////////////
//
// BinaryFile.h
//
// Class for manipulating binary files.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __BinaryFile_h_
#define __BinaryFile_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>

#include <3waytypes.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class BinaryFile
{
public:
    /**
     * Construct with file path and name.
     * Doesn't open the file at this point.
     *
     * \param fileName File path and name.
     */
    BinaryFile(const char * fileName);
    virtual ~BinaryFile();

    /**
     * Open the file for read/write.
     *
     * Will append data to end of file and but start with file position to
     * be start of file.
     *
     * On appending data, the file pointer moves to the end of the file and
     * will require a Rewind() before read.
     */
    bool Open();

    /**
     * Close the file.
     */
    void Close();

    /**
     * Delete the file.  File *must* be closed before deleting.
     */
    bool Delete();

    /**
     * Rewind file position to start of file.
     */
    void Rewind();

    /**
     * Get current file position indicator.
     *
     * \return Current file pos or < 0 on error.
     */
    s32 GetFilePos();

    /**
     * Get EOF status.  Only goes true on reading beyond the end of the file.
     *
     * \return true if end-of-file.
     */
    bool GetEof();

    /**
     * Append data to the end of the file.
     *
     * \param writeBuffer    Buffer to write to end of file.
     * \param writeBufferLen Num bytes to write.
     * \param flushAndSync   If true, flush C lib buffers then sync to disk.
     * \return               true on success, false on failure.
     */
    bool AppendData(const u8* writeBuffer, u32 writeBufferLen, bool flushAndSync = false);

    /**
     * Read data of suggested length from the current read position.
     * If end of file reached, return value will be less than readBufferLen.
     *
     * \param readBuffer    Buffer to read in to.
     * \param readBufferLen Max bytes of data to read.
     * \return              Num bytes read.  0 on error.
     */
    u32 ReadData(u8* readBuffer, u32 readBufferLen);

private:
    /**
     * File path and name.
     */
    std::string m_fileName;

    /**
     * File handle for open file.
     */
    FILE* m_fileHandle;

};

}

#endif
