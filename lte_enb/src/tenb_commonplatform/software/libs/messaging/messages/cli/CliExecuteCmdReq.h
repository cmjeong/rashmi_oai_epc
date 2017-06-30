///////////////////////////////////////////////////////////////////////////////
//
// CliExecuteCmdReq.h
//
// Message for requesting the execution of a CLI command that an application
// supports.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CliExecuteCmdReq_h_
#define __CliExecuteCmdReq_h_

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

class CliExecuteCmdReq : public threeway::Serialisable
{
public:
    /**
     * Construction / destruction.
     */
    CliExecuteCmdReq(const char * cmd, const char * args);
    CliExecuteCmdReq();
    virtual ~CliExecuteCmdReq();

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_CLI_EXECUTE_CMD_REQ; };
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    /**
     * Accessors.
     */
    string GetCliCmd() const { return m_cmd; };
    string GetCliCmdArgs() const { return m_args; };
    
    /**
     * Convert to string for debug.
     */
    virtual string ToString() const;
    
private:
    string m_cmd;
    string m_args;
};

#endif
