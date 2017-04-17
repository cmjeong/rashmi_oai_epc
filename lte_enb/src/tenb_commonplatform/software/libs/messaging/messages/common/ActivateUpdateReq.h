///////////////////////////////////////////////////////////////////////////////
//
// ActivateUpdateReq.h
//
// Send this to OAM to install a previously downloaded update to an update
// bank.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ActivateUpdateReq_h_
#define __ActivateUpdateReq_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class ActivateUpdateReq : public threeway::Serialisable
{
public:
    static const unsigned short MaxUpdateReqStringLength = 80;

    /**
     * Default constructor.
     */
    ActivateUpdateReq() : m_dummyPayload(0){};

    virtual ~ActivateUpdateReq() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_SW_ACTIVATE_REQ; };
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);
    virtual std::string ToString() const;

private:
	u8 m_dummyPayload ;
};

#endif
