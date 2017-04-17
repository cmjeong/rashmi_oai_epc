///////////////////////////////////////////////////////////////////////////////
//
// SerialisedData.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include <sstream>
#include <system/SerialisationIds.h>
#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "SerialisedData.h"

namespace threeway
{

SerialisedData::SerialisedData(u32 serialisationId, const u8* serialData, u32 dataLength) :
    m_serialisationId(serialisationId),
    m_serialData(0),
    m_serialDataLength(dataLength)
{
    if( serialData && m_serialDataLength)
    {
        RSYS_ASSERT(m_serialDataLength <= MESSENGER_MAX_SERIALISED_PACKET_LEN);

        m_serialData = new u8[m_serialDataLength];
        memcpy(m_serialData, serialData, m_serialDataLength);
    }
    else
    {
        RSYS_ASSERT(m_serialDataLength == 0);
    }
}

SerialisedData::~SerialisedData()
{
    delete[] m_serialData;
}

std::string SerialisedData::ToString() const
{
    std::ostringstream stream;

    stream << SerialisationIdToString((SerialisationId)m_serialisationId) << "(id=" << m_serialisationId << ")"
           << ", dataLength=" << m_serialDataLength;

    return(stream.str());
}

}
