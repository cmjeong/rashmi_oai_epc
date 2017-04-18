///////////////////////////////////////////////////////////////////////////////
//
// KpiRegisterReq.cpp
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

#include "KpiRegisterReq.h"

using namespace std;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

KpiRegisterReq::KpiRegisterReq(set<KpiGroupId> kpiGroupIds) :
    m_kpiGroupIds(kpiGroupIds)
{
    ENTER();
    EXIT();
}

s32 KpiRegisterReq::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    // Serialise all the members.
    u8* serialisedData = data;

    SerialiseItU32Set(m_kpiGroupIds, serialisedData, dataMaxBytes);

    RETURN(serialisedData - data);
}

bool KpiRegisterReq::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    DeSerialiseItU32Set(m_kpiGroupIds, data, (u16)256 /* fairly arbitrary limit check - enum has gaps so can't easily do this programmatically */);

    RETURN(true);
}

std::string KpiRegisterReq::ToString() const
{
    ENTER();

    ostringstream stream;

    stream << "Num KPI groups = " << m_kpiGroupIds.size();

    RETURN(stream.str());
}
