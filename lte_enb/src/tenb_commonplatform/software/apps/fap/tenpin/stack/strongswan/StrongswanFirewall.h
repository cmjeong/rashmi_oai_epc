///////////////////////////////////////////////////////////////////////////////
//
// StrongswanFirewall.h
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __StrongswanFirewall_h_
#define __StrongswanFirewall_h_

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "TenpinStackInterfaces.h"

#include <map>

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

namespace threeway
{

typedef std::map<u32, std::string> RulesDb;

class StrongswanFirewall : public ITenpinFirewall
{
public:
    // Singleton
    virtual ~StrongswanFirewall() {}
    static shared_ptr<StrongswanFirewall> GetInstance();

    // Implement ITenpinStackFirewall
    virtual void Open(shared_ptr<TenpinFirewallOpenReq> req, FirewallHandles& handles);
    virtual void Close(const FirewallHandles& handles);

private:
    // Singleton
    StrongswanFirewall() :
        m_handle(0)
    {}
    static shared_ptr<StrongswanFirewall> s_instance;

    // Rules database
    u32     m_handle;
    RulesDb m_rules;

    static const int oam_ret_zero = 0;

    bool        HaveRule(u32 handle);
    void        InsertRule(u32 handle, std::string ruleStr);
    std::string RemoveRule(u32 handle);
    bool isIPv6;

    // Rules building
    void BuildRuleChain(ostringstream& rule, bool in);
    void BuildRuleProtocol(ostringstream& rule, const char * prefix, const char * protocol);
    void BuildRuleAddr(ostringstream& rule, const char * prefix, string addr);
    void BuildRulePort(ostringstream& rule, const char * prefix, u16 port);
    void BuildRule(ostringstream& rule, bool in, const char * protocol, string fromAddr, u16 fromPort, string toAddr, u16 toPort);

    // Manipulation of iptables firewall
    u32  AppendRule(ostringstream& rule);
    void DeleteRule(u32 handle);
};

} // namespace threeway

#endif
