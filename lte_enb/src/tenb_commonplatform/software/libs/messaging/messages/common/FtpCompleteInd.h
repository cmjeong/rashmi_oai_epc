///////////////////////////////////////////////////////////////////////////////
//
// FtpCompleteInd.h
//
// Send from OAM to indicate complete of an Ftp.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __FtpCompleteInd_h_
#define __FtpCompleteInd_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>
#include <system/TimeWrap.h>

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class FtpCompleteInd : public threeway::Serialisable
{
public:
    static const unsigned short MaxFtpComleteIndStringLength = 120;

    /**
     * Default constructor.  For messaging internal use only.
     */
    FtpCompleteInd() :
        m_ftpRequestIdentity(0),
        m_ftpConfirmIdentity(0),
        m_succeeded(false),
        m_startTime(0),
        m_stopTime(0),
        m_failureString("")
        {
        };

    /**
     * Construct a KPI configure request message.
     */
   FtpCompleteInd(
        u32 ftpRequestIdentity,
        u32 ftpConfirmIdentity,
        bool succeeded,
        const threeway::TimeWrap & startTime,
        const threeway::TimeWrap & stopTime,
        const std::string & failureString );

    virtual ~FtpCompleteInd() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_FTP_COMPLETE_IND; };
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);
    virtual std::string ToString() const;

    /**
     * Getters.
     */
    u32 GetFtpRequestIdentity() const { return m_ftpRequestIdentity; }
    u32 GetFtpConfirmIdentity() const { return m_ftpConfirmIdentity; }
    const bool & GetSucceeded() const { return m_succeeded; }
    const threeway::TimeWrap & GetStartTime() const { return m_startTime; }
    const threeway::TimeWrap & GetStopTime() const { return m_stopTime; }
    const std::string & GetFailureString() const { return m_failureString; }

private:

    u32 m_ftpRequestIdentity;
    u32 m_ftpConfirmIdentity;
    bool m_succeeded;
    threeway::TimeWrap m_startTime;
    threeway::TimeWrap m_stopTime;
    std::string m_failureString;
};

#endif
