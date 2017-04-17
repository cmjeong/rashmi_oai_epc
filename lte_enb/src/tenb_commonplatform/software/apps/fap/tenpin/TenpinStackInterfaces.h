//////////////////////////////////////////////////////////////////////////////
//
// TenpinStackInterfaces.h
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __TenpinStackInterfaces_h_
#define __TenpinStackInterfaces_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <messaging/transport/CliHandler.h>
#include <messaging/messages/tenpin/TenpinFirewall.h>
#include <messaging/messages/tenpin/TenpinFirewallOpenReq.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "IPsecTunnelDb.h"

///////////////////////////////////////////////////////////////////////////////
// Types
///////////////////////////////////////////////////////////////////////////////

typedef enum {

    CERTIFICATE_RADISYS_ROOT_1 = 0,
    CERTIFICATE_RADISYS_ROOT_2,
    CERTIFICATE_RADISYS_BATCH,
    CERTIFICATE_RADISYS_FAP,

} TenpinCertificate_e;

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

namespace threeway
{

class ITenpinFirewall
{
public:
    virtual ~ITenpinFirewall() {}

    virtual void Open(shared_ptr<TenpinFirewallOpenReq> req, FirewallHandles& handles) = 0;
    virtual void Close(const FirewallHandles& handles) = 0;
};

class ITenpinDns
{
public:
    virtual ~ITenpinDns() {}

    virtual void Add(u32 id, const IPv4Address& serverAddr) = 0;
    virtual void Remove(u32 id) = 0;
};

class ITenpinIke
{
public:
    virtual ~ITenpinIke() {}

    virtual void Start(const IPsecTunnelDb& tunnelDb, const std::string& fapId) =0;
    virtual void Stop(void) = 0;
    /* Adding changes for PSK */
    virtual void CreateTunnel(void) = 0;
    virtual void Teardown(IPsecTunnelDb& db, u32 tunnelId) = 0;
    virtual void Reconfigure(const IPsecTunnelDb& db, const std::string& fapId) = 0;

    virtual const char * FilenameCertificate(TenpinCertificate_e tc) = 0;
    virtual bool CheckCertificates(void) = 0;
    virtual void GetTrustedCAs(unsigned char * theCAs, unsigned int * lenCAs) = 0;
    virtual void GetOwnRootCAs(unsigned char * theCAs, unsigned int * lenCAs) = 0;
    virtual void GetOwnIntermediateCAs(unsigned char * theCAs, unsigned int * lenCAs) = 0;

    virtual void RegisterCli(shared_ptr<CliHandler> handler) = 0;
};

class ITenpinHwCrypto
{
public:
    virtual ~ITenpinHwCrypto() {}

    virtual void Enable(void) = 0;
    virtual void Disable(void) = 0;
};

class ITenpinStack
{
public:
    virtual ~ITenpinStack() {}

    virtual bool Init(void) = 0;

    virtual shared_ptr<ITenpinFirewall> GetFirewall(void) = 0;
    virtual shared_ptr<ITenpinDns>      GetDns(void) = 0;
    virtual shared_ptr<ITenpinIke>      GetIke(void) = 0;
    virtual shared_ptr<ITenpinHwCrypto> GetHwCrypto(void) = 0;
};

} // namespace threeway

#endif
