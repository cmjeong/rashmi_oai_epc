///////////////////////////////////////////////////////////////////////////////
//
// SingleThreadedAppWithAttrCache.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>

#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "SingleThreadedAppWithAttrCache.h"

using namespace std;
using namespace boost;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

SingleThreadedAppWithAttrCache::SingleThreadedAppWithAttrCache(const char * appName) :
    SingleThreadedApplicationWithMessaging(appName),
    m_exit(false),
    m_appWithAttrCacheFsmImpl(*this)
{
}

SingleThreadedAppWithAttrCache::~SingleThreadedAppWithAttrCache()
{
}

void SingleThreadedAppWithAttrCache::StartAttributeCache()
{
    RSYS_ASSERT(m_messenger != NULL);

    m_attribCache.reset(new AppMibAttributeCache(m_messenger, *this, *this));
}

bool SingleThreadedAppWithAttrCache::MessageHandler(shared_ptr<threeway::MessageSerialisedData> & message)
{
    RSYS_ASSERT(m_attribCache != NULL);

    // First, pass to parent
    bool handled = SingleThreadedApplicationWithMessaging::MessageHandler(message);

    if( !handled )
    {
        // Is this one of our Param handling messages?
        switch(message->GetSerialisationId())
        {
            case SERIALISATION_ID_REGISTER_ENTITY_CNF:
            {
                shared_ptr<RegisterEntityCnf> registerEntityCnf = Serialisable::DeSerialise<RegisterEntityCnf>(message);
                RSYS_ASSERT(registerEntityCnf != NULL);

                TRACE("RegisterEntityCnf received", registerEntityCnf->ToString().c_str());
                m_appWithAttrCacheFsmImpl.m_fsm.InjectRegisterEntityCnf(registerEntityCnf);

                handled = true;
            }
                break;

            case SERIALISATION_ID_MIB_SUBSCRIBE_ATTRIBUTES_CNF:
            {
                shared_ptr<MibSubscribeAttributesCnf> mibSubscribeAttributesCnf = Serialisable::DeSerialise<MibSubscribeAttributesCnf>(message);
                RSYS_ASSERT(mibSubscribeAttributesCnf != NULL);

                TRACE("MibSubscribeAttributesCnf received", mibSubscribeAttributesCnf->ToString().c_str());
                m_appWithAttrCacheFsmImpl.m_fsm.InjectMibSubscribeAttributesCnf(mibSubscribeAttributesCnf);
            }
                break;

            case SERIALISATION_ID_REQUEST_START_RSP:
            {
                m_appWithAttrCacheFsmImpl.m_fsm.InjectRequestStartRsp(NULL);

                handled = true;
            }
                break;

            case SERIALISATION_ID_MIB_SUBSCRIBE_ATTRIBUTES_IND:
                m_attribCache->HandleMibSubscribeAttributesInd(message);
                break;

            case SERIALISATION_ID_MIB_SUBSCRIBE_ATTRIBUTES_DELETE_IND:
                m_attribCache->HandleMibSubscribeAttributesDeleteInd(message);
                break;

            default:
                break;
        }
    }

    return handled;
}

void SingleThreadedAppWithAttrCache::AddSubscription(std::vector<SubscriptionDescriptor>& subscriptions,
                                                     u32 subscriptionId,
                                                     MessagingEntity entity,
                                                     const MibDN& dn,
                                                     const MibAttributeIds& attrIds)
{
    MibAttributeIdsByDn attrIdsByDn;

    attrIdsByDn[dn] = attrIds;

    SubscriptionDescriptor desc;
    desc.m_subscriptionId = subscriptionId;
    desc.m_entity = entity;
    desc.m_attributeIdsByDn = attrIdsByDn;

    subscriptions.push_back(desc);
}

void SingleThreadedAppWithAttrCache::HandleTimerExpiry(shared_ptr<TimerExpiry> timer)
{
    m_appWithAttrCacheFsmImpl.HandleTimerExpiry(timer->GetTimerHandle());
}

int SingleThreadedAppWithAttrCache::AppMain ()
{
    // Let concrete app do whatever it needs to.
    InitialiseApp();

    // Start up the various key bits.
    StartMessaging();
    StartAttributeCache();

    // Register our PID with the watchdog.
    //WatchdogRegisterPid();//Commented to avoid redudency

    m_appWithAttrCacheFsmImpl.m_fsm.InjectStart(NULL);

    // Loop, processing received events.
    while(!m_exit)
    {
        HandleEventCallbacksAndQueues(1000);
        DoOtherMainLoopProcessing();
    }

    return 0;
}

}
