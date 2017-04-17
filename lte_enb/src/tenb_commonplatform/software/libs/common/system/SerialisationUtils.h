///////////////////////////////////////////////////////////////////////////////
//
// SerialisationUtils.h
//
// Helper functions for serialising objects and basic types.
//
// NOTE!  These functions make for efficient easy to write/read code but
// the downside is lack of bounds checking when writing to the target buffer.
// Generally this is OK as these will be called from a Serialise/DeSerialise
// function that should have already checked buffer size.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __SerialisationUtils_h_
#define __SerialisationUtils_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>
#include <set>
#include <3waytypes.h>
#include <system/NumberConversions.h>
#include <system/Trace.h>

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Functions
///////////////////////////////////////////////////////////////////////////////

void SerialiseIt(const u8 value, u8*& pSerialisedData);
void DeSerialiseIt(u8& value, const u8*& pSerialisedData);

void SerialiseIt(const u16 value, u8*& pSerialisedData);
void DeSerialiseIt(u16& value, const u8*& pSerialisedData);

void SerialiseIt(const s16 value, u8*& pSerialisedData);
void DeSerialiseIt(s16& value, const u8*& pSerialisedData);

void SerialiseIt(const u32 value, u8*& pSerialisedData);
void DeSerialiseIt(u32& value, const u8*& pSerialisedData);
/*These prototypes are added for adding support for real type kpi*/
void SerialiseIt(const float value, u8*& pSerialisedData);
void DeSerialiseIt(float& value, const u8*& pSerialisedData);

void SerialiseIt(const s32 value, u8*& pSerialisedData);
void DeSerialiseIt(s32& value, const u8*& pSerialisedData);

void SerialiseIt(const std::string& value, u8*& pSerialisedData);
void DeSerialiseIt(std::string& value, const u8*& pSerialisedData, u16 maxStrLen);

void SerialiseIt(const std::vector<std::string>& value, u8*& pSerialisedData);
void DeSerialiseIt(std::vector<std::string>& value, const u8*& pSerialisedData, u16 maxStrLen);

void SerialiseIt(const std::vector<u32>& value, u8*& pSerialisedData);
void DeSerialiseIt(std::vector<u32>& value, const u8*& pSerialisedData);

void SerialiseIt(const std::vector<s32>& value, u8*& pSerialisedData);
void DeSerialiseIt(std::vector<s32>& value, const u8*& pSerialisedData);

void SerialiseIt(const bool value, u8*& pSerialisedData);
void DeSerialiseIt(bool& value, const u8*& pSerialisedData);

void SerialiseIt(const void *value, u8*& pSerialisedData);
void DeSerialiseIt(void *&value, const u8*& pSerialisedData);
/**
 * (De)Serialise a set that contains elements that can happily be cast to U32.
 * This was added for enums in particular.
 */
template <class T>
void SerialiseItU32Set(const std::set<T>& value, u8*& pSerialisedData, u32 dataMaxBytes) // As this could go nuts let's validate length...
{
    ENTER();

    u32 numEntries = value.size();
    RSYS_ASSERT_PRINTF((2 + numEntries * 4) <= dataMaxBytes, "numEntries=%" PRIu32 ", dataMaxBytes=%" PRIu32, numEntries, dataMaxBytes);

    U16ToBigEndianByteArray((u16)numEntries, pSerialisedData);
    pSerialisedData += 2;

    typename std::set< T >::const_iterator iter = value.begin();
    while(iter != value.end())
    {
        U32ToBigEndianByteArray((u32)(*iter), pSerialisedData);
        pSerialisedData += 4;
        ++iter;
    }

    EXIT();
}

template <class T>
void DeSerialiseItU32Set(std::set<T>& value, const u8*& pSerialisedData, u16 maxEntries)
{
    ENTER();

    value.clear();

    u16 numEntries = BigEndianByteArrayToU16(pSerialisedData);
    pSerialisedData += 2;

    RSYS_ASSERT_PRINTF(numEntries <= maxEntries, "numEntries=%u, maxEntries=%u", numEntries, maxEntries);

    for(u16 i = 0; i < numEntries; i++)
    {
        value.insert((T)BigEndianByteArrayToU32(pSerialisedData));
        pSerialisedData += 4;
    }

    EXIT();
}

#endif
