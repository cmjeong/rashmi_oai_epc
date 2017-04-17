///////////////////////////////////////////////////////////////////////////////
//
// MfSetAdminStateCnf.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Trace.h>
#include <system/SerialisationUtils.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MfSetAdminStateCnf.h"

using namespace std;
using namespace boost;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

MfSetAdminStateCnf::MfSetAdminStateCnf() :
    m_managedFing(MF_INVALID)
{
    ENTER();
    EXIT();
}

MfSetAdminStateCnf::MfSetAdminStateCnf(ManagedFing managedFing) :
    m_managedFing(managedFing)
{
    ENTER();
    EXIT();
}

s32 MfSetAdminStateCnf::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    RSYS_ASSERT(dataMaxBytes >= 128);

    const u8* const dataStart = data;

    SerialiseIt((u32)m_managedFing, data);

    RETURN(data - dataStart);
}

bool MfSetAdminStateCnf::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();
    RSYS_ASSERT(dataLen >= 4);

    u32 managedFingU32;
    DeSerialiseIt(managedFingU32, data);
    m_managedFing = (ManagedFing)managedFingU32;

    RETURN(true);
}

std::string MfSetAdminStateCnf::ToString() const
{
    ENTER();

    ostringstream stream;

    stream << "fing=" << ManagedFingToString(m_managedFing);

    RETURN(stream.str());
}
