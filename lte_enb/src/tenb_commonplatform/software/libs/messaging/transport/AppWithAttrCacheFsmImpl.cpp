///////////////////////////////////////////////////////////////////////////////
//
// AppWithAttrCacheFsmImpl.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "AppWithAttrCacheFsmImpl.h"
#include "SingleThreadedAppWithAttrCache.h"

using namespace std;
using namespace boost;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

AppWithAttrCacheFsmImpl::AppWithAttrCacheFsmImpl(SingleThreadedAppWithAttrCache& app) :
    m_app(app),
    m_primaryEntity(ENTITY_INVALID),
    m_fsm(*this, true /* trace enabled */)
{
    m_registerGuardTimer = m_app.CreateTimer("Register Guard Timer", 2000,
                                             TimerEngineInterface::TIMER_WAIT,
                                             TimerEngineInterface::TIMER_REPEAT);
    m_subscribeGuardTimer = m_app.CreateTimer("Subscribe Guard Timer", 10000,
                                              TimerEngineInterface::TIMER_WAIT,
                                              TimerEngineInterface::TIMER_REPEAT);
    m_readyGuardTimer = m_app.CreateTimer("Ready Guard Timer", 2000,
                                          TimerEngineInterface::TIMER_WAIT,
                                          TimerEngineInterface::TIMER_REPEAT);
}

AppWithAttrCacheFsmImpl::~AppWithAttrCacheFsmImpl()
{
}

void AppWithAttrCacheFsmImpl::HandleTimerExpiry(TimerHandle timerHandle)
{
    if(timerHandle == m_registerGuardTimer)
    {
        m_fsm.InjectTimerExpiryRegistration(NULL);
    }
    else if(timerHandle == m_subscribeGuardTimer)
    {
        m_fsm.InjectTimerExpirySubscriptions(NULL);
    }
    else if(timerHandle == m_readyGuardTimer)
    {
        m_fsm.InjectTimerExpiryReady(NULL);
    }
}

void AppWithAttrCacheFsmImpl::SendEntityRegisterReqs(void*)
{
    // Get list of entities to register from concrete app.
    m_entities = m_app.GetSupportedEntities();
    RSYS_ASSERT(!m_entities.empty());

    m_primaryEntity = m_entities.at(0);

    // Send register request for each.
    SendOutstandingEntityRegisterReqs(NULL);
}

void AppWithAttrCacheFsmImpl::SendOutstandingEntityRegisterReqs(void*)
{
    TRACE("Entities left to register", (u32)m_entities.size());

    // Send register request for any left in the list.
    for(vector<MessagingEntity>::const_iterator iter = m_entities.begin();
        iter != m_entities.end();
        ++iter)
    {
        m_app.RegisterEntity(*iter);
    }
}

void AppWithAttrCacheFsmImpl::SendSubscribeAttributesReqs()
{
    // Send subscribe for each.
    SendOutstandingSubscribeAttributesReqs(NULL);
}

void AppWithAttrCacheFsmImpl::SendOutstandingSubscribeAttributesReqs(void*)
{
    TRACE("Subscriptions left to request", (u32)m_subscriptions.size());

    // Send subscribe for any left in the list.
    for(vector<SubscriptionDescriptor>::const_iterator iter = m_subscriptions.begin();
        iter != m_subscriptions.end();
        ++iter)
    {
        RSYS_ASSERT_PRINTF(iter->m_attributeIdsByDn.size() == 1,
                           "Subscription must have 1 and only 1 DN but this has %"PRIu32" : %s",
                           (u32)iter->m_attributeIdsByDn.size(),
                           iter->m_attributeIdsByDn.ToString().c_str());

        m_app.GetMibCache().SubscribeMibAttributes(iter->m_subscriptionId,
                                                   iter->m_entity,
                                                   iter->m_attributeIdsByDn.begin()->first,
                                                   iter->m_attributeIdsByDn.begin()->second,
                                                   false);
    }
}

void AppWithAttrCacheFsmImpl::SendReadyToStart(boost::shared_ptr<MibSubscribeAttributesCnf>)
{
    SendReadyToStart();
}

void AppWithAttrCacheFsmImpl::SendReadyToStart(void*)
{
    SendReadyToStart();
}

void AppWithAttrCacheFsmImpl::SendReadyToStart()
{
    RSYS_ASSERT(m_primaryEntity != ENTITY_INVALID);

    m_app.NotifyReady(ENTITY_OAM, m_primaryEntity);
}

void AppWithAttrCacheFsmImpl::RegisteringEntry()
{
    m_app.StartTimer(m_registerGuardTimer);
}

void AppWithAttrCacheFsmImpl::RegisteringExit()
{
    m_app.StopTimer(m_registerGuardTimer);
}

void AppWithAttrCacheFsmImpl::SubscribingEntry()
{
    m_app.StartTimer(m_subscribeGuardTimer);
}

void AppWithAttrCacheFsmImpl::SubscribingExit()
{
    m_app.StopTimer(m_subscribeGuardTimer);
}

void AppWithAttrCacheFsmImpl::InformingReadyEntry()
{
    m_app.StartTimer(m_readyGuardTimer);
}

void AppWithAttrCacheFsmImpl::InformingReadyExit()
{
    m_app.StopTimer(m_readyGuardTimer);
}

void AppWithAttrCacheFsmImpl::StartedEntry()
{
    m_app.StartApp();
}

bool AppWithAttrCacheFsmImpl::AllEntitiesRegistered(boost::shared_ptr<RegisterEntityCnf> registerEntityCnf)
{
    RSYS_ASSERT(registerEntityCnf != NULL);

    // Erase the one that has now registered from the list then check for an empty list
    // indicating all are now registered.

    TRACE("Received", registerEntityCnf->ToString());
    for(vector<MessagingEntity>::iterator iter = m_entities.begin();
        iter != m_entities.end();
        ++iter)
    {
        if(registerEntityCnf->GetEntity() == *iter)
        {
            TRACE("Entity registered successfully", MessagingEntityToString(registerEntityCnf->GetEntity()))
            m_entities.erase(iter);
            break;
        }
    }

    return m_entities.empty();
}

bool AppWithAttrCacheFsmImpl::HaveSubscriptions()
{
    // Get list of subscriptions.
    m_subscriptions.clear();
    m_app.GetSubscriptions(m_subscriptions);

    return !m_subscriptions.empty();
}

bool AppWithAttrCacheFsmImpl::AllSubscriptionsReceived(boost::shared_ptr<MibSubscribeAttributesCnf> mibSubscribeAttributesCnf)
{
    RSYS_ASSERT(mibSubscribeAttributesCnf != NULL);

    // Erase the subscription from the list then check for an empty list
    // indicating all subscriptions complete.

    TRACE("Received", mibSubscribeAttributesCnf->ToString());

    for(vector<SubscriptionDescriptor>::iterator iter = m_subscriptions.begin();
        iter != m_subscriptions.end();
        ++iter)
    {
        if(mibSubscribeAttributesCnf->GetSubscriptionId() == iter->m_subscriptionId)
        {
            TRACE("Subscribed successfully", mibSubscribeAttributesCnf->GetSubscriptionId());
            m_subscriptions.erase(iter);
            break;
        }
    }

    return m_subscriptions.empty();
}
