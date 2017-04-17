///////////////////////////////////////////////////////////////////////////////
//
// KpiConfigureReq.cpp
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

#include "KpiConfigureReq.h"

using namespace std;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

KpiConfigureReq::KpiConfigureReq() :
    m_measurementIntervalSecs(0), m_perodicUploadIntervalSecs(0), m_perodicUploadPhaseAllignInMin(0)
{
    ENTER();

    EXIT();
}

KpiConfigureReq::KpiConfigureReq(set<KpiGroupId> kpiGroupIds, u32 measurementIntervalSecs, u32 perodicUploadIntervalSecs, u32 perodicUploadPhaseAllignInMin) :
    m_kpiGroupIds(kpiGroupIds), m_measurementIntervalSecs(measurementIntervalSecs), m_perodicUploadPhaseAllignInMin(perodicUploadPhaseAllignInMin), 
    m_perodicUploadIntervalSecs(perodicUploadIntervalSecs)
{
    ENTER();

    // Preconditions.  No point having empty set of ids...
    RSYS_ASSERT(kpiGroupIds.size() > 0);

    EXIT();
}

s32 KpiConfigureReq::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    // Preconditions.
    RSYS_ASSERT(dataMaxBytes >= 10); // measurementIntervalSecs +perodicUploadIntervalSecs+ num group ids + at least one group id

    // Serialise all the members.
    u8* serialisedData = data;

    SerialiseIt(m_measurementIntervalSecs, serialisedData);
    SerialiseIt(m_perodicUploadIntervalSecs, serialisedData);
    SerialiseIt(m_perodicUploadPhaseAllignInMin, serialisedData);    
    SerialiseItU32Set(m_kpiGroupIds, serialisedData, dataMaxBytes - (serialisedData - data));

    RETURN(serialisedData - data);
}

bool KpiConfigureReq::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    // Preconditions.
    RSYS_ASSERT(dataLen >= 10); // measurementIntervalSecs + num group ids + at least one group id

    DeSerialiseIt(m_measurementIntervalSecs, data);
    DeSerialiseIt(m_perodicUploadIntervalSecs, data);
    DeSerialiseIt(m_perodicUploadPhaseAllignInMin, data);    
    DeSerialiseItU32Set(m_kpiGroupIds, data, MAX_KPI_GROUPS);

    RETURN(true);
}

std::string KpiConfigureReq::ToString() const
{
    ENTER();

    ostringstream stream;

    stream << "CollectionPeriod=" << m_measurementIntervalSecs << "PerodicUploadInterval=" << m_perodicUploadIntervalSecs \
           << "m_perodicUploadPhaseAllignInMin=" << m_perodicUploadPhaseAllignInMin << "kpiGroupIds=";

    set<KpiGroupId>::const_iterator iter = m_kpiGroupIds.begin();
    while(iter != m_kpiGroupIds.end())
    {
        const char * desc = KpiGroup::GetKpiGroupDescription(*iter);
        stream << (desc != NULL ? desc : "") << "(" << (u32)(*iter) << ") ";
        ++iter;
    }

    RETURN(stream.str());
}
