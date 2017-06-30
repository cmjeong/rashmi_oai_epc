///////////////////////////////////////////////////////////////////////////////
//
// MfSetAdminStateCnf.h
//
// Sent by a Managed Fing to confirm that the requested state change has
// occurred.  In the case of Shutting Down, the message will only be sent
// once the MF has reached the Locked state.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MfSetAdminStateCnf_h_
#define __MfSetAdminStateCnf_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>
#include <platform/ManagedFing.h>

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class MfSetAdminStateCnf : public threeway::Serialisable
{
public:

    /**
     * Default constructor.  For messaging internal use only.
     */
    MfSetAdminStateCnf();

    /**
     * Construct a MfSetAdminStateCnf.
     */
    MfSetAdminStateCnf(ManagedFing managedFing);

    virtual ~MfSetAdminStateCnf() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_MF_SET_ADMIN_STATE_CNF; };
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);
    virtual std::string ToString() const;

    /**
     * Setters/Getters
     */
    ManagedFing GetManagedFing() { return m_managedFing; }

private:

    ManagedFing m_managedFing;
};

#endif
