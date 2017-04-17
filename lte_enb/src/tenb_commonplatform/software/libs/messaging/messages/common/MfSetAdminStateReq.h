///////////////////////////////////////////////////////////////////////////////
//
// MfSetAdminStateReq.h
//
// Commands a Managed Fing to change its admin state.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MfSetAdminStateReq_h_
#define __MfSetAdminStateReq_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>
#include <system/ManagedObject.h>
#include <platform/ManagedFing.h>

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class MfSetAdminStateReq : public threeway::Serialisable
{
public:

    /**
     * Default constructor.  For messaging internal use only.
     */
    MfSetAdminStateReq();

    /**
     * Construct a MfSetAdminStateReq.
     */
    MfSetAdminStateReq(ManagedFing managedFing, threeway::ManagedObject::AdminState adminState);

    virtual ~MfSetAdminStateReq() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_MF_SET_ADMIN_STATE_REQ; };
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);
    virtual std::string ToString() const;

    /**
     * Setters/Getters
     */
    ManagedFing GetManagedFing() { return m_managedFing; }
    threeway::ManagedObject::AdminState GetAdminState() { return m_adminState; }

private:

    ManagedFing m_managedFing;
    threeway::ManagedObject::AdminState m_adminState;
};

#endif
