///////////////////////////////////////////////////////////////////////////////
//
// IuCsUpInitialisationSuccess
//
// Internal signalling message in Cs User Plane, indicating that the
// INITIALISATION procedure has succeeded.  This in turn causes the ACK
// response to be sent to Iu, aborting call establishment.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __IuCsUpInitialisationSuccess_h_
#define __IuCsUpInitialisationSuccess_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////
class IuCsUpInitialisationSuccess : public threeway::Serialisable
{
public:
    // Need a default constructor for decoding received messages...
    IuCsUpInitialisationSuccess () { m_successDchNumber = 0xff; }
    IuCsUpInitialisationSuccess (u8 successDchNumber);
    virtual ~IuCsUpInitialisationSuccess();

    /**
     * Get / Set
     */
    u8 GetDchNumber () const { return m_successDchNumber; }
    void SetDchNumber (u8 successDchNumber) { m_successDchNumber = successDchNumber; }

    /**
     * Implement Serialisable virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_CS_UP_INITIALISATION_SUCCESS; };
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    /**
     * Return string representation for debug.
     */
    virtual std::string ToString() const;

private:
    // Just a single, solitary byte :)
    static const u32 SERIALISATION_NUM_BYTES = 1;

    // The zero based Dch number allocated in Rrc during Rab establishment.
    u8 m_successDchNumber;
};

#endif
