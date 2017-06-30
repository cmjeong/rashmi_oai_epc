///////////////////////////////////////////////////////////////////////////////
//
// RemCnf.cpp
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
#include <system/SerialisationUtils.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "RemCnf.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

RemCnf::RemCnf() :
    m_remSucceeded(false)
{
    ENTER();
    EXIT();
}

RemCnf::RemCnf(bool remSucceeded, RemResults& remResults) :
    m_remSucceeded(remSucceeded), m_remResults(remResults)
{
    ENTER();
    EXIT();
}

RemCnf::~RemCnf()
{
    ENTER();
    EXIT();
}

s32 RemCnf::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    RSYS_ASSERT(dataMaxBytes >= sizeof(RemResults) + 1);

    const u8 * const dataStart = data;
    m_remResults.Serialise(data);
	SerialiseIt(m_remSucceeded, data);

    RETURN(data - dataStart);
}

bool RemCnf::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();
    m_remResults.DeSerialise(data);
	DeSerialiseIt(m_remSucceeded, data);
    RETURN(true);
}

string RemCnf::ToString() const
{
    ENTER();

    ostringstream stream;

    stream << "RemCnf:\n" << m_remResults.ToString() << " REM Succeeded=" << (m_remSucceeded ? "true" : "false") << "\n";

    RETURN(stream.str());
}
