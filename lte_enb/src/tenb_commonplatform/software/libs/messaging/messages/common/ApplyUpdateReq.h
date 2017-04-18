///////////////////////////////////////////////////////////////////////////////
//
// ApplyUpdateReq.h
//
// Send this to OAM to apply a previously downloaded update.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ApplyUpdateReq_h_
#define __ApplyUpdateReq_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class ApplyUpdateReq : public threeway::Serialisable
{
public:
    static const unsigned short MaxUpdateReqStringLength = 80;

    /**
     * Default constructor.  For messaging internal use only.
     */
    ApplyUpdateReq()/*:m_updateAction(OAM_UPDATE_ACTION_UNDEFINED)*/ {};

    /**
     * Construct a FTP Get request message.
     */
    ApplyUpdateReq(
        const std::string & updateDir,
        const std::string & updateFilename
        );

    virtual ~ApplyUpdateReq() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_SW_UPDATE_REQ; };
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
