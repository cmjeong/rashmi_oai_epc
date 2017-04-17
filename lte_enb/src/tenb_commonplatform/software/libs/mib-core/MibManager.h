///////////////////////////////////////////////////////////////////////////////
//
// MibManager.h
//
// A class to encapsulate MibObject creation and deletion
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MibManager_h_
#define __MibManager_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <Radisys.h>
#include <boost/shared_ptr.hpp>
#include <mib-common/MibAttributeValuesByDn.h>
#include <mib-common/MibAttributeIdsByDn.h>
#include <mib-common/MibObjectClassesByDn.h>
#include <mib-common/MibObjectDeleteResult.h>
#include <system/Utilities.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MibInterface.h" // inherited
#include "MibObject.h"
#include "NonVolatileStoreInterface.h"
#include "MibSubscriptionManager.h" // inherited

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class MibManager : public MibInterface
{
public:
    /**
     * Default constructor.
     */
    MibManager(MibSubscriptionNotifyInterface* subscriptionNotifyInterface);

    /**
     * Destructor.
     */
    virtual ~MibManager();

    /**
     * Implement MibInterface.
     */
    virtual void CreateObject(const MibDN& parent, const MibRDN & childRdn);
    virtual void CreateObject(const MibDN& parent, const MibRDN & childRdn, const MibAttributeValues& attributeValues);
    virtual MibObjectDeleteResult DeleteObject(const MibDN& dnToDelete);
    virtual boost::weak_ptr<MibObject> FindMibObject(const MibDN& dn) const;
    virtual boost::weak_ptr<MibObject> FindMibObjectNoAssert(const MibDN& dn, bool &isPresent) const;
    virtual MibAttrValidationFailures ValidateAttributes(const MibDN& moDn, const MibAttributeValues& attributeValues, bool checkAccessClass = true) const;
    virtual void SetAttributes(const MibDN& moDn, const MibAttributeValues& attributeValues, bool forced = false);
    virtual void GetAttributes(const MibDN& moDn,
                               const MibAttributeIds& attributeIds,
                               MibAttributeValues& mibAttributeValues) const;
    virtual void DeleteAttributes(const MibDN& moDn,
                                  const MibAttributeIds& attributeIds);

    /**
     * Get all attribute values where the current value differs from the default.
     */
    void GetAttributesDiffFromDefaults(MibAttributeValuesByDn& diffFromDefaultValuesByDn);

    /**
     * Get all attribute values that have been explicitly set in NV.
     */
    void GetAttributesSetInNv(MibAttributeValuesByDn& setInNvValuesByDn);

    /**
     * Reset entire MIB to factory defaults.  This means delete everything in the operational
     * NV store except specific attributes.
     * TODO: This is currently quite simplistic as it only affects the NV store and we don't change the
     * in-memory MIB.  We expect to reboot but have a short period of time where the two are inconsistent.
     * So resetting to factory defaults sets a flag that prevents further NV MIB changes to protect against this.
     */
    void ResetNvToFactoryDefaults();

    /**
     * Delegates to MibSubscriptionManager
     */
    void AddSubscription(
            u32 subscriberId,
            const char * subscriberName,
            u32 subscriptionId ,
            const MibAttributeIdsByDn& subscribedAttributes ,
            const MibObjectClassesByDn& subscribedObjects);

    void RemoveSubscription(u32 subscriberId, u32 subscriptionId);

    /**
     * Dump subscriptions.
     */
    std::string SubscriptionsToString() const;

    char* m_pOamConfigFilesDir;

    std::string m_sOamConfigFilesDir;

    void UpdateNvDirPath(const char *path);

    /**
     * To check NV files are properly read
     */
    bool nvStoreInitialized;
    u16 numOfCells;
private:
    /**
     * Return a weak_ptr to the desired object.
     * If the desired object does not exist in the tree then it will assert.
     * @param dn
     * @return boost::weak_ptr<MibObject>
     */
    boost::weak_ptr<MibObject> FindMibObjectByRelativeDn(MibDN dn, boost::shared_ptr<MibObject> current) const;
    boost::weak_ptr<MibObject> FindMibObjectByRelativeDnNoAssert(MibDN dn, boost::shared_ptr<MibObject> current, bool &isPresent) const;

    /**
     * This is the top of the normal operational MIB tree.
     * When this object is deleted, the tree will automatically disappear.
     */
    boost::shared_ptr<MibObject> m_mibRoot;

    /**
     * NV store for operational MOs.
     */
    shared_ptr<NonVolatileStoreInterface> m_operationalNvStore;

    /**
     * NV store for factory MOs.
     */
    shared_ptr<NonVolatileStoreInterface> m_factoryNvStore;

    /**
     * Attribute subscriptions.
     */
    shared_ptr<MibSubscriptionManager> m_subscriptionManager;
};

#endif
