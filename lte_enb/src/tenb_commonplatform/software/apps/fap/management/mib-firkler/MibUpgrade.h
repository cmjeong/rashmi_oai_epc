///////////////////////////////////////////////////////////////////////////////
//
// MibUpgrade.h
//
// This is an encapsulation of the Mib upgrade procedure.
// A call to Perform() will upgrade the MIB.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MibUpgrade_h_
#define __MibUpgrade_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <map>

#include <boost/shared_ptr.hpp>
#include <mib-core/NonVolatileStoreInterface.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MibUpgrader.h"

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class MibUpgrade
{
public:
    /***
     * Perform the upgrade for the necessary files that are collectively the MIB.
     * Do *not* call this function whilst a MIB is valid as this could potentially
     * invalidate the MIB.
     * @param currentVersion
     */
    static void UpdateOamMiBDirPath(); 
    static void DoMibUpgrade();

private:
    // This will perform the upgrade.
    static void Perform(NvStoreSchemaVersion targetVersion, const std::string& nvStoreFile, bool isFactoryFile, bool isHomeFapBuild);

    // Perform an individual upgrade step.
    static void UpgradeFactoryFile(NvStoreSchemaVersion targetSchema, NonVolatileStoreUpgradeDowngradeInterface& schemingNvStore, bool isHomeFapBuild);
    static void UpgradeOperationalFile(NvStoreSchemaVersion targetSchema, NonVolatileStoreUpgradeDowngradeInterface& schemingNvStore, bool isHomeFapBuild);

    static void Upgrade0To1(NonVolatileStoreUpgradeDowngradeInterface &schemingNvStore, bool isFactoryFile);
    static void UpgradeOperational0To1(NonVolatileStoreUpgradeDowngradeInterface &schemingNvStore);
    static void UpgradeOperational1To2(NonVolatileStoreUpgradeDowngradeInterface &schemingNvStore, bool isHomeFapBuild);
    static void UpgradeOperational2To3(NonVolatileStoreUpgradeDowngradeInterface &schemingNvStore, bool isHomeFapBuild);
    static void UpgradeOperational3To4(NonVolatileStoreUpgradeDowngradeInterface &schemingNvStore);
    static void UpgradeOperational4To5(NonVolatileStoreUpgradeDowngradeInterface &schemingNvStore);
    static void UpgradeOperational5To6(NonVolatileStoreUpgradeDowngradeInterface &schemingNvStore);
    static void UpgradeOperational6To7(NonVolatileStoreUpgradeDowngradeInterface &schemingNvStore);
    static void UpgradeOperational7To8(NonVolatileStoreUpgradeDowngradeInterface &schemingNvStore);
    static void UpgradeOperational8To9(NonVolatileStoreUpgradeDowngradeInterface &schemingNvStore);
    static void UpgradeOperational9To10(NonVolatileStoreUpgradeDowngradeInterface &schemingNvStore);
    static void UpgradeOperational10To11(NonVolatileStoreUpgradeDowngradeInterface &schemingNvStore);
    static void UpgradeFactory1To2(NonVolatileStoreUpgradeDowngradeInterface &schemingNvStore);


    static void PerformNameSwap(std::string & potentialName);

};

#endif // __MibUpgrade_h_
