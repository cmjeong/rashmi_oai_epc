///////////////////////////////////////////////////////////////////////////////
//
// MessagingRouteInd.h
//
// Message send from the post office to all registered applications whenever
// there's a routing table update.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MessagingRouteInd_h_
#define __MessagingRouteInd_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "messaging/transport/MessageRoutingTable.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class MessagingRouteInd : public threeway::Serialisable
{
public:
    /**
     * Construction / destruction.
     */
    MessagingRouteInd() {};
    MessagingRouteInd(const threeway::MessageRoutingTable& routes);
    virtual ~MessagingRouteInd() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_MESSAGING_ROUTE_IND; }
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    /**
     * Accessors.
     */

    // OK, just for clarification, I know I'm returning a reference to a member
    // object, but I expect the caller to use or copy the routing table whilst
    // handling this message. Don't even think about storing this...
    threeway::MessageRoutingTable& GetRoutingTable() { return m_routingTable; }

    /**
     * Convert to string for debug.
     */
    virtual std::string ToString() const;

private:

    // The routing table
    threeway::MessageRoutingTable  m_routingTable;

};

#endif
