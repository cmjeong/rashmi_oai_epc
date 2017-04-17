///////////////////////////////////////////////////////////////////////////////
//
// TenpinApplication.h
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __TenpinApplication_h_
#define __TenpinApplication_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <mobnet/FapId.h>
#include <messaging/transport/ApplicationWithMessaging.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "TenpinStackInterfaces.h"
#include "TenpinHardwareInterfaces.h"
#include "TenpinX509Interfaces.h"
#include "IPsecTunnelDb.h"
#include "TenpinConfiguration.h"
#include "Tenpin_fsm.h"

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

using namespace Tenpin;

namespace threeway
{

class TenpinApplication :
    public threeway::ApplicationWithMessaging,
    public TenpinFsmInterface
{
public:
    // Singleton
    ~TenpinApplication() {}
    static TenpinApplication& GetInstance();

    u32 ThreadProcedure();

    const IPsecTunnelDb&        GetTunnelDb()       { return m_tunnelDb; }
    const TenpinConfiguration&  GetConfiguration()  { return m_configuration; }
    shared_ptr<ITenpinDns>      GetDns()            { return m_dns; }
    shared_ptr<ITenpinTpm>      GetTpm()            { return m_tpm; }
    shared_ptr<ITenpinIke>      GetIke()            { return m_ike; }
    shared_ptr<ITenpinX509>     GetX509()           { return m_x509; }
    void HandleLogUpload();
    void StartLogTimer(u32 timer_value);

    void TunnelTeardownAndReconfigure(u32 id);
    static bool isWatchdogDereg;

protected:
    void HandleTimerExpiry(shared_ptr<TimerExpiry> timer);

private:
    // Singleton
    TenpinApplication();
    static shared_ptr<TenpinApplication> s_instance;

    // Implement MessageHandler interface
    virtual bool MessageHandler(shared_ptr<threeway::MessageSerialisedData> & message);

    TimerHandle                 m_guardTimer;
    TimerHandle                 m_ikeGraceTimer;
    threeway::TimerHandle       m_watchdogKickTimer;
    shared_ptr<ITenpinFirewall> m_firewall;
    shared_ptr<ITenpinDns>      m_dns;
    shared_ptr<ITenpinIke>      m_ike;
    shared_ptr<ITenpinHwCrypto> m_hwCrypto;
    shared_ptr<ITenpinTpm>      m_tpm;
    shared_ptr<ITenpinX509>     m_x509;
    std::string                 m_fapId;
    IPsecTunnelDb               m_tunnelDb;
    TenpinConfiguration         m_configuration;

    // Implement FSM interface
    TenpinInterfaceDefinition();

    // Implement actions required by Tenpin FSM
    virtual void ExtractCertificates(void * notUsed);
    virtual void ExtractFapId(void * notUsed);
    virtual void PublishFapId(void * notUsed);
    virtual void StartGuardTimer(void * notUsed);
    virtual void StopGuardTimer(void * notUsed);
    virtual void DeleteGuardTimer(void * notUsed);
    virtual void StartIkeGraceTimer(void * notUsed);
    virtual void StopIkeGraceTimer(void * notUsed);
    virtual void DeleteIkeGraceTimer(void * notUsed);
    virtual void SubscribeAttributes(void * notUsed);
    virtual void NotifyOamUnusable(void * notUsed);
    virtual void NotifyOamReady(void * notUsed);
    virtual void NotifyOamOperational(void * notUsed);
    virtual void RegisterCliCommands(void * notUsed);
    virtual void StartIke(void * notUsed);
    virtual void StopIke(void * notUsed);

    // Implement conditions required by Tenpin FSM
    virtual bool CheckCertificates(void);
    virtual bool CheckFapId(void);
    TimerHandle logTimerHandle;
    // FSM instance must be last
    TenpinFsm   m_fsm;
};

} // namespace threeway

#endif
