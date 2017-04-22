#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>

#include <system/Trace.h>
#include <messaging/messages/tenpin/TenpinFirewallOpenReq.h>
#include <messaging/messages/tenpin/TenpinFirewallCloseReq.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "TenpinApplication.h"
#include "IPsecTunnelDb.h"

using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Local Classes
///////////////////////////////////////////////////////////////////////////////

namespace threeway {

class IPsecTunnel
{
public:
    IPsecTunnel(u32 id, MessagingEntity owner, const Fqdn& destFqdn) :
        m_id(id),
        m_owner(owner),
        m_destFqdn(destFqdn),
        m_destAddr(""),
        m_connected(false),
        m_tunnelAddr("")
    {
       TRACE_PRINTF("in ipsectunnel ");
    }

    ~IPsecTunnel() { FirewallClose(); }

    u32                 GetId()         const   { return m_id; };
    MessagingEntity     GetOwner()      const   { return m_owner; };
    const Fqdn&         GetDestFqdn()   const   { return m_destFqdn; };
    const IPAddress&  GetDestAddr()   const   { return m_destAddr; };
    bool                GetConnected()  const   { return m_connected; };
    const IPAddress&  GetTunnelAddr() const   { return m_tunnelAddr; };

    void ResolveDestAddr(void);

    void Connected(const IPAddress& addr);
    void Disconnected(void);

    void FirewallOpened(const FirewallHandles& handles);
    void FirewallClosed(void);

private:
    void FirewallOpen(void);
    void FirewallClose(void);

private:
    u32                 m_id;
    MessagingEntity     m_owner;
    Fqdn                m_destFqdn;   // configured ipsec gateway fqdn
    IPAddress         m_destAddr;   // resolved ipsec gateway ip address
    bool                m_connected;
    IPAddress         m_tunnelAddr; // tunnel inner ip address
    FirewallHandles     m_handles;
};

void IPsecTunnel::ResolveDestAddr(
    void
)
{
    /* gethostbyname() is not a re-entrant function */
    /* provisioning only occurs off the main thread */

    const char * hostname = m_destFqdn.ToString().c_str();

    if (hostname)
    {
        TRACE_PRINTF("Resolving hostname '%s'", hostname);
        int afType = AF_INET6;
        struct hostent * resolved = gethostbyname2(hostname,AF_INET6);
        if(resolved == NULL)
        {
            resolved = gethostbyname2(hostname,AF_INET);
            afType = AF_INET;
        }
        if (resolved)
        {
            TRACE_PRINTF("...resolved to official hostname '%s'", resolved->h_name);

            if (afType == resolved->h_addrtype)
            {
                /* select the first address in the resolved list */
                /* ditch the rest :) */
                char first[32];

                memset(first, 0, sizeof(first));

                inet_ntop(afType, resolved->h_addr_list[0], first, sizeof(first));

                m_destAddr.Set(first);
                if(!m_destAddr.CheckIfIPv6())
                {
                      TRACE_PRINTF("...resolved to IPv4 address '%s'", m_destAddr.ipv4.ToString());
                }
                else
                {
                      TRACE_PRINTF("...resolved to IPv6 address '%s'", m_destAddr.ipv6.ToString());
                }
            }
            else
            {
                TRACE_PRINTF("...failed, did not resolve to IP address(es)");
            }
        }
        else
        {
            TRACE_PRINTF("...failed %s", hstrerror(h_errno));
        }
    }
}

void IPsecTunnel::Connected(
    const IPAddress&  addr
)
{
    m_connected  = true;
    m_tunnelAddr = addr;

    FirewallOpen();
}

void IPsecTunnel::Disconnected(
    void
)
{
    m_connected = false;
    m_tunnelAddr.Clear();

    FirewallClose();
}

void IPsecTunnel::FirewallOpened(
    const FirewallHandles&  handles
)
{
    m_handles = handles;
}

void IPsecTunnel::FirewallClosed(
    void
)
{
    m_handles.clear();
}

void IPsecTunnel::FirewallOpen(
    void
)
{
    TenpinFirewallOpenReq req;
    req.SetToken(m_id);
    req.SetPassIn();
    req.SetPassOut();
    req.SetLocalAddr(m_tunnelAddr);
    TenpinApplication::GetInstance().SendMessage(req, ENTITY_TENPIN, ENTITY_TENPIN);
}

void IPsecTunnel::FirewallClose(
    void
)
{
    TenpinFirewallCloseReq req;
    req.SetToken(m_id);
    req.m_handles = m_handles;
    TenpinApplication::GetInstance().SendMessage(req, ENTITY_TENPIN, ENTITY_TENPIN);

    m_handles.clear();
}

class CliWalker : public IIPsecTunnelDbWalker
{
public:
    virtual ~CliWalker() {}
    CliWalker() {}

    // Implement IIPsecTunnelDbWalker
    bool Tunnel(
        u32                 id,
        const Fqdn&         destFqdn,
        const IPAddress&  destAddr,
        MessagingEntity     owner,
        bool                connected,
        const IPAddress&  tunnelAddr
    )
    {
        responseText <<         "id="           << id;
        responseText << " " <<  "destFqdn="     << destFqdn.ToString();
        responseText << " " <<  "destAddr="     << destAddr.Get();
        responseText << " " <<  "owner="        << MessagingEntityToString(owner);
        responseText << " " <<  "connected="    << connected;
        responseText << " " <<  "tunnelAddr="   << tunnelAddr.Get();
        responseText << "\n";
        return true;
    }

    const std::string str() { return responseText.str(); }

private:
    std::ostringstream responseText;
};

}; // namespace

///////////////////////////////////////////////////////////////////////////////
// Public Functions
///////////////////////////////////////////////////////////////////////////////

u32 IPsecTunnelDb::s_id;

u32 IPsecTunnelDb::Provision(
    MessagingEntity owner,
    const Fqdn&     destFqdn
)
{
    u32 id = NextId();

    if (id)
    {
        IPsecTunnel * tunnel = new IPsecTunnel(id, owner, destFqdn);

        if (tunnel)
        {
            db.insert(std::make_pair(id, tunnel));

            tunnel->ResolveDestAddr();
        }
        else
        {
            id = 0;
        }
    }

    return id;
}

void IPsecTunnelDb::DeProvision(
    u32 id
)
{
    TunnelDb::iterator it = db.find(id);

    if (it != db.end())
    {
        db.erase(it);
    }
}

void IPsecTunnelDb::GetTunnelDestAddr(
    u32             id,
    IPAddress&    destAddr
)
{
    IPsecTunnel * tunnel = GetTunnel(id);

    if (tunnel)
    {
        destAddr = tunnel->GetDestAddr();
    }
}

MessagingEntity IPsecTunnelDb::Owner(
    u32 id
)
{
    IPsecTunnel * tunnel = GetTunnel(id);

    return (tunnel ? tunnel->GetOwner() : ENTITY_INVALID);
}

MessagingEntity IPsecTunnelDb::Connected(
    u32                 id,
    const IPAddress&  tunnelAddr
)
{
    IPsecTunnel * tunnel = GetTunnel(id);

    if (tunnel && !tunnel->GetConnected())
    {
        tunnel->Connected(tunnelAddr);
    }

    return Owner(id);
}

MessagingEntity IPsecTunnelDb::Disconnected(
    u32 id
)
{
    IPsecTunnel * tunnel = GetTunnel(id);

    if (tunnel)
    {
        tunnel->Disconnected();
    }

    return Owner(id);
}

void IPsecTunnelDb::FirewallOpened(
    u32                     id,
    const FirewallHandles&  handles
)
{
    IPsecTunnel * tunnel = GetTunnel(id);

    if (tunnel)
    {
        tunnel->FirewallOpened(handles);
    }
}

void IPsecTunnelDb::FirewallClosed(
    u32 id
)
{
    IPsecTunnel * tunnel = GetTunnel(id);

    if (tunnel)
    {
        tunnel->FirewallClosed();
    }
}

bool IPsecTunnelDb::Walk(
    IIPsecTunnelDbWalker& walker
) const
{
    bool walk = true;

    for (TunnelDb::const_iterator it = db.begin(); walk && (it != db.end()); it++)
    {
        u32             id     = it->first;
        IPsecTunnel *   tunnel = it->second;

        walk = walker.Tunnel(
            id,
            tunnel->GetDestFqdn(),
            tunnel->GetDestAddr(),
            tunnel->GetOwner(),
            tunnel->GetConnected(),
            tunnel->GetTunnelAddr()
        );
    }

    return walk;
}

void IPsecTunnelDb::RegisterCli(
    shared_ptr<CliHandler>  handler
)
{
    CliCmdDescriptor showTunnels = {
        "show-tunnels",
        0,
        0,
        "dev",
        "show-tunnels",
        "Show tunnels"
    };
    handler->RegisterCliCmd(showTunnels, &IPsecTunnelDb::CliShowTunnels);

    CliCmdDescriptor deleteTunnel = {
        "delete-tunnel",
        1,
        1,
        "dev",
        "delete-tunnel <id>",
        "Delete tunnel"
    };

    handler->RegisterCliCmd(deleteTunnel, &IPsecTunnelDb::CliDeleteTunnel);
}

shared_ptr<CliResponse> IPsecTunnelDb::CliShowTunnels(
    const CliArguments& cliArgs
)
{
    CliWalker walker;

    TenpinApplication::GetInstance().GetTunnelDb().Walk(walker);

    shared_ptr<CliResponse> response(new CliResponse(walker.str()));
    return response;
}

shared_ptr<CliResponse> IPsecTunnelDb::CliDeleteTunnel(
    const CliArguments& cliArgs
)
{
    u32 id = 0;

    if (cliArgs.at(0).IsU32())
    {
        id = cliArgs.at(0).GetU32();

        TenpinApplication::GetInstance().TunnelTeardownAndReconfigure(id);
    }

    shared_ptr<CliResponse> response(
        new CliResponse(
            id ? "deleted" : "bad id",
            id ? CLI_ERROR_NONE : CLI_ERROR_COMMAND_FAILED
        )
    );
    return response;
}

///////////////////////////////////////////////////////////////////////////////
// Private Functions
///////////////////////////////////////////////////////////////////////////////

u32 IPsecTunnelDb::NextId(
    void
)
{
    u32 id = 0;

    /* carried over from previous implementation:
     * this is too simple for a generically usable component
     */

    while (0 == id)
    {
        if (1000 <= s_id)
        {
            s_id = 0;
        }

        ++s_id;

        if (!GetTunnel(s_id))
        {
            id = s_id;
        }
    }

    return id;
}

IPsecTunnel * IPsecTunnelDb::GetTunnel(
    u32 id
)
{
    TunnelDb::iterator it = db.find(id);

    if (it != db.end())
    {
        return it->second;
    }

    return NULL;
}
