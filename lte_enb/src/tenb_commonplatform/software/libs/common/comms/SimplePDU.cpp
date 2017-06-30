///////////////////////////////////////////////////////////////////////////////
//
// SimplePDU.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <string.h>
#include <ctype.h>

#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "SimplePDU.h"

using namespace std;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

SimplePDU::SimplePDU(u32 initialStartOffset) :
    m_startOffset(initialStartOffset),
    m_length(0)
{
    ENTER();

    RSYS_ASSERT(m_startOffset + m_length < sizeof(m_dataPacket) );

    memset( &m_dataPacket[m_startOffset], 0, m_length);

    EXIT();
}

SimplePDU::SimplePDU(SimplePDU& simplePdu, u32 initialStartOffset) :
    m_startOffset(initialStartOffset),
    m_length(0)
{
    ENTER();

    // Copy packet.
    SetPacket(simplePdu.GetPacket(), simplePdu.GetPacketLength());

    EXIT();
}

SimplePDU::~SimplePDU()
{
    ENTER();
    EXIT();
}

const u8* SimplePDU::GetPacket() const
{
    ENTER();
    RETURN(&(m_dataPacket[m_startOffset]));
}

u8* SimplePDU::GetPacketRaw(u32& maxLength)
{
    ENTER();

    u8* data = &(m_dataPacket[m_startOffset]);
    maxLength = sizeof(m_dataPacket) - m_startOffset;

    RETURN(data);
}

u32 SimplePDU::GetPacketLength() const
{
    ENTER();
    RETURN(m_length);
}

void SimplePDU::SetPacket(const u8* data, u32 length)
{
    ENTER();

    RSYS_ASSERT_PRINTF(m_startOffset + length <= sizeof(m_dataPacket),
                       "Setting SimplePDU packet with length %" PRIu32 ", but only have %" PRIu32 " available",
                       length, (u32)(sizeof(m_dataPacket) - m_startOffset));

    memcpy(&(m_dataPacket[m_startOffset]), data, length);
    m_length = length;

    EXIT();
}

void SimplePDU::AddToHead(const u8* data, u32 length)
{
    ENTER();

    RSYS_ASSERT_PRINTF(length <= m_startOffset,
                       "Adding data to SimplePDU head with length %" PRIu32 ", but only have %" PRIu32 " available",
                       length, m_startOffset);

    // We've got enough room.
    m_startOffset -= length;
    m_length += length;
    if(data != NULL)
    {
        memcpy(&(m_dataPacket[m_startOffset]), data, length);
    }

    EXIT();
}

void SimplePDU::AddToHead(u32 length)
{
    ENTER();

    AddToHead(NULL, length);

    EXIT();
}

void SimplePDU::AddToTail(const u8* data, u32 length)
{
    ENTER();

    u32 spareTailSpace = sizeof(m_dataPacket) - m_startOffset - m_length;
    RSYS_ASSERT_PRINTF(length <= spareTailSpace,
                       "Adding data to SimplePDU tail with length %" PRIu32 ", but only have %" PRIu32 " available",
                       length, spareTailSpace);

    // We've got enough room.
    if(data != NULL)
    {
       if(m_startOffset+m_length < PDU_MAX_LENGTH)
       {
          memcpy(&(m_dataPacket[m_startOffset+m_length]), data, length);
       }
    }
    m_length += length;

    EXIT();
}

void SimplePDU::AddToTail(u32 length)
{
    ENTER();

    AddToTail(NULL, length);

    EXIT();
}

void SimplePDU::PadHead(u8 padByte, u32 length)
{
    ENTER();

    RSYS_ASSERT_PRINTF(length <= m_startOffset,
                       "Padding SimplePDU head with length %" PRIu32 ", but only have %" PRIu32 " available",
                       length, m_startOffset);

    // We've got enough room.
    m_startOffset -= length;
    m_length += length;
    while(length > 0)
    {
        m_dataPacket[m_startOffset+length-1] = padByte;
        length--;
    }

    EXIT();
}

void SimplePDU::PadTail(u8 padByte, u32 length)
{
    ENTER();

    u32 spareTailSpace = sizeof(m_dataPacket) - m_startOffset - m_length;
    RSYS_ASSERT_PRINTF(length <= spareTailSpace,
                       "Padding SimplePDU tail with length %" PRIu32 ", but only have %" PRIu32 " available",
                       length, spareTailSpace);

    // We've got enough room.
    if(m_startOffset + m_length < PDU_MAX_LENGTH)
    {
       memset((void*)&m_dataPacket[m_startOffset + m_length], (int)padByte, length);
    }
    m_length += length;

    EXIT();
}

void SimplePDU::TrimHead(u32 trimLength)
{
    ENTER();

    RSYS_ASSERT_PRINTF(trimLength <= m_length,
                       "Trimming SimplePDU head by %" PRIu32 ", but packet is only %" PRIu32 " long",
                       trimLength, m_length);

    m_startOffset += trimLength;
    m_length -= trimLength;

    EXIT();
}

void SimplePDU::TrimTail(u32 trimLength)
{
    ENTER();

    RSYS_ASSERT_PRINTF(trimLength <= m_length,
                       "Trimming SimplePDU tail by %" PRIu32 ", but packet is only %" PRIu32 " long",
                       trimLength, m_length);

    m_length -= trimLength;

    EXIT();
}

void SimplePDU::Reset(u32 initialStartOffset)
{
    ENTER();

    m_startOffset = initialStartOffset;
    m_length = 0;

    EXIT();
}

string SimplePDU::ToString() const
{
    ENTER ();

    ostringstream stream;

    ToString(stream, true, false);

    RETURN (stream.str());
}

string SimplePDU::ToStringAsHex(u32 maxNumBytes) const
{
    ENTER ();

    ostringstream stream;

    ToString(stream, false, true, maxNumBytes);

    RETURN (stream.str());
}

void SimplePDU::ToString(ostringstream& stream, bool shortText, bool asHex, u32 maxNumBytes) const
{
    ENTER ();

    char hex[5];

    stream << PDU::ToString() << ", offset=" << m_startOffset << ", length=" << m_length;

    if (!shortText)
    {
        u32 i, checksum = 0;
        u32 len = 0;

        stream << " : ";

        if(maxNumBytes == 0)
        {
            len = m_length;
        }
        else
        {
            len = m_length > maxNumBytes ? maxNumBytes : m_length;
        }

        for(i = 0; i < len; i++)
        {
            checksum += m_dataPacket[m_startOffset + i];
            if(asHex)
            {
                snprintf(hex, sizeof(hex), "%02X", m_dataPacket[m_startOffset + i]);
                stream << hex << " ";
            }
            else
            {
                if(isprint(m_dataPacket[m_startOffset + i]))
                {
                    stream << m_dataPacket[m_startOffset + i];
                }
                else
                {
                    stream << '.';
                }
            }
        }

        if(len < m_length)
        {
            stream << " [truncated]";
        }

        stream << " (checksum " << checksum << ")";
    }

    EXIT();
}

}
