///////////////////////////////////////////////////////////////////////////////
//
// CliExecuteCmdProgressInd.h
//
// Progress indication for CLI commands.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CliExecuteCmdProgressInd_h_
#define __CliExecuteCmdProgressInd_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <system/Serialisable.h>
#include <system/SerialisationIds.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class CliExecuteCmdProgressInd : public threeway::Serialisable
{
public:
    /**
     * Construction / destruction.
     *
     * \param progressInfo Info string or NULL to just present generic progress (e.g. dots) to user.
     */
    CliExecuteCmdProgressInd(const char * progressInfo);
    CliExecuteCmdProgressInd() {};
    virtual ~CliExecuteCmdProgressInd() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_CLI_EXECUTE_CMD_PROGRESS_IND; };
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    /**
     * Accessors.
     */
    const char * GetProgressInfo() const { return (m_progressInfo.size() > 0 ? m_progressInfo.c_str() : NULL); };

    /**
     * Convert to string for debug.
     */
    virtual string ToString() const;

private:
    string m_progressInfo;
};

#endif
