///////////////////////////////////////////////////////////////////////////////
//
// MibAttributeIdsMessage.h
//
// Base class for MIB messaging API messages that contain attribute IDs.
// E.g. GetAttributesReq, SubscribeAttributesReq, ...
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MibAttributeIdsMessage_h_
#define __MibAttributeIdsMessage_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <Radisys.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "mib-common/MibAttributeIdsByDn.h"
#include "mib-common/MibObjectClassesByDn.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class MibAttributeIdsMessage : public threeway::Serialisable
{
public:
    /**
     * Default constructor.
     */
    MibAttributeIdsMessage();

    /**
     * Destructor.
     */
    virtual ~MibAttributeIdsMessage();

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);
    virtual std::string ToString() const;

    /**
     * Add attribute IDs to the message.  Can be called multiple times for *different* DNs.
     *
     * \dn              MO to add attribute IDs to.
     * \attributeIds    Attribute IDs to add.
     */
    void AddAttributeIds(const MibDN& dn, const MibAttributeIds& attributeIds);

    /**
     * Add object classes to the message.  Can be called multiple times for *different* DNs.
     *
     * \dn              MO to add attribute IDs to.
     * \objectClasses   Object classes to add.
     */
    void AddObjectClasses(const MibDN& dn, const MibObjectClasses& objectClasses);

    /**
     * Get attribute IDs for a given DN.
     */
    const MibAttributeIds& GetMibAttributeIds(const MibDN& dn) const;

    /**
     * Get attribute IDs for all DNs.
     */
    const MibAttributeIdsByDn& GetMibAttributeIdsByDn() const { return m_attributeIdsByDn; }

    /**
     * Get object classes for all DNs.
     */
    const MibObjectClassesByDn& GetMibObjectClassesByDn() const { return m_objectClassesByDn; }

protected:

private:

    /**
     * DN to attribute ID/value pairs.
     */
    MibAttributeIdsByDn m_attributeIdsByDn;

    /**
     * DN to object-class/value pairs.
     */
    MibObjectClassesByDn m_objectClassesByDn;
};

#endif
