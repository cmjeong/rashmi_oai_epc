///////////////////////////////////////////////////////////////////////////////
//
// FtpGetCnf.h
//
// Send from OAM to confirm a software update.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ApplyUpdateCnf_h_
#define __ApplyUpdateCnf_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class ApplyUpdateCnf : public threeway::Serialisable
{
public:
    static const unsigned short MaxApplyUpdateCnfStringLength = 80;

    /**
     * Default constructor.  For messaging internal use only.
     */
    ApplyUpdateCnf();

    /**
     * Construct a KPI configure request message.
     */
    ApplyUpdateCnf(
        bool succeeded,
        const std::string & failureString );

    virtual ~ApplyUpdateCnf() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_SW_UPDATE_CNF; };
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
