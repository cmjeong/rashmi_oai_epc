///////////////////////////////////////////////////////////////////////////////
//
// KpiAggregator.cpp
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

#include "KpiAggregator.h"
#include "KpiGroup.h"

using namespace std;
using namespace threeway;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

KpiAggregator::KpiAggregator(KpiLogFileMgr& kpiGroupList) :
    m_kpiGroupList(kpiGroupList),
    m_haveAggregated(false),
    m_numKpiGroupsAggregated(0),
    m_numKpiGroupsIgnored(0)
{
    ENTER();

    EXIT();
}

KpiAggregator::~KpiAggregator()
{
    ENTER();

    EXIT();
}

u32 KpiAggregator::AggregateKpis(const TimeWrap& startDateTime, const TimeWrap& endDateTime)
{
    ENTER();

    TRACE_PRINTF("Aggregating KPIs between %s and %s", startDateTime.ToString().c_str(), endDateTime.ToString().c_str());

    // Start afresh.
    m_kpiGroups.clear();

    m_startDateTime = startDateTime;
    m_endDateTime = endDateTime;
    m_numKpiGroupsAggregated = 0;
    m_numKpiGroupsIgnored = 0;

    // Iterate through all KPI groups in the log file(s).
    m_kpiGroupList.AcceptVisitor(*this);

    m_haveAggregated = true;

    TRACE_PRINTF("AggregateKpis() complete: %"PRIu32" groups aggregated, %"PRIu32" ignored.",
                  m_numKpiGroupsAggregated, m_numKpiGroupsIgnored);
		  
    return m_numKpiGroupsAggregated;		  

    EXIT();
}

u32 KpiAggregator::GetKpiTotalCount(KpiId kpiId) const
{
    /*ENTER();

    // Preconditions.
    RSYS_ASSERT(m_haveAggregated);

    KpiGroupId kpiGroupId;
    bool kpiGroupIdFound = KpiGroup::GetKpiGroupId(kpiId, kpiGroupId);

    RSYS_ASSERT(kpiGroupIdFound);

    KpiGroups::const_iterator iter = m_kpiGroups.find(kpiGroupId);
    
    
    
    if(iter != m_kpiGroups.end())
    {
        RETURN(iter->second.GetKpi(kpiId));
    }*/

    RETURN(0);
}

void KpiAggregator::VisitKpiGroup(const KpiGroup& kpiGroup)
{
    ENTER();

    // Check date/time.
    TimeWrap timestamp;
    kpiGroup.GetTimestamp(timestamp);
    
   
    if((timestamp.GetUnixTime() > m_startDateTime.GetUnixTime()) &&
       (timestamp.GetUnixTime() <= m_endDateTime.GetUnixTime()))
    {
       m_numKpiGroupsAggregated++;
	
       m_kpiGroups[kpiGroup.GetKpiGroupId()][timestamp.GetUnixTime()] = kpiGroup;
    }
    else
    {
        m_numKpiGroupsIgnored++;
	
	    //TRACE_PRINTF ( " Curent time[%s] start[%s] end[%s]\n",  timestamp.ToString().c_str(),  m_startDateTime.ToString().c_str(), m_endDateTime.ToString().c_str() );  
    }

    EXIT();
}

std::string KpiAggregator::ToString() const
{
    ENTER();

    ostringstream stream;

    KpiGroups::const_iterator iter = m_kpiGroups.begin();
    
    while(iter != m_kpiGroups.end())
    {
        KpiGroupInfo::const_iterator innerIter = iter->second.begin();
        stream << innerIter->second.ToString() << endl;
        ++iter;
    }

    RETURN(stream.str());
}

}
