
///////////////////////////////////////////////////////////////////////////////
//
// MfManager.cpp
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
#include <messaging/messages/common/MfSetAdminStateReq.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MfManager.h"

using namespace std;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

void MfManager::RegisterMf(ManagedFing mf, MessagingEntity mfEntity)
{
    if(m_mfs.find(mf) == m_mfs.end())
    {
        TRACE("Registering new MF", ManagedFingToString(mf));
    }
    else
    {
        // Already registered, just validate is same messaging entity.
        RSYS_ASSERT_PRINTF(m_mfs.at(mf).m_messagingEntity == mfEntity, "%s %s", ManagedFingToString(mf), MessagingEntityToString(mfEntity));
        return;
    }

    ManagedFingDescriptor mfDesc = { mfEntity, ManagedObject::OP_STATE_DISABLED, ManagedObject::ADMIN_STATE_LOCKED, false, "" };
    m_mfs[mf] = mfDesc;
}

void MfManager::UpdateMfOpState(ManagedFing mf,
                                threeway::ManagedObject::OpState opState,
                                const string& additionalInfo)
{
    RSYS_ASSERT_PRINTF(m_mfs.find(mf) != m_mfs.end(), "%s", ManagedFingToString(mf));

    TRACE_PRINTF("Updating MF op state: %s %s", ManagedFingToString(mf), ManagedObject::OpStateToString(opState));

    // Intentionally don't set admin state, may have been set by previous call to the other UpdateMfOpState().
    m_mfs.at(mf).m_opState = opState;
    m_mfs.at(mf).m_additionalInfo = additionalInfo;
}

void MfManager::UpdateMfOpState(ManagedFing mf,
                                threeway::ManagedObject::OpState opState,
                                threeway::ManagedObject::AdminState adminState,
                                const string& additionalInfo)
{
    RSYS_ASSERT_PRINTF(m_mfs.find(mf) != m_mfs.end(), "%s", ManagedFingToString(mf));

    TRACE_PRINTF("Updating MF op state: %s %s %s", ManagedFingToString(mf), ManagedObject::OpStateToString(opState), ManagedObject::AdminStateToString(adminState));

    m_mfs.at(mf).m_opState = opState;
    m_mfs.at(mf).m_adminState = adminState;
    m_mfs.at(mf).m_adminStateValid = true;
    m_mfs.at(mf).m_additionalInfo = additionalInfo;
}

bool MfManager::SetMfAdminState(ManagedFing mf, threeway::ManagedObject::AdminState adminState) const
{
    if(m_mfs.find(mf) == m_mfs.end())
    {
        // Could assert but this may be called from CLI so that would be a bit brutal.
        TRACE_PRINTF_LEV(TRACE_WARNING, "Can't set admin state of MF as not registered: %s %s", ManagedFingToString(mf), ManagedObject::AdminStateToString(adminState));
        return(false);
    }

    TRACE_PRINTF("Setting admin state of MF: %s %s", ManagedFingToString(mf), ManagedObject::AdminStateToString(adminState));

    MfSetAdminStateReq setAdminStateReq(mf, adminState);
    m_sendMessageInterface.SendMessage(setAdminStateReq, m_mfs.at(mf).m_messagingEntity, ENTITY_OAM);

    return(true);
}

std::string MfManager::ToString() const
{
    ostringstream stream;

    for(RegisteredManagedFings::const_iterator iter = m_mfs.begin();
        iter != m_mfs.end();
        ++iter)
    {
        stream << ManagedFingToString(iter->first)
               << ": "
               << ManagedObject::OpStateToString(iter->second.m_opState);

        if(iter->second.m_adminStateValid)
        {
            stream << " " << ManagedObject::OpStateToString(iter->second.m_opState);
        }

        stream << " \"" << iter->second.m_additionalInfo << "\""
               << " ("
               << MessagingEntityToString(iter->second.m_messagingEntity)
               << ")"
               << endl;
    }

    return stream.str();
}
