///////////////////////////////////////////////////////////////////////////////
//
// StrongswanFirewall.cpp
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Trace.h>
#include <comms/IPv4Address.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "TenpinStack.h"
#include "StrongswanFirewall.h"

using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Static Data
///////////////////////////////////////////////////////////////////////////////

shared_ptr<StrongswanFirewall> StrongswanFirewall::s_instance;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

shared_ptr<StrongswanFirewall> StrongswanFirewall::GetInstance()
{
    if (NULL == s_instance)
    {
        s_instance.reset(new StrongswanFirewall());
    }

    return s_instance;
}

bool StrongswanFirewall::HaveRule(
    u32 handle
)
{
    RulesDb::iterator it = m_rules.find(handle);

    return (it != m_rules.end());
}

void StrongswanFirewall::InsertRule(
    u32         handle,
    std::string ruleStr
)
{
    m_rules.insert(std::make_pair(handle, ruleStr));
}

std::string StrongswanFirewall::RemoveRule(
    u32 handle
)
{
    std::string ruleStr;

    RulesDb::iterator it = m_rules.find(handle);

    if (it != m_rules.end())
    {
        ruleStr = it->second;
        m_rules.erase(it);
    }

    return ruleStr;
}

void StrongswanFirewall::BuildRuleChain(
    ostringstream&  rule,
    bool            in
)
{
    if (in)
    {
        rule << "INPUT";
    }
    else
    {
        rule << "OUTPUT";
    }
}

void StrongswanFirewall::BuildRuleProtocol(
    ostringstream&  rule,
    const char *    prefix,
    const char *    protocol
)
{
    if (protocol)
    {
        rule << " " << prefix << " " << protocol;
    }
}

void StrongswanFirewall::BuildRuleAddr(
    ostringstream&  rule,
    const char *    prefix,
    string          addr
)
{
    if (addr != "")
    {
        IPAddress ip(addr.c_str());
        isIPv6 = ip.CheckIfIPv6();
        rule << " " << prefix << " " << ip.Get();
    }
}

void StrongswanFirewall::BuildRulePort(
    ostringstream&  rule,
    const char *    prefix,
    u16             port
)
{
    if (port)
    {
        rule << " " << prefix << " " << port;
    }
}

void StrongswanFirewall::BuildRule(
    ostringstream&  rule,
    bool            in,
    const char *    protocol,
    string          fromAddr,
    u16             fromPort,
    string          toAddr,
    u16             toPort
)
{
    BuildRuleChain(rule, in);
    BuildRuleProtocol(rule, "--protocol", protocol);
    BuildRuleAddr(rule, "--src", fromAddr);
    BuildRulePort(rule, "--sport", fromPort);
    BuildRuleAddr(rule, "--dst", toAddr);
    BuildRulePort(rule, "--dport", toPort);
    rule << " --jump ACCEPT";
}

u32 StrongswanFirewall::AppendRule(
    ostringstream&  rule
)
{
    std::string ruleStr = rule.str();

    ostringstream command;
    if(isIPv6)
    {
        command << "ip6tables --append " << ruleStr;
    }
    else
    {
        command << "iptables --append " << ruleStr;
    }

    TRACE_PRINTF("updating firewall rules: %s", command.str().c_str());
    if (0 == system(command.str().c_str()))
    {
        u32 handle = ++m_handle;
        InsertRule(handle, ruleStr);
        return handle;
    }

    return 0;
}

void StrongswanFirewall::DeleteRule(
    u32 handle
)
{
    if (HaveRule(handle))
    {
        std::string ruleStr = RemoveRule(handle);

        ostringstream command;
        if(isIPv6)
        {
           command << "ip6tables --delete " << ruleStr.c_str();
        }
        else
        {
           command << "iptables --delete " << ruleStr.c_str();
        }

        TRACE_PRINTF("updating firewall rules: %s", command.str().c_str());
        if(system(command.str().c_str()) != oam_ret_zero)
	{
		TRACE_MSG("StrongswanFirewall::DeleteRule, Failed to delete Firewall rules");
	}
    }
}

void StrongswanFirewall::Open(
    shared_ptr<TenpinFirewallOpenReq>   req,
    FirewallHandles&                    handles
)
{
    const char * protocol = NULL;

    if (req->GetProtocolUdp())
    {
        protocol = "udp";
    }

    if (req->GetPassIn())
    {
        ostringstream rule;
        BuildRule(
            rule,
            true,
            protocol,
            req->GetRemoteAddr(),
            req->GetRemotePort(),
            req->GetLocalAddr(),
            req->GetLocalPort()
        );
        handles.push_back(AppendRule(rule));
    }

    if (req->GetPassOut())
    {
        ostringstream rule;
        BuildRule(
            rule,
            false,
            protocol,
            req->GetLocalAddr(),
            req->GetLocalPort(),
            req->GetRemoteAddr(),
            req->GetRemotePort()
        );
        handles.push_back(AppendRule(rule));
    }
}

void StrongswanFirewall::Close(
    const FirewallHandles&  handles
)
{
    for (FirewallHandles::const_iterator it = handles.begin(); it != handles.end(); it++)
    {
        DeleteRule(*it);
    }
}
