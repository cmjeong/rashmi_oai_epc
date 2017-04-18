///////////////////////////////////////////////////////////////////////////////
//
// InstallUpdateCnf.h
//
// Send by OAM to confirm a software installation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __InstallUpdateCnf_h_
#define __InstallUpdateCnf_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class InstallUpdateCnf : public threeway::Serialisable
{
public:
    static const unsigned short MaxInstallUpdateCnfStringLength = 80;

    /**
     * Default constructor.  For messaging internal use only.
     */
    InstallUpdateCnf();

    /**
     * Construct a KPI configure request message.
     */
    InstallUpdateCnf(
        bool succeeded,
        const std::string & failureString );

    virtual ~InstallUpdateCnf() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_SW_INSTALL_CNF; };
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
