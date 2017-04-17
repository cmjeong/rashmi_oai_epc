///////////////////////////////////////////////////////////////////////////////
//
// AppWithAttrCacheFsmImpl.h
//
// Implementation of AppWithAttrCache.fsm
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __AppWithAttrCacheFsmImpl_h_
#define __AppWithAttrCacheFsmImpl_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <Radisys.h>
#include <system/TimerInterface.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "AppWithAttrCache_fsm_interface.h"
#include "AppWithAttrCache_fsm.h"
#include "SubscriptionDescriptor.h"

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

class SingleThreadedAppWithAttrCache;

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class AppWithAttrCacheFsmImpl : public AppWithAttrCacheFsmInterface
{
public:
    friend class SingleThreadedAppWithAttrCache;

    /**
     * Default constructor.
     */
    AppWithAttrCacheFsmImpl(SingleThreadedAppWithAttrCache& app);

    /**
     * Destructor.
     */
    virtual ~AppWithAttrCacheFsmImpl();

    /**
     * Handle timers relating to this FSM.
     */
    void HandleTimerExpiry(TimerHandle timerHandle);

    /**
     * Implement FSM virtuals.
     */
    AppWithAttrCacheInterfaceDefinition();

private:
    // Application singleton.
    SingleThreadedAppWithAttrCache& m_app;

    // Supported messaging entities (from concrete app).
    // Entries are deleted as they are successfully registered.
    std::vector<MessagingEntity> m_entities;

    // The primary entity is the first in the list of supported entities.
    // We take a note of it as the above list is whittled down to empty
    // as entities are successfully registered.
    // This is the entity we'll use for informing OAM that the
    // app is ready to start.
    MessagingEntity m_primaryEntity;

    // Subscriptions (from concrete app).
    // Entries are deleted as they are successfully subscribed.
    std::vector<SubscriptionDescriptor> m_subscriptions;

    /**
     * Guard timers for start up procedures.
     */
    threeway::TimerHandle m_registerGuardTimer;
    threeway::TimerHandle m_subscribeGuardTimer;
    threeway::TimerHandle m_readyGuardTimer;

    // Put this last in case initial state uses other member data.
    AppWithAttrCacheFsm m_fsm;
};

}

#endif
