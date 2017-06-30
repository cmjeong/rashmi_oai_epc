///////////////////////////////////////////////////////////////////////////////
//
// IPsecTunnelDb.h
//
// Copyright radisys Limited
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __IPsecTunnelDb_h_
#define __IPsecTunnelDb_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <map>
#include <system/Fqdn.h>
#include <comms/IPv4Address.h>
#include <comms/IPAddress.h>
#include <messaging/transport/MessagingEntity.h>
#include <messaging/transport/CliHandler.h>

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

namespace threeway
{

class IIPsecTunnelDbWalker {

public:
    virtual ~IIPsecTunnelDbWalker() {}

    virtual bool Tunnel(u32 id, const Fqdn& destFqdn, const IPAddress& destAddr, MessagingEntity owner, bool connected, const IPAddress& tunnelAddr) = 0;
};

class IPsecTunnel;

typedef std::map<u32, IPsecTunnel *> TunnelDb;

class IPsecTunnelDb
{
public:
    IPsecTunnelDb() {}
    ~IPsecTunnelDb() {}

    u32  Provision(MessagingEntity owner, const Fqdn& destFqdn);
    void DeProvision(u32 id);

    void GetTunnelDestAddr(u32 id, IPAddress& destAddr);

    MessagingEntity Owner(u32 id);
    MessagingEntity Connected(u32 id, const IPAddress& tunnelAddr);
    MessagingEntity Disconnected(u32 id);

    void FirewallOpened(u32 id, const FirewallHandles& handles);
    void FirewallClosed(u32 id);

    bool Walk(IIPsecTunnelDbWalker& walker) const;

    void RegisterCli(shared_ptr<CliHandler> handler);

private:
    static u32  s_id;
    TunnelDb    db;

    u32             NextId(void);
    IPsecTunnel *   GetTunnel(u32 id);

    static shared_ptr<CliResponse> CliShowTunnels(const CliArguments& cliArgs);
    static shared_ptr<CliResponse> CliDeleteTunnel(const CliArguments& cliArgs);
};

} // namespace threeway

#endif
