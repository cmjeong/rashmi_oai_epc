///////////////////////////////////////////////////////////////////////////////
//
// MibChangedAttributesNotifyInterface.h
//
// Interface for informing of changes in attribute values.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MibChangedAttributesNotifyInterface_h_
#define __MibChangedAttributesNotifyInterface_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <mib-common/MibAttributeIds.h>
#include <mib-common/MibDN.h>

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

/**
 * Interface for being informed about attribute changes.
 * I.e. this is how MibSubscriptionManager finds out about changed attributes.
 */
class MibChangedAttributesNotifyInterface
{
public:
    virtual ~MibChangedAttributesNotifyInterface() {};

    /**
     * Provide a list of attributes that have *changed* on a given object.
     */
    virtual void HandleChangedAttributes(const MibDN& dn,
                                         const MibAttributeIds& changedAttributeIds) const = 0;

    /**
     * Provide a list of attributes that have been deleted from, a given object.
     */
    virtual void HandleDeletedAttributes(const MibDN& dn,
                                         const MibAttributeIds& deletedAttributeIds) const = 0;

};

#endif
