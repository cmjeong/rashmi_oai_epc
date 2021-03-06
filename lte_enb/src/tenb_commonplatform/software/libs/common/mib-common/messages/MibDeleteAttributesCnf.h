///////////////////////////////////////////////////////////////////////////////
//
// MibGetAttributesCnf.h
//
// Message for confirming deletion of attributes on one or more MOs.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MibDeleteAttributesCnf_h_
#define __MibDeleteAttributesCnf_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MibAttributeIdsMessage.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class MibDeleteAttributesCnf : public MibAttributeIdsMessage
{
public:
    /**
     * Confirm deletion of attributes on one or more MOs.
     */
    MibDeleteAttributesCnf() {};

    /**
     * Destructor.
     */
    virtual ~MibDeleteAttributesCnf() {};

    /**
     * Implement Serialisable virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_MIB_DELETE_ATTRIBUTES_CNF; };

private:

};

#endif
