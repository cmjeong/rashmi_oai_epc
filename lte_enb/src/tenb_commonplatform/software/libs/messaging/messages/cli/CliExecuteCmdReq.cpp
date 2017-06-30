///////////////////////////////////////////////////////////////////////////////
//
// CliExecuteCmdReq.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <system/SerialisationIds.h>
#include <system/Trace.h>
#include <system/NumberConversions.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "CliExecuteCmdReq.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CliExecuteCmdReq::CliExecuteCmdReq(const char * cmd, const char * args) :
    m_cmd(cmd),
    m_args(args)
{
    ENTER();
    EXIT();
}

CliExecuteCmdReq::CliExecuteCmdReq()
{
    ENTER();
    EXIT();
}

CliExecuteCmdReq::~CliExecuteCmdReq()
{
    ENTER();
    EXIT();
}

s32 CliExecuteCmdReq::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    u16 cmdLen = m_cmd.size();
    u16 argsLen = m_args.size();
    u32 lenRequired = 2 /* cmd len */ + cmdLen + 2 /* args len */ + argsLen;
    if(dataMaxBytes >= lenRequired)
    {
        U16ToBigEndianByteArray(cmdLen, data);
        data += 2;

        memcpy(data, m_cmd.c_str(), cmdLen);
        data += cmdLen;

        U16ToBigEndianByteArray(argsLen, data);
        data += 2;

        memcpy(data, m_args.c_str(), argsLen);
        data += argsLen;

        RETURN((s32)lenRequired);
    }

    RETURN(-1);
}

bool CliExecuteCmdReq::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    if(dataLen < 4)
    {
        // Not long enough, needs to contain at least two 2-byte
        // length fields.
        RETURN(false);
    }

    // Get length of command string.
    u16 cmdLen = BigEndianByteArrayToU16(data);
    data += 2;

    // Get the command string into our string object.
    char cmd[cmdLen+1];
    cmd[cmdLen] = '\0';
    memcpy(cmd, data, cmdLen);
    data += cmdLen;
    m_cmd = cmd;

    // Get length of arguments string.
    u16 argsLen = BigEndianByteArrayToU16(data);
    data += 2;

    // Get the arguments string into our string object.
    char args[argsLen+1];
    args[argsLen] = '\0';
    memcpy(args, data, argsLen);
    data += argsLen;
    m_args = args;

    RETURN(true);
}

string CliExecuteCmdReq::ToString() const
{
    ENTER();

    ostringstream stream;

    stream << "CliExecuteCmdReq: cmd=" << m_cmd << ", args=" << m_args;

    RETURN(stream.str());
}
