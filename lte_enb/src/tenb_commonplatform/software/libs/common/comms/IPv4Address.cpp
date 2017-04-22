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

#include "IPv4Address.h"


namespace threeway
{

IPv4Address::IPv4Address() :
    m_isSet(false),
    m_ipAddress(0)
{
    ENTER();

    m_asString[0] = '\0';

    EXIT();
}

IPv4Address::IPv4Address(const char * ipAddress) :
    m_isSet(true)
{
    ENTER();

    m_asString[0] = '\0';
    Set(ipAddress);

    EXIT();
}

IPv4Address::IPv4Address(u8 digit0, u8 digit1, u8 digit2, u8 digit3)
{
    ENTER();

    m_asString[0] = '\0';
    SetDigits(digit0, digit1, digit2, digit3);

    EXIT();
}

IPv4Address::IPv4Address(u32 ipAddress)
{
    ENTER();

    m_ipAddress = ipAddress;
    m_asString[0] = '\0';
    m_isSet = true;

    EXIT();
}

IPv4Address::IPv4Address(const IPv4Address& rhs)
{
    ENTER();

    m_asString[0] = '\0';
    m_isSet = rhs.m_isSet;
    m_ipAddress = rhs.m_ipAddress;

    EXIT();
}

IPv4Address::~IPv4Address()
{
    ENTER();
    EXIT();
}

void IPv4Address::Clear()
{
    ENTER();

    m_isSet = false;
    m_ipAddress = 0;

    EXIT();
}

void IPv4Address::SetDigits(u8 digit0, u8 digit1, u8 digit2, u8 digit3)
{
    ENTER();

    // Store in memory NBO.
    u8* pIpAddress = (u8*)&m_ipAddress;
    pIpAddress[0] = digit0;
    pIpAddress[1] = digit1;
    pIpAddress[2] = digit2;
    pIpAddress[3] = digit3;
    m_isSet = true;

    EXIT();
}

void IPv4Address::Set(u32 ipAddress)
{
    ENTER();

    m_ipAddress = ipAddress;
    m_isSet = true;

    EXIT();
}

void IPv4Address::Set(const char *ipAddress)
{
    ENTER();

    Set(inet_addr(ipAddress)); // inet_addr will return value that is NBO (i.e. is NBO in memory).

    EXIT();
}

void IPv4Address::Set(struct in_addr ipAddress)
{
    ENTER();

    u32 ipAddrU32 = htonl(ipAddress.s_addr);
    u8 msByte, byte2, byte3, lsByte;

    U32ToBytes(ipAddrU32, &msByte, &byte2, &byte3, &lsByte);
    SetDigits(msByte, byte2, byte3, lsByte);

    EXIT();
}

bool IPv4Address::GetDigits(u8 &digit0, u8 &digit1, u8 &digit2, u8 &digit3) const
{
    ENTER();

    // IP address is stored NBO.
    u8* pIpAddress = (u8*)&m_ipAddress;
    digit0 = pIpAddress[0];
    digit1 = pIpAddress[1];
    digit2 = pIpAddress[2];
    digit3 = pIpAddress[3];

    RETURN(m_isSet);
}

bool IPv4Address::Get(u32 &ipAddress) const
{
    ENTER();

    ipAddress = m_ipAddress;

    RETURN(m_isSet);
}

u32 IPv4Address::Get() const
{
    ENTER();

    RETURN(m_ipAddress);
}

bool IPv4Address::Get(char *ipAddress) const
{
    ENTER();

    u8 digit0, digit1, digit2, digit3;

    GetDigits(digit0, digit1, digit2, digit3);
    snprintf(ipAddress, 16, "%u.%u.%u.%u", digit0, digit1, digit2, digit3);

    RETURN(m_isSet);
}

IPv4Address& IPv4Address::operator=(const IPv4Address& rhs)
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

bool IPv4Address::operator==(const IPv4Address &ipAddress) const
{
    return(m_ipAddress == ipAddress.m_ipAddress);
}

bool IPv4Address::operator!=(const IPv4Address &ipAddress) const
{
    return(!operator==(ipAddress));
}

bool IPv4Address::operator<(const IPv4Address &ipAddress) const
{
    return(m_ipAddress < ipAddress.m_ipAddress);
}

bool IPv4Address::operator>(const IPv4Address &ipAddress) const
{
    return(m_ipAddress > ipAddress.m_ipAddress);
}

const IPv4Address& IPv4Address::operator++()
{
    // I'm sure this could be more cunning but this is hopefully clear!
    // Have to really keep an eye on that endian-ness...
    u8 digit0, digit1, digit2, digit3;
    GetDigits(digit0, digit1, digit2, digit3);
    u32 intVal = (((u32)digit0) << 24) +
                 (((u32)digit1) << 16) +
                 (((u32)digit2) << 8) +
                 (u32)digit3;

    // Do the increment then store back as individual digits.
    intVal++; // Will wrap as expected 255.255.255.255 -> 0.0.0.0

    SetDigits((u8)((intVal >> 24) & 0xFF),
              (u8)((intVal >> 16) & 0xFF),
              (u8)((intVal >> 8) & 0xFF),
              (u8)(intVal & 0xFF));

    return *this;
}

const char *IPv4Address::ToString() const
{
    ENTER();

    Get(m_asString);

    RETURN(m_asString);
}

IPv4Address operator+(IPv4Address ipAddress, s32 increment)
{
    // I'm sure this could be more cunning but this is hopefully clear!
    // Have to really keep an eye on that endian-ness...
    u8 digit0, digit1, digit2, digit3;
    ipAddress.GetDigits(digit0, digit1, digit2, digit3);
    u32 intVal = (((u32)digit0) << 24) +
                 (((u32)digit1) << 16) +
                 (((u32)digit2) << 8) +
                 (u32)digit3;

    // Do the increment.
    intVal += increment;

    IPv4Address retIpAddress((u8)((intVal >> 24) & 0xFF),
                             (u8)((intVal >> 16) & 0xFF),
                             (u8)((intVal >> 8) & 0xFF),
                             (u8)(intVal & 0xFF));
    return retIpAddress;
}

bool IPv4Address::GetEthernetAddress (const char *ethernetDevice, IPv4Address &ipAddress)
{
    ENTER ();
    TRACE ("Trying To Detect Address Of", ethernetDevice);

    RSYS_ASSERT(ethernetDevice != NULL);
    RSYS_ASSERT(strlen(ethernetDevice) > 0);

    s32 socketNumber = socket (AF_INET, SOCK_STREAM, 0);
    if (socketNumber == (-1))
    {
        TRACE_PRINTF("ERROR: GetEthernetAddress, Socket creation failed %d\n", socketNumber);
        RETURN (false);
    }

    struct ifreq ifReq;
    memset (&ifReq, 0, sizeof (struct ifreq));

    strncpysafe (ifReq.ifr_name, ethernetDevice, sizeof(ifReq.ifr_name));
    ifReq.ifr_addr.sa_family = AF_INET;

    if (ioctl (socketNumber, SIOCGIFADDR, &ifReq) == 0)
    {
        struct sockaddr_in sin;

        // Copy to overcome accessing restricted pointer of a different type
        memcpy(&sin, &ifReq.ifr_addr, sizeof(sin));

        ipAddress.Clear ();
        ipAddress.Set (inet_ntoa(sin.sin_addr));
        TRACE ("Located Address: It's", ipAddress.ToString ());
    }//end if

    close(socketNumber);
    RETURN (true);
}

size_t IPv4Address::GetHostByName(const char * hostname, vector<IPv4Address> & addresses )
{
    // To clear or not to clear...
    //addresses.clear();

    if(hostname)
    {
        TRACE_PRINTF("IPv4Address::GetHostByName( %s ) BLOCKING call.", hostname );

        struct hostent *host = gethostbyname( hostname );

        /* Get host data */
        if (host)
        {
            for( int i = 0; host->h_addr_list[i] != NULL; i++)
            {
                struct in_addr * inAddr = (struct in_addr *)host->h_addr_list[i];

                IPv4Address ipAddress;
                ipAddress.Set( *inAddr );

                addresses.push_back(ipAddress);

                TRACE_PRINTF("IPv4Address::GetHostByName( %s ) is %s.", hostname, ipAddress.ToString() );
            }
        }
    }

    return addresses.size();
}


}
