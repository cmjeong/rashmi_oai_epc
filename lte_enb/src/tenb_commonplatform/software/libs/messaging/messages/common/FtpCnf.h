///////////////////////////////////////////////////////////////////////////////
//
// FtpCnf.h
//
// Send from OAM to confirm an FTP Get.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __FtpCnf_h_
#define __FtpCnf_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class FtpCnf : public threeway::Serialisable
{
public:
    /**
     * Default constructor.  For messaging internal use only.
     */
    FtpCnf() :
        m_ftpRequestIdentity(0),
        m_ftpConfirmIdentity(0)
    {
    };

    /**
     * Construct a KPI configure request message.
     */
    FtpCnf(
            u32 ftpRequestIdentity,
            u32 ftpConfirmIdentity );
    virtual ~FtpCnf() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_FTP_CNF; };
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);
    virtual std::string ToString() const;

    /**
     * Getters.
     */
    u32 GetFtpRequestIdentity() const { return m_ftpRequestIdentity; }
    u32 GetFtpConfirmIdentity() const { return m_ftpConfirmIdentity; }

private:

    u32 m_ftpRequestIdentity;
    u32 m_ftpConfirmIdentity;
};

#endif
