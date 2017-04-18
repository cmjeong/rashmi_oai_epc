///////////////////////////////////////////////////////////////////////////////
//
// MfOpStateInformInd
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
#include <system/NumberConversions.h>
#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "MfOpStateInformInd.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

MfOpStateInformInd::MfOpStateInformInd() :
    m_managedFing(MF_INVALID),
    m_opState(ManagedObject::OP_STATE_DISABLED),
    m_adminState(ManagedObject::ADMIN_STATE_LOCKED),
    m_adminStatePresent(false),
    m_additionalInfoValue(0)
{
}

MfOpStateInformInd::MfOpStateInformInd(ManagedFing managedFing,
                                       ManagedObject::OpState opState,
                                       u32 additionalInfoValue,
                                       const char * additionalInfoString) :
    m_managedFing(managedFing),
    m_opState(opState),
    m_adminState(ManagedObject::ADMIN_STATE_LOCKED),
    m_adminStatePresent(false),
    m_additionalInfoValue(additionalInfoValue)
{
    SetAdditionalInfoString(additionalInfoString);
}

MfOpStateInformInd::MfOpStateInformInd(ManagedFing managedFing,
                                       ManagedObject::OpState opState,
                                       ManagedObject::AdminState adminState,
                                       u32 additionalInfoValue,
                                       const char * additionalInfoString) :
    m_managedFing(managedFing),
    m_opState(opState),
    m_adminState(adminState),
    m_adminStatePresent(true),
    m_additionalInfoValue(additionalInfoValue)
{
    SetAdditionalInfoString(additionalInfoString);
}

MfOpStateInformInd::~MfOpStateInformInd()
{
}

s32 MfOpStateInformInd::Serialise(u8* data, u32 dataMaxBytes) const
{
    RSYS_ASSERT(dataMaxBytes >= 128);

    const u8* const dataStart = data;

    SerialiseIt((u32)m_managedFing, data);
    SerialiseIt((u32)m_opState, data);
    SerialiseIt(m_adminStatePresent, data);
    SerialiseIt((u32)m_adminState, data);
    SerialiseIt((u32)m_additionalInfoValue, data);
    SerialiseIt(m_additionalInfoString, data);

    return (data - dataStart);
}

bool MfOpStateInformInd::DeSerialise(const u8* data, u32 dataLen)
{
    RSYS_ASSERT(dataLen >= 4);

    u32 managedFingU32;
    DeSerialiseIt(managedFingU32, data);
    m_managedFing = (ManagedFing)managedFingU32;

    u32 opStateU32;
    DeSerialiseIt(opStateU32, data);
    m_opState = (ManagedObject::OpState)opStateU32;

    DeSerialiseIt(m_adminStatePresent, data);

    u32 adminStateU32;
    DeSerialiseIt(adminStateU32, data);
    m_adminState = (ManagedObject::AdminState)adminStateU32;

    DeSerialiseIt(m_additionalInfoValue, data);
    DeSerialiseIt(m_additionalInfoString, data, ADDITIONAL_INFO_MAX_LEN);

    return (true);
}

ManagedObject::AdminState MfOpStateInformInd::GetAdminState() const
{
    RSYS_ASSERT_PRINTF(m_adminStatePresent, "Admin state not present: %s", ToString().c_str());

    return m_adminState;
}

string MfOpStateInformInd::ToString() const
{
    ostringstream stream;

    stream << "fing=" << ManagedFingToString(m_managedFing);
    stream << ", opState=" << ManagedObject::OpStateToString(m_opState);
    if(m_adminStatePresent)
    {
        stream << ", adminState=" << ManagedObject::AdminStateToString(m_adminState);
    }
    stream << ", additionalInfo=" << m_additionalInfoValue << " \"" << m_additionalInfoString << "\"";

    return (stream.str());
}

void MfOpStateInformInd::SetAdditionalInfoString(const char * additionalInfoString)
{
    if(additionalInfoString != NULL)
    {
        m_additionalInfoString = additionalInfoString;

        if(m_additionalInfoString.length() > ADDITIONAL_INFO_MAX_LEN)
        {
            // Truncate the additional info.
            m_additionalInfoString.resize(ADDITIONAL_INFO_MAX_LEN);
        }
    }
}
