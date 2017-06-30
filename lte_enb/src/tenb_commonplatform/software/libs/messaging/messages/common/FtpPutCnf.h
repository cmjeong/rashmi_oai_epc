///////////////////////////////////////////////////////////////////////////////
//
// FtpPutCnf.h
//
// Send from OAM to confirm an FTP Get.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __FtpPutCnf_h_
#define __FtpPutCnf_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>
#include <system/TimeWrap.h>

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class FtpPutCnf : public threeway::Serialisable
{
public:
    static const unsigned short MaxFtpPutCnfStringLength = 80;

    /**
     * Default constructor.  For messaging internal use only.
     */
    FtpPutCnf() :
        m_succeeded(false)
        {};

    /**
     * Construct a FTP Put confirm message.
     */
    FtpPutCnf(
        bool succeeded,
        const threeway::TimeWrap & startTime,
        const threeway::TimeWrap & stopTime,
        const std::string & failureString );

    virtual ~FtpPutCnf() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_FTP_PUT_CNF; };
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);
    virtual std::string ToString() const;

    /**
     * Getters.
     */
    const bool & GetSucceeded() const { return m_succeeded; }
    const threeway::TimeWrap & GetStartTime() const { return m_startTime; }
    const threeway::TimeWrap & GetStopTime() const { return m_stopTime; }
    const std::string & GetFailureString() const { return m_failureString; }

private:

    bool m_succeeded;
    threeway::TimeWrap m_startTime;
    threeway::TimeWrap m_stopTime;
    std::string m_failureString;
};

#endif
