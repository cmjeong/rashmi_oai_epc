///////////////////////////////////////////////////////////////////////////////
//
// InstallUpdateCnf.cpp
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

#include "InstallUpdateCnf.h"

using namespace std;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

InstallUpdateCnf::InstallUpdateCnf() :
            m_succeeded(false),
            m_failureString("")
{
    ENTER();

    EXIT();
}

InstallUpdateCnf::InstallUpdateCnf(
        bool succeeded,
        const std::string & failureString ) :
            m_succeeded(succeeded),
            m_failureString(failureString)
{
    ENTER();

    EXIT();
}

s32 InstallUpdateCnf::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    // Preconditions.
    RSYS_ASSERT(dataMaxBytes >= (1 /* bool */ + 2 /* str len */ + m_failureString.length()) );

    // Serialise all the members.
    u8* serialisedData = data;

    SerialiseIt(m_succeeded, serialisedData);
    SerialiseIt(m_failureString, serialisedData);

    RETURN(serialisedData - data);
}

bool InstallUpdateCnf::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    DeSerialiseIt(m_succeeded, data );
    DeSerialiseIt(m_failureString, data, MaxInstallUpdateCnfStringLength);

    RETURN(true);
}

std::string InstallUpdateCnf::ToString() const
{
    ENTER();

    ostringstream stream;

    stream << "InstallUpdate(cnf) " << (m_succeeded?"[OK]":"[NOK]") << m_failureString;

    RETURN(stream.str());
}
