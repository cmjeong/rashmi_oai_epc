///////////////////////////////////////////////////////////////////////////////
//
// CliExecuteCmdCnf.cpp
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
#include <system/Trace.h>
#include <system/NumberConversions.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "CliExecuteCmdCnf.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CliExecuteCmdCnf::CliExecuteCmdCnf(const char *nameSpace, const char *cmd, const char * result, const s16 status, const bool unsolicited) :
	m_namespace(nameSpace),
	m_command(cmd),
    m_result(result),
    m_status(status),
    m_unsolicited(unsolicited)
{
    ENTER();
    EXIT();
}

CliExecuteCmdCnf::CliExecuteCmdCnf() :
    m_status(0),
    m_unsolicited(false)
{
    ENTER();
    EXIT();
}

CliExecuteCmdCnf::~CliExecuteCmdCnf()
{
    ENTER();
    EXIT();
}

s32 CliExecuteCmdCnf::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    u16 namespaceLen = m_namespace.size() ;
    u16 commandLen = m_command.size();
    u16 resultLen = m_result.size();
    u32 lenRequired = 2 + namespaceLen + /* m_namespace + length */
                      2 + commandLen + 	 /* m_command + length */
    	              2 + resultLen +    /* m_result + length */
    	              2 + 				 /* m_status */
    	              2 /* m_unsolicited */ ;

    if(dataMaxBytes >= lenRequired)
    {
    	// Namespace
        U16ToBigEndianByteArray(namespaceLen, data);
        data += 2;
        memcpy(data, m_namespace.c_str(), namespaceLen);
        data += namespaceLen;

        // Command
        U16ToBigEndianByteArray(commandLen, data);
        data += 2;
        memcpy(data, m_command.c_str(), commandLen);
        data += commandLen;

        // Result
        U16ToBigEndianByteArray(resultLen, data);
        data += 2;
        memcpy(data, m_result.c_str(), resultLen);
        data += resultLen;

        S16ToBigEndianByteArray(m_status, data) ;
        data += 2;
        U16ToBigEndianByteArray(m_unsolicited, data);

        RETURN((s32)lenRequired);
    }

    RETURN(-1);
}

bool CliExecuteCmdCnf::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();
    bool ok = false ;

    if(dataLen >= 10) // Cope with an empty namespace, command, and result strings with a 2-byte length field for each and a 2-byte status field.
    {
    	int stringLength = 0 ;

    	// Get length of nameSpace string.
    	u16 namespaceLen = BigEndianByteArrayToU16(data);
    	data += 2;
		char nameSpace[namespaceLen+1];
		nameSpace[namespaceLen] = '\0';
		memcpy(nameSpace, data, namespaceLen);
		data += namespaceLen;
		stringLength += namespaceLen ;

    	// Get length of command string.
    	u16 commandLen = BigEndianByteArrayToU16(data);
    	data += 2;
		char command[commandLen+1];
		command[commandLen] = '\0';
		memcpy(command, data, commandLen);
		data += commandLen;
		stringLength += commandLen ;

    	// Get length of result string.
    	u16 resultLen = BigEndianByteArrayToU16(data);
    	data += 2;
		char result[resultLen+1];
		result[resultLen] = '\0';
		memcpy(result, data, resultLen);
		data += resultLen;
		stringLength += resultLen ;

    	if (dataLen >= (u32)(stringLength + 10))
    	{
    		m_status = BigEndianByteArrayToS16(data) ;
    		data+=2;
    		m_unsolicited = BigEndianByteArrayToS16(data) ;
    		m_result = result;
    		m_namespace = nameSpace ;
    		m_command = command ;
    		ok = true ;
    	}
    }
    RETURN(ok);
}

string CliExecuteCmdCnf::ToString() const
{
    ENTER();

    ostringstream stream;

    stream << "CliExecuteCmdCnf: result=" << m_result;

    RETURN(stream.str());
}
