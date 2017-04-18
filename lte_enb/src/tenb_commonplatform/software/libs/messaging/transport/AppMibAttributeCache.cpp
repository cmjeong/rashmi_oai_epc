///////////////////////////////////////////////////////////////////////////////
//
// AppMibAttributeCache.cpp
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
#include <string.h>
#include <stdlib.h>
#include <mib-common/messages/MibSetAttributesReq.h>
#include <mib-common/messages/MibDeleteAttributesReq.h>
#include <mib-common/messages/MibSubscribeAttributesInd.h>
#include <mib-common/messages/MibSubscribeAttributesDeleteInd.h>
#include <mib-common/messages/MibSubscribeAttributesReq.h>
#include <mib-common/messages/MibSubscribeAttributesCnf.h>
#include <mib-common/messages/MibUnsubscribeReq.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "AppMibAttributeCache.h"
#define MAX_CHARS_FOR_CELLIDX 15
using namespace std;
using namespace boost;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

AppMibAttributeCache::AppMibAttributeCache(shared_ptr<Messenger> messenger,
                                           SendMessageInterface& sendMessageInterface,
                                           MibAttributeUpdatedInformInterface& updateInformInterface) :
    m_messenger(messenger),
    m_sendMessageInterface(sendMessageInterface),
    m_updateInformInterface(updateInformInterface)
{
    Thread::InitialiseMutex(m_mibAttrCacheMutex);

    m_fapZeroDn = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP);
}

AppMibAttributeCache::~AppMibAttributeCache()
{
    Thread::DestroyMutex(m_mibAttrCacheMutex);
}

void AppMibAttributeCache::PerformBlockingMibSubscribe(
        u32 subscriptionId,
        const MessagingEntity& entity,
        threeway::Serialisable & subscribeReq )
{
   // Ensure messenger is operating in polled mode
   m_messenger->SwitchToPolledMode();

   // Send it to OAM.
   m_sendMessageInterface.SendMessage(subscribeReq, ENTITY_MIB, entity);

   // Wait until oam responds....
   // oam will send REGISTER_ENTITY_CNF once it has sent any MIB attributes that are required.
   TRACE("  Waiting for response", MessagingEntityToString(entity));

   bool waitForResponse = true;
   while(waitForResponse)
   {
      // Wait a short while for a response.
      MessagingEntity fromEntity;
      MessagingEntity toEntity;
      shared_ptr<SerialisedData> receivedMessage = m_messenger->BlockingReceiveMessage(5000, fromEntity, toEntity);

      // May or may not have received a message so check pointer.
      if(receivedMessage != NULL)
      {
         switch(receivedMessage->GetSerialisationId())
         {
            case SERIALISATION_ID_MIB_SUBSCRIBE_ATTRIBUTES_CNF:
               {
                  shared_ptr<MibSubscribeAttributesCnf> mibSubscribeAttributesCnf = Serialisable::DeSerialise<MibSubscribeAttributesCnf>(receivedMessage);
                  RSYS_ASSERT(mibSubscribeAttributesCnf != NULL);

                  if(mibSubscribeAttributesCnf->GetSubscriptionId() == subscriptionId)
                  {
                     // We have our response...
                     waitForResponse = false;
                     TRACE("  MibSubscribeCnf received!", MessagingEntityToString(entity));
                  }
               }
               break;

            case SERIALISATION_ID_MIB_SUBSCRIBE_ATTRIBUTES_IND:
               HandleMibSubscribeAttributesInd(receivedMessage);
               break;

            case SERIALISATION_ID_MIB_SUBSCRIBE_ATTRIBUTES_DELETE_IND:
               HandleMibSubscribeAttributesDeleteInd(receivedMessage);
               break;

            default:
               TRACE_LEV(TRACE_WARNING, "SubscribeMibAttributes: Received unhandled message while waiting for SUBSCRIBE_MIB_PARAMS_CNF", receivedMessage->ToString().c_str());
               break;
         }
      }
      else
      {
         TRACE("  Timed out waiting, sending MibSubscribeAttributesReq again", MessagingEntityToString(entity));

         // Send it to OAM.
         m_sendMessageInterface.SendMessage(subscribeReq, ENTITY_MIB, entity);
      }
   }

   // Return to callback mode
   m_messenger->RestoreCallbackMode();
}

void AppMibAttributeCache::SubscribeMibAttributes(u32 subscriptionId, const MessagingEntity& entity, const MibDN& dn, const MibAttributeIds& mibAttributes, bool waitForResponse)
{
    TRACE_PRINTF("Subscribing to MIB attributes for entity=%s(%"PRIu32"), subscriptionId=%"PRIu32, MessagingEntityToString(entity), (u32)entity, subscriptionId);

    if(m_messenger == NULL)
    {
        TRACE_MSG_LEV(TRACE_WARNING, "No messenger for subscribing to MIB attributes");
        return;
    }

    MibSubscribeAttributesReq mibSubscribeAttributesReq(subscriptionId, dn, mibAttributes);

    if(waitForResponse)
    {
        PerformBlockingMibSubscribe( subscriptionId, entity, mibSubscribeAttributesReq);
    }
    else
    {
        // Send it to OAM.
        m_sendMessageInterface.SendMessage(mibSubscribeAttributesReq, ENTITY_MIB, entity);
    }
}

void AppMibAttributeCache::SubscribeMibAttributes(u32 subscriptionId,
                                              const MessagingEntity& entity,
                                              const MibAttributeIds& mibAttributes,
                                              bool waitForResponse)
{
    SubscribeMibAttributes(subscriptionId, entity, m_fapZeroDn, mibAttributes, waitForResponse);
}

void AppMibAttributeCache::SubscribeMibAttributes(u32 subscriptionId,
                                    const MessagingEntity& entity,
                                    const MibAttributeIdsByDn& attributeIdsByDn,
                                    const MibObjectClassesByDn& objectClassesByDn,
                                    bool waitForResponse)
{
    TRACE_PRINTF("%s subscrition(%"PRIu32") to MIB attributes=%s, objects=%s.", MessagingEntityToString(entity), subscriptionId, attributeIdsByDn.ToString().c_str(), objectClassesByDn.ToString().c_str());

    if(m_messenger == NULL)
    {
        TRACE_MSG_LEV(TRACE_WARNING, "No messenger for subscribing to MIB attributes");
        return;
    }

    MibSubscribeAttributesReq mibSubscribeAttributesReq(subscriptionId);

    for( MibAttributeIdsByDn::const_iterator i = attributeIdsByDn.begin();
         i != attributeIdsByDn.end();
         ++i)
    {
        mibSubscribeAttributesReq.AddAttributeIds(i->first, i->second);
    }

    for( MibObjectClassesByDn::const_iterator i = objectClassesByDn.begin();
         i != objectClassesByDn.end();
         ++i)
    {
        mibSubscribeAttributesReq.AddObjectClasses(i->first, i->second);
    }

    if(waitForResponse)
    {
        PerformBlockingMibSubscribe( subscriptionId, entity, mibSubscribeAttributesReq);
    }
    else
    {
        // Send it to OAM.
        m_sendMessageInterface.SendMessage(mibSubscribeAttributesReq, ENTITY_MIB, entity);
    }
}



void AppMibAttributeCache::UnsubscribeMibAttributes(u32 subscriptionId, MessagingEntity entity)
{
    MibUnsubscribeReq mibUnsubscribeAttributesReq(subscriptionId);
    m_sendMessageInterface.SendMessage(mibUnsubscribeAttributesReq, ENTITY_MIB, entity);
}

void AppMibAttributeCache::SetMibAttributes(const MibAttributeValues& mibAttributeValues, MessagingEntity sourceEntity)
{
    TRACE_PRINTF("Old SetMibAttributes function");
    SetMibAttributes(m_fapZeroDn, mibAttributeValues, sourceEntity);
}

void AppMibAttributeCache::SetMibAttributes(const MibDN& mibDn, const MibAttributeValues& mibAttributeValues, MessagingEntity sourceEntity)
{
    TRACE_PRINTF("Old SetMibAttributes function definition ");
    // Update local cache.
    MibAttributeValuesByDn mibAttributeValuesByDn;
    mibAttributeValuesByDn[mibDn] = mibAttributeValues;
    UpdateMibAttributesInCache(SUBSCRIBER_ID_NULL, mibAttributeValuesByDn);

    // Tell MIB.
    MibSetAttributesReq mibSetAttributesReq(mibDn, mibAttributeValues);
    m_sendMessageInterface.SendMessage(mibSetAttributesReq, ENTITY_MIB, sourceEntity);

	//If multi instance object, update Object status as object modified.
	UpdateMIOObjStatus(mibDn, sourceEntity);
}

void AppMibAttributeCache::SetMibAttributesByDn(const MibDN& mibDn, const MibAttributeValues& mibAttributeValues, MessagingEntity sourceEntity)
{
    // Update local cache.
    TRACE_PRINTF("New SetMibAttributesByDn function");
    MibAttributeValuesByDn mibAttributeValuesByDn;
    mibAttributeValuesByDn[mibDn] = mibAttributeValues;
    UpdateMibAttributesInCache(SUBSCRIBER_ID_NULL, mibAttributeValuesByDn);

    // Tell MIB.
    MibSetAttributesReq mibSetAttributesReq(mibDn, mibAttributeValues);
    m_sendMessageInterface.SendMessage(mibSetAttributesReq, ENTITY_MIB, sourceEntity);
}

void AppMibAttributeCache::DeleteMibAttributes(const MibDN& mibDn, const MibAttributeIds& mibAttributeIds, MessagingEntity sourceEntity)
{
    // Delete from local cache.
    MibAttributeIdsByDn mibAttributeIdsByDn;
    mibAttributeIdsByDn[mibDn] = mibAttributeIds;
    DeleteMibAttributesFromCache(mibAttributeIdsByDn);

    // Tell MIB.
    MibDeleteAttributesReq mibDeleteAttributesReq(mibDn, mibAttributeIds);
    m_sendMessageInterface.SendMessage(mibDeleteAttributesReq, ENTITY_MIB, sourceEntity);
}

void AppMibAttributeCache::HandleMibSubscribeAttributesInd(shared_ptr<SerialisedData> receivedMessage)
{
    shared_ptr<MibSubscribeAttributesInd> subscribeAttributesInd = Serialisable::DeSerialise<MibSubscribeAttributesInd>(receivedMessage);
    RSYS_ASSERT(subscribeAttributesInd != NULL);

    UpdateMibAttributesInCache(subscribeAttributesInd->GetSubscriptionId(), subscribeAttributesInd->GetMibAttributeValuesByDn());
}

void AppMibAttributeCache::HandleMibSubscribeAttributesDeleteInd(shared_ptr<SerialisedData> receivedMessage)
{
    shared_ptr<MibSubscribeAttributesDeleteInd> subscribeAttributesDeleteInd = Serialisable::DeSerialise<MibSubscribeAttributesDeleteInd>(receivedMessage);
    RSYS_ASSERT(subscribeAttributesDeleteInd != NULL);

    DeleteMibAttributesFromCache(subscribeAttributesDeleteInd->GetMibAttributeIdsByDn());
}

bool AppMibAttributeCache::IsMibAttributePresent(MibAttributeId mibAttributeId) const
{
    return IsMibAttributePresent(m_fapZeroDn, mibAttributeId);
}

bool AppMibAttributeCache::IsMibAttributePresent(const MibDN& dn, MibAttributeId mibAttributeId) const
{
    Thread::Guard attributesGuard(m_mibAttrCacheMutex);

    MibAttributeValuesByDn::const_iterator dnIter = m_mibAttributesCache.find(dn);
    if(dnIter == m_mibAttributesCache.end())
    {
        return (false);
    }

    return (dnIter->second.IsAttributePresent(mibAttributeId));
}

bool AppMibAttributeCache::IsMibObjectPresent(const MibDN& dn) const
{
    Thread::Guard attributesGuard(m_mibAttrCacheMutex);

    MibAttributeValuesByDn::const_iterator dnIter = m_mibAttributesCache.find(dn);

    return (dnIter != m_mibAttributesCache.end());
}

u32 AppMibAttributeCache::GetMibObjectCount(const MibDN& parent, MibObjectClass child) const
{
    u32 count = 0;
    MibAttributeValuesByDn::const_iterator dnIter = m_mibAttributesCache.begin();

    while(dnIter != m_mibAttributesCache.end())
    {
        MibDN  cacheParent = dnIter->first;
        MibRDN cacheChild  = cacheParent.back();
        cacheParent.pop_back();

        if(    (cacheParent == parent)
            && (child == cacheChild.GetMibObjectClass())
           )
        {
            count++;
        }

        dnIter++;
    }

    return count;
}

set<u32> AppMibAttributeCache::GetMibObjectInstances(const MibDN& parent, MibObjectClass child) const
{
    set<u32> instances;

    MibAttributeValuesByDn::const_iterator dnIter = m_mibAttributesCache.begin();

    while(dnIter != m_mibAttributesCache.end())
    {
        MibDN  cacheParent = dnIter->first;
        MibRDN cacheChild  = cacheParent.back();
        cacheParent.pop_back();

        if(    (cacheParent == parent)
            && (child == cacheChild.GetMibObjectClass())
          )
        {
            instances.insert(cacheChild.GetMibObjectInstance());
        }

        dnIter++;
    }

    return instances;
}

void AppMibAttributeCache::GetMibAttribute(const MibDN& dn, MibAttributeId mibAttributeId, u32& value) const
{
    TRACE_PRINTF("u32 dn passed now is %s",dn.ToString().c_str());
    shared_ptr<MibAttributeValue> attrValue = GetMibAttribute(dn, mibAttributeId);
    value = attrValue->GetValueU32();
}

void AppMibAttributeCache::GetMibAttribute(const MibDN& dn, MibAttributeId mibAttributeId, u16& value) const
{
    shared_ptr<MibAttributeValue> attrValue = GetMibAttribute(dn, mibAttributeId);
    value = (u16)attrValue->GetValueU32();
}

void AppMibAttributeCache::GetMibAttribute(const MibDN& dn, MibAttributeId mibAttributeId, u8& value) const
{
    TRACE_PRINTF("dn passed is %s",dn.ToString().c_str());
    shared_ptr<MibAttributeValue> attrValue = GetMibAttribute(dn, mibAttributeId);
    value = (u8)attrValue->GetValueU32();
}

void AppMibAttributeCache::GetMibAttribute(const MibDN& dn, MibAttributeId mibAttributeId, s32& value) const
{
    shared_ptr<MibAttributeValue> attrValue = GetMibAttribute(dn, mibAttributeId);
    value = attrValue->GetValueS32();
}

void AppMibAttributeCache::GetMibAttribute(const MibDN& dn, MibAttributeId mibAttributeId, s16& value) const
{
    shared_ptr<MibAttributeValue> attrValue = GetMibAttribute(dn, mibAttributeId);
    value = (s16)attrValue->GetValueS32();
}

void AppMibAttributeCache::GetMibAttribute(const MibDN& dn, MibAttributeId mibAttributeId, s8& value) const
{
    shared_ptr<MibAttributeValue> attrValue = GetMibAttribute(dn, mibAttributeId);
    value = (s8)attrValue->GetValueS32();
}

void AppMibAttributeCache::GetMibAttribute(const MibDN& dn, MibAttributeId mibAttributeId, bool& value) const
{
    TRACE_PRINTF("dn passed now is %s",dn.ToString().c_str());
    shared_ptr<MibAttributeValue> attrValue = GetMibAttribute(dn, mibAttributeId);
    value = attrValue->GetValueU32() == 0 ? false : true;
}

void AppMibAttributeCache::GetMibAttribute(const MibDN& dn, MibAttributeId mibAttributeId, std::string& value) const
{
    shared_ptr<MibAttributeValue> attrValue = GetMibAttribute(dn, mibAttributeId);
    value = attrValue->GetValueString();
}

void AppMibAttributeCache::GetMibAttribute(const MibDN& dn, MibAttributeId mibAttributeId, std::vector<std::string>& value) const
{
    shared_ptr<MibAttributeValue> attrValue = GetMibAttribute(dn, mibAttributeId);
    value = attrValue->GetValueStringArray();
}

void AppMibAttributeCache::GetMibAttribute(const MibDN& dn, MibAttributeId mibAttributeId, std::vector<u32>& value) const
{
    shared_ptr<MibAttributeValue> attrValue = GetMibAttribute(dn, mibAttributeId);
    value = attrValue->GetValueU32Array();
}
/* mohan */
void AppMibAttributeCache::GetMibAttribute(const MibDN& dn, MibAttributeId mibAttributeId, std::vector<s32>& value) const
{
    shared_ptr<MibAttributeValue> attrValue = GetMibAttribute(dn, mibAttributeId);
    value = attrValue->GetValueS32Array();
}

void AppMibAttributeCache::GetMibAttribute(const MibDN& dn, MibAttributeId mibAttributeId, threeway::IPv4Address& value) const
{
    std::string ipAddressAsString;
    GetMibAttribute(dn, mibAttributeId, ipAddressAsString);
    value.Set(ipAddressAsString.c_str());
}

void AppMibAttributeCache::GetMibAttribute(const MibDN& dn, MibAttributeId mibAttributeId, threeway::TimeWrap& value) const
{
    std::string dateAndTimeAsString;
    GetMibAttribute(dn, mibAttributeId, dateAndTimeAsString);
    value.Set(dateAndTimeAsString.c_str());
}

void AppMibAttributeCache::GetMibAttribute(const MibDN& dn, MibAttributeId mibAttributeId, threeway::Fqdn& value) const
{
    std::string fqdnAsString;
    GetMibAttribute(dn, mibAttributeId, fqdnAsString);
    value.Set(fqdnAsString);
}

void AppMibAttributeCache::GetMibAttribute(const MibDN& dn, MibAttributeId mibAttributeId, threeway::Url& value) const
{
    std::string urlAsString;
    GetMibAttribute(dn, mibAttributeId, urlAsString);
    value.Set(urlAsString);
}

void AppMibAttributeCache::GetMibAttribute(MibAttributeId mibAttributeId, u32& value) const
{
    shared_ptr<MibAttributeValue> attrValue = GetMibAttribute(m_fapZeroDn, mibAttributeId);
    value = attrValue->GetValueU32();
}

void AppMibAttributeCache::GetMibAttribute(MibAttributeId mibAttributeId, u16& value) const
{
    shared_ptr<MibAttributeValue> attrValue = GetMibAttribute(m_fapZeroDn, mibAttributeId);
    value = (u16)attrValue->GetValueU32();
}

void AppMibAttributeCache::GetMibAttribute(MibAttributeId mibAttributeId, u8& value) const
{
    shared_ptr<MibAttributeValue> attrValue = GetMibAttribute(m_fapZeroDn, mibAttributeId);
    value = (u8)attrValue->GetValueU32();
}

void AppMibAttributeCache::GetMibAttribute(MibAttributeId mibAttributeId, s32& value) const
{
    shared_ptr<MibAttributeValue> attrValue = GetMibAttribute(m_fapZeroDn, mibAttributeId);
    value = attrValue->GetValueS32();
}

void AppMibAttributeCache::GetMibAttribute(MibAttributeId mibAttributeId, s16& value) const
{
    shared_ptr<MibAttributeValue> attrValue = GetMibAttribute(m_fapZeroDn, mibAttributeId);
    value = (s16)attrValue->GetValueS32();
}

void AppMibAttributeCache::GetMibAttribute(MibAttributeId mibAttributeId, s8& value) const
{
    shared_ptr<MibAttributeValue> attrValue = GetMibAttribute(m_fapZeroDn, mibAttributeId);
    value = (s8)attrValue->GetValueS32();
}

void AppMibAttributeCache::GetMibAttribute(MibAttributeId mibAttributeId, bool& value) const
{
    shared_ptr<MibAttributeValue> attrValue = GetMibAttribute(m_fapZeroDn, mibAttributeId);
    value = attrValue->GetValueU32() == 0 ? false : true;
}

void AppMibAttributeCache::GetMibAttribute(MibAttributeId mibAttributeId, std::string& value) const
{
    shared_ptr<MibAttributeValue> attrValue = GetMibAttribute(m_fapZeroDn, mibAttributeId);
    value = attrValue->GetValueString();
}

void AppMibAttributeCache::GetMibAttribute(MibAttributeId mibAttributeId, std::vector<std::string>& value) const
{
    shared_ptr<MibAttributeValue> attrValue = GetMibAttribute(m_fapZeroDn, mibAttributeId);
    value = attrValue->GetValueStringArray();
}

void AppMibAttributeCache::GetMibAttribute(MibAttributeId mibAttributeId, std::vector<u32>& value) const
{
    shared_ptr<MibAttributeValue> attrValue = GetMibAttribute(m_fapZeroDn, mibAttributeId);
    value = attrValue->GetValueU32Array();
}
/* mohan */
void AppMibAttributeCache::GetMibAttribute(MibAttributeId mibAttributeId, std::vector<s32>& value) const
{
    shared_ptr<MibAttributeValue> attrValue = GetMibAttribute(m_fapZeroDn, mibAttributeId);
    value = attrValue->GetValueS32Array();
}

void AppMibAttributeCache::GetMibAttribute(MibAttributeId mibAttributeId, IPv4Address& value) const
{
    std::string ipAddressAsString;
    GetMibAttribute(m_fapZeroDn, mibAttributeId, ipAddressAsString);
    value.Set(ipAddressAsString.c_str());
}

void AppMibAttributeCache::GetMibAttribute(MibAttributeId mibAttributeId, threeway::TimeWrap& value) const
{
    std::string dateAndTimeAsString;
    GetMibAttribute(m_fapZeroDn, mibAttributeId, dateAndTimeAsString);
    value.Set(dateAndTimeAsString.c_str());
}

void AppMibAttributeCache::GetMibAttribute(MibAttributeId mibAttributeId, threeway::Fqdn& value) const
{
    std::string fqdnAsString;
    GetMibAttribute(m_fapZeroDn, mibAttributeId, fqdnAsString);
    value.Set(fqdnAsString);
}

void AppMibAttributeCache::GetMibAttribute(MibAttributeId mibAttributeId, threeway::Url& value) const
{
    std::string urlAsString;
    GetMibAttribute(m_fapZeroDn, mibAttributeId, urlAsString);
    value.Set(urlAsString);
}

void AppMibAttributeCache::UpdateMibAttributesInCache(u32 subscriptionId, const MibAttributeValuesByDn& mibAttributeValuesByDn)
{
   MibAttributeIdsByDn allIdsByDn;
   MibAttributeValues oldValues;
   MibAttributeValues newValues;
   MibAttributeValuesByDn oldValuesDn;
   MibAttributeValuesByDn newValuesDn;

   {
      Thread::Guard attributesGuard(m_mibAttrCacheMutex);
      for(MibAttributeValuesByDn::const_iterator newAttrsByDnIter = mibAttributeValuesByDn.begin();
            newAttrsByDnIter != mibAttributeValuesByDn.end();
            ++newAttrsByDnIter)
      {
         const MibDN& dn = newAttrsByDnIter->first;
         const MibAttributeValues& newAttrValues = newAttrsByDnIter->second;

         TRACE_PRINTF("Updating MIB cache: %s: %s", dn.ToString().c_str(), newAttrValues.ToString().c_str());

         // See if we already have this DN.
         if(m_mibAttributesCache.find(dn) == m_mibAttributesCache.end())
         {
            // Don't have this DN yet so add it.
            m_mibAttributesCache[dn] = newAttrValues;

            if(newAttrValues.GetAttributeCount() > 0)
            {
               newValuesDn[dn] = newAttrValues;
            }
         }
         else
         {
            // We do have this DN, merge the attribute values in.
            m_mibAttributesCache.at(dn).AddAttributes(newAttrValues, oldValues, newValues);
            // Only add to domain if any values were actually changed
            if(newValues.GetAttributeCount() > 0)
            {
               oldValuesDn[dn] = oldValues;
               newValuesDn[dn] = newValues;
            }

         }

         const MibAttributeIds & ids = newAttrValues.GetAttributeIds();

         allIdsByDn[dn].insert( ids.begin(), ids.end() );
      }
   }

   // Only send is something has changed.
   // Updated the changed interface.
   if(newValuesDn.size() > 0)
   {
      m_updateInformInterface.MibAttributesUpdated(subscriptionId, oldValuesDn, newValuesDn);
   }

   // Call the hook that apps can use to find out about change attribute values.
   for(
         MibAttributeIdsByDn::const_iterator byDn = allIdsByDn.begin();
         byDn != allIdsByDn.end();
         ++byDn)
   {
      for(
            MibAttributeIds::const_iterator allIds = byDn->second.begin();
            allIds != byDn->second.end();
            ++allIds)
      {
         m_updateInformInterface.MibAttributeUpdated(byDn->first, *allIds);
      }
   }

   // Alternatively, a client may wish to receive all Ids en-mass
   m_updateInformInterface.MibAttributesUpdated(subscriptionId, allIdsByDn);
}

void AppMibAttributeCache::DeleteMibAttributesFromCache(const MibAttributeIdsByDn& attributeIdsToDeleteByDn)
{
   TRACE_PRINTF("AppMibAttributeCache::DeleteMibAttributesFromCache(%s)",attributeIdsToDeleteByDn.ToString().c_str());

   MibAttributeIds allIds;

   {
      Thread::Guard attributesGuard(m_mibAttrCacheMutex);

      for(MibAttributeIdsByDn::const_iterator attrsByDnIter = attributeIdsToDeleteByDn.begin();
            attrsByDnIter != attributeIdsToDeleteByDn.end();
            ++attrsByDnIter)
      {
         const MibDN& dn = attrsByDnIter->first;
         const MibAttributeIds& attrIds = attrsByDnIter->second;

         // See if we already have this DN.
         if(m_mibAttributesCache.find(dn) != m_mibAttributesCache.end())
         {
            if(attrIds.empty())
            {
               MibAttributeValues & mibAttributeValues = m_mibAttributesCache.at(dn);
               MibAttributeIds      mibAttributeIds    = mibAttributeValues.GetAttributeIds();

               TRACE_PRINTF("Deleting object from MIB cache: %s {including attributes %s}", dn.ToString().c_str(), mibAttributeIds.ToString().c_str());

               m_mibAttributesCache.erase(dn);
            }
            else
            {
               TRACE_PRINTF("Deleting attributes from MIB cache: %s: %s", dn.ToString().c_str(), attrIds.ToString().c_str());

               // We do have this DN, delete the attributes.
               for(MibAttributeIds::const_iterator idsIter = attrIds.begin();
                     idsIter != attrIds.end();
                     ++idsIter)
               {
                  m_mibAttributesCache.at(dn).RemoveAttribute(*idsIter);
               }
            }
         }
      }
   }
}

shared_ptr<MibAttributeValue> AppMibAttributeCache::GetMibAttribute(const MibDN& dn, MibAttributeId mibAttributeId) const
{
   Thread::Guard attributesGuard(m_mibAttrCacheMutex);
   MibAttributeValuesByDn::const_iterator dnIter;
   TRACE_PRINTF("dn is %s",dn.ToString().c_str());
      dnIter = m_mibAttributesCache.find(dn);
      RSYS_ASSERT_PRINTF(dnIter != m_mibAttributesCache.end(), "dn=%s not present", dn.ToString().c_str());
      RSYS_ASSERT_PRINTF(dnIter->second.IsAttributePresent(mibAttributeId), "%s: %s not present", dn.ToString().c_str(), getMibAttributeName(mibAttributeId));

   return dnIter->second.GetAttributeValue(mibAttributeId);
}

void AppMibAttributeCache::GetMibAttributeAsString(const MibDN& dn, MibAttributeId mibAttributeId, string& value) const
{
   Thread::Guard paramsGuard(m_mibAttrCacheMutex);
   MibAttributeValuesByDn::const_iterator dnIter;
   dnIter = m_mibAttributesCache.find(dn);
   RSYS_ASSERT_PRINTF(dnIter != m_mibAttributesCache.end(), "dn=%s not present", dn.ToString().c_str());
   RSYS_ASSERT_PRINTF(dnIter->second.IsAttributePresent(mibAttributeId), "%s: %s not present", dn.ToString().c_str(), getMibAttributeName(mibAttributeId));
   TRACE_PRINTF("%s Cached Parameter(%s) is of type - MIB_OBJECT_CLASS_FAP",__FUNCTION__,getMibAttributeName(mibAttributeId));

   value = dnIter->second.GetAttributeValue(mibAttributeId)->GetValueAsString();
}

/*
*  Function to return the instance number of the Object if it is 
*  a Multi Instance Object
*/
int AppMibAttributeCache::GetMibObjectInstanceNum(string dn) const
{
   char* dnchar = const_cast<char*>(dn.c_str());
   char * token = strtok(dnchar,".");
   char * lasttoken = NULL;
   int ret = 0;
   while(token != NULL)
   {
      lasttoken = token;
      token = strtok(NULL,".");
   }

   TRACE_PRINTF("Object instance token int = %s", lasttoken);

   if(NULL != lasttoken)
   {
      ret = atoi(lasttoken);
   }
   else
   {
      ret = -1;
   }
   return ret;
}

void AppMibAttributeCache::UpdateMIOObjStatus(const MibDN& mibDn, MessagingEntity sourceEntity)
{
#if 0
	TRACE_PRINTF(" AppMibAttributeCache::UpdateMIOObjStatus");
	if( (mibDn.ToString().find("LTE_RAN_NEIGH_LIST_LTE_CELL")) != string::npos)
			 {
			char * instance = GetMibObjectInstanceNum(mibDn.ToString());
	
			if( instance != NULL )
			  {
		         std::vector<u32> neighCellSrc;
					MibAttributeValues mibAttributeValues;
					MibDN dnNeighCell = MibDN::GenerateMibDN(MIB_OBJECT_CLASS_FAP_LTE);
					
					MibAttributeValuesByDn::const_iterator dnIter = m_mibAttributesCache.find(dnNeighCell);
					dnIter->second.GetAttributeValue(PARAM_ID_LTE_X_RADISYS_LTE_CELL_SRC,neighCellSrc);
					neighCellSrc[atoi(instance)] = 1;
					mibAttributeValues.AddAttribute(PARAM_ID_LTE_X_RADISYS_LTE_CELL_SRC, neighCellSrc);
               SetMibAttributes(mibAttributeValues, sourceEntity);
			  }
			
			 }

#endif

}


}
