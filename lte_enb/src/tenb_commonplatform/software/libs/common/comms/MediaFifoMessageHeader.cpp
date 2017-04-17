///////////////////////////////////////////////////////////////////////////////
//
// MediaFifoMessageHeader.cpp
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
#include <system/Trace.h>
#include <system/SerialisationUtils.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MediaFifoMessageHeader.h"

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

MediaFifoMessageHeader::MediaFifoMessageHeader ()
{
    ENTER();
    bzero (&m_header, CsUpFifoMessageHeader_Size);
    EXIT();
}

MediaFifoMessageHeader::MediaFifoMessageHeader (u8 *headerBuffer, u32 dchNumber, u16 rtpSeqNumber, u32 rtpTimestamp, u16 mediaPayloadType, u16 mediaPayloadStatus, u16 numberOfPayloadBits)
{
    ENTER();
    RSYS_ASSERT (headerBuffer);

    m_header.allocatedDchNumber        = dchNumber;
    m_header.mediaTimeStamp            = rtpTimestamp;
    m_header.mediaSequenceNumber       = rtpSeqNumber;
    m_header.mediaPayloadType          = mediaPayloadType;
    m_header.mediaPayloadStatus        = mediaPayloadStatus;
    m_header.mediaPayloadNumberOfBits  = numberOfPayloadBits;

    SerialiseIt(m_header.allocatedDchNumber,       headerBuffer);
    SerialiseIt(m_header.mediaTimeStamp,           headerBuffer);
    SerialiseIt(m_header.mediaSequenceNumber,      headerBuffer);
    SerialiseIt(m_header.mediaPayloadType,         headerBuffer);
    SerialiseIt(m_header.mediaPayloadStatus,       headerBuffer);
    SerialiseIt(m_header.mediaPayloadNumberOfBits, headerBuffer);

    EXIT();
}

MediaFifoMessageHeader::MediaFifoMessageHeader (const u8 *headerBuffer)
{
    ENTER();
    DecodeHeaderBuffer(headerBuffer);
    EXIT();
}

MediaFifoMessageHeader::~MediaFifoMessageHeader ()
{
    ENTER();
    EXIT();
}

void MediaFifoMessageHeader::DecodeHeaderBuffer (const u8 *headerBuffer)
{
    ENTER();
    RSYS_ASSERT (headerBuffer);

    DeSerialiseIt(m_header.allocatedDchNumber,       headerBuffer);
    DeSerialiseIt(m_header.mediaTimeStamp,           headerBuffer);
    DeSerialiseIt(m_header.mediaSequenceNumber,      headerBuffer);
    DeSerialiseIt(m_header.mediaPayloadType,         headerBuffer);
    DeSerialiseIt(m_header.mediaPayloadStatus,       headerBuffer);
    DeSerialiseIt(m_header.mediaPayloadNumberOfBits, headerBuffer);

    EXIT ();
}

u32 MediaFifoMessageHeader::GetDchNumber () const
{
    ENTER ();
    RETURN (m_header.allocatedDchNumber);
}

u16 MediaFifoMessageHeader::GetRtpSeqNumber () const
{
    ENTER ();
    RETURN (m_header.mediaSequenceNumber);
}

u32 MediaFifoMessageHeader::GetRtpTimestamp () const
{
    ENTER ();
    RETURN (m_header.mediaTimeStamp);
}

u16 MediaFifoMessageHeader::GetMediaPayloadType () const
{
    ENTER ();
    RETURN (m_header.mediaPayloadType);
}

u16 MediaFifoMessageHeader::GetMediaPayloadStatus () const
{
    ENTER ();
    RETURN (m_header.mediaPayloadStatus);
}

u16 MediaFifoMessageHeader::GetNumberOfPayloadBits () const
{
    ENTER ();
    RETURN (m_header.mediaPayloadNumberOfBits);
}

u16 MediaFifoMessageHeader::GetNumberOfPayloadBytes () const
{
    ENTER ();
    RETURN ((m_header.mediaPayloadNumberOfBits + 7) >> 3);
}

std::string MediaFifoMessageHeader::ToString () const
{
    ENTER ();

    std::ostringstream returnString;

    returnString << "{ MediaFifoHeader" << std::endl;
    returnString << "  Dch Number      : " <<
        m_header.allocatedDchNumber << std::endl;
    returnString << "  Sequence Number : " <<
        m_header.mediaSequenceNumber << std::endl;
    returnString << "  Timestamp       : " <<
        m_header.mediaTimeStamp << std::endl;
    returnString << "  Media Type      : " <<
        m_header.mediaPayloadType << std::endl;
    returnString << "  Media Status    : " <<
        m_header.mediaPayloadStatus << std::endl;
    returnString << "  Payload Bits    : " <<
        m_header.mediaPayloadNumberOfBits << std::endl;
    returnString << "}" << std::endl;

    RETURN (returnString.str ());
}

}

