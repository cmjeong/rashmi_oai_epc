///////////////////////////////////////////////////////////////////////////////
//
// MibDeleteObjectCnf.h
//
// Message for confirming deletion of a MIB object.
// Currently this has to succeed so this message just contains the deleted DN.
// Core MIB will assert if deletion is not possible - it's a coding bug!
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MibDeleteObjectCnf_h_
#define __MibDeleteObjectCnf_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////
#include <mib-common/MibObjectDeleteResult.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MibDnMessage.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class MibDeleteObjectCnf : public MibDnMessage
{
public:
    /**
     * Constructor
     */
    MibDeleteObjectCnf(const MibDN& dn, MibObjectDeleteResult result) : MibDnMessage(dn), m_result(result) {};

    /**
     * Default constructor to allow deserialisation.
     */
    MibDeleteObjectCnf() : m_result(MIB_OBJ_DEL_SUCCESS) {};

    /**
     * Destructor.
     */
    virtual ~MibDeleteObjectCnf() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    s32 Serialise(u8* data, u32 dataMaxBytes) const;
    bool DeSerialise(const u8* data, u32 dataLen);
    u32 GetSerialisationId() const { return SERIALISATION_ID_MIB_DELETE_OBJECT_CNF; };

    std::string ToString() const;

    MibObjectDeleteResult GetDeleteResult() const;

private:
    MibObjectDeleteResult m_result;
};

#endif
