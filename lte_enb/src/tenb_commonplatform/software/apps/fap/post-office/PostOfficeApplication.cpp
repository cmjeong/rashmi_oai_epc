///////////////////////////////////////////////////////////////////////////////
//
// PostOfficeApplication.cpp
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
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <signal.h>
#include <unistd.h>

#include <system/Trace.h>
#include <system/NumberConversions.h>
#include <comms/NetUtils.h>
#include <messaging/messages/common/RegisterEntityReq.h>
#include <messaging/messages/common/RegisterEntityCnf.h>
#include <messaging/messages/common/MessagingRouteInd.h>
#ifdef CLOG
#include <clog/clog.h>
#endif

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "PostOfficeApplication.h"

///////////////////////////////////////////////////////////////////////////////
// Static Data
///////////////////////////////////////////////////////////////////////////////

shared_ptr<PostOfficeApplication> PostOfficeApplication::s_instance;

DeclareAppVersionStamp

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

typedef std::map <MessagingEntity, MessagingEntity> EphemeralAliases;

class MessagingEndpoint
{
public:
    MessagingEndpoint(IPv4Address& addr, u16 port) : m_addr(addr), m_port(port) {}
    virtual ~MessagingEndpoint () {}

public:
    bool HostedAt(IPv4Address& addr, u16 port)
    {
        return ((m_addr == addr) && (m_port == port));
    };

    bool HostedAt(IPv4Address& addr)
    {
        return (m_addr == addr);
    };

    void HostStatic(MessagingEntity entity)
    {
        m_statics.push_back(entity);
    };

    void ToastStatic(MessagingEntity entity)
    {
        for ( MessagingEntities::iterator it = m_statics.begin();
              it != m_statics.end();
              it++
            )
        {
            if (entity == *it)
            {
                m_statics.erase(it);
                return;
            }
        }
    };

    MessagingEntity PrimaryStatic(void)
    {
        if (m_statics.empty())
        {
            return ENTITY_INVALID;
        }

        return m_statics[0];
    }

    MessagingEntity GetAlias(MessagingEntity entity)
    {
        MessagingEntity alias = ENTITY_INVALID;

        EphemeralAliases::const_iterator it = m_aliases.find(entity);

        if (it != m_aliases.end())
        {
            alias = it->second;
        }

        return alias;
    }

    MessagingEntity GetAliased(MessagingEntity alias)
    {
        MessagingEntity entity = ENTITY_INVALID;

        for ( EphemeralAliases::const_iterator it = m_aliases.begin();
              (ENTITY_INVALID == entity) && (it != m_aliases.end());
              it++
            )
        {
            if (alias == it->second)
            {
                entity = it->first;
            }
        }

        return entity;
    }

    MessagingEntity HostAlias(MessagingEntity entity, MessagingEntity alias)
    {
        if (    (ENTITY_INVALID != entity)
             && (ENTITY_INVALID != alias)
           )
        {
            m_aliases[entity] = alias;

            return alias;
        }

        return ENTITY_INVALID;
    }

    void ToSockaddr(struct sockaddr_in * sa)
    {
        bzero(sa, sizeof(*sa));
        sa->sin_family      = AF_INET;
        sa->sin_addr.s_addr = m_addr.Get();
        sa->sin_port        = htons(m_port);
    };

private:
    IPv4Address         m_addr;
    u16                 m_port;
    MessagingEntities   m_statics;
    EphemeralAliases    m_aliases;
};

PostOfficeApplication& PostOfficeApplication::GetInstance()
{
    if (NULL == s_instance)
    {
        s_instance.reset(new PostOfficeApplication());
    }

    return (*s_instance);
}

static void HandleSIGINT(
    int notUsed
)
{
    PostOfficeApplication::GetInstance().ForceExit();
}

int PostOfficeApplication::Main(
    int     deprecated__argc,
    char *  deprecated__argv[]
)
{
    SetPostOfficeAddress();

    m_routingTable.AddDefaultRoute(MessageRouteEntry(ENTITY_POSTOFFICE, m_localHostAddress, m_postOfficePort));

    m_sock.reset(new UdpSocket(m_postOfficePort, *this));
    m_sock->StartReceiving();

    signal(SIGTTIN, SIG_IGN);
    signal(SIGINT,  HandleSIGINT);

#if 0
    bool forever = (GetCmdLineArgument("--forever") ? true : false);
    while (    (!m_loopForceExit)
            && (    (forever)
                 || (EOF != fgetc(stdin))
                 || ferror(stdin)
               )
          )
    {
        clearerr(stdin);
        sleep(2);
#ifdef PRODUCT_generic 
	PostOfficeGetCoverage();
#endif
    }
#else
    while (!m_loopForceExit)
    {
       sleep(2);
#ifdef PRODUCT_generic 
       PostOfficeGetCoverage();
#endif
    };
#endif

    return 0;
}

void PostOfficeApplication::HandleUdpRx(
    s32 fd
)
{
    struct sockaddr_in  from;
    socklen_t           fromLen = sizeof(from);

    const int bufferLen = recvfrom(fd, m_buffer, sizeof(m_buffer), 0, (struct sockaddr *)&from, &fromLen);

    // Pass to clogger
#ifdef CLOG
    union clog_msg_data *clog;
    if(ClogAlloc(CLOG_MSG_MESSENGER, bufferLen, &clog))
    {
        memcpy(clog, m_buffer, bufferLen);
        ClogFree(clog);
    }
#endif
    MessagingEntity fromEntity;
    MessagingEntity toEntity;
    u32             serialisationId;

    int decodedLen = DecodeMessageHeader(m_buffer, bufferLen, fromEntity, toEntity, serialisationId);

    if (decodedLen)
    {
        u16 endpointPort = ntohs(from.sin_port);
        IPv4Address endpointAddress(inet_ntoa(from.sin_addr));

        TRACE_PRINTF(
            "%s -> %s id=%" PRIu32 " len=%d recv'd from %s:%u",
            MessagingEntityToString(fromEntity),
            MessagingEntityToString(toEntity),
            serialisationId,
            (bufferLen - decodedLen),
            endpointAddress.ToString(),
            endpointPort
        );

        fromEntity = MapFromEntity(endpointAddress, endpointPort, fromEntity);

        if (ENTITY_POSTOFFICE == toEntity)
        {
            HandleMessage(fromEntity, toEntity, serialisationId, &m_buffer[decodedLen], (bufferLen - decodedLen), endpointAddress, endpointPort);
        }
        else
        {
            RewriteMessageHeader(&m_buffer[0], fromEntity, MapToEntity(toEntity), serialisationId);
            SendToEndpoint(&m_buffer[0], bufferLen, GetMessagingEndpoint(toEntity));
        }
    }
}

shared_ptr<MessagingEndpoint> PostOfficeApplication::GetMessagingEndpoint(
    IPv4Address&    endpointAddress,
    u16             endpointPort
)
{
    shared_ptr<MessagingEndpoint> endpoint;

    for ( Endpoints::const_iterator it = m_endpoints.begin();
          !endpoint && (it != m_endpoints.end());
          it++
        )
    {
        if ((*it)->HostedAt(endpointAddress, endpointPort))
        {
            endpoint = *it;
        }
    }

    if (!endpoint && endpointPort)
    {
        MessagingEndpoint * me = new MessagingEndpoint(endpointAddress, endpointPort);

        if (me)
        {
            endpoint.reset(me);
            m_endpoints.push_back(endpoint);
        }
    }

    return endpoint;
}

shared_ptr<MessagingEndpoint> PostOfficeApplication::GetMessagingEndpoint(
    MessagingEntity entity
)
{
    shared_ptr<MessagingEndpoint> endpoint;

    EntityRegistry::const_iterator it = m_entityRegistry.find(entity);

    if (it != m_entityRegistry.end())
    {
        endpoint = it->second;
    }
    else
    {
        endpoint = GetMessagingEndpoint(m_localHostAddress, MessagingEntityGetBoundPort(entity));
    }

    return endpoint;
}

bool PostOfficeApplication::RegisterableEntities(
    shared_ptr<RegisterEntityReq>& req
)
{
    bool registerable = false;

    if (req)
    {
        registerable = true;

        for ( MessagingEntities::const_iterator it = req->m_entities.begin();
              (registerable) && (it != req->m_entities.end());
              it++
            )
        {
            MessagingEntity entity = *it;

            if (MessagingEntityIsEphemeral(entity))
            {
                registerable = false;
            }
        }
    }

    return registerable;
}

shared_ptr<MessagingEndpoint> PostOfficeApplication::RegisterEntities(
    MessagingEntities&  entities,
    IPv4Address&        endpointAddress,
    u16                 endpointPort
)
{
    shared_ptr<MessagingEndpoint> endpoint = GetMessagingEndpoint(endpointAddress, endpointPort);

    if (endpoint)
    {
        for ( MessagingEntities::const_iterator it = entities.begin();
              it != entities.end();
              it++
            )
        {
            MessagingEntity entity = *it;

            shared_ptr<MessagingEndpoint> existing = GetMessagingEndpoint(entity);

            if (existing)
            {
                existing->ToastStatic(entity);
            }

            endpoint->HostStatic(entity);

            m_entityRegistry[entity] = endpoint;

            m_routingTable.AddRoute(entity, MessageRouteEntry(entity, endpointAddress, endpointPort));
        }
    }

    return endpoint;
}

MessagingEntity PostOfficeApplication::MapFromEntity(
    IPv4Address&    fromAddress,
    u16             fromPort,
    MessagingEntity fromEntity
)
{
    MessagingEntity mapped = ENTITY_INVALID;

    if (!MessagingEntityIsEphemeral(fromEntity)) /* static */
    {
        mapped = fromEntity;
    }
    else if (fromAddress == m_localHostAddress) /* local ephemeral */
    {
        mapped = MessagingEntityBindEphemeral(fromEntity, fromPort);
    }
    else /* remote ephemeral */
    {
        mapped = MapRemoteFromEntity(fromAddress, fromPort, fromEntity);
    }

    return mapped;
}

MessagingEntity PostOfficeApplication::MapToEntity(
    MessagingEntity toEntity
)
{
    MessagingEntity mapped;

    if (!MessagingEntityIsEphemeral(toEntity)) /* static */
    {
        mapped = toEntity;
    }
    else if (MessagingEntityIsBoundEphemeral(toEntity)) /* local ephemeral */
    {
        mapped = toEntity;
    }
    else /* remote ephemeral */
    {
        mapped = MapRemoteToEntity(toEntity);
    }

    return mapped;
}

MessagingEntity PostOfficeApplication::MapRemoteFromEntity(
    IPv4Address&    fromAddress,
    u16             fromPort,
    MessagingEntity fromEntity
)
{
    MessagingEntity mapped = ENTITY_INVALID;

    shared_ptr<MessagingEndpoint> endpoint = GetMessagingEndpoint(fromAddress, fromPort);

    if (endpoint)
    {
        mapped = endpoint->GetAlias(fromEntity);

        if (ENTITY_INVALID == mapped)
        {
            mapped = endpoint->HostAlias(fromEntity, MessagingEntityNextUnboundEphemeral(&m_aliasedCounter));

            if (ENTITY_INVALID != mapped)
            {
                m_entityRegistry[mapped] = endpoint;
            }
        }
    }

    return mapped;
}

MessagingEntity PostOfficeApplication::MapRemoteToEntity(
    MessagingEntity toEntity
)
{
    MessagingEntity mapped = ENTITY_INVALID;

    shared_ptr<MessagingEndpoint> endpoint = GetMessagingEndpoint(toEntity);

    if (endpoint)
    {
        mapped = endpoint->GetAliased(toEntity);
    }

    return mapped;
}

void PostOfficeApplication::SetPostOfficeAddress(
    void
)
{
    struct sockaddr_in sa;

    const char * addr = GetCmdLineArgument("--po-addr");

    if (    (addr)
         && (0 < inet_pton(AF_INET, addr, &sa.sin_addr))
       )
    {
        m_postOfficeAddress.Clear();
        m_postOfficeAddress.Set(addr);
    }

    if (m_postOfficeAddress == m_localHostAddress)
    {
        m_postOfficeAddress.Clear();
        NetUtils::GetLocalIpAddress(m_postOfficeAddress);
    }
}

#ifdef PRODUCT_generic 
void PostOfficeApplication ::PostOfficeGetCoverage()
{

    //s32 result = CLI_ERROR_NONE;
    //ostringstream responseStream ;

    //responseStream << "Generating coverage for OAM";
    __gcov_flush();
    //shared_ptr<CliResponse> response (new CliResponse(responseStream.str(), result)) ;

    return ;
}
#endif
int PostOfficeApplication::DecodeMessageHeader(
    u8 *                buffer,
    int                 bufferLen,
    MessagingEntity&    fromEntity,
    MessagingEntity&    toEntity,
    u32&                serialisationId
)
{
    if (12 <= bufferLen)
    {
        fromEntity      = BigEndianByteArrayToU32(&buffer[0]);
        toEntity        = BigEndianByteArrayToU32(&buffer[4]);
        serialisationId = BigEndianByteArrayToU32(&buffer[8]);

        return 12;
    }

    return 0;
}

int PostOfficeApplication::EncodeMessageHeader(
    u8 *                buffer,
    int                 bufferLen,
    MessagingEntity     fromEntity,
    MessagingEntity     toEntity,
    u32                 serialisationId
)
{
    if (12 <= bufferLen)
    {
        U32ToBigEndianByteArray(fromEntity,      &buffer[0]);
        U32ToBigEndianByteArray(toEntity,        &buffer[4]);
        U32ToBigEndianByteArray(serialisationId, &buffer[8]);

        return 12;
    }

    return 0;
}

void PostOfficeApplication::RewriteMessageHeader(
    u8 *            buffer,
    MessagingEntity fromEntity,
    MessagingEntity toEntity,
    u32             serialisationId
)
{
    U32ToBigEndianByteArray(fromEntity,      &buffer[0]);
    U32ToBigEndianByteArray(toEntity,        &buffer[4]);
    U32ToBigEndianByteArray(serialisationId, &buffer[8]);
}

void PostOfficeApplication::HandleMessage(
    MessagingEntity fromEntity,
    MessagingEntity toEntity,
    u32             serialisationId,
    u8 *            buffer,
    int             bufferLen,
    IPv4Address&    endpointAddress,
    u16             endpointPort
)
{
    if (serialisationId == SERIALISATION_ID_REGISTER_ENTITY_REQ)
    {
        shared_ptr<RegisterEntityReq> req = Serialisable::DeSerialise<RegisterEntityReq>(buffer, bufferLen);

        if (RegisterableEntities(req))
        {
            shared_ptr<MessagingEndpoint> endpoint = RegisterEntities(req->m_entities, endpointAddress, endpointPort);

            if (endpoint)
            {
                RegisterEntityCnf cnf(req->m_entities);
                SendMessageToEndpoint(cnf, ENTITY_POSTOFFICE, fromEntity, endpoint);

                SendRoutingTableToEndpoints();
            }
        }
    }
}

void PostOfficeApplication::SendToEndpoint(
    u8 *                            buffer,
    int                             bufferLen,
    shared_ptr<MessagingEndpoint>   endpoint
)
{
    if (endpoint)
    {
        struct sockaddr_in to;

        endpoint->ToSockaddr(&to);

        sendto(m_sock->GetFd(), buffer, bufferLen, 0, (struct sockaddr *)&to, sizeof(to));
    }
}

void PostOfficeApplication::SendMessageToEndpoint(
    const Serialisable&             message,
    MessagingEntity                 fromEntity,
    MessagingEntity                 toEntity,
    shared_ptr<MessagingEndpoint>   endpoint
)
{
    const int bufferLen = sizeof(m_buffer);

    int encodedLen = EncodeMessageHeader(m_buffer, bufferLen, fromEntity, toEntity, message.GetSerialisationId());

    if (encodedLen)
    {
        s32 serialised = message.Serialise(&m_buffer[encodedLen], (bufferLen - encodedLen));

        if (0 <= serialised)
        {
            encodedLen += serialised;

            SendToEndpoint(m_buffer, encodedLen, endpoint);
        }
    }
}

void PostOfficeApplication::SendRoutingTableToEndpoints(
    void
)
{
    for ( Endpoints::const_iterator it = m_endpoints.begin();
          it != m_endpoints.end();
          it++
        )
    {
        shared_ptr<MessagingEndpoint> endpoint = *it;

        MessagingEntity toEntity = endpoint->PrimaryStatic();

        if (ENTITY_INVALID != toEntity)
        {
            if (endpoint->HostedAt(m_localHostAddress))
            {
                MessagingRouteInd ind(m_routingTable);

                SendMessageToEndpoint(ind, ENTITY_POSTOFFICE, toEntity, endpoint);
            }
            else // not localhost => split system
            {
                MessageRoutingTable routingTable(m_routingTable);

                MessageRouteEntry defaultRoute;

                if (routingTable.GetDefaultRoute(defaultRoute))
                {
                    defaultRoute.SetIpAddress(m_postOfficeAddress);
                    routingTable.AddDefaultRoute(defaultRoute);
                }

                routingTable.VisitAllRoutes(0, *this);

                MessagingRouteInd ind(routingTable);

                SendMessageToEndpoint(ind, ENTITY_POSTOFFICE, toEntity, endpoint);
            }
        }
    }
}

void PostOfficeApplication::MessageRouteVisit(
    MessageRouteEntry&  route,
    u32                 token
)
{
    if (route.isLocalHost())
    {
        route.SetIpAddress(m_postOfficeAddress);
    }
}

int main (int argc, char **argv)
{
    /* Become the session leader.
     *  This works around a bug in busybox where spawned tasks may recieve
     *  CTRL+C typed at the console because it doesn't put tasks into new
     *  sessions.
     */
    setsid();
#ifdef CLOG
    ClogInit();
#endif

    return PostOfficeApplication::GetInstance().Run(argc, argv);

}
