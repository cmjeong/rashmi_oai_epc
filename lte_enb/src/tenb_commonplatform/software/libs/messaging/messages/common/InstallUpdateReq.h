///////////////////////////////////////////////////////////////////////////////
//
// InstallUpdateReq.h
//
// Send this to OAM to install a previously downloaded update to an update
// bank.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __InstallUpdateReq_h_
#define __InstallUpdateReq_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class InstallUpdateReq : public threeway::Serialisable
{
public:
    static const unsigned short MaxUpdateReqStringLength = 80;

    /**
     * Default constructor.  For messaging internal use only.
     */
    InstallUpdateReq() {};

    /**
     * Construct an install update request message.
     */
    InstallUpdateReq(
        const std::string & updateDir,
        const std::string & updateFilename
        );

    virtual ~InstallUpdateReq() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_SW_INSTALL_REQ; };
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);
    virtual std::string ToString() const;

    /**
     * Getters.
     */
    const std::string & GetUpdateDir() const { return m_updateDir; }
    const std::string & GetUpdateFilename() const { return m_updateFilename; }

private:

    std::string m_updateDir;
    std::string m_updateFilename;
};

#endif
