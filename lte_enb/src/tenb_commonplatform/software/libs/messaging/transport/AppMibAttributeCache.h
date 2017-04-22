///////////////////////////////////////////////////////////////////////////////
//
// AppMibAttributeCache.h
//
// Class to add attribute retrieval/caching to an app.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __AppMibAttributeCache_h_
#define __AppMibAttributeCache_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <map>
#include <string>

#include <boost/shared_ptr.hpp>

#include <system/Serialisable.h>
#include <system/Fqdn.h>
#include <mib-common/MibAttributeValues.h>
#include <mib-common/MibAttributeValuesByDn.h>
#include <mib-common/MibAttributeIdsByDn.h>
#include <mib-common/MibObjectClassesByDn.h>
#include <MibAttributeId.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Messenger.h"
#include "MibAccessInterface.h"
#include <mib-common/MIOAutoManage.h>
using namespace boost;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Const values
///////////////////////////////////////////////////////////////////////////////

static const u32 SUBSCRIBER_ID_NULL = 0xFFFFFFFF;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class MibAttributeUpdatedInformInterface
{
public:
    /**
     * Constructor/destructor.
     *
     * Interface class so default constructor is sufficient.
     * Virtual destructor required to avoid warnings.
     */
    virtual ~MibAttributeUpdatedInformInterface() {}

    /**
     * Inform client when a MIB attribute is updated by the cache.
     * Lets client perform some action on a new MIB attribute value.
     */
    virtual void MibAttributeUpdated(const MibDN & dn,MibAttributeId mibAttributeId) = 0;
    /**
     * Inform client when a number of MIB attributes in a subscription are changed
     * and updated by the cache.  The oldvalues and new values will only contain
     * those items that have changed within the subscription, not the entire subscription.
     * Lets the client perform some action on these changed MIB attribute values.
     */
    virtual void MibAttributesUpdated(u32 subscriptionId, const MibAttributeValuesByDn &oldValues, const MibAttributeValuesByDn &newValues) = 0;

    /**
     * Inform client when MIB dn/attributes is updated by the cache.
     * Lets client perform some action on MIB dn/attributes updates.
     */
    virtual void MibAttributesUpdated(u32 subscriptionId, const MibAttributeIdsByDn& mibAttributeValuesByDn) = 0;
};

class AppMibAttributeCache : public MibAccessInterface
{
public:
    /**
     * Constructor/destructor.
     */
    // TODO - bit cludgy having messenger and send message interface...
    AppMibAttributeCache(shared_ptr<Messenger> messenger, SendMessageInterface& sendMessageInterface, MibAttributeUpdatedInformInterface& updateInformInterface);
    virtual ~AppMibAttributeCache();

    /**
     * Implement MibAccessInterface.
     */
    virtual void SubscribeMibAttributes(u32 subscriptionId,
                                        const MessagingEntity& entity,
                                        const MibDN& dn,
                                        const MibAttributeIds& mibParams,
                                        bool waitForResponse);
    virtual void SubscribeMibAttributes(u32 subscriptionId,
                                        const MessagingEntity& entity,
                                        const MibAttributeIdsByDn& attributeIdsByDn,
                                        const MibObjectClassesByDn& objectClassesByDn,
                                        bool waitForResponse);
    virtual void SubscribeMibAttributes(u32 subscriptionId,
                                        const MessagingEntity& entity,
                                        const MibAttributeIds& mibParams,
                                        bool waitForResponse);
    virtual void UnsubscribeMibAttributes(u32 subscriptionId, MessagingEntity entity);

    virtual void HandleMibSubscribeAttributesInd(shared_ptr<SerialisedData> receivedMessage);
    virtual void HandleMibSubscribeAttributesDeleteInd(shared_ptr<SerialisedData> receivedMessage);

    virtual bool IsMibObjectPresent(const MibDN& dn) const;
    virtual u32 GetMibObjectCount(const MibDN& parent, MibObjectClass child) const;
    virtual set<u32> GetMibObjectInstances(const MibDN& parent, MibObjectClass child) const;

    virtual bool IsMibAttributePresent(MibAttributeId mibAttributeId) const;
    virtual bool IsMibAttributePresent(const MibDN& dn, MibAttributeId mibAttributeId) const;


    virtual void GetMibAttribute(const MibDN& dn, MibAttributeId mibAttributeId, u32& value) const;
    virtual void GetMibAttribute(const MibDN& dn, MibAttributeId mibAttributeId, u16& value) const;
    virtual void GetMibAttribute(const MibDN& dn, MibAttributeId mibAttributeId, u8& value) const;
    virtual void GetMibAttribute(const MibDN& dn, MibAttributeId mibAttributeId, s32& value) const;
    virtual void GetMibAttribute(const MibDN& dn, MibAttributeId mibAttributeId, s16& value) const;
    virtual void GetMibAttribute(const MibDN& dn, MibAttributeId mibAttributeId, s8& value) const;
    virtual void GetMibAttribute(const MibDN& dn, MibAttributeId mibAttributeId, bool& value) const;
    virtual void GetMibAttribute(const MibDN& dn, MibAttributeId mibAttributeId, std::string& value) const;
    virtual void GetMibAttribute(const MibDN& dn, MibAttributeId mibAttributeId, std::vector<std::string>& value) const;
    virtual void GetMibAttribute(const MibDN& dn, MibAttributeId mibAttributeId, std::vector<u32>& value) const;
    virtual void GetMibAttribute(const MibDN& dn, MibAttributeId mibAttributeId, std::vector<s32>& value) const; /* mohan */
    virtual void GetMibAttribute(const MibDN& dn, MibAttributeId mibAttributeId, threeway::IPv4Address& value) const;
    virtual void GetMibAttribute(const MibDN& dn, MibAttributeId mibAttributeId, threeway::TimeWrap& value) const;
    virtual void GetMibAttribute(const MibDN& dn, MibAttributeId mibAttributeId, threeway::Fqdn& value) const;
    virtual void GetMibAttribute(const MibDN& dn, MibAttributeId mibAttributeId, threeway::Url& value) const;
    virtual void GetMibAttributeAsString(const MibDN& dn, MibAttributeId mibAttributeId, string& value) const;

    virtual void GetMibAttribute(MibAttributeId mibAttributeId, u32& value) const;
    virtual void GetMibAttribute(MibAttributeId mibAttributeId, u16& value) const;
    virtual void GetMibAttribute(MibAttributeId mibAttributeId, u8& value) const;
    virtual void GetMibAttribute(MibAttributeId mibAttributeId, s32& value) const;
    virtual void GetMibAttribute(MibAttributeId mibAttributeId, s16& value) const;
    virtual void GetMibAttribute(MibAttributeId mibAttributeId, s8& value) const;
    virtual void GetMibAttribute(MibAttributeId mibAttributeId, bool& value) const;
    virtual void GetMibAttribute(MibAttributeId mibAttributeId, std::string& value) const;
    virtual void GetMibAttribute(MibAttributeId mibAttributeId, std::vector<std::string>& value) const;
    virtual void GetMibAttribute(MibAttributeId mibAttributeId, std::vector<u32>& value) const;
    virtual void GetMibAttribute(MibAttributeId mibAttributeId, std::vector<s32>& value) const; /* mohan */
    virtual void GetMibAttribute(MibAttributeId mibAttributeId, threeway::IPv4Address& value) const;
    virtual void GetMibAttribute(MibAttributeId mibAttributeId, threeway::TimeWrap& value) const;
    virtual void GetMibAttribute(MibAttributeId mibAttributeId, threeway::Fqdn& value) const;
    virtual void GetMibAttribute(MibAttributeId mibAttributeId, threeway::Url& value) const;

    virtual void SetMibAttributes(const MibAttributeValues& mibAttributeValues, MessagingEntity sourceEntity);
    virtual void SetMibAttributes(const MibDN& mibDn, const MibAttributeValues& mibAttributeValues, MessagingEntity sourceEntity);
    virtual void SetMibAttributesByDn(const MibDN& mibDn, const MibAttributeValues& mibAttributeValues, MessagingEntity sourceEntity);

    virtual void DeleteMibAttributes(const MibDN& mibDn, const MibAttributeIds& mibAttributeIds, MessagingEntity sourceEntity);

protected:

    // Local storage of MIB parameters.
    MibAttributeValuesByDn m_mibAttributesCache;

private:

    /**
     * Update attributes in the the local cache.
     *
     * \param mibAttributeValuesByDn    MIB attributes indexed by DN to set in the local cache.
     */
    void UpdateMibAttributesInCache(u32 subscriptionId, const MibAttributeValuesByDn& mibAttributeValuesByDn);

    /**
     * Delete MIB attributes from the local cache.
     *
     * \param attributeIdsToDeleteByDn MIB attribute IDs indexed by DN to delete from the local cache.
     */
    void DeleteMibAttributesFromCache(const MibAttributeIdsByDn& attributeIdsToDeleteByDn);

    /**
     * Get the value for an attribute in generic form.
     */
    shared_ptr<MibAttributeValue> GetMibAttribute(const MibDN& dn, MibAttributeId mibAttributeId) const;

    void PerformBlockingMibSubscribe( u32 subscriptionId, const MessagingEntity& entity, threeway::Serialisable& subscriptionReq );

    shared_ptr<Messenger> m_messenger;
    SendMessageInterface& m_sendMessageInterface;
    MibAttributeUpdatedInformInterface& m_updateInformInterface;

    /**
     * Cache a copy of this for efficiency.
     */
    MibDN m_fapZeroDn;

    /**
     * Thread protection for access to local MIB attribute cache.
     */
    mutable Mutex m_mibAttrCacheMutex;
	int GetMibObjectInstanceNum(string dn) const;
	void UpdateMIOObjStatus(const MibDN& mibDn, MessagingEntity sourceEntity);
};

}

#endif
