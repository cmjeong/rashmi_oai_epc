///////////////////////////////////////////////////////////////////////////////
//
// MibAccessInterface.h
//
// Provides abstract access to a MIB.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MibAccessInterface_h_
#define __MibAccessInterface_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <boost/shared_ptr.hpp>

#include <system/SerialisedData.h>
#include <system/Url.h>
#include <system/Fqdn.h>
#include <comms/IPv4Address.h>
#include <system/TimeWrap.h>
#include <mib-common/MibDN.h>
#include <mib-common/MibAttributeIds.h>
#include <mib-common/MibAttributeValues.h>
#include <mib-common/MibAttributeIdsByDn.h>
#include <mib-common/MibObjectClassesByDn.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MessagingEntity.h"

using namespace boost;

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class MibAccessInterface
{
public:
    virtual ~MibAccessInterface() {};

    /**
     * Subscribe to a set of MIB parameters.
     *
     * \param subscriptionId  Used as a tag for reference when receiving a subscription IND or when unsubscribing.
     * \param entity          Entity that is subscribing to the parameters.
     * \param dn              Object to subscribe to.
     * \param mibParams       Set of MIB parameters that this entity is interested in.
     * \param waitForResponse Wait until all MIB params have been updated and confirm has been received.
     */
    virtual void SubscribeMibAttributes(u32 subscriptionId,
                                        const MessagingEntity& entity,
                                        const MibDN& dn,
                                        const MibAttributeIds& mibParams,
                                        bool waitForResponse) = 0;
    virtual void SubscribeMibAttributes(u32 subscriptionId,
                                        const MessagingEntity& entity,
                                        const MibAttributeIdsByDn& attributeIdsByDn,
                                        const MibObjectClassesByDn& objectClassesByDn,
                                        bool waitForResponse) = 0;
    virtual void SubscribeMibAttributes(u32 subscriptionId,
                                        const MessagingEntity& entity,
                                        const MibAttributeIds& mibParams,
                                        bool waitForResponse) = 0; // Defaults to FAP.0 DN.

    /**
     * Unsubscribe from a set of MIB parameters.
     *
     * \param entity          Entity that is subscribing to the parameters.
     * \param subscriptionId  The subscription to remove.
     */
    virtual void UnsubscribeMibAttributes(u32 subscriptionId, MessagingEntity entity) = 0;

    /**
     * Handle a message containing the values of MIB attributes than have been subscribed to.
     */
    virtual void HandleMibSubscribeAttributesInd(shared_ptr<threeway::SerialisedData> receivedMessage) = 0;

    /**
     * Handle a message containing the IDs of MIB attributes that have been subscribed to
     * but have been deleted in the MIB.
     */
    virtual void HandleMibSubscribeAttributesDeleteInd(shared_ptr<threeway::SerialisedData> receivedMessage) = 0;

    virtual bool IsMibObjectPresent(const MibDN& dn) const = 0;
    virtual u32 GetMibObjectCount(const MibDN& parent, MibObjectClass child) const = 0;
    virtual set<u32> GetMibObjectInstances(const MibDN& parent, MibObjectClass child) const = 0;


    /**
     * Check if MIB attribute available in local cache.
     * Defaults to DN of FAP.0
     *
     * \mibAttributeId MIB attribute to check.
     */
    virtual bool IsMibAttributePresent(MibAttributeId mibAttributeId) const = 0;

    /**
     * Check if MIB attribute available in local cache against given DN.
     *
     * \dn             Object DN.
     * \mibAttributeId MIB attribute to check.
     */
    virtual bool IsMibAttributePresent(const MibDN& dn, MibAttributeId mibAttributeId) const = 0;

    /**
     * Get current value of a MIB parameter.  Asserts if not present.
     *
     * \dn              Distinguished name of the object to get the attribute from.
     * \mibAttributeId  Attribute to get current value of.
     * \value           Will be set to value of parameter.
     */
    virtual void GetMibAttribute(const MibDN& dn, MibAttributeId mibAttributeId, u32& value) const = 0;
    virtual void GetMibAttribute(const MibDN& dn, MibAttributeId mibAttributeId, u16& value) const = 0;
    virtual void GetMibAttribute(const MibDN& dn, MibAttributeId mibAttributeId, u8& value) const = 0;
    virtual void GetMibAttribute(const MibDN& dn, MibAttributeId mibAttributeId, s32& value) const = 0;
    virtual void GetMibAttribute(const MibDN& dn, MibAttributeId mibAttributeId, s16& value) const = 0;
    virtual void GetMibAttribute(const MibDN& dn, MibAttributeId mibAttributeId, s8& value) const = 0;
    virtual void GetMibAttribute(const MibDN& dn, MibAttributeId mibAttributeId, bool& value) const = 0;
    virtual void GetMibAttribute(const MibDN& dn, MibAttributeId mibAttributeId, std::string& value) const = 0;
    virtual void GetMibAttribute(const MibDN& dn, MibAttributeId mibAttributeId, std::vector<std::string>& value) const = 0;
    virtual void GetMibAttribute(const MibDN& dn, MibAttributeId mibAttributeId, std::vector<u32>& value) const = 0;
    virtual void GetMibAttribute(const MibDN& dn, MibAttributeId mibAttributeId, std::vector<s32>& value) const = 0;/* mohan */
    virtual void GetMibAttribute(const MibDN& dn, MibAttributeId mibAttributeId, threeway::IPv4Address& value) const = 0;
    virtual void GetMibAttribute(const MibDN& dn, MibAttributeId mibAttributeId, threeway::TimeWrap& value) const = 0;
    virtual void GetMibAttribute(const MibDN& dn, MibAttributeId mibAttributeId, threeway::Fqdn& value) const = 0;
    virtual void GetMibAttribute(const MibDN& dn, MibAttributeId mibAttributeId, threeway::Url& value) const = 0;
    virtual void GetMibAttributeAsString(const MibDN& dn, MibAttributeId mibAttributeId, string& value) const = 0;

    /**
     * Get current value of a FAP object MIB parameter.  Asserts if not present.
     *
     * \mibAttributeId  Attribute to get current value of.
     * \value           Will be set to value of parameter.
     */
    virtual void GetMibAttribute(MibAttributeId mibAttributeId, u32& value) const = 0;
    virtual void GetMibAttribute(MibAttributeId mibAttributeId, u16& value) const = 0;
    virtual void GetMibAttribute(MibAttributeId mibAttributeId, u8& value) const = 0;
    virtual void GetMibAttribute(MibAttributeId mibAttributeId, s32& value) const = 0;
    virtual void GetMibAttribute(MibAttributeId mibAttributeId, s16& value) const = 0;
    virtual void GetMibAttribute(MibAttributeId mibAttributeId, s8& value) const = 0;
    virtual void GetMibAttribute(MibAttributeId mibAttributeId, bool& value) const = 0;
    virtual void GetMibAttribute(MibAttributeId mibAttributeId, std::string& value) const = 0;
    virtual void GetMibAttribute(MibAttributeId mibAttributeId, std::vector<std::string>& value) const = 0;
    virtual void GetMibAttribute(MibAttributeId mibAttributeId, std::vector<u32>& value) const = 0;
    virtual void GetMibAttribute(MibAttributeId mibAttributeId, std::vector<s32>& value) const = 0; /*  mohan*/
    virtual void GetMibAttribute(MibAttributeId mibAttributeId, threeway::IPv4Address& value) const = 0;
    virtual void GetMibAttribute(MibAttributeId mibAttributeId, threeway::TimeWrap& value) const = 0;
    virtual void GetMibAttribute(MibAttributeId mibAttributeId, threeway::Fqdn& value) const = 0;
    virtual void GetMibAttribute(MibAttributeId mibAttributeId, threeway::Url& value) const = 0;

    /**
     * Set MIB attributes on specified DN in local cache and send set attributes message to MIB.
     */
    virtual void SetMibAttributesByDn(const MibDN& mibDn, const MibAttributeValues& mibAttributeValues, MessagingEntity sourceEntity) = 0;

    /**
     * Set MIB attributes on specified DN in local cache and send set attributes message to MIB.
     */
    virtual void SetMibAttributes(const MibDN& mibDn, const MibAttributeValues& mibAttributeValues, MessagingEntity sourceEntity) = 0;

    /**
     * Set MIB attributes on FAP.0 DN in local cache and send set attributes message to MIB.
     */
    virtual void SetMibAttributes(const MibAttributeValues& mibAttributeValues, MessagingEntity sourceEntity) = 0;

    /**
     * Delete MIB attributes on specified DN from local cache and send delete attributes message to MIB.
     */
    virtual void DeleteMibAttributes(const MibDN& mibDn, const MibAttributeIds& mibAttributeIds, MessagingEntity sourceEntity) = 0;
};

#endif
