///////////////////////////////////////////////////////////////////////////////
//
// IuCsUpInitialisationFailure
//
// Internal signalling message in Cs User Plane, indicating that the
// INITIALISATION procedure has failed.  This in turn causes the NACK
// response to be sent to Iu, aborting call establishment.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __IuCsUpInitialisationFailure_h_
#define __IuCsUpInitialisationFailure_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////
class IuCsUpInitialisationFailure : public threeway::Serialisable
{
public:
    // Need a default constructor for decoding received messages...
    IuCsUpInitialisationFailure () { m_failedDchNumber = 0xff; }
    IuCsUpInitialisationFailure (u8 failedDchNumber);
    virtual ~IuCsUpInitialisationFailure();

    /**
     * Get / Set
     */
    u8 GetDchNumber () const { return m_failedDchNumber; }
    void SetDchNumber (u8 failedDchNumber) { m_failedDchNumber = failedDchNumber; }

    /**
     * Implement Serialisable virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_CS_UP_INITIALISATION_FAILURE; };
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
    u8 m_failedDchNumber;
};

#endif
