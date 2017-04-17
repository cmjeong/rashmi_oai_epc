///////////////////////////////////////////////////////////////////////////////
//
// CliExecuteCmdInd.h
//
// Message containing a fragment of the response to a CLI command.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CliExecuteCmdInd_h_
#define __CliExecuteCmdInd_h_

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

class CliExecuteCmdInd : public threeway::Serialisable
{
public:
    /**
     * Construction / destruction.
     */
    CliExecuteCmdInd(const char * result);
    CliExecuteCmdInd(const char * result, size_t length);
    CliExecuteCmdInd();
    virtual ~CliExecuteCmdInd();

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_CLI_EXECUTE_CMD_IND; };
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    /**
     * Accessors.
     */
    const char * GetResult() const { return m_result.c_str(); };

    /**
     * Convert to string for debug.
     */
    virtual string ToString() const;

private:
    string m_result;
};

#endif
