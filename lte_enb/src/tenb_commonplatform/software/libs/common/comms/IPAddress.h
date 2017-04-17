///////////////////////////////////////////////////////////////////////////////
//
// IPAddress.h
//
// General purpose class representing a v4 IP address.
//
// Copyright Radisys Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __IPAddress_h_
#define __IPAddress_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <netinet/ip.h>
#include <vector>
#include <cstring>
#include <3waytypes.h>
#include "IPv4Address.h"
#include "IPv6Address.h"
#include <arpa/inet.h>
#include<system/Trace.h>
#define IPMAXSIZE 39
///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class IPAddress
{
public:
    IPAddress()
    {  
         m_isIPv6 = false;
    }
       
    IPAddress(const char * ipAddress)
    {
      Set(ipAddress);
    }
    void Set(const char *ipAddress) ;
    bool CheckIfIPv6() const;
    char * Get() const;
    void Clear() ;
    threeway::IPv4Address ipv4;
    threeway::IPv6Address ipv6;

private:
    bool m_isIPv6;
    mutable char m_ipString[IPMAXSIZE];
};


#endif
