///////////////////////////////////////////////////////////////////////////////
//
// BitReader.h
//
// Helper class to read bit orientated data from a byte array.

// PLEASE NOTE: This class is used as the base class for MacBitReader.h for
//              manipulating MAC data and thus is very time sensitive!
//              Please take care when modifying this code and please
//              consult the engineer responsible for MAC before committing
//              any changes!
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __BitReader_h_
#define __BitReader_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <Radisys.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class BitReader
{
public:
    /**
     * Default constructor.
     */
    BitReader();

    /**
     * Constructor. The bit array begins at firstBit in firstByte_p.
     *
     * \param firstByte_p   Pointer to data buffer.
     * \param firstBit      First bit position (7=MSB, 0=LSB)
     * \param numBits       Number of bits in the buffer.
     */
    BitReader(const u8 *firstByte_p, const u8 firstBit, const u32 numBits);

    /**
     * Copy Constructor.
     */
    BitReader(const BitReader& rhs);

    /**
     * Destructor.
     */
    virtual ~BitReader() {};

    /**
     * Reset the reader to the beginning of the buffer.
     */
    void ResetReader(void);

    /**
     * Find out the total number of bits
     *
     * \return Number of bits in PDU
     */
    u32 NumBits(void) const { return m_numBits; };

    /**
     * Find out how many bits remain to be read
     *
     * \return Number of bits remaining to be read
     */
    u32 BitsRemaining(void) const { return m_bitsRemaining; };

    /**
     * Accessor functions to read the specific number of bits
     *
     * \param  numBits The number of bits to read
     * \param  data    The data read will be written to this param (LSB aligned)
     * \return True if bits read OK, false otherwise.
     */
    bool ReadBits(u8 numBits, u8& data);   // Up to 8 bits
    bool ReadBits(u8 numBits, u32& data);  // Up to 32 bits

    /**
     * Special function to read a bit and test if set
     *
     * @param data
     * @return
     */
    bool ReadBit(bool & data);   // return bit as a bool.
    
    /**
     * Accessor functions to peak at the specific number of bits, without moving
     * the read position forward.
     *
     * \param  numBits The number of bits to read
     * \param  data    The data read will be written to this param (LSB aligned)
     * \return True if bits read OK, false otherwise.
     */
    bool PeakBits(u8 numBits, u8& data);   // Up to 8 bits
    bool PeakBits(u8 numBits, u32& data);  // Up to 32 bits

    /**
     * Special function to peek a bit and test if set
     *
     * @param data
     * @return
     */
    bool PeakBit(bool & data);   // return bit as a bool.

    /**
     * Skip forward by given number of bits.
     *
     * \param  numBits Number of bits to skip
     * \return True if bits skipped OK, false otherwise.
     */
    bool SkipBits(const u32 numBits);

protected:

    /**
     * Move the reader on by the given number of bits
     *
     * \param  numBits Number of bits to move on by
     */
    void MoveReader(u32 numBits);

    // Store the buffer details
    u8  *m_bufferStart;
    u8   m_firstBit;
    u32  m_numBits;

    // Current accessor information
    u8  *m_buff;
    s8   m_currentBit;    // deliberate signed value for loop arithmetic
    u16  m_bitsRemaining;
};

#endif
