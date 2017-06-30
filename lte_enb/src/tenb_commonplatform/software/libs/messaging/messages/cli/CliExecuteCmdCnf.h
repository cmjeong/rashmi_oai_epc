///////////////////////////////////////////////////////////////////////////////
//
// CliExecuteCmdCnf.h
//
// Message containing the response to a CLI command.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CliExecuteCmdCnf_h_
#define __CliExecuteCmdCnf_h_

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

class CliExecuteCmdCnf : public threeway::Serialisable
{
public:
    /**
     * Construction / destruction.
     */
    CliExecuteCmdCnf(const char *nameSpace, const char * command, const char * result, const s16 status = 0, const bool unsolicited = false);
    CliExecuteCmdCnf();
    virtual ~CliExecuteCmdCnf();

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_CLI_EXECUTE_CMD_CNF; };
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    /**
     * Accessors.
     */
    const char * GetResult() const { return m_result.c_str(); };
    const char * GetCommand() const { return m_command.c_str(); };
    const char * GetNamespace() const { return m_namespace.c_str(); };
    s16 GetStatus() const {return m_status;};
    bool GetUnsolicited() const {return m_unsolicited;};

    /**
     * Convert to string for debug.
     */
    virtual string ToString() const;

private:
	string m_namespace;
	string m_command ;
    string m_result;
    s16 m_status ;
    bool m_unsolicited ;
};

#endif
