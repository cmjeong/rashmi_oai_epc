///////////////////////////////////////////////////////////////////////////////
//
// BitReader.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//                        *** W A R N I N G ! ***
///////////////////////////////////////////////////////////////////////////////
//        This class is used as the base class for MacBitReader.h for
//        manipulating MAC data and thus is very time sensitive!
//        Please take care when modifying this code and please
//        consult the engineer responsible for MAC before committing
//        any changes!
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "BitReader.h"

using namespace std;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Static Data
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

BitReader::BitReader() :
    m_bufferStart(NULL),
    m_firstBit(7),
    m_numBits(0),
    m_buff(NULL),
    m_currentBit(7),
    m_bitsRemaining(0)
{
}

BitReader::BitReader(const u8 *firstByte_p, const u8 firstBit, const u32 numBits) :
    m_bufferStart(const_cast<u8 *>(firstByte_p)),
    m_firstBit(firstBit),
    m_numBits(numBits),
    m_buff(NULL),
    m_currentBit(7),
    m_bitsRemaining(0)
{
    ResetReader();
}

BitReader::BitReader(const BitReader& rhs)
{
    m_bufferStart   = rhs.m_bufferStart;
    m_firstBit      = rhs.m_firstBit;
    m_numBits       = rhs.m_numBits;
    m_buff          = rhs.m_buff;
    m_currentBit    = rhs.m_currentBit;
    m_bitsRemaining = rhs.m_bitsRemaining;
}

void BitReader::ResetReader(void)
{
    m_buff          = m_bufferStart;
    m_currentBit    = m_firstBit;
    m_bitsRemaining = m_numBits;
}

bool BitReader::SkipBits(const u32 numBits)
{
    bool success = false;

    if (numBits <= m_bitsRemaining)
    {
        MoveReader(numBits);
        success = true;
    }

    return(success);
}

bool BitReader::ReadBits(u8 numBits, u8& data)
{
    RSYS_ASSERT(numBits <= 8);

    u32 data32   = 0;
    bool success = ReadBits(numBits, data32);
    data = data32;

    return(success);
}

bool BitReader::ReadBits(u8 numBits, u32& data)
{
    bool success = false;
    data = 0;

    if (numBits <= m_bitsRemaining)
    {
        m_bitsRemaining -= numBits;

        while (numBits > 0)
        {
            if (*m_buff & (1 << m_currentBit))
            {
                data |= (1 << (numBits - 1));
            }

            if (--m_currentBit < 0)
            {
                m_buff++;
                m_currentBit = 7;
            }

            numBits--;
        }

        success = true;
    }

    return(success);
}

bool BitReader::ReadBit(bool & data)
{
    u32 data32   = 0;
    bool success = ReadBits(1, data32);
    data = (bool)data32;

    return(success);
}

bool BitReader::PeakBits(u8 numBits, u8& data)
{
    RSYS_ASSERT(numBits <= 8);

    u32 data32   = 0;
    bool success = PeakBits(numBits, data32);
    data = data32;

    return(success);
}

bool BitReader::PeakBits(u8 numBits, u32& data)
{
    // Save current context
    u8 *saveBuff      = m_buff;
    u8  saveBit       = m_currentBit;
    u32 saveRemaining = m_bitsRemaining;

    bool success = ReadBits(numBits, data);

    // Restore context
    m_buff          = saveBuff;
    m_currentBit    = saveBit;
    m_bitsRemaining = saveRemaining;

    return(success);
}

bool BitReader::PeakBit(bool & data)
{
    u32 data32   = 0;
    bool success = PeakBits(1, data32);
    data = (bool)data32;

    return(success);
}

void BitReader::MoveReader(u32 numBits)
{
    RSYS_ASSERT(m_bitsRemaining >= numBits);

    // First, offset by the number of whole bytes
    m_buff += (numBits >> 3);

    // Now adjust by remainder of bits (firstBit 7=MSB, 0=LSB)
    u8 remainingBits = numBits % 8;

    if (remainingBits <= m_currentBit)
    {
        // Only need to adjust firstBit
        m_currentBit -= remainingBits;
    }
    else
    {
        m_buff++;
        m_currentBit += (8 - remainingBits);
    }
    RSYS_ASSERT(m_currentBit < 8);

    m_bitsRemaining -= numBits;
}

