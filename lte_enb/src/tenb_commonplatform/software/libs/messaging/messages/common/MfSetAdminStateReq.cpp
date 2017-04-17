///////////////////////////////////////////////////////////////////////////////
//
// MfSetAdminStateReq.cpp
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

#include "MfSetAdminStateReq.h"

using namespace std;
using namespace boost;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

MfSetAdminStateReq::MfSetAdminStateReq() :
    m_managedFing(MF_INVALID),
    m_adminState(ManagedObject::ADMIN_STATE_UNLOCKED)
{
    ENTER();
    EXIT();
}

MfSetAdminStateReq::MfSetAdminStateReq(ManagedFing managedFing, threeway::ManagedObject::AdminState adminState) :
    m_managedFing(managedFing),
    m_adminState(adminState)
{
    ENTER();
    EXIT();
}

s32 MfSetAdminStateReq::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    RSYS_ASSERT(dataMaxBytes >= 128);

    const u8* const dataStart = data;

    SerialiseIt((u32)m_managedFing, data);
    SerialiseIt((u32)m_adminState, data);

    RETURN(data - dataStart);
}

bool MfSetAdminStateReq::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();
    RSYS_ASSERT(dataLen >= 8);

    u32 managedFingU32;
    DeSerialiseIt(managedFingU32, data);
    m_managedFing = (ManagedFing)managedFingU32;

    u32 adminStateU32;
    DeSerialiseIt(adminStateU32, data);
    m_adminState = (ManagedObject::AdminState)adminStateU32;

    RETURN(true);
}

std::string MfSetAdminStateReq::ToString() const
{
    ENTER();

    ostringstream stream;

    stream << "fing=" << ManagedFingToString(m_managedFing);
    stream << ", adminState=" << ManagedObject::AdminStateToString(m_adminState);

    RETURN(stream.str());
}
