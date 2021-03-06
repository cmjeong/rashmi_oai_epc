///////////////////////////////////////////////////////////////////////////////
//
// AppWithAttrCache_fsm_interface.h
//
// Autogenerated from AppWithAttrCache.fsm
//
// Fsm Interface Class
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __AppWithAttrCache_fsm_interface_h_
#define __AppWithAttrCache_fsm_interface_h_
///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/ThreadWithQueue.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "messaging/transport/MessageSerialisedData.h"
#include "messaging/messages/common/RegisterEntityCnf.h"
#include "mib-common/messages/MibSubscribeAttributesCnf.h"

///////////////////////////////////////////////////////////////////////////////
// Defines
///////////////////////////////////////////////////////////////////////////////

// Definition at end of file
#undef AppWithAttrCacheInterfaceDefinition


/*** WARNING: Code AUTO-GENERATED from AppWithAttrCache.fsm. Do not edit! ***/
class AppWithAttrCacheFsmInterface
{
public:
    AppWithAttrCacheFsmInterface() {}
    virtual ~AppWithAttrCacheFsmInterface() {}
    
    // Actions
    virtual void SendEntityRegisterReqs(void*) = 0;
    virtual void SendOutstandingEntityRegisterReqs(void*) = 0;
    virtual void SendSubscribeAttributesReqs() = 0;
    virtual void SendOutstandingSubscribeAttributesReqs(void*) = 0;
    virtual void SendReadyToStart() = 0;
    virtual void SendReadyToStart(boost::shared_ptr<MibSubscribeAttributesCnf>) = 0;
    virtual void SendReadyToStart(void*) = 0;
    
    // Entry/Exit
    virtual void RegisteringEntry() = 0;
    virtual void RegisteringExit() = 0;
    virtual void SubscribingEntry() = 0;
    virtual void SubscribingExit() = 0;
    virtual void InformingReadyEntry() = 0;
    virtual void InformingReadyExit() = 0;
    virtual void StartedEntry() = 0;
    
    // Guard Conditions
    virtual bool AllEntitiesRegistered(boost::shared_ptr<RegisterEntityCnf>) = 0;
    virtual bool HaveSubscriptions() = 0;
    virtual bool AllSubscriptionsReceived(boost::shared_ptr<MibSubscribeAttributesCnf>) = 0;
    
};

// Auto-updating Interface Definition
#define AppWithAttrCacheInterfaceDefinition()  \
    virtual void SendEntityRegisterReqs(void*); \
    virtual void SendOutstandingEntityRegisterReqs(void*); \
    virtual void SendSubscribeAttributesReqs(); \
    virtual void SendOutstandingSubscribeAttributesReqs(void*); \
    virtual void SendReadyToStart(); \
    virtual void SendReadyToStart(boost::shared_ptr<MibSubscribeAttributesCnf>); \
    virtual void SendReadyToStart(void*); \
    virtual void RegisteringEntry(); \
    virtual void RegisteringExit(); \
    virtual void SubscribingEntry(); \
    virtual void SubscribingExit(); \
    virtual void InformingReadyEntry(); \
    virtual void InformingReadyExit(); \
    virtual void StartedEntry(); \
    virtual bool AllEntitiesRegistered(boost::shared_ptr<RegisterEntityCnf>); \
    virtual bool HaveSubscriptions(); \
    virtual bool AllSubscriptionsReceived(boost::shared_ptr<MibSubscribeAttributesCnf>)

#endif // __AppWithAttrCache_fsm_interface_h_

