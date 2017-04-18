///////////////////////////////////////////////////////////////////////////////
//
// TenpinFirewallOpenReq.h
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __TenpinFirewallOpenReq_h_
#define __TenpinFirewallOpenReq_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////
#include <comms/IPAddress.h>
///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "TenpinFirewall.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class TenpinFirewallOpenReq : public threeway::Serialisable
{
public:
    TenpinFirewallOpenReq() :
        m_token(0),
        m_passIn(0),
        m_passOut(0),
        m_protocolUdp(0),
        m_broadcast(0),
        m_localAddr(""),
        m_localPort(0),
        m_remoteAddr(""),
        m_remotePort(0)
    {};
    virtual ~TenpinFirewallOpenReq() {};

    // Implement Serialisable

    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_TENPIN_FIREWALL_OPEN_REQ; }
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);
    virtual std::string ToString() const;

    // Rule Configuration - Basic Methods

    void    SetToken            (u32 token)         { m_token = token; }
    void    SetPassIn           (void)              { m_passIn = true; }
    void    SetPassOut          (void)              { m_passOut = true; }
    void    SetProtocolUdp      (void)              { m_protocolUdp = true; }
    void    SetBroadcast        (void)              { m_broadcast = true; }
    void    SetLocalAddr        (u32 localAddr)     { m_localAddr = localAddr; }
    void    SetLocalPort        (u16 localPort)     { m_localPort = localPort; }
    void    SetRemoteAddr       (u32 remoteAddr)    { m_remoteAddr = remoteAddr; }
    void    SetRemotePort       (u16 remotePort)    { m_remotePort = remotePort; }

    u32     GetToken            (void) const    { return m_token; }
    bool    GetPassIn           (void) const    { return m_passIn; }
    bool    GetPassOut          (void) const    { return m_passOut; }
    bool    GetProtocolUdp      (void) const    { return m_protocolUdp; }
    bool    GetBroadcast        (void) const    { return m_broadcast; }
    string  GetLocalAddr        (void) const    { return m_localAddr; }
    u16     GetLocalPort        (void) const    { return m_localPort; }
    string  GetRemoteAddr       (void) const    { return m_remoteAddr; }
    u16     GetRemotePort       (void) const    { return m_remotePort; }

    // Rule Configuration - Overloads

    void    SetLocalAddr    (IPAddress& localAddr)    { m_localAddr = localAddr.Get(); }
    void    SetRemoteAddr   (IPAddress& remoteAddr)   { m_remoteAddr = remoteAddr.Get(); }

private:
    static const u32 serialisedLen = (4 * sizeof(u8)) + (3 * sizeof(u32)) + (2 * sizeof(u16));

    u32     m_token;
    bool    m_passIn;
    bool    m_passOut;
    bool    m_protocolUdp;
    bool    m_broadcast;
    string  m_localAddr;
    u16     m_localPort;
    string  m_remoteAddr;
    u16     m_remotePort;
};

#endif
