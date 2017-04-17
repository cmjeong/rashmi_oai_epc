///////////////////////////////////////////////////////////////////////////////
//
// MibSubscriptionManager.h
//
// Manages subscriptions to MIB attributes.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MibSubscriptionManager_h_
#define __MibSubscriptionManager_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <Radisys.h>
#include <MibAttributeId.h>
#include <mib-common/MibAttributeValuesByDn.h>
#include <mib-common/MibAttributeIdsByDn.h>
#include <mib-common/MibObjectClassesByDn.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MibInterface.h"
#include "MibChangedAttributesNotifyInterface.h"
#include "MibObjectClass.h"

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

/**
 * Interface for informing client that it should send a subscription
 * to some client.  Done this way to avoid polluting this code with knowledge
 * of the transport mechanism to clients.
 * I.e. MibSubscriptionManager tells some other code to send the notifications.
 */
class MibSubscriptionNotifyInterface
{
public:
    virtual ~MibSubscriptionNotifyInterface() {};

    /**
     * Provide a list of objects with attribute values to send to the subscriber.
     */
    virtual void SendSubscriptionNotification(
            u32 subscriberId,
            u32 subscriptionId,
            const MibAttributeValuesByDn & mibAttributeValuesByDn) = 0;

    /**
     * Provide a list of attribute IDs to be deleted in subscriber.
     */
    virtual void SendSubscriptionDeleteNotification(u32 subscriberId, u32 subscriptionId,
                                                    const MibAttributeIdsByDn& deletedAttributeIdsByDn) = 0;

};


/**
 * Class for managing a set of subscriptions and informing subscribers about changes
 * to those subscriptions.  When one or more attribute values changes in a subscription
 * the subscriber will be sent the full set again.
 */
class MibSubscriptionManager : public MibChangedAttributesNotifyInterface
{
public:
    typedef enum
    {
        REMOVE_SUBSCRIPTION_OK,
        REMOVE_SUBSCRIPTION_NO_SUCH_SUB,
    } RemoveSubscriptionResult;

    /**
     * Default constructor.
     */
    MibSubscriptionManager(const MibInterface& mib, MibSubscriptionNotifyInterface& subscriptionNotifyInterface);

    /**
     * Destructor.
     */
    virtual ~MibSubscriptionManager();

    /**
     * Implement MibChangedAttributeNotifyInterface.
     */
    virtual void HandleChangedAttributes(const MibDN& dn,
                                         const MibAttributeIds& changedAttributeIds) const;
    virtual void HandleDeletedAttributes(const MibDN& dn,
                                         const MibAttributeIds& deletedAttributeIds) const;

    /**
     * Add a subscription.
     * Each subscriber can have multiple subscriptions - the subscription ID is assigned by the subscriber
     * and it is up to the subscriber to ensure they are unique.  Otherwise this method may well assert...
     */
    void AddSubscription(
            u32 subscriberId,
            const char * subscriberName,
            u32 subscriptionId,
            const MibAttributeIdsByDn& subscribedAttributes,
            const MibObjectClassesByDn& subscribedObjects );

    /**
     * Remove a subscription.
     */
    RemoveSubscriptionResult RemoveSubscription(u32 subscriberId, u32 subscriptionId);

    /**
     * Dump out our subscriptions.
     */
    std::string ToString() const;

private:

    /**
     * Internal function for doing the guts of HandleChanged/DeletedAttributes().
     */
    void HandleChangedOrDeletedAttributes(const MibDN& dn, const MibAttributeIds& attributeIds, bool attribsDeleted) const;

    /**
     * Injected dependencies.
     */
    const MibInterface& m_mibInterface;
    MibSubscriptionNotifyInterface& m_subscriptionNotifyInterface;

    /**
     * Subscriptions are stored for efficiency of lookup when attribute values change.
     * So there are two stores:
     *
     * 1. Indexed by DN, then by attribute ID to get to a list of subscriber + subscription ID pairs.
     *    So we can rattle through all changed attributes and build a list of subscriber/subscription pairs.
     *    => MibSubscriptionsByDn
     *
     * 2. Subscribe+Subscription ID pair to DN and list of attributes that form that subscription.
     *    So we can take our list of subscriber/subscription pairs and quickly find the complete list
     *    of attributes to send them.
     */

    /**
     * Uniquely identify a subscription.
     * Make it a class so we can use it in STL containers.
     */
    class MibSubscriptionIdentifier
    {
    public:
        u32 m_subscriberId;
        std::string m_subscriberName;
        u32 m_subscriptionId;
        bool operator==(const MibSubscriptionIdentifier& rhs) const;
        bool operator<(const MibSubscriptionIdentifier& rhs) const;
        bool operator>(const MibSubscriptionIdentifier& rhs) const { RSYS_ASSERT(false); return false; };

        std::string ToString() const;
    };

    /**
     * A subscription class i.e. an identifier + object to subscribe to.
     */
    class MibSubscription
    {
    public:
    	MibSubscription() {}
        std::string ToString() const;

        MibSubscriptionIdentifier m_mibSubscriptionIdentifier;

        MibAttributeIdsByDn  m_attributeIdsByDn;
        MibObjectClassesByDn m_objectClassesByDn;

        virtual ~MibSubscription() {}
    };


    /**
     * Map from an attribute ID to a subscription descriptor.  Only makes sense
     * when used in something that is object DN specific, such as the map below.
     */
    typedef std::map<MibAttributeId, std::set<MibSubscriptionIdentifier> > MibSubscriptionsByAttributeId;

    /**
     * Map from object DN to list of subscriptions indexed by attribute ID.
     */
    typedef std::map<MibDN, MibSubscriptionsByAttributeId> MibAttributeSubscriptionsByDn;
    MibAttributeSubscriptionsByDn m_attributeSubscriptionsByDn;

    /**
     * Map from an object class to a subscription descriptor.  Only makes sense
     * when used in something that is object DN specific, such as the map below.
     */
    typedef std::map<MibObjectClass, std::set<MibSubscriptionIdentifier> > MibSubscriptionsByObjectClass;

    /**
     * Map from object DN to list of subscriptions indexed by object class.
     */
    typedef std::map<MibDN, MibSubscriptionsByObjectClass> MibObjectSubscriptionsByDn;
    MibObjectSubscriptionsByDn m_objectSubscriptionsByDn;

    /**
     * Map from a subscription identifier to a subscription.
     */
    typedef std::map<MibSubscriptionIdentifier, MibSubscription> MibSubscriptionsByIdentifier;
    MibSubscriptionsByIdentifier  m_subscriptionsByIdentifier;
};

#endif
