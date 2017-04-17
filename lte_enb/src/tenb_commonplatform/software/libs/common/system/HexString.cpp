///////////////////////////////////////////////////////////////////////////////
//
// HexString.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <ctype.h>
#include <string.h>

#include <system/Trace.h>
#include <system/StringUtils.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "HexString.h"

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

HexString::HexString() :
    m_isSet(false),
    m_minLength(HEX_STRING_DEFAULT_MIN_LENGTH),
    m_maxLength(HEX_STRING_DEFAULT_MAX_LENGTH)
{
    m_hexString.clear();
}

HexString::HexString(const char * hexString) :
    m_isSet(false),
    m_minLength(HEX_STRING_DEFAULT_MIN_LENGTH),
    m_maxLength(HEX_STRING_DEFAULT_MAX_LENGTH)
{
    SetHexString(hexString);
}

HexString::HexString(const u8* hexArray, u32 hexArrayLength) :
    m_isSet(false),
    m_minLength(HEX_STRING_DEFAULT_MIN_LENGTH),
    m_maxLength(HEX_STRING_DEFAULT_MAX_LENGTH)
{
    SetHexArray(hexArray, hexArrayLength);
}

HexString::HexString(u32 minLength, u32 maxLength) :
    m_isSet(false),
    m_minLength(HEX_STRING_DEFAULT_MIN_LENGTH),
    m_maxLength(HEX_STRING_DEFAULT_MAX_LENGTH)
{
    m_hexString.clear();
    SetLengthRange(minLength, maxLength);
}

HexString::HexString(u32 minLength, u32 maxLength, const char * hexString) :
    m_isSet(false),
    m_minLength(HEX_STRING_DEFAULT_MIN_LENGTH),
    m_maxLength(HEX_STRING_DEFAULT_MAX_LENGTH)
{
    SetLengthRange(minLength, maxLength);
    SetHexString(hexString);
}

HexString::HexString(u32 minLength, u32 maxLength, const u8* hexArray, u32 hexArrayLength) :
    m_isSet(false),
    m_minLength(HEX_STRING_DEFAULT_MIN_LENGTH),
    m_maxLength(HEX_STRING_DEFAULT_MAX_LENGTH)
{
    SetLengthRange(minLength, maxLength);
    SetHexArray(hexArray, hexArrayLength);
}

HexString::~HexString()
{
    m_hexString.clear();
}

void HexString::SetHexString(const char * hexString)
{
    RSYS_ASSERT(hexString != NULL);

    // Check length, will throw if out of range.
    LengthCheck(strlen(hexString));

    m_hexString = hexString;
    m_isSet = true;
}

void HexString::SetHexArray(const u8* hexArray, u32 hexArrayLength)
{
    RSYS_ASSERT(hexArray != NULL);

    // Check length, will throw if out of range.
    LengthCheck(hexArrayLength);

    m_hexString.resize(hexArrayLength);
   
    // Convert each char to hex.
    for(u32 i = 0; i < hexArrayLength; i++)
    {
        m_hexString[i] = ByteToHexChar(hexArray[i]);
    }
    m_isSet = true;
}

/**
 * Append a char from the set [0..9a..fA..F]
 */
bool HexString::AppendHexDigit( char c )
{
    bool validHexDigit = (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
    bool roomForAppend = m_hexString.size() < m_maxLength;

    bool append = roomForAppend && validHexDigit;

    if(append)
    {
        m_hexString.append(1,c);

        m_isSet = true;
    }

    return append;
}

/**
 * Convert number between 0 and 15 to [0..9a-f] and AppendHexDigit
 */
bool HexString::AppendNibble( u8 nibble )
{
    const char hexDigit[16 + 1] = "0123456789abcdef";

    return AppendHexDigit( hexDigit[nibble & 0xf] );
}

/**
 * Append MS then LS nibbles
 */
bool HexString::AppendByte( u8 byte )
{
    return AppendNibble( byte >> 4  ) &&
           AppendNibble( byte & 0xf );
}


bool HexString::GetByteArray(u8* byteArray, u32 byteArrayMaxLen) const
{
    RSYS_ASSERT(byteArray != NULL);

    if(m_isSet)
    {

        u32 hexStrLen = m_hexString.size();

        RSYS_ASSERT_PRINTF(byteArrayMaxLen >= hexStrLen, "HexString: Not enough room (%" PRIu32 ") to return as byte array", byteArrayMaxLen);

        for(u32 i = 0; i < hexStrLen; i++)
        {
            byteArray[i] = HexCharToByte(m_hexString[i]);
        }
    }

    return m_isSet;
}

bool HexString::GetHexByteArray(u8* hexByteArray, u32 hexByteArrayMaxLen) const
{
    RSYS_ASSERT(hexByteArray != NULL);

    if(m_isSet)
    {
        u32 hexStrLen = m_hexString.size();

        RSYS_ASSERT_PRINTF(hexByteArrayMaxLen >= (hexStrLen/2+1), "HexString: Not enough room (%" PRIu32 ") to return as hex byte array", hexByteArrayMaxLen);

        u32 i = 0;
        u32 j = 0;

        if(hexStrLen%2)
        {
            hexByteArray[j++] = HexCharToByte(m_hexString[i++]);
        }

        while(i < hexStrLen)
        {
            u8 hexByte = HexCharToByte(m_hexString[i++]);
            hexByte = (hexByte << 4) & 0xF0;
            hexByte = hexByte | (HexCharToByte(m_hexString[i++]));
            
            hexByteArray[j++] = hexByte;
        }
    }

    return m_isSet;
}

bool HexString::GetU32Array(long unsigned int *u32Array, u32 u32ArrayMaxLen)
{
    RSYS_ASSERT(u32Array != NULL);

    if(m_isSet)
    {
        u32 hexStrLen = m_hexString.size();

        RSYS_ASSERT_PRINTF(u32ArrayMaxLen >= hexStrLen, "HexString: Not enough room (%" PRIu32 ") to return as u32 array", u32ArrayMaxLen);

        for(u32 i = 0; i < hexStrLen; i++)
        {
            u8 hexCharAsByte = HexCharToByte(m_hexString[i]);
            u32Array[i] = hexCharAsByte;
        }
    }

    return m_isSet;

}

void HexString::GetMsBits(u8 numBits, std::vector<u8>& msBitsAsBytes)
{
    RSYS_ASSERT(m_isSet);
    RSYS_ASSERT(numBits <= GetNumBits());

    u8 numBytes = numBits + 7 / 8;
    //u8 bytes[numBytes];

    msBitsAsBytes.reserve(numBytes);

    // TODO
    RSYS_ASSERT(false);
}

u32 HexString::GetSize() const
{
    if(m_isSet)
    {
        return (u32)(m_hexString.size());
    }

    return 0;
}

u32 HexString::GetNumBits() const
{
    return ( GetSize() * 4 );
}

bool HexString::operator==(const HexString &rhs) const
{
    if(m_isSet == rhs.m_isSet)
    {
        if(m_isSet == false)
        {
            // Neither are set so consider them equal!
            return true;
        }
        // Both are set so return the string comparison.
        return ( (m_hexString.compare(rhs.m_hexString.c_str())) == 0 );
    }

    // One is set and the other isn't - so they are not equal!
    return false;
}

bool HexString::operator!=(const HexString &rhs) const
{
    return(!operator==(rhs));
}

bool HexString::operator<(const HexString &rhs) const
{
    if(m_isSet == rhs.m_isSet)
    {
        if(m_isSet == false)
        {
            // Neither are set so consider them equal!
            return false;
        }

        // Both are set so return the string comparison.
        return ( (m_hexString.compare(rhs.m_hexString.c_str())) < 0 );
    }

    // One is set and the other isn't - so they are not equal!
    return rhs.m_isSet;
}

const char * HexString::ToString() const
{
    if(m_isSet)
    {
        return m_hexString.c_str();
    }

    return "<undefined>";
}

void HexString::SetLengthRange(u32 minLength, u32 maxLength)
{

    RSYS_ASSERT_PRINTF(minLength <= maxLength,
                       "HexString: Min length (%" PRIu32 ") greater than max length (%" PRIu32 ")",
                       minLength, maxLength);
    RSYS_ASSERT_PRINTF(maxLength <= HEX_STRING_MAX_STORAGE_LENGTH - 1,
                       "HexString: Max length (%" PRIu32 ") greater than available storage length (%" PRIu32 ")",
                       maxLength, HEX_STRING_MAX_STORAGE_LENGTH-1);

    m_minLength = minLength;
    m_maxLength = maxLength;
}

void HexString::LengthCheck(u32 length)
{
    RSYS_ASSERT(length <= m_hexString.max_size() /* Max number of characters the string object can hold */);
    RSYS_ASSERT_PRINTF(length <= m_maxLength, "HexString: String too long (is %" PRIu32 ", max %" PRIu32 ")", (u32)length, m_maxLength);
    RSYS_ASSERT_PRINTF(length >= m_minLength, "HexString: String too short (is %" PRIu32 ", min %" PRIu32 ")", (u32)length, m_minLength);
}

char HexString::ByteToHexChar(u8 byte)
{
    RSYS_ASSERT(byte <= 15);

    if(byte < 10)
    {
        return '0' + byte;
    }
    else
    {
        return 'A' + (byte - 10);
    }
}

u8 HexString::HexCharToByte(char hexChar) const
{
    hexChar = (char)toupper(hexChar);
    if((hexChar >= 'A') && (hexChar <= 'F'))
    {
        return hexChar - 'A' + 10;
    }
    if((hexChar >= '0') && (hexChar <= '9'))
    {
        return hexChar - '0';
    }

    RSYS_ASSERT_PRINTF(false, "HexString: Char (%c) is not a hex char", hexChar);

    return 0;
}


void HexString::Clone(const HexString& hexStrRef)
{
    m_hexString.clear();
    m_isSet = hexStrRef.m_isSet;
    if (m_isSet)
    {
        m_hexString = hexStrRef.m_hexString;
        m_minLength = hexStrRef.m_minLength;
        m_maxLength = hexStrRef.m_maxLength;
    }
    else
    {
        m_minLength = HEX_STRING_DEFAULT_MIN_LENGTH;
        m_maxLength = HEX_STRING_MAX_STORAGE_LENGTH;
    }
}

}
