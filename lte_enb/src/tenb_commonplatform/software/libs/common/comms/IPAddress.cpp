///////////////////////////////////////////////////////////////////////////////
//
// IPAddress.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
//////////////////////////////////////////////////////////////////////////////


#include "IPAddress.h"

void IPAddress::Clear() 
{
   if(m_isIPv6)
   {
      ipv6.Clear();
   }
   else
   {
      ipv4.Clear();
   }
   m_ipString[0] = '\0';
}

bool IPAddress::CheckIfIPv6() const
{
   return m_isIPv6;
}

char * IPAddress::Get() const
{
   return m_ipString;
}

void IPAddress::Set(const char *ipAddress) 
{
   strcpy(m_ipString,ipAddress);
   struct in6_addr inaddr= {};
   bool valid = true;
   if(inet_pton(AF_INET6,ipAddress,&inaddr)==1)
   {
         m_isIPv6 = true;
   }
   else
   {
       struct in_addr inaddr4= {};
       if(inet_pton(AF_INET,ipAddress,&inaddr4)!=1)
       {
          TRACE_PRINTF("NEITHER VALID IPV6 ADDRESS NOR VALID IPV4 ADDRESS:%s",ipAddress);
          valid = false;
       }   
       m_isIPv6 = false;
    }
   if(valid)
   {
       if(m_isIPv6)
       {
             ipv6.Set(ipAddress);
       }
       else 
       {
             ipv4.Set(ipAddress);
       }
   }
}



