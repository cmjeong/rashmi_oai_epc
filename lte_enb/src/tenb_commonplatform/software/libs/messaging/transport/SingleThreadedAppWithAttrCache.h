///////////////////////////////////////////////////////////////////////////////
//
// SingleThreadedAppWithAttrCache.h
//
// Extends SingleThreadedApplicationWithMessaging class to add MIB attribute
// retrieval/caching.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __SingleThreadedAppWithAttrCache_h_
#define __SingleThreadedAppWithAttrCache_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <map>
#include <string>

#include <boost/shared_ptr.hpp>

#include <messaging/transport/SingleThreadedApplicationWithMessaging.h>
#include <system/Serialisable.h>
#include <mib-common/MibAttributeValues.h>
#include <mib-common/MibAttributeValuesByDn.h>
#include <mib-common/MibAttributeIdsByDn.h>
#include <MibAttributeId.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "AppMibAttributeCache.h"
#include "AppWithAttrCacheFsmImpl.h"
#include "SubscriptionDescriptor.h"

using namespace boost;
using namespace std;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class SingleThreadedAppWithAttrCache :
    public SingleThreadedApplicationWithMessaging,
    public MibAttributeUpdatedInformInterface
{
protected:

    friend class AppWithAttrCacheFsmImpl;

    /**
     * Construct SingleThreadedAppWithAttrCache
     *
     * \param appName      Give the application a name - passed to ApplicationWithMessaging
     */
    SingleThreadedAppWithAttrCache(const char * appName);

public:
    virtual ~SingleThreadedAppWithAttrCache();

    /**
     * Get interface for accessing the MIB.
     */
    MibAccessInterface& GetMibCache() const { RSYS_ASSERT(m_attribCache != NULL); return *m_attribCache; };

protected:
    /**
     * Handle messages specific to attribute cache (having given base class a go first).
     */
    virtual bool MessageHandler(shared_ptr<threeway::MessageSerialisedData> & message);

    /**
     * Hook for concrete app to locally initialise stuff that can't be done in constructor.
     * E.g. locally registering KPI and CLI handlers.
     * Called before messaging and attribute cache are started up.
     */
    virtual void InitialiseApp() {};

    /**
     * Hook for concrete app to do anything necessary after app has been "started"
     * by reception of START message.
     * E.g. Register KPIs, startup protocol stacks etc.
     */
    virtual void StartApp() {};

    /**
     * Hook to allow concrete apps to do any other processing in the main app loop.
     * Generally discouraged!
     */
    virtual void DoOtherMainLoopProcessing() {};

    /**
     * Hook for cleaning up on app exit.
     */
    virtual void StopApp() {};

    /**
     * Hook for concrete app to report the entities it supports.
     * These will be automatically registered during app startup.
     * If more than one entity is included, the first is deemed the
     * 'primary entity' and is the one that will be used to report
     * that the app is 'ready to start' to OAM.
     */
    virtual std::vector<MessagingEntity> GetSupportedEntities() = 0;

    /**
     * Hook for concrete app to supply its MIB subscriptions.
     * These will be automatically subscribed to during app startup.
     */
    virtual void GetSubscriptions(std::vector<SubscriptionDescriptor>& subscriptions) {};

    /**
     * Hook to allow concrete apps to monitor changes to MIB attributes.
     * Note that this function should be implemented defensively as it could be called before
     * the application has received the start message.
     */
    virtual void MibAttributeUpdated(const MibDN & dn, MibAttributeId mibAttributeId) {}
    virtual void MibAttributesUpdated(u32 subscriptionId, const MibAttributeValuesByDn &oldValues, const MibAttributeValuesByDn &newValues) {}
    virtual void MibAttributesUpdated(u32 subscriptionId, const MibAttributeIdsByDn& mibAttributeValuesByDn) {}

    /**
     * Helper function for populating vector of subscription descriptors where subscription
     * is on single DN (this is actually the only option at time of writing).
     */
    void AddSubscription(std::vector<SubscriptionDescriptor>& subscriptions,
                         u32 subscriptionId,
                         MessagingEntity entity,
                         const MibDN& dn,
                         const MibAttributeIds& attrIds);

    /**
     * Request the app to exit.
     */
    void Exit() { m_exit = true; };

    /**
     * Handle timers related to the app FSM.
     */
    virtual void HandleTimerExpiry(shared_ptr<TimerExpiry> timer);

private:

    /**
     * Hide this, derived classes just use the hooks above.
     */
    virtual int AppMain();

    /**
     * Call this once messaging started.
     */
    void StartAttributeCache();

    /**
     * Instance of class for managing MIB attribute cache for this app.
     */
    boost::shared_ptr<AppMibAttributeCache> m_attribCache;

    /**
     * Some apps need to exit so let them through this var...
     */
    bool m_exit;

    /**
     * FSM for controlling startup of the application.
     */
    AppWithAttrCacheFsmImpl m_appWithAttrCacheFsmImpl;
};

}

#endif
