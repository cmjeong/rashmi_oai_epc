///////////////////////////////////////////////////////////////////////////////
//
// MibAttributesMessage.h
//
// Base class for MIB messaging API messages that contain attribute values.
// E.g. SetAttributesReq, GetAttributesCnf, SubscribeInd...
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MibAttributesMessage_h_
#define __MibAttributesMessage_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <Radisys.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "mib-common/MibAttributeValuesByDn.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class MibAttributesMessage : public threeway::Serialisable
{
public:
    /**
     * Default constructor.
     */
    MibAttributesMessage();

    /**
     * Destructor.
     */
    virtual ~MibAttributesMessage();

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);
    virtual std::string ToString() const;

    /**
     * Add attributes to the message.  Can be called multiple times for *different* DNs.
     *
     * \dn          MO to add attributes to.
     * \attributes  Attributes to add.
     */
    void AddAttributes(const MibDN& dn, const MibAttributeValues& attributes);

    /**
     * Get list of DNs in the message.
     */
    std::vector<MibDN> GetDnList() const;

    /**
     * Get attribute values for a given DN.
     */
    const MibAttributeValues& GetMibAttributeValues(const MibDN& dn) const;

    /**
     * Get attribute values by DN.
     */
    const MibAttributeValuesByDn& GetMibAttributeValuesByDn() const { return m_attributes; };

protected:

private:

    /**
     * DN to attribute ID/value pairs.
     */
    MibAttributeValuesByDn m_attributes;
};

#endif
