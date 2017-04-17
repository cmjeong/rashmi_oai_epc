///////////////////////////////////////////////////////////////////////////////
//
// ManagedObject.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>

#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ManagedObject.h"

using namespace boost;
using namespace std;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

const char * ManagedObject::AdminStateToString(AdminState adminState)
{
    switch(adminState)
    {
    case ADMIN_STATE_UNLOCKED:
        return "Unlocked";
        break;
    case ADMIN_STATE_LOCKED:
        return "Locked";
        break;
    case ADMIN_STATE_SHUTTING_DOWN:
        return "ShuttingDown";
        break;
    }

    RSYS_ASSERT_FAIL("Invalid value for AdminState %"PRIu32, (u32)adminState);
    return "<invalid>";
}

const char * ManagedObject::OpStateToString(OpState opState)
{
    switch(opState)
    {
    case OP_STATE_ENABLED:
        return "Enabled";
        break;
    case OP_STATE_DISABLED:
        return "Disabled";
        break;
    }

    RSYS_ASSERT_FAIL("Invalid value for OpState %"PRIu32, (u32)opState);
    return "<invalid>";
}

ManagedObject::ManagedObject() :
    m_adminState(ADMIN_STATE_LOCKED)
{
    ENTER();
    EXIT();
}

ManagedObject::~ManagedObject()
{
    ENTER();
    EXIT();
}

void ManagedObject::SetAdminState(AdminState adminState)
{
    ENTER();

    m_adminState = adminState;

    EXIT();
}

ManagedObject::AdminState ManagedObject::GetAdminState() const
{
    ENTER();

    RETURN(m_adminState);
}

const char * ManagedObject::GetAdminStateString() const
{
    ENTER();

    RETURN(AdminStateToString(m_adminState));
}

void ManagedObject::SetParentMO(shared_ptr<ManagedObject> parent)
{
    ENTER();

    m_parent = parent;

    EXIT();
}

shared_ptr<ManagedObject> ManagedObject::GetParentMO() const
{
    ENTER();

    RETURN(m_parent);
}

ManagedObject::OpState ManagedObject::GetOpState() const
{
    ENTER();

    // Default implementation is that if MO is admin state Unlocked or Shutting Down then MO is 'enabled'.
    RETURN(m_adminState != ADMIN_STATE_LOCKED ? OP_STATE_ENABLED : OP_STATE_DISABLED);
}

string ManagedObject::GetOpStateString() const
{
    ENTER();

    RETURN(OpStateToString(GetOpState()));
}

string ManagedObject::ToString() const
{
    ENTER();

    ostringstream stream;

    stream << GetAdminStateString() << " [" << GetOpStateString() << "]";

    RETURN(stream.str());
}

}
