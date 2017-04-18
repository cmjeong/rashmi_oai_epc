///////////////////////////////////////////////////////////////////////////////
//
// MibSubscriptionManager.cpp
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

#include "MibSubscriptionManager.h"

using namespace std;
using namespace boost;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

bool MibSubscriptionManager::MibSubscriptionIdentifier::operator==(const MibSubscriptionIdentifier& rhs) const
{
    return (m_subscriberId == rhs.m_subscriberId) && (m_subscriptionId == rhs.m_subscriptionId);
}

bool MibSubscriptionManager::MibSubscriptionIdentifier::operator<(const MibSubscriptionIdentifier& rhs) const
{
    if(m_subscriberId < rhs.m_subscriberId)
    {
        return true;
    }

    if(m_subscriberId > rhs.m_subscriberId)
    {
        return false;
    }

    return m_subscriptionId < rhs.m_subscriptionId;
}

MibSubscriptionManager::MibSubscriptionManager(const MibInterface& mib, MibSubscriptionNotifyInterface& subscriptionNotifyInterface) :
    m_mibInterface(mib),
    m_subscriptionNotifyInterface(subscriptionNotifyInterface)
{
    ENTER();

    EXIT();
}

MibSubscriptionManager::~MibSubscriptionManager()
{
    ENTER();

    EXIT();
}

void MibSubscriptionManager::HandleChangedAttributes(const MibDN& dn, const MibAttributeIds& changedAttributeIds) const
{
    ENTER();

    HandleChangedOrDeletedAttributes(dn, changedAttributeIds, false /* changed values */);

    EXIT();
}

void MibSubscriptionManager::HandleDeletedAttributes(const MibDN& dn, const MibAttributeIds& deletedAttributeIds) const
{
    ENTER();

    HandleChangedOrDeletedAttributes(dn, deletedAttributeIds, true /* deleted attributes */);

    EXIT();
}

void MibSubscriptionManager::AddSubscription(
        u32 subscriberId,
        const char * subscriberName,
        u32 subscriptionId,
        const MibAttributeIdsByDn& attributeIdsByDn,
        const MibObjectClassesByDn& objectClassesByDn)
{
   MibAttributeValuesByDn mibAttributeValuesByDn;

   // Remove any existing one first.
   RemoveSubscription(subscriberId, subscriptionId);

   // Build a subscription identifier.
   MibSubscriptionIdentifier mibSubscriptionIdentifier;
   mibSubscriptionIdentifier.m_subscriberId = subscriberId;
   mibSubscriptionIdentifier.m_subscriberName = subscriberName;
   mibSubscriptionIdentifier.m_subscriptionId = subscriptionId;

   // Build a subscription.
   MibSubscription subscription;
   subscription.m_mibSubscriptionIdentifier = mibSubscriptionIdentifier;
   subscription.m_attributeIdsByDn          = attributeIdsByDn;
   subscription.m_objectClassesByDn         = objectClassesByDn;

   // Add it to the easy map.
   m_subscriptionsByIdentifier[mibSubscriptionIdentifier] = subscription;

   // And now the trickier two maps...

   TRACE_PRINTF("AddSubscription::MibAttributeSubscriptionsByDn");
   // Firstly: MibAttributeSubscriptionsByDn.
   for(MibAttributeIdsByDn::const_iterator i = attributeIdsByDn.begin();
         i != attributeIdsByDn.end();
         i++)
   {
      // See if we already have this DN, if not add it.
      MibDN dn = i->first;
      MibAttributeIds mibAttributeIds = i->second;

      TRACE_PRINTF("AddSubscription::MibAttributeIdsByDn dn=%s, attr=%s", dn.ToString().c_str(), mibAttributeIds.ToString().c_str() );

      MibAttributeSubscriptionsByDn::iterator dnIter = m_attributeSubscriptionsByDn.find(dn);
      if(dnIter == m_attributeSubscriptionsByDn.end())
      {
         // No entry for this DN so add one.
         MibSubscriptionsByAttributeId emptySubsByAttr;

         m_attributeSubscriptionsByDn[dn] = emptySubsByAttr;
         dnIter = m_attributeSubscriptionsByDn.find(dn);
         RSYS_ASSERT(dnIter != m_attributeSubscriptionsByDn.end());
      }

      // Get the map of attribute ID -> set of subscription identifiers.
      MibSubscriptionsByAttributeId& mibSubscriptionsByAttributeId = dnIter->second;

      // Now iterate through the supplied attribute IDs and add each to the map, mapping each
      // to the subscription identifier that we are adding.  This gives quick access to
      // a subscription identifier from an attribute ID.
      for( MibAttributeIds::const_iterator attrIdsIter = mibAttributeIds.begin();
            attrIdsIter != mibAttributeIds.end();
            attrIdsIter++)
      {
         // Add to map, overwriting if already there.
         mibSubscriptionsByAttributeId[*attrIdsIter].insert(mibSubscriptionIdentifier);
      }

      RSYS_ASSERT( mibAttributeValuesByDn.find(dn) == mibAttributeValuesByDn.end() );
      MibAttributeValues mibAttributeValues;
      m_mibInterface.GetAttributes(dn, mibAttributeIds, mibAttributeValues);

      if(mibAttributeValues.GetAttributeCount() > 0)
      {
         mibAttributeValuesByDn[dn] = mibAttributeValues;
      }
   }

   // Secondly: MibObjectSubscriptionsByDn.
   for(MibObjectClassesByDn::const_iterator i = objectClassesByDn.begin();
         i != objectClassesByDn.end();
         i++)
   {
      // See if we already have this DN, if not add it.
      MibDN dn = i->first;
      MibObjectClasses mibObjectClasses = i->second;

      MibObjectSubscriptionsByDn::iterator dnIter = m_objectSubscriptionsByDn.find(dn);
      if(dnIter == m_objectSubscriptionsByDn.end())
      {
         TRACE_PRINTF("AddSubscription creating new empty ObjectSubsByDN (%s) subscription map entry", dn.ToString().c_str() );

         // No entry for this DN so add one.
         MibSubscriptionsByObjectClass emptySubsByObj;
         m_objectSubscriptionsByDn[dn] = emptySubsByObj;
         dnIter = m_objectSubscriptionsByDn.find(dn);
         RSYS_ASSERT(dnIter != m_objectSubscriptionsByDn.end());
      }

      // Get the map of object  -> set of subscription identifiers.
      MibSubscriptionsByObjectClass& mibSubscriptionsByObjectClass = dnIter->second;

      for(MibObjectClasses::const_iterator objClassesIter = mibObjectClasses.begin();
            objClassesIter != mibObjectClasses.end();
            objClassesIter++)
      {
         MibObjectClass mibObjectClass = *objClassesIter;

         TRACE_PRINTF("AddSubscription to %s on %s", MibObjectClassToString(mibObjectClass), dn.ToString().c_str() );

         // Add to map, overwriting if already there.
         mibSubscriptionsByObjectClass[*objClassesIter].insert(mibSubscriptionIdentifier);

         weak_ptr<MibObject> mo = m_mibInterface.FindMibObject(dn);
         shared_ptr<MibObject> mibObject = mo.lock();

         if(mibObject)
         {
            set< shared_ptr<MibObject> > childObjects;

            mibObject->GetChildObjects(mibObjectClass, childObjects);

            for( set< shared_ptr<MibObject> >::iterator childIter = childObjects.begin();
                  childIter != childObjects.end();
                  childIter++ )
            {
               shared_ptr<MibObject> childObject = *childIter;
               MibAttributeValues childAttributeValues;

               TRACE_PRINTF("AddSubscription childObject %s.", childObject->ToString().c_str() );
               childObject->GetMibAttributes(childAttributeValues);

               if(childAttributeValues.GetAttributeCount() > 0)
               {
                  mibAttributeValuesByDn[childObject->GetDN()] = childAttributeValues;
               }
            }
         }
      }
   }

   // May not actually have any so check.
   if(mibAttributeValuesByDn.size())
   {
      m_subscriptionNotifyInterface.SendSubscriptionNotification(
            subscriberId,
            subscriptionId,
            mibAttributeValuesByDn);
   }
}

MibSubscriptionManager::RemoveSubscriptionResult MibSubscriptionManager::RemoveSubscription(u32 subscriberId, u32 subscriptionId)
{
    // Build a subscription identifier.
    MibSubscriptionIdentifier mibSubscriptionIdentifier;
    mibSubscriptionIdentifier.m_subscriberId = subscriberId;
    mibSubscriptionIdentifier.m_subscriptionId = subscriptionId;

    // Remove it from the easy map.
    MibSubscriptionsByIdentifier::iterator findSubByIdentifierIter = m_subscriptionsByIdentifier.find(mibSubscriptionIdentifier);
    if(findSubByIdentifierIter == m_subscriptionsByIdentifier.end())
    {
        return REMOVE_SUBSCRIPTION_NO_SUCH_SUB;
    }

    for( MibAttributeIdsByDn::iterator i = findSubByIdentifierIter->second.m_attributeIdsByDn.begin() ;
         i != findSubByIdentifierIter->second.m_attributeIdsByDn.end();
         i++)
    {
        // Grab the DN for use below.
        MibDN dn = i->first;

        // The trickier two...

        // Firstly: MibAttributeSubscriptionsByDn
        // See if we already have this DN, if not we're done.
        MibAttributeSubscriptionsByDn::iterator dnAttrIter = m_attributeSubscriptionsByDn.find(dn);
        if(dnAttrIter != m_attributeSubscriptionsByDn.end())
        {
            // Get the map of attribute ID -> set of subscription identifiers.
            MibSubscriptionsByAttributeId& mibSubscriptionsByAttributeId = dnAttrIter->second;

            // Now iterate through all the attribute IDs and erase any matching subscribers.
            for( MibSubscriptionsByAttributeId::iterator mibSubsByAttrIter = mibSubscriptionsByAttributeId.begin();
                mibSubsByAttrIter != mibSubscriptionsByAttributeId.end();
                ++mibSubsByAttrIter)
            {
                if(mibSubsByAttrIter->second.find(mibSubscriptionIdentifier) != mibSubsByAttrIter->second.end())
                {
                    mibSubsByAttrIter->second.erase(mibSubscriptionIdentifier);
                }
            }
        }

        // Secondly: MibObjectSubscriptionsByDn.
        MibObjectSubscriptionsByDn::iterator dnObjIter = m_objectSubscriptionsByDn.find(dn);
        if(dnObjIter != m_objectSubscriptionsByDn.end())
        {
            // Get the map of object ID -> set of subscription identifiers.
            MibSubscriptionsByObjectClass& mibSubscriptionsByObjectClass = dnObjIter->second;

            // Now iterate through all the object IDs and erase any matching subscribers.
            for( MibSubscriptionsByObjectClass::iterator mibSubsByObjIter = mibSubscriptionsByObjectClass.begin();
                mibSubsByObjIter != mibSubscriptionsByObjectClass.end();
                ++mibSubsByObjIter)
            {
                if(mibSubsByObjIter->second.find(mibSubscriptionIdentifier) != mibSubsByObjIter->second.end())
                {
                    mibSubsByObjIter->second.erase(mibSubscriptionIdentifier);
                }
            }
        }
    }

    // And erase the subscription.
    m_subscriptionsByIdentifier.erase(findSubByIdentifierIter);

    RETURN(REMOVE_SUBSCRIPTION_OK);
}

std::string MibSubscriptionManager::ToString() const
{
    ENTER();

    ostringstream stream;

    MibSubscriptionsByIdentifier::const_iterator subsByIdentIter = m_subscriptionsByIdentifier.begin();
    while(subsByIdentIter != m_subscriptionsByIdentifier.end())
    {
        stream << subsByIdentIter->second.ToString() << endl;
        ++subsByIdentIter;
    }

    RETURN(stream.str());
}

// TODO: May need to support multiple DN deletion
// Clarify (somehow) that a delete where attibutesIds.empty(), means delete "MibDN"
void MibSubscriptionManager::HandleChangedOrDeletedAttributes(const MibDN& dn, const MibAttributeIds& attributeIds, bool attribsDeleted) const
{
    ENTER();

    // Build up map of affected subscriptions to related attribute Ids.
    map<MibSubscriptionIdentifier, MibAttributeIds> affectedSubscriptionIds;

    //Firstly, look through the attribute subscriptions and deal with them
    // Look up attribute IDs in the map of DN->AttrID->Subscription
    MibAttributeSubscriptionsByDn::const_iterator dnAttrIter = m_attributeSubscriptionsByDn.find(dn);
    if(dnAttrIter != m_attributeSubscriptionsByDn.end())
    {
        const MibSubscriptionsByAttributeId& mibSubscriptionsByAttributeId = dnAttrIter->second;

        for( MibAttributeIds::const_iterator changedIdsIter = attributeIds.begin();
            changedIdsIter != attributeIds.end();
            ++changedIdsIter)
        {
            const MibAttributeId & changedMibAttributeId = *changedIdsIter;

            MibSubscriptionsByAttributeId::const_iterator foundIdIter = mibSubscriptionsByAttributeId.find(changedMibAttributeId);
            if(foundIdIter != mibSubscriptionsByAttributeId.end())
            {
                // We found the attribute, now see who wants to know about it.
                const set<MibSubscriptionIdentifier> subscriptionIdentifiers = foundIdIter->second;

                for(set<MibSubscriptionIdentifier>::const_iterator subIdentIter = subscriptionIdentifiers.begin();
                    subIdentIter != subscriptionIdentifiers.end();
                    ++subIdentIter)
                {
                    MibSubscriptionIdentifier mibSubscriptionIdentifier = *subIdentIter;

                    /**
                     * To maintain current behaviour, add ALL attributes from subscription, not just changed ones!
                     * This may need to change to reduce size of messages
                     */
                    MibSubscriptionsByIdentifier::const_iterator subsByIdIter = m_subscriptionsByIdentifier.find(mibSubscriptionIdentifier);
                    RSYS_ASSERT(subsByIdIter != m_subscriptionsByIdentifier.end());

                    MibSubscription mibSubscription = subsByIdIter->second;

                    TRACE_PRINTF("Adding to affected subscriptions(attr): subscriberId=%"PRIu32", subscriptionId=%"PRIu32,
                                 subIdentIter->m_subscriberId, subIdentIter->m_subscriptionId);

                    affectedSubscriptionIds[mibSubscriptionIdentifier] = mibSubscription.m_attributeIdsByDn[dn];
                }
            }
        }
    }

    MibDN  parentDn = dn;
    parentDn.pop_back();
    MibRDN leafRdn  = dn.back();

    MibObjectSubscriptionsByDn::const_iterator dnObjIter = m_objectSubscriptionsByDn.find(parentDn);
    if(dnObjIter != m_objectSubscriptionsByDn.end())
    {
        const MibSubscriptionsByObjectClass& mibSubscriptionsByObjectClass = dnObjIter->second;

        // Any subscriptions to that parent/child pair?
        MibSubscriptionsByObjectClass::const_iterator foundObjectClassIter = mibSubscriptionsByObjectClass.find( leafRdn.GetMibObjectClass() );
        if(foundObjectClassIter != mibSubscriptionsByObjectClass.end())
        {
            // We found the object, now see who wants to know about it.
            const std::set<MibSubscriptionIdentifier>& mibSubscriptionIdentifiers = foundObjectClassIter->second;

            if(attributeIds.empty())
            {
                if(attribsDeleted)
                {
                    // If there are no attributes, a delete action will delete the dn object.
                    for(std::set<MibSubscriptionIdentifier>::const_iterator subIdentIter = mibSubscriptionIdentifiers.begin();
                        subIdentIter != mibSubscriptionIdentifiers.end();
                        ++subIdentIter)
                    {
                        MibAttributeIds emptyMibAttributeIds;

                        TRACE_PRINTF("Adding to affected subscriptions(obj): subscriberId=%"PRIu32", subscriptionId=%"PRIu32,
                                     subIdentIter->m_subscriberId, subIdentIter->m_subscriptionId);

                        affectedSubscriptionIds[*subIdentIter] = emptyMibAttributeIds;
                    }
                }
            }
            else
            {
                for( MibAttributeIds::const_iterator changedIdsIter = attributeIds.begin();
                     changedIdsIter != attributeIds.end();
                     ++changedIdsIter)
                {
                    const MibAttributeId & changedMibAttributeId = *changedIdsIter;

                    MibSubscriptionsByObjectClass::const_iterator foundObjectClassIter = mibSubscriptionsByObjectClass.find( leafRdn.GetMibObjectClass() );
                    if(foundObjectClassIter != mibSubscriptionsByObjectClass.end())
                    {
                        for(std::set<MibSubscriptionIdentifier>::const_iterator subIdentIter = mibSubscriptionIdentifiers.begin();
                            subIdentIter != mibSubscriptionIdentifiers.end();
                            ++subIdentIter)
                        {
                            TRACE_PRINTF("Adding to affected subscriptions(obj): subscriberId=%"PRIu32", subscriptionId=%"PRIu32,
                                         subIdentIter->m_subscriberId, subIdentIter->m_subscriptionId);
                            affectedSubscriptionIds[*subIdentIter].insert(changedMibAttributeId);
                        }
                    }
                }
            }
        }
    }

    // Now go and tell our notify interface about the subscriptions that need to be sent.
    for( map<MibSubscriptionIdentifier, MibAttributeIds>::iterator affectedSubscriptionsIter = affectedSubscriptionIds.begin();
         affectedSubscriptionsIter != affectedSubscriptionIds.end();
         affectedSubscriptionsIter++)
    {
        const MibSubscriptionIdentifier & affectedMibSubscriptionIdentifier = affectedSubscriptionsIter->first;
        MibAttributeIds                 & affectedMibAttributeIds           = affectedSubscriptionsIter->second;

        TRACE_PRINTF("affectedSubscriptionIds %s", affectedMibSubscriptionIdentifier.ToString().c_str() );

        MibSubscriptionsByIdentifier::const_iterator subsByIdIter = m_subscriptionsByIdentifier.find(affectedMibSubscriptionIdentifier);

        RSYS_ASSERT(subsByIdIter != m_subscriptionsByIdentifier.end());

        MibSubscription mibSubscription = subsByIdIter->second;

        if(attribsDeleted)
        {
            // Tell our notify interface.
            TRACE_PRINTF("m_subscriptionNotifyInterface.SendSubscriptionDeleteNotification(deleted)");

            MibAttributeIdsByDn mibAttributeIdsByDn;

            mibAttributeIdsByDn[dn] = attributeIds;

            m_subscriptionNotifyInterface.SendSubscriptionDeleteNotification(
                    affectedMibSubscriptionIdentifier.m_subscriberId,
                    affectedMibSubscriptionIdentifier.m_subscriptionId,
                    mibAttributeIdsByDn );
        }
        else
        {
            MibAttributeValuesByDn mibAttributeValuesByDn;

            MibAttributeValues changedAttributeValues;
            m_mibInterface.GetAttributes(dn, affectedMibAttributeIds, changedAttributeValues);

            mibAttributeValuesByDn[dn] = changedAttributeValues;

            // And tell our notify interface.
            m_subscriptionNotifyInterface.SendSubscriptionNotification(
                    affectedMibSubscriptionIdentifier.m_subscriberId,
                    affectedMibSubscriptionIdentifier.m_subscriptionId,
                    mibAttributeValuesByDn);
        }
    }

    if(affectedSubscriptionIds.empty())
    {
        TRACE_PRINTF("HandleChangedOrDeletedAttributes: %s - no affected subscriptions found.", dn.ToString().c_str());
    }
}

std::string MibSubscriptionManager::MibSubscription::ToString() const
{
    ostringstream stream;
    stream << m_mibSubscriptionIdentifier.ToString()
           << ", attr=" << m_attributeIdsByDn.ToString()
           << ", obj=" << m_objectClassesByDn.ToString();

    return stream.str();
}

std::string MibSubscriptionManager::MibSubscriptionIdentifier::ToString() const
{
    ostringstream stream;
    stream << "subscriber=" << m_subscriberId
           << "/" << m_subscriberName
           << ", subscriptionId=" << m_subscriptionId;

    return stream.str();
}

