///////////////////////////////////////////////////////////////////////////////
//
// CliExecuteCmdInd.cpp
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

#include "CliExecuteCmdInd.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CliExecuteCmdInd::CliExecuteCmdInd(const char * result) :
    m_result(result)
{
    ENTER();
    EXIT();
}

CliExecuteCmdInd::CliExecuteCmdInd(const char * result, size_t length) :
    m_result(result, length)
{
    ENTER();
    EXIT();
}

CliExecuteCmdInd::CliExecuteCmdInd()
{
    ENTER();
    EXIT();
}

CliExecuteCmdInd::~CliExecuteCmdInd()
{
    ENTER();
    EXIT();
}

s32 CliExecuteCmdInd::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    u16 resultLen = m_result.size();
    u32 lenRequired = 4 /* result len */ + resultLen;
    if(dataMaxBytes >= lenRequired)
    {
        U16ToBigEndianByteArray(resultLen, data);
        data += 2;

        memcpy(data, m_result.c_str(), resultLen);
        data += resultLen;

        RETURN((s32)lenRequired);
    }

    RETURN(-1);
}

bool CliExecuteCmdInd::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();
    bool ok = false ;

    if(dataLen >= 4) // Cope with an empty result string plus a 2-byte length field and a 2-byte status field.
    {
    	// Get length of result string.
    	u16 resultLen = BigEndianByteArrayToU16(data);
    	data += 2;
    	if (dataLen >= (u32)(resultLen + 4))
    	{
    		// Get the result string into our string object.
    		char result[resultLen+1];
    		result[resultLen] = '\0';
    		memcpy(result, data, resultLen);
    		data += resultLen;
    		m_result = result;
    		ok = true ;
    	}
    }
    RETURN(ok);
}

string CliExecuteCmdInd::ToString() const
{
    ENTER();

    ostringstream stream;

    stream << "CliExecuteCmdInd: result=" << m_result;

    RETURN(stream.str());
}
