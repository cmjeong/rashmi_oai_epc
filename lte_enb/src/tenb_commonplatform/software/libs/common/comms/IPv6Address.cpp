///////////////////////////////////////////////////////////////////////////////
//
// IPv4Address.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <net/if.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <memory.h>
#include <unistd.h>

#include <system/Trace.h>
#include <system/NumberConversions.h>
#include <system/StringUtils.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "IPv6Address.h"


namespace threeway
{

IPv6Address::IPv6Address() :
    m_isSet(false)
{
    ENTER();
    memset(m_ipAddress.s6_addr16,0,sizeof(m_ipAddress));
    m_asString[0] = '\0';
    EXIT();
}

IPv6Address::IPv6Address(const char * ipAddress) :
    m_isSet(true)
{
    ENTER();

    m_asString[0] = '\0';
    Set(ipAddress);

    EXIT();
}

IPv6Address::IPv6Address(u16 hexdigit0, u16 hexdigit1, u16 hexdigit2, u16 hexdigit3,u16 hexdigit4,u16 hexdigit5,u16 hexdigit6,u16 hexdigit7)
{
    ENTER();

    m_asString[0] = '\0';
    SetDigits(hexdigit0, hexdigit1, hexdigit2, hexdigit3, hexdigit4, hexdigit5, hexdigit6, hexdigit7);

    EXIT();
}

IPv6Address::IPv6Address(u16 ipAddress[])
{
    ENTER();
   
    SetDigits(ipAddress[0],ipAddress[1],ipAddress[2],ipAddress[3],ipAddress[4],ipAddress[5],ipAddress[6],ipAddress[7]);
    m_asString[0] = '\0';

    EXIT();
}

IPv6Address::IPv6Address(const IPv6Address& rhs)
{
    ENTER();

    m_asString[0] = '\0';
    m_isSet = rhs.m_isSet;
    m_ipAddress = rhs.m_ipAddress;

    EXIT();
}

IPv6Address::~IPv6Address()
{
    ENTER();
    EXIT();
}

void IPv6Address::Clear()
{
    ENTER();

    m_isSet = false;
    memset(m_ipAddress.s6_addr16,0,sizeof(m_ipAddress));

    EXIT();
}

void IPv6Address::SetDigits(u16 digit0, u16 digit1, u16 digit2, u16 digit3,u16 digit4,u16 digit5,u16 digit6,u16 digit7)
{
    ENTER();
    char ipAddress[39];

   string hexdigit0 = DecimalToHexadecimal(digit0);
   string hexdigit1 = DecimalToHexadecimal(digit1);
   string hexdigit2 = DecimalToHexadecimal(digit2);
   string hexdigit3 = DecimalToHexadecimal(digit3);
   string hexdigit4 = DecimalToHexadecimal(digit4);
   string hexdigit5 = DecimalToHexadecimal(digit5);
   string hexdigit6 = DecimalToHexadecimal(digit6);
   string hexdigit7 = DecimalToHexadecimal(digit7);
   snprintf(ipAddress, 39, "%s:%s:%s:%s:%s:%s:%s:%s", hexdigit0.c_str(), hexdigit1.c_str(), hexdigit2.c_str(), hexdigit3.c_str(), hexdigit4.c_str(), hexdigit5.c_str(), hexdigit6.c_str(), hexdigit7.c_str());
    Set(ipAddress);
    m_isSet = true; 

    EXIT();
}

void IPv6Address::Set(u16 ipAddress[])
{
    ENTER();
    SetDigits(ipAddress[0],ipAddress[1],ipAddress[2],ipAddress[3],ipAddress[4],ipAddress[5],ipAddress[6],ipAddress[7]);
    m_isSet = true;

    EXIT();
}

void IPv6Address::Set(const char *ipAddress)
{
    ENTER();
    struct in6_addr inaddr= {};
    if(inet_pton(AF_INET6,ipAddress,&inaddr)==1)
    {
        m_ipAddress = inaddr;
        m_isSet = true;
    }
    else
    {
       TRACE_PRINTF("ERROR:INCORRECT IPV6 ADDRESS");
    }

    EXIT();
}

void IPv6Address::Set(struct in6_addr ipAddress)
{
    ENTER();

    m_ipAddress = ipAddress; 

    EXIT();
}
bool IPv6Address::GetDigitsU8(u8 digitu8[]) const
{
   ENTER();
   int i=0,j=0;
   while(i<16)
   {
         digitu8[i] =  (ntohs(m_ipAddress.s6_addr16[j]) >>8) & 0xFF;
         //printf("\n *** rakesh digitu8[%d]=%x m_ipAddress.s6_addr16[%d]=%x",i,digitu8[i],j,ntohs(m_ipAddress.s6_addr16[j]));
         i++;
         digitu8[i] =  (ntohs(m_ipAddress.s6_addr16[j])) & 0xFF;
         //printf("\n *** rakesh digitu8[%d]=%x m_ipAddress.s6_addr16[%d]=%x",i,digitu8[i],j,ntohs(m_ipAddress.s6_addr16[j]));
         i++;
         j++;
   }
   RETURN(m_isSet);
}
bool IPv6Address::GetDigits(u16 &digit0, u16 &digit1, u16 &digit2, u16 &digit3, u16 &digit4, u16 &digit5, u16 &digit6, u16 &digit7) const
{
    ENTER();

    digit0 = ntohs(m_ipAddress.s6_addr16[0]);
    digit1 = ntohs(m_ipAddress.s6_addr16[1]);
    digit2 = ntohs(m_ipAddress.s6_addr16[2]);
    digit3 = ntohs(m_ipAddress.s6_addr16[3]);
    digit4 = ntohs(m_ipAddress.s6_addr16[4]);
    digit5 = ntohs(m_ipAddress.s6_addr16[5]);
    digit6 = ntohs(m_ipAddress.s6_addr16[6]);
    digit7 = ntohs(m_ipAddress.s6_addr16[7]);

    RETURN(m_isSet);
}

bool IPv6Address::Get(u16 ipAddress[]) const
{
    ENTER();
    GetDigits(ipAddress[0],ipAddress[1],ipAddress[2],ipAddress[3],ipAddress[4],ipAddress[5],ipAddress[6],ipAddress[7]);
    RETURN(m_isSet);
}
bool IPv6Address::Get(u8 ipAddress[]) const
{
    ENTER();
    GetDigitsU8(ipAddress);
    RETURN(m_isSet);
}
in6_addr IPv6Address::Get() const
{
    ENTER();

    RETURN(m_ipAddress);
}

bool IPv6Address::Get(char *ipAddress) const
{
    ENTER();

    u16 digit0, digit1, digit2, digit3, digit4, digit5, digit6, digit7;

    GetDigits(digit0, digit1, digit2, digit3, digit4, digit5, digit6, digit7);
    snprintf(ipAddress, 39, "%x:%x:%x:%x:%x:%x:%x:%x", digit0, digit1, digit2, digit3, digit4, digit5, digit6, digit7);

    RETURN(m_isSet);
}

string IPv6Address::DecimalToHexadecimal(u16 digit) const
{
   stringstream hexdecimal;
   hexdecimal<<std::hex<<digit;
   return(hexdecimal.str());
}
IPv6Address& IPv6Address::operator=(const IPv6Address& rhs)
{
    ENTER();

    // Check for self-assignment.
    if(this == &rhs)
    {
        RETURN(*this);
    }

    m_isSet = rhs.m_isSet;
    m_ipAddress = rhs.m_ipAddress;

    RETURN(*this);
}

bool IPv6Address::operator==(const IPv6Address &ipAddress) const
{
    return(!strcmp(ipAddress.ToString(),this->ToString()));
      
}

bool IPv6Address::operator!=(const IPv6Address &ipAddress) const
{
    return(!operator==(ipAddress));
}

bool IPv6Address::operator<(const IPv6Address &ipAddress) const
{
   
    int noOfDigits = sizeof(struct in6_addr)/(m_ipAddress.s6_addr16[0]);
    for(int digit = 0;digit < noOfDigits ;digit++)
    { 
       if(ntohs(m_ipAddress.s6_addr16[digit]) < ntohs(ipAddress.m_ipAddress.s6_addr16[digit]))
       {
          return true;
       }
    }
    return false;
}
    

bool IPv6Address::operator>(const IPv6Address &ipAddress) const
{
   int noOfDigits = sizeof(struct in6_addr)/sizeof(m_ipAddress.s6_addr16[0]);
   for(int digit = 0;digit < noOfDigits ;digit++)
   {
       if(ntohs(m_ipAddress.s6_addr16[digit]) > ntohs(ipAddress.m_ipAddress.s6_addr16[digit]))
       {
           return true;
       }
   }
   return false;
}


const char *IPv6Address::ToString() const
{
    ENTER();

    Get(m_asString);

    RETURN(m_asString);
}

bool IPv6Address::GetEthernetAddress (const char *ethernetDevice, IPv6Address &ipAddress)
{
    ENTER ();
    TRACE ("Trying To Detect Address Of", ethernetDevice);

    RSYS_ASSERT(ethernetDevice != NULL);
    RSYS_ASSERT(strlen(ethernetDevice) > 0);

    s32 socketNumber = socket (AF_INET6, SOCK_STREAM, 0);
    if (socketNumber == (-1)) 
    {
	TRACE_PRINTF("ERROR: GetEthernetAddress, Socket creation failed %d\n", socketNumber);
    	RETURN (false);
    }
	
    struct ifreq ifReq;
    memset (&ifReq, 0, sizeof (struct ifreq));

    strncpysafe (ifReq.ifr_name, ethernetDevice, sizeof(ifReq.ifr_name));
    ifReq.ifr_addr.sa_family = AF_INET6;

    if (ioctl (socketNumber, SIOCGIFADDR, &ifReq) == 0)
    {
        struct sockaddr_in6 sin;

        // Copy to overcome accessing restricted pointer of a different type
        /* Kloc work fix for ABV.ANY_SIZE_ARRAY */
        memcpy(&sin, &ifReq.ifr_addr, sizeof(ifReq.ifr_addr));

        ipAddress.Clear ();
        ipAddress.Set (sin.sin6_addr);
        TRACE ("Located Address: It's", ipAddress.ToString ());
    }//end if

    close(socketNumber);
    RETURN (true);
}

size_t IPv6Address::GetHostByName(const char * hostname, vector<IPv6Address> & addresses )
{
    // To clear or not to clear...
    addresses.clear();

    if(hostname)
    {
        TRACE_PRINTF("IPv6Address::GetHostByName( %s ) BLOCKING call.", hostname );

        struct hostent *host = gethostbyname2( hostname, AF_INET6);

        //Get host data 
        if (host)
        {
            for( int i = 0; host->h_addr_list[i] != NULL; i++)
            {
                struct in6_addr * inAddr = (struct in6_addr *)host->h_addr_list[i];

                IPv6Address ipAddress;
                ipAddress.Set( *inAddr );

                addresses.push_back(ipAddress);

                TRACE_PRINTF("IPv6Address::GetHostByName( %s ) is %s.", hostname, ipAddress.ToString() );
            }
        }
   }

    return addresses.size();
}


}
