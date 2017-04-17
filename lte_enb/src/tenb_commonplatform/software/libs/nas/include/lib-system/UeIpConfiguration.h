///////////////////////////////////////////////////////////////////////////////
//
// UeIpConfiguration.h
//
// Contents of the nas-ue-ip-configuration file.
//
// Copyright © 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __UeIpConfiguration_h_
#define __UeIpConfiguration_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <comms/IPv4Address.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "NASTextFile.h"
#include "NumberList.h"

///////////////////////////////////////////////////////////////////////////////
// Class: UeIpConfiguration
// Desc : Read the UE IP configuration file, and provide accessors so the
//        various application settings can be retrieved.
///////////////////////////////////////////////////////////////////////////////
class UeIpConfiguration : public NASTextFile
{
public:
	// Construction / destruction.
	UeIpConfiguration();
	virtual ~UeIpConfiguration();

	// Accessors for the parameters: should be safe to use the NAS_TRACE
	// macros for these.
	
    // UE IP address pool.
    void GetLeases(threeway::IPv4Address& baseAddress, u32& numberOfLeases);
    void GetForbiddenList(NumberList& numberList);

    // UE DNS servers.
    const char * GetUePrimaryDnsServer() const;
    const char * GetUeSecondaryDnsServer() const;

    // Inactivity timer for GGSN connections.
    u32 GetGgsnConnectionInactiveExpirySecs() const;
};

#endif
