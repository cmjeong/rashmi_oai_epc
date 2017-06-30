///////////////////////////////////////////////////////////////////////////////
//
// MessagingRouteInd.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <system/NumberConversions.h>
#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MessagingRouteInd.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

MessagingRouteInd::MessagingRouteInd(const MessageRoutingTable& routes) :
    m_routingTable(routes)
{
    ENTER();

    EXIT();
}

s32 MessagingRouteInd::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    // Serialise to:
    //   4 bytes - routing table length (bytes)
    //   n bytes - routing table contents

    const u32 headerLen = 4; // 1 * u32 as above

    if ((dataMaxBytes >= headerLen) &&
        (dataMaxBytes <= (MESSENGER_MAX_SERIALISED_PACKET_LEN-headerLen)))
    {
        u32 routingTableLen = m_routingTable.Serialise(&data[headerLen], dataMaxBytes - headerLen);
        // poke the routing table length in once we've found it out from Serialise
        U32ToBigEndianByteArray(routingTableLen, &data[0]);
        RETURN(headerLen + routingTableLen);
    }

    RETURN(-1);
}

bool MessagingRouteInd::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    // DeSerialise from:
    //   4 bytes - routing table length (bytes)
    //   n bytes - routing table contents

    const u32 headerLen = 4; // 1 * u32 as above

    if(dataLen >= headerLen)
    {
        // Clear any existing routing table entries
        m_routingTable.ClearRoutingTable();

        u32 routingTableLen = BigEndianByteArrayToU32(&data[0]);
        // is there a routing table present?
        if (routingTableLen > 0)
        {
            // sanity check the received length
            if ((routingTableLen <= (dataLen-headerLen)) &&
                (routingTableLen <= (MESSENGER_MAX_SERIALISED_PACKET_LEN-headerLen)))
            {
                RETURN(m_routingTable.DeSerialise(&data[4], dataLen-headerLen));
            }
            else
            {
                TRACE_PRINTF("Failed to deserialise MessagingRouteInd - data length too large, dataLen=%" PRIu32, dataLen);
            }
        }
    }
    else
    {
        TRACE_PRINTF("Failed to deserialise MessagingRouteInd - wrong data length, dataLen=%" PRIu32, dataLen);
    }

    RETURN(false);
}

string MessagingRouteInd::ToString() const
{
    ENTER();

    ostringstream stream;

    stream << "MessagingRouteInd " << m_routingTable.ToString();

    RETURN(stream.str());
}
