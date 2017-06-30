///////////////////////////////////////////////////////////////////////////////
//
// 3 Way Networks Source File
//
///////////////////////////////////////////////////////////////////////////////
//
// UeIpConfiguration.cpp
//
// Contents of the nas-ue-ip-configuration file.
//
// Copyright � 3 Way Networks, Ltd.
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <System3Way.h>
#include <NASTrace.h>
#include <NASString.h>
#include <comms/IPv4Address.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "UeIpConfiguration.h"

using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Local Definitions
///////////////////////////////////////////////////////////////////////////////

// Default DNS servers.
// These are fairly randomly chosen to be those offered by dnsmax.com
// http://my.dnsmax.com/help/faq.php - down the bottom for server domain names.
static const char DEFAULT_UE_PRIMARY_DNS_SERVER[] = "65.98.81.93";
static const char DEFAULT_UE_SECONDARY_DNS_SERVER[] = "69.72.159.22";

///////////////////////////////////////////////////////////////////////////////
// Class: UeIpConfiguration
// Desc : Read the UE IP configuration file, and provide accessors so the
//        various application settings can be retrieved.
///////////////////////////////////////////////////////////////////////////////
UeIpConfiguration::UeIpConfiguration() :
	NASTextFile ("/mnt/bank-active/config/", NAS_UE_IP_CONFIGURATION)
{
}

UeIpConfiguration::~UeIpConfiguration ()
{
}

void UeIpConfiguration::GetLeases(IPv4Address& baseAddress, u32 &numberOfLeases)
{
    NAS_ENTER ();

    baseAddress.Set(GetStringParameter ("FirstLeaseAddress"));
    numberOfLeases = GetU32Parameter ("NumberOfLeases", 0);

    NAS_EXIT ();
}

void UeIpConfiguration::GetForbiddenList(NumberList &numberList)
{
    NAS_ENTER ();

    u32 numberOfForbiddenLeases = GetU32Parameter ("NumberOfForbiddenAddresses", 0);
    NAS_TRACE ("Number Of Forbidden Addresses Is", numberOfForbiddenLeases);

    for (u32 i=1;i<=numberOfForbiddenLeases;i++)
    {
        NASString searchString;
        snprintf ((char *) searchString, searchString.GetSize(), "ForbiddenAddress_%" PRIu32, i);

        const char *ipAddressStr = GetStringParameter ((const char *) searchString, "0.0.0.0");
        NAS_TRACE ("Loaded Forbidden Address", ipAddressStr);

        IPv4Address ipAddress(ipAddressStr);
        numberList.push_back (ipAddress.Get());
    }//end for

    NAS_EXIT ();
}

const char * UeIpConfiguration::GetUePrimaryDnsServer() const
{
    NAS_ENTER ();
    NAS_RETURN (GetStringParameter("UePrimaryDnsServer", DEFAULT_UE_PRIMARY_DNS_SERVER));
}

const char * UeIpConfiguration::GetUeSecondaryDnsServer() const
{
    NAS_ENTER ();
    NAS_RETURN (GetStringParameter("UeSecondaryDnsServer", DEFAULT_UE_SECONDARY_DNS_SERVER));
}

u32 UeIpConfiguration::GetGgsnConnectionInactiveExpirySecs() const
{
    NAS_ENTER ();
    NAS_RETURN (GetU32Parameter("GgsnConnectionInactiveExpirySecs", 3600));
}
