///////////////////////////////////////////////////////////////////////////////
//
// SerialisationUtils.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <iterator>

#include <string.h>
#include <system/Trace.h>
#include <system/NumberConversions.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "SerialisationUtils.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Functions
///////////////////////////////////////////////////////////////////////////////

void SerialiseIt(const u8 value, u8*& pSerialisedData)
{
    ENTER();

    *pSerialisedData = value;
    pSerialisedData++;

    EXIT();
}

void DeSerialiseIt(u8& value, const u8*& pSerialisedData)
{
    ENTER();

    value = *pSerialisedData;
    pSerialisedData++;

    EXIT();
}

void SerialiseIt(const u16 value, u8*& pSerialisedData)
{
    ENTER();

    U16ToBigEndianByteArray(value, pSerialisedData);
    pSerialisedData += 2;

    EXIT();
}

void DeSerialiseIt(u16& value, const u8*& pSerialisedData)
{
    ENTER();

    value = BigEndianByteArrayToU16(pSerialisedData);
    pSerialisedData += 2;

    EXIT();
}

void SerialiseIt(const s16 value, u8*& pSerialisedData)
{
    ENTER();

    U16ToBigEndianByteArray((u16)value, pSerialisedData);
    pSerialisedData += 2;

    EXIT();
}

void DeSerialiseIt(s16& value, const u8*& pSerialisedData)
{
    ENTER();

    value = (s16)BigEndianByteArrayToU16(pSerialisedData);
    pSerialisedData += 2;

    EXIT();
}

void SerialiseIt(const u32 value, u8*& pSerialisedData)
{
    ENTER();

    U32ToBigEndianByteArray(value, pSerialisedData);
    pSerialisedData += 4;

    EXIT();
}

void DeSerialiseIt(u32& value, const u8*& pSerialisedData)
{
    ENTER();

    value = BigEndianByteArrayToU32(pSerialisedData);
    pSerialisedData += 4;

    EXIT();
}
/**
 *This function serialise float value
*/
void SerialiseIt(const float value, u8*& pSerialisedData)
{
    ENTER();

    FloatToBigEndianByteArray(value, pSerialisedData);
    pSerialisedData += 4;

    EXIT();
}

/**
 * This function deserialise float value
*/
void DeSerialiseIt(float& value, const u8*& pSerialisedData)
{
    ENTER();

    value = BigEndianByteArrayToFloat(pSerialisedData);
    pSerialisedData += 4;

    EXIT();
}


void SerialiseIt(const std::vector<u32>& value, u8*& pSerialisedData)
{
    std::vector<u32>::size_type numOfU32 = value.size();

    U16ToBigEndianByteArray((u16)numOfU32, pSerialisedData);
    pSerialisedData += 2;

    for (std::vector<u32>::const_iterator iter = value.begin();
         iter != value.end();
         ++iter)
    {
        SerialiseIt(*iter, pSerialisedData);
    }
}

void DeSerialiseIt(std::vector<u32>& value, const u8*& pSerialisedData)
{
    u16 vectorLen = BigEndianByteArrayToU16(pSerialisedData);
    pSerialisedData += 2;

    value.clear();
    value.reserve(vectorLen);

    u32 receivedU32;

    for (; vectorLen != 0; --vectorLen)
    {
        DeSerialiseIt(receivedU32, pSerialisedData);
        value.push_back(receivedU32);
    }
}

void SerialiseIt(const std::vector<s32>& value, u8*& pSerialisedData)
{
    std::vector<s32>::size_type numOfS32 = value.size();

    U16ToBigEndianByteArray((u16)numOfS32, pSerialisedData);
    pSerialisedData += 2;

    for (std::vector<s32>::const_iterator iter = value.begin();
         iter != value.end();
         ++iter)
    {
        SerialiseIt(*iter, pSerialisedData);
    }
}

void DeSerialiseIt(std::vector<s32>& value, const u8*& pSerialisedData)
{
    u16 vectorLen = BigEndianByteArrayToU16(pSerialisedData);
    pSerialisedData += 2;

    value.clear();
    value.reserve(vectorLen);

    s32 receivedS32;

    for (; vectorLen != 0; --vectorLen)
    {
        DeSerialiseIt(receivedS32, pSerialisedData);
        value.push_back(receivedS32);
    }
}


void SerialiseIt(const s32 value, u8*& pSerialisedData)
{
    ENTER();

    U32ToBigEndianByteArray((u32)value, pSerialisedData);
    pSerialisedData += 4;

    EXIT();
}

void DeSerialiseIt(s32& value, const u8*& pSerialisedData)
{
    ENTER();

    value = (s32)BigEndianByteArrayToU32(pSerialisedData);
    pSerialisedData += 4;

    EXIT();
}

void SerialiseIt(const std::string& value, u8*& pSerialisedData)
{
    ENTER();

    u32 strLen = value.length();

    U16ToBigEndianByteArray((u16)strLen, pSerialisedData);
    pSerialisedData += 2;

    memcpy(pSerialisedData, value.c_str(), strLen);
    pSerialisedData += strLen;

    EXIT();
}

void DeSerialiseIt(std::string& value, const u8*& pSerialisedData, u16 maxStrLen)
{
    ENTER();

    value.clear();

    u16 strLen = BigEndianByteArrayToU16(pSerialisedData);
    pSerialisedData += 2;

    RSYS_ASSERT_PRINTF(strLen <= maxStrLen, "strLen=%"PRIu32", maxStrLen=%"PRIu32, strLen, maxStrLen);

    value.assign((const char *)pSerialisedData, strLen);
    pSerialisedData += strLen;

    EXIT();
}

void SerialiseIt(const std::vector<std::string>& value, u8*& pSerialisedData)
{
    ENTER();

    std::vector<std::string>::size_type numOfStrings = value.size();

    U16ToBigEndianByteArray((u16)numOfStrings, pSerialisedData);
    pSerialisedData += 2;

    for (std::vector<std::string>::const_iterator stringIter = value.begin();
            not(stringIter == value.end());
            ++stringIter)
    {
        SerialiseIt(*stringIter, pSerialisedData); // pSerialisedData is updated with every call
    }

    EXIT();
}

void DeSerialiseIt(std::vector<std::string>& value, const u8*& pSerialisedData, u16 maxBufLen)
{
    ENTER();

    u16 vectorLen = BigEndianByteArrayToU16(pSerialisedData);
    pSerialisedData += 2;

    value.clear();
    value.reserve(vectorLen);

    std::string receivedString;

    for (; vectorLen != 0; --vectorLen)
    {
        DeSerialiseIt(receivedString, pSerialisedData, maxBufLen); // populate receivedString
        maxBufLen -= receivedString.size();
        value.push_back(receivedString);
    }

    EXIT();
}

void SerialiseIt(const bool value, u8*& pSerialisedData)
{
    ENTER();

    *pSerialisedData = (u8)(value ? 1 : 0);
    pSerialisedData++;

    EXIT();
}

void DeSerialiseIt(bool& value, const u8*& pSerialisedData)
{
    ENTER();

    value = (*pSerialisedData > 0) ? true : false;
    pSerialisedData++;

    EXIT();
}

void SerialiseIt(const void *value, u8*& pSerialisedData)
{
    ENTER();

    U32ToBigEndianByteArray((u32)value, pSerialisedData);
    pSerialisedData += 4;

    EXIT();
}

void DeSerialiseIt(void *& value, const u8*& pSerialisedData)
{
    ENTER();

    value = (void*)BigEndianByteArrayToU32(pSerialisedData);
    pSerialisedData += 4;

    EXIT();
}

