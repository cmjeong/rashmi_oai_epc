///////////////////////////////////////////////////////////////////////////////
//
// UpdateConstants.h
//
// Miscellaneous constants used by Update/FTP app.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef UPDATECONSTANTS_H_
#define UPDATECONSTANTS_H_

///////////////////////////////////////////////////////////////////////////////
// Local Constants
///////////////////////////////////////////////////////////////////////////////

// Paths and names for files and directories associated with SW update
static const string AppUpdateFirstRunFileName = "/mnt/config/app_package_first_run" ;
static const string AppUpdateFileName = "/mnt/config/app_package_update" ;
static const string AppFallbackFileName = "/mnt/config/app_package_fallback" ;
static const string AppActiveFileName = "/mnt/config/app_package_active" ;
static const string KernelUpdateFileName = "/mnt/config/kernel_update" ;
static const string AppPackageValidFileName = "app_package_valid" ;
static const string AppPackageUnpackedFileName = "app_package_unpacked" ;
static const string BankChecksumFileName = "bank.md5" ;

// Name of link used by TR069 to put updates in right place
static const string AppDownloadPathName = "/tmp/SwLoadFtpDest" ;

// Place where we actually expect updates to turn up
static const string AppUpdatePathName = "/tmp/updates" ;

// Identifiers for App source banks
#ifdef HARDWARE_hbs2_4
static const string AppBankA = "mtd:appsA" ;
static const string AppBankB = "mtd:appsB" ;
#else
static const string AppBankA = "AppImageA" ;
static const string AppBankB = "AppImageB" ;
#endif
// Identifiers for links to active/inactive SW banks
static const string ActiveBank = "/mnt/bank-active" ;
static const string InactiveBank ="/mnt/install" ;
static const string ActiveDbx = "/mnt/dbx" ;

// String for kernel update flag
static const string KernelUpdateIsRequired = "True" ;
static const string KernelUpdateNotRequired = "False" ;

static const string compatibilityFileName = "UpdateInfo.txt" ;
static const string contentFileName = "UpdateInfo.txt" ;

static const string preInstallScriptFilename = "PreInstallScript" ;
static const string postInstallScriptFilename = "PostInstallScript" ;
static const string postDownloadScriptFilename = "PostDownloadScript" ;
static const string stopAppsForUpdateScriptFilename = "StopAppsForUpdate" ;

const u32 ErrorStringLength = 128 ;
const size_t maxLinkTargetLen = 30;


typedef enum
{
	UPDATE_APPS,
	UPDATE_CERTIFICATES,
	UPDATE_KERNEL,
    UPDATE_UBOOT,
    UPDATE_CONTENT_INVALID
} SwUpdateContent;

#endif /* UPDATECONSTANTS_H_ */
