///////////////////////////////////////////////////////////////////////////////
//
// PostOfficeApplication.h
//
// Post Office Messaging:
//
// Copyright radisys Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __PostOfficeApplication_h_
#define __PostOfficeApplication_h_
#ifdef PRODUCT_generic
extern "C" void __gcov_flush(void);
#endif

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <map>

#include <boost/shared_ptr.hpp>

#include <system/Application.h>
#include <system/Serialisable.h>
#include <comms/UdpSocket.h>
#include <messaging/transport/MessagingEntity.h>
#include <messaging/transport/Messenger.h>
#include <messaging/transport/MessageRoutingTable.h>
#include <messaging/transport/MessageRouteEntry.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

using namespace boost;
using namespace std;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

// forward declaration
class MessagingEndpoint;

class PostOfficeApplication : public threeway::Application,
                              public threeway::UdpRxInterface,
                              public threeway::MessageRoutingTableVisitor
{
public:
    // Singleton
    ~PostOfficeApplication() {};
    static PostOfficeApplication& GetInstance();

public:
    int Main(int deprecated__argc, char * deprecated__argv[]);
    void HandleUdpRx(s32 fd);
    void MessageRouteVisit(threeway::MessageRouteEntry& route, u32 token);

public:
    void ForceExit(void) { m_loopForceExit = true; }

private:
    shared_ptr<MessagingEndpoint> GetMessagingEndpoint(IPv4Address& endpointAddress, u16 endpointPort);
    shared_ptr<MessagingEndpoint> GetMessagingEndpoint(MessagingEntity entity);

    bool                          RegisterableEntities(shared_ptr<RegisterEntityReq>& req);
    shared_ptr<MessagingEndpoint> RegisterEntities(MessagingEntities& entities, IPv4Address& endpointAddress, u16 endpointPort);

    MessagingEntity MapFromEntity(
        IPv4Address&    fromAddress,
        u16             fromPort,
        MessagingEntity fromEntity
    );
    MessagingEntity MapToEntity(
        MessagingEntity toEntity
    );
    MessagingEntity MapRemoteFromEntity(
        IPv4Address&    fromAddress,
        u16             fromPort,
        MessagingEntity fromEntity
    );
    MessagingEntity MapRemoteToEntity(
        MessagingEntity toEntity
    );

    void SetPostOfficeAddress();
#ifdef PRODUCT_generic
    void PostOfficeGetCoverage();
#endif

    int DecodeMessageHeader(
        u8 *                buffer,
        int                 bufferLen,
        MessagingEntity&    fromEntity,
        MessagingEntity&    toEntity,
        u32&                serialisationId
    );
    int EncodeMessageHeader(
        u8 *                buffer,
        int                 bufferLen,
        MessagingEntity     fromEntity,
        MessagingEntity     toEntity,
        u32                 serialisationId
    );
    void RewriteMessageHeader(
        u8 *                buffer,
        MessagingEntity     fromEntity,
        MessagingEntity     toEntity,
        u32                 serialisationId
    );
    void HandleMessage(
        MessagingEntity fromEntity,
        MessagingEntity toEntity,
        u32             serialisationId,
        u8 *            buffer,
        int             bufferLen,
        IPv4Address&    endpointAddress,
        u16             endpointPort
    );
    void SendToEndpoint(
        u8 *                            buffer,
        int                             bufferLen,
        shared_ptr<MessagingEndpoint>   endpoint
    );
    void SendMessageToEndpoint(
        const Serialisable&             message,
        MessagingEntity                 fromEntity,
        MessagingEntity                 toEntity,
        shared_ptr<MessagingEndpoint>   endpoint
    );
    void SendRoutingTableToEndpoints(void);

private:
    // Singleton
    PostOfficeApplication() :
        Application("post-office"),
        m_loopForceExit(false),
        m_localHostAddress("127.0.0.1"),
        m_postOfficeAddress("127.0.0.1"),
        m_postOfficePort(PORT_POSTOFFICE),
        m_aliasedCounter(0)
    {
        memset(m_buffer, 0, sizeof(m_buffer));
    };
    static shared_ptr<PostOfficeApplication> s_instance;
    bool                            m_loopForceExit;
    IPv4Address                     m_localHostAddress;
    IPv4Address                     m_postOfficeAddress;
    u16                             m_postOfficePort;
    u16                             m_aliasedCounter;
    shared_ptr<threeway::UdpSocket> m_sock;
    u8                              m_buffer[MESSENGER_MAX_SERIALISED_PACKET_LEN];

    // A MessagingEntity is hosted at a MessagingEndpoint
    // A MessagingEndpoint may host more than one MessagingEntity
    // The routing table is distributed to the MessagingEndpoints
    typedef map < MessagingEntity, shared_ptr<MessagingEndpoint> > EntityRegistry;
    EntityRegistry m_entityRegistry;

    typedef vector < shared_ptr<MessagingEndpoint> > Endpoints;
    Endpoints m_endpoints;

    // Routing table
    threeway::MessageRoutingTable m_routingTable;
};

#endif
