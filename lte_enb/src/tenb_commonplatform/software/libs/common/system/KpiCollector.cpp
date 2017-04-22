///////////////////////////////////////////////////////////////////////////////
//
// KpiCollector.cpp
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

#include "KpiCollector.h"

using namespace threeway;
using namespace boost;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

KpiCollector::KpiCollector()
{
    ENTER();
    EXIT();
}

KpiCollector::~KpiCollector()
{
    ENTER();
    EXIT();
}

/*This funtion calls when KPI value type is integer*/
void KpiCollector::IncKpiByIntVal(KpiId kpiId,u32 cellId, u32 increment)
{
    ENTER();

    KpiGroupId kpiGroupId = FindOrAddGroups(kpiId,cellId);

    RSYS_ASSERT(m_kpiMeasurementSets[kpiGroupId].size() == NUM_MEASUREMENT_SETS);

    // Do the increment.
    for(u8 i = 0; i < NUM_MEASUREMENT_SETS; i++)
    {
        m_kpiMeasurementSets[kpiGroupId].at(i)->IncKpiByIntVal(kpiId,cellId, increment);
    }

    EXIT();
}

/*This function calls when KPI value type is real*/
void KpiCollector::IncKpiByRealVal(KpiId kpiId,u32 cellId, float  increment)
{
    ENTER();

    KpiGroupId kpiGroupId = FindOrAddGroups(kpiId,cellId);

    RSYS_ASSERT(m_kpiMeasurementSets[kpiGroupId].size() == NUM_MEASUREMENT_SETS);

    // Do the increment.
    for(u8 i = 0; i < NUM_MEASUREMENT_SETS; i++)
    {
        m_kpiMeasurementSets[kpiGroupId].at(i)->IncKpiByRealVal(kpiId,cellId, increment);
    }

    EXIT();
}

bool KpiCollector::GetKpiGroup(KpiGroupId kpiGroupId, u8 kpiMeasurementSet, bool resetKpis, KpiGroup& kpiGroup)
{
    ENTER();

    RSYS_ASSERT(kpiMeasurementSet < NUM_MEASUREMENT_SETS);

    KpiMeasurementSets::iterator iter = m_kpiMeasurementSets.find(kpiGroupId);
    if(iter != m_kpiMeasurementSets.end())
    {
        RSYS_ASSERT(iter->second.size() == NUM_MEASUREMENT_SETS);

        // Touch it...
        iter->second.at(kpiMeasurementSet)->TouchTimestamp();

        // Copy the KPI group to return to caller.
        kpiGroup = *(iter->second.at(kpiMeasurementSet));

        if(resetKpis)
        {
            // Reset the KPIs for this group to 0.
            iter->second.at(kpiMeasurementSet)->ResetKpis();
        }

        RETURN(true);
    }

    RETURN(false);
}

std::string KpiCollector::ToString() const
{
    ENTER();

    ostringstream stream;

    KpiMeasurementSets::const_iterator iter = m_kpiMeasurementSets.begin();
    while(iter != m_kpiMeasurementSets.end())
    {
        RSYS_ASSERT(iter->second.size() == NUM_MEASUREMENT_SETS);
        for(u8 i = 0; i < NUM_MEASUREMENT_SETS; i++)
        {
            RSYS_ASSERT(iter->second.at(i) != NULL);
            stream << "[" << i << "]: " << iter->second.at(i)->ToString() << endl;
        }
    }

    RETURN(stream.str());
}

KpiGroupId KpiCollector::FindOrAddGroups(KpiId kpiId,u32 cellId)
{
    ENTER();

    KpiGroupId kpiGroupId;
    bool kpiGroupFound = KpiGroup::GetKpiGroupId(kpiId, kpiGroupId);
    RSYS_ASSERT_PRINTF(kpiGroupFound, "kpiGroupId=%"PRIu32", kpiId=%"PRIu32, (u32)kpiGroupId, (u32)kpiId);

    if(m_kpiMeasurementSets.find(kpiGroupId) == m_kpiMeasurementSets.end())
    {
        // We haven't used this group before, add it...
        KpiGroups kpiGroups;
        for(u8 i = 0; i < NUM_MEASUREMENT_SETS; i++)
        {
            shared_ptr<KpiGroup> kpiGroup(new KpiGroup(kpiGroupId));
            kpiGroups.push_back(kpiGroup);
        }
        m_kpiMeasurementSets[kpiGroupId] = kpiGroups;
    }

    RETURN(kpiGroupId);
}
