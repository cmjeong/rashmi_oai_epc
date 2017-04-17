///////////////////////////////////////////////////////////////////////////////
//
// SystemConfiguration.h
//
// Contents of the 3Way_SystemConfiguration.txt file.  Contains things like
// the network timers, etc.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __SystemConfiguration_h_
#define __SystemConfiguration_h_

///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////

#include "NASTextFile.h"

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Class: SystemConfiguration
// Desc : Read the system configuration file, and provide accessors so the
//        various application settings can be retrieved.
///////////////////////////////////////////////////////////////////////////////
class SystemConfiguration : public NASTextFile
{
public:
	// Construction / destruction.
	SystemConfiguration ();
	virtual ~SystemConfiguration ();

	// Accessors for the parameters: should be safe to use the NAS_TRACE
	// macros for these.

	// Version Parameter name + value are globally defined and never change.
	u32 GetVersionNumber () const;

	bool GenerateTraceFiles () const;
	const char *GetInstallDir () const;
	const char *GetInstallDirNOTRACE () const;
	const char *GetTraceDir () const;
	u32 GetTraceFileLimit () const;
	bool CaptureSubscribersIMSI () const;
	const char *GetUDPLoggingAddress () const;
	u16 GetUDPLoggingPort (const char *appName) const;
	const char *GetSipMediaDestination () const;
};

#endif
