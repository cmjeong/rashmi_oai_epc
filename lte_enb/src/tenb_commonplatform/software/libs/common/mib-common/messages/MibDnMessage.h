///////////////////////////////////////////////////////////////////////////////
//
// MibDnMessage.h
//
// Abstract class for a message containing a DN.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MibDnMessage_h_
#define __MibDnMessage_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "mib-common/MibDN.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class MibDnMessage : public threeway::Serialisable
{
public:
    /**
     * Constructor
     */
    MibDnMessage(const MibDN& dn);

    /**
     * Default constructor to allow deserialisation.
     */
    MibDnMessage() {};

    /**
     * Destructor.
     */
    virtual ~MibDnMessage() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    s32 Serialise(u8* data, u32 dataMaxBytes) const;
    bool DeSerialise(const u8* data, u32 dataLen);
    std::string ToString() const;

    /**
     * Accessors
     */
    MibDN GetDn() const { return m_dn; };

private:

    MibDN m_dn;

};

#endif
