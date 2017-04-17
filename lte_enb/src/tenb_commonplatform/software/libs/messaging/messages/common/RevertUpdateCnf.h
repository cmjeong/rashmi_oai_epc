///////////////////////////////////////////////////////////////////////////////
//
// RevertUpdateCnf.h
//
// Send by OAM to confirm a software installation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __RevertUpdateCnf_h_
#define __RevertUpdateCnf_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class RevertUpdateCnf : public threeway::Serialisable
{
public:
    static const unsigned short MaxRevertUpdateCnfStringLength = 80;

    /**
     * Default constructor.  For messaging internal use only.
     */
    RevertUpdateCnf();

    /**
     * Construct a KPI configure request message.
     */
    RevertUpdateCnf(
        bool succeeded,
        const std::string & failureString );

    virtual ~RevertUpdateCnf() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_SW_REVERT_CNF; };
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);
    virtual std::string ToString() const;

    /**
     * Getters.
     */
    const bool & GetSucceeded() const { return m_succeeded; }
    const std::string & GetFailureString() const { return m_failureString; }

private:

    bool m_succeeded;
    std::string m_failureString;
};

#endif
