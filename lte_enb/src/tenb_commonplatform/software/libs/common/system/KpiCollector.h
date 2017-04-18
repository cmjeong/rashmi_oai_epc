///////////////////////////////////////////////////////////////////////////////
//
// KpiCollector.h
//
// Class for collecting KPIs.  Derived classes implement application/module
// specific work for implementing KPIs.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __KpiCollector_h_
#define __KpiCollector_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <map>
#include <string>

#include <boost/shared_ptr.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <platform/KpiTypes.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "KpiGroup.h"

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class KpiCollector
{
public:

    KpiCollector();
    virtual ~KpiCollector();

    /**
     * Increment specified KPI for all instances.
     */

    /**
     * Increment specified KPI by specified amount for all instances.
     */
    /**
     * This function increments KPI by an integer value
    */
    void IncKpiByIntVal(KpiId kpiId,u32 cellId, u32 increment);
    /**
     * This function increments KPI by a real value 
    */
    void IncKpiByRealVal(KpiId kpiId,u32 cellId, float increment);
    /**
     * Get a particular KPI group.
     *
     * \param kpiGroupId Group ID of group to fetch.
     * \param kpiMeasurementSet Which of the independent sets of measurements to get?
     * \param resetKpis  If true, the current values will be reset to zero.
     * \param kpiGroup   If group found, set to current value, if not found, left unchanged.
     * \return           true if group found.
     */
    bool GetKpiGroup(KpiGroupId kpiGroupId, u8 kpiMeasurementSet, bool resetKpis, KpiGroup& kpiGroup);

    /**
     * Get current KPI groups, KPIs and their current values.
     */
    std::string ToString() const;

private:

    // Number of independent measurement sets supported by the collector.
    static const u8 NUM_MEASUREMENT_SETS = 2;

    // Typedefs

    /*
     *       _________________KpiMeasurementSets_________________
     *      /                                                    \
     *                           ___________KpiGroups____________
     *                          /                                \
     *       KpiGroupId[1]  =>  [ KpiGroup[ID=1]  KpiGroup[ID=1] ]
     *
     *       KpiGroupId[3]  =>  [ KpiGroup[ID=3]  KpiGroup[ID=3] ]
     *
     *                           |_____________| |_____________|
     *                                  |               |
     *                           e.g. for TR069    e.g. for CLI
     */

    /**
     * Group together multiple independent KPI groups indexed
     * by their group ID.  So from one group ID we can find N
     * groups all collecting the same KPIs but can be independently
     * queried and reset.
     */
    typedef std::vector< boost::shared_ptr<KpiGroup> > KpiGroups;

    /**
     * Multiple independent sets of the same KPI group is called
     * a measurement "set".
     */
    typedef std::map<boost::tuple<u32,KpiGroupId>, KpiGroups> KpiMeasurementSets;

    /**
     * Find the KPI Group ID from the KPI ID and if we're not already
     * collecting for that group ID, add empty it to our measurement sets.
     */
    KpiGroupId FindOrAddGroups(KpiId kpiId,u32 cellId);

    /**
     * Groups of KPIs that we are collecting stats for.
     * There are N independent sets of these to allow independent counting
     * for different purposes.  E.g. one is likely to be for the "official" KPI
     * reporting mechanism such as TR-069 and one for development
     * and test purposes.
     */
    KpiMeasurementSets m_kpiMeasurementSets;

};

}

#endif
