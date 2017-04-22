///////////////////////////////////////////////////////////////////////////////
//
// KpiReadReq.cpp
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

#include "KpiReadReq.h"

using namespace std;
using namespace threeway;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

KpiReadReq::KpiReadReq() :
    m_kpiMeasurementSet(0),
    m_kpiReadMode(READ_KPIS),
    m_isCollectionReqPending(false),
    m_periodicUploadIntervalInSecs(0)
{
    ENTER();
    m_kpiGroupIdList.clear();
    EXIT();
}

KpiReadReq::KpiReadReq(set<KpiGroupId> kpiGroupIdList, u8 kpiMeasurementSet, KpiReadMode readMode, bool isCollectionReqPending, u32 uploadIntervalinSecs) :
    m_kpiGroupIdList(kpiGroupIdList),
    m_kpiMeasurementSet(kpiMeasurementSet),
    m_kpiReadMode(readMode),
    m_isCollectionReqPending(isCollectionReqPending),
    m_periodicUploadIntervalInSecs(uploadIntervalinSecs)
{
    ENTER();
    EXIT();
}

s32 KpiReadReq::Serialise(u8* data, u32 dataMaxBytes) const
{
    ENTER();

    // Preconditions.
    RSYS_ASSERT(dataMaxBytes >= 8); // measurement set + read mode + numentries + atleast one GroupId

    // Serialise all the members.
    u8* serialisedData = data;

    SerialiseIt(m_periodicUploadIntervalInSecs, serialisedData);
    SerialiseIt(m_isCollectionReqPending, serialisedData);
    SerialiseIt(m_kpiMeasurementSet, serialisedData);
    SerialiseIt((u8)m_kpiReadMode, serialisedData);
    SerialiseItU32Set(m_kpiGroupIdList, serialisedData, dataMaxBytes - (serialisedData - data)); 

    RETURN(serialisedData - data);
}

bool KpiReadReq::DeSerialise(const u8* data, u32 dataLen)
{
    ENTER();

    // Preconditions.
    RSYS_ASSERT(dataLen >= 8); // measurement set + read mode + numentries + atleast one GroupId

    u8 value8;

    DeSerialiseIt(m_periodicUploadIntervalInSecs, data);

    DeSerialiseIt(m_isCollectionReqPending, data);

    DeSerialiseIt(m_kpiMeasurementSet, data);

    DeSerialiseIt(value8, data);
    m_kpiReadMode = (KpiReadMode)value8;

    DeSerialiseItU32Set(m_kpiGroupIdList, data, MAX_KPI_GROUPS);

    RETURN(true);
}

std::string KpiReadReq::ToString() const
{
    ENTER();

    ostringstream stream;

    stream << "set=" << (u32)m_kpiMeasurementSet
           << ", readMode=" << (m_kpiReadMode == READ_KPIS ? "Read KPIs without reset" : "Read KPIs with reset");

    set<KpiGroupId>::const_iterator iter = m_kpiGroupIdList.begin();
    while(iter != m_kpiGroupIdList.end())
    {
       const char * desc = KpiGroup::GetKpiGroupDescription(*iter);
       stream << (desc != NULL ? desc : "") << "(" << (u32)(*iter) << ") ";
       ++iter;
    }

    RETURN(stream.str());
}
