///////////////////////////////////////////////////////////////////////////////
//
// HexString.h
//
// Manage a string of hex digits.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __HexString_h_
#define __HexString_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>

#include <Radisys.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////


namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

static const u32 HEX_STRING_MAX_STORAGE_LENGTH = 0xff;
static const u32 HEX_STRING_DEFAULT_MIN_LENGTH = 0;
static const u32 HEX_STRING_DEFAULT_MAX_LENGTH = HEX_STRING_MAX_STORAGE_LENGTH - 1; // -1 for null term

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class HexString
{
public:
    /**
     * Various constructors to build a HexString from a string of hex digits
     * e.g. 123ABC (null terminated) or a byte array [1,2,3,10,11,12] and
     * length, with or without length constraints.
     */
    HexString();
    HexString(const char * hexString);
    HexString(const u8* hexArray, u32 hexArrayLength);
    HexString(u32 minLength, u32 maxLength);
    HexString(u32 minLength, u32 maxLength, const char * hexString);
    HexString(u32 minLength, u32 maxLength, const u8* hexArray, u32 hexArrayLength);
    virtual ~HexString();

    /**
     * Various setters for different formats.
     */
    void SetHexString(const char * hexString);
    void SetHexArray(const u8* hexArray, u32 hexArrayLength);

    /**
     * Check whether it has ever been set.
     */
    bool IsSet() const { return m_isSet; }


    /**
     * Append a char from the set [0..9a..fA..F]
     */
    bool AppendHexDigit( char c );
    /**
     * Convert number between 0 and 15 to [0..9a-f] and AppendHexDigit
     */
    bool AppendNibble( u8 nibble );
    /**
     * Append MS then LS nibbles
     */
    bool AppendByte( u8 byte );
    /**
     * Get hex string as a byte array.
     *
     * \param byteArray Storage area for byte array.
     * \param byteArrayMaxLen Available space at *byteArray
     * \return true if hex string is set, false otherwise
     */
    bool GetByteArray(u8* byteArray, u32 byteArrayMaxLen) const;

    /**
     * Get hex string as a Hex-byte array.
     *
     * \param hexByteArray Storage area for hexByte array.
     * \param hexByteArrayMaxLen Available space at *hexByteArray
     * \return true if hexByte string is set, false otherwise
     */

    bool GetHexByteArray(u8* hexByteArray, u32 hexByteArrayMaxLen) const;

    /**
     * Get hex string as a u32 array.
     *
     * \param u32Array Storage area for byte array.
     * \param u32ArrayMaxLen Available space at *byteArray
     * \return true if hex string is set, false otherwise
     */
    bool GetU32Array(long unsigned int *u32Array, u32 u32ArrayMaxLen);

    /**
     * Get N MS bits and put them in an array of bytes such that bit 0
     * of byte 0 is the LSB of the N bits.
     */
    void GetMsBits(u8 numBits, std::vector<u8>& msBitsAsBytes);

    /**
     * Get hex string size
     */
    u32 GetSize() const;
    u32 GetNumBits() const;

    /**
     * == operator
     *
     * We compare whether both are set or not and if set whether
     * the strings match.  Min/max length values are not compared.
     */
    bool operator==(const HexString &rhs) const;
    bool operator!=(const HexString &rhs) const;

    /**
     * < operator to let us use these in STL tree containers such as map.
     */
    bool operator<(const HexString &rhs) const;

    /**
     * Get hex string as a.... hex string.
     *
     * \return Pointer to null terminated hex string.
     */
    virtual const char * ToString() const;

protected:

    /**
     * Copies the contents of the passed reference into this object.
     * @param hexStrRef reference to copy
     */
    void Clone(const HexString& hexStrRef);

private:
    /**
     * Check the length limits make sense and set them.
     */
    void    SetLengthRange(u32 minLength, u32 maxLength);

    /**
     * Check a hex string of the supplied length is within our length limits.
     */
    void    LengthCheck(u32 length);

    /**
     * HexChar<>Byte conversion.
     */
    char    ByteToHexChar(u8 byte);
    u8      HexCharToByte(char hexChar) const;

    // Indicates if string has actually been set or is empty.
    bool    m_isSet;
    // Storage space.
    std::string    m_hexString; 
    // Length limits.
    u32     m_minLength;
    u32     m_maxLength;

};

}

#endif
