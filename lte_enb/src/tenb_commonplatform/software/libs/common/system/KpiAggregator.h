///////////////////////////////////////////////////////////////////////////////
//
// KpiAggregator.h
//
// Visits a KpiGroup store and aggregates the KPIs so you only have one
// instance of each KPI group ID.  I.e. multiple KPI group objects with the
// same KPI group ID get added together into a single object.
//
// Can also specify a time/date range.  KPI groups with a timestamp outside
// this range will be ignored.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __KpiAggregator_h_
#define __KpiAggregator_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/KpiLogFileMgr.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class KpiAggregator : public KpiGroupVisitor
{
public:

    /**
     * Constructor.
     *
     * \param kpiList Log file manager that we can visit.  Could generalise
     *                to a "KpiGroupList" in the future.
     */
    KpiAggregator(KpiLogFileMgr& kpiGroupList);

    virtual ~KpiAggregator();

    /**
     * Go aggregate those KPIs!
     * After this call, client can request the total count for a particular KPI.
     *
     * \param startDateTime Start date/time to consider (inclusive).
     * \param endDateTime   End date/time to consider (inclusive).
     */
    u32 AggregateKpis(const TimeWrap& startDateTime, const TimeWrap& endDateTime);

    /**
     * Get the total count for a KPI.  This is the sum of all values of
     * the specified KPI.
     */
    u32 GetKpiTotalCount(KpiId kpiId) const;
    
    /**
     * Implement KpiGroupVisitor.
     * Callback after we visit our KPI group list/container object.
     */
    void VisitKpiGroup(const KpiGroup& kpiGroup);

    /**
     * Get as string for trace.
     */
    std::string ToString() const;
    
    
protected:

//private:

    
    typedef std::map<u32, KpiGroup> KpiGroupInfo;
    
    typedef std::map<KpiGroupId, KpiGroupInfo> KpiGroups;

    /**
     * Store the visitor reference as we need to use it in HandleObjectRead
     * after calling AcceptVisitor().
     */
    KpiLogFileMgr& m_kpiGroupList;

    /**
     * Groups of KPIs - aggregated, only 1 object per group ID.
     */
    KpiGroups m_kpiGroups;

    /**
     * Record these as members during aggregation as we need them
     * in our visit method.
     */
    TimeWrap m_startDateTime;
    TimeWrap m_endDateTime;

    /**
     * Set true once AggregateKpis() has been called so we can
     * check when calling GetKpiTotalCount().
     */
    bool m_haveAggregated;

    /**
     * Keep a count for trace purposes.
     */
    u32 m_numKpiGroupsAggregated;
    u32 m_numKpiGroupsIgnored;
    
};

}

#endif
