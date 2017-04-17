///////////////////////////////////////////////////////////////////////////////
//
// TenpinResolvConfDns.h
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __TenpinResolvConfDns_h_
#define __TenpinResolvConfDns_h_

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "TenpinStackInterfaces.h"

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

namespace threeway
{

class TenpinResolvConfDns : public ITenpinDns
{
public:
    // Singleton
    virtual ~TenpinResolvConfDns() {}
    static shared_ptr<TenpinResolvConfDns> GetInstance();

    // Implement ITenpinStackDns
    virtual void Add(u32 id, const IPv4Address& serverAddr);
    virtual void Remove(u32 id);

private:
    // Singleton
    TenpinResolvConfDns() :
        m_configFilename("/etc/resolv.conf"),
        m_tempFilename("/etc/resolv.tmp")
    {}
    static shared_ptr<TenpinResolvConfDns> s_instance;

    const char * m_configFilename;
    const char * m_tempFilename;

    // Helpers
};

} // namespace threeway

#endif
