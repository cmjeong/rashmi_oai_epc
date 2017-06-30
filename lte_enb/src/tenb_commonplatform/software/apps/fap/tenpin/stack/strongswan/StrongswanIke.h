///////////////////////////////////////////////////////////////////////////////
//
// StrongswanIke.h
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __StrongswanIke_h_
#define __StrongswanIke_h_

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "TenpinConfiguration.h"

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

namespace threeway
{

class StrongswanIke : public ITenpinIke
{
public:
    // Singleton
    virtual ~StrongswanIke() {}
    static shared_ptr<StrongswanIke> GetInstance();

    // Implement ITenpinIke
    void Start(const IPsecTunnelDb& tunnelDb, const std::string& fapId);
    void Stop(void);
    void Teardown(IPsecTunnelDb& tunnelDb, u32 tunnelId);
    void Reconfigure(const IPsecTunnelDb& tunnelDb, const std::string& fapId);

    void RegisterCli(shared_ptr<CliHandler> handler);

    const char * FilenameCertificate(TenpinCertificate_e tc);
    bool CheckCertificates(void);
    void GetTrustedCAs(unsigned char * theCAs, unsigned int * lenCAs);
    void GetOwnRootCAs(unsigned char * theCAs, unsigned int * lenCAs);
    void GetOwnIntermediateCAs(unsigned char * theCAs, unsigned int * lenCAs);

    // Reconfiguration of a single tunnel
    bool ReconfigureTunnel(const std::string& fapId, u32 tunnelId, const Fqdn& destFqdn, const IPAddress& destAddr);

private:
    // Singleton
    StrongswanIke();
    static shared_ptr<StrongswanIke> s_instance;

    void ConfigFileEmpty(void);
    void ConfigFileSetup(void);
    void ConfigFileAppendTunnels(const IPsecTunnelDb& tunnelDb, const std::string& fapId);
    void ConfigFileAppendTunnel(const std::string& fapId, u32 tunnelId, const Fqdn& destFqdn, const IPAddress& destAddr);
    void ServiceStart(void);
    void ServiceStop(void);
    /* Adding changes for PSK */
    void CreateTunnel(void);
    void ServiceReconfigure(void);

    u32          TimePeriod(u32 val);
    const char * TimeUnits(u32 val);

    u32          ConfigItemTimePeriod(const TenpinConfiguration& config, TenpinConfigurationItem_e item);
    const char * ConfigItemTimeUnits(const TenpinConfiguration& config, TenpinConfigurationItem_e item);

    const char * ConfigItemNatTraversal(const TenpinConfiguration& config);
    u32          ConfigItemPeriodIkeLifeTime(const TenpinConfiguration& config);
    const char * ConfigItemUnitsIkeLifeTime(const TenpinConfiguration& config);
    u32          ConfigItemPeriodKeyLife(const TenpinConfiguration& config);
    const char * ConfigItemUnitsKeyLife(const TenpinConfiguration& config);
    u32          ConfigItemMarginTime(const TenpinConfiguration& config);
    u32          ConfigItemPeriodMarginTime(const TenpinConfiguration& config);
    const char * ConfigItemUnitsMarginTime(const TenpinConfiguration& config);
    string       ConfigItemCipherSuitesIke(const TenpinConfiguration& config);
    string       ConfigItemCipherSuitesEsp(const TenpinConfiguration& config);
    const char * ConfigItemLeftSendCert(const TenpinConfiguration& config);
    const char * ConfigItemDpdAction(const TenpinConfiguration& config);
    u32          ConfigItemPeriodDpdDelay(const TenpinConfiguration& config);
    u32          ConfigItemAuthMethod(const TenpinConfiguration&  config);
    const char * ConfigItemUnitsDpdDelay(const TenpinConfiguration& config);
    const char * ConfigItemUnitsIkeRekeyLifeTime(const TenpinConfiguration& config);
    const char * ConfigItemUnitsIpsecLifeTimeTime(const TenpinConfiguration& config);

    string m_fileConfig;
    string m_fileScript;
    string m_cmdStart;
    string m_cmdup;
    string m_cmdStop;
    string m_cmdTeardown;
    string m_cmdReconfigure;

    // CLI commands
    static shared_ptr<CliResponse> CliShowConfig(const CliArguments& cliArgs);
};

} // namespace threeway

#endif
