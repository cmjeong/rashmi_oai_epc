///////////////////////////////////////////////////////////////////////////////
//
// KpiGroup.h
//
// KPI group brings together a set of related KPIs.
// This class contains the actual counts for each of the KPIs within the group.
// There may be multiple instances of the same group in order to manage
// different KPI collection strategies/schedules.  These are managed by the
// KpiCollector.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __KpiGroup_h_
#define __KpiGroup_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <map>
#include <boost/any.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <boost/tuple/tuple.hpp>
using boost::any_cast;
#include <string>

#include <3waytypes.h>
#include <system/Trace.h>
#include <system/Serialisable.h>
#include <system/SerialisationIds.h>
#include <system/TimeWrap.h>

#include <platform/KpiTypes.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////
using namespace boost;
namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

/**
 * Aggregate a set of related KPIs.
 */
class KpiGroup : public Serialisable
{
public:
    /**
     * Look for the definition of a particular KPI.
     *
     * \return Pointer to definition struct or NULL if not found.
     */
    static const KpiDefinition* GetKpiDefinition(KpiId kpiId);

    /**
     * Look for the definition of a particular KPI group.
     *
     * \return Pointer to definition struct or NULL if not found.
     */
    static const KpiGroupDefinition* GetKpiGroupDefinition(KpiGroupId kpiGroupId);

    /**
     * Get KPI group ID from KPI ID.
     */
    static bool GetKpiGroupId(KpiId kpiId, KpiGroupId& kpiGroupId);

    /**
     * Get KPI description text.
     *
     * \return Description if found, NULL if not.
     */
    static const char * GetKpiDescription(KpiId kpiId);

    /**
     * Get KPI group description text.
     *
     * \return Description if found, NULL if not.
     */
    static const char * GetKpiGroupDescription(KpiGroupId kpiGroupId);

    /**
     * Get KPI group description text from a KPI ID.
     *
     * \return Description if found, NULL if not.
     */
    static const char * GetKpiGroupDescription(KpiId kpiId);


    KpiGroup(); // For messaging architecture only.
    KpiGroup(KpiGroupId kpiGroupId);
    ~KpiGroup();

    /**
     * Implement Serialisable.
     */
    u32 GetSerialisationId() const { return SERIALISATION_ID_KPI_GROUP; };
    s32 Serialise(u8* data, u32 dataMaxBytes) const;
    bool DeSerialise(const u8* data, u32 dataLen);
    std::string ToString() const;

    /**
     * Get group ID.
     */
    KpiGroupId GetKpiGroupId() const { RSYS_ASSERT(m_groupDefinition != NULL); return m_groupDefinition->kpiGroupId; }

    /**
     * Increment the given KPI by 1.
     */

    /**
     * Increment the given KPI by N.  KPI must be of type KPI_
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
     * This function is used to get integer type KPI value
     */
    u32 GetIntTypKpi(KpiId kpiId,u32 cellId) const;
    /**
     * This function is used to get real type KPI value
    */
    float GetRealTypKpi(KpiId kpiId,u32 cellId) const;

    /**
     * Reset KPIs to 0.
     */
    void ResetKpis();

    /**
     * Timestamp this KPI group.  Will set the internal timestamp to be
     * the current time.  Can be used when
     */
    void TouchTimestamp();
    void TouchAndAlignTimeStampToUploadInterval(u32 uploadIntervalInSeconds);

    /**
     * Get current timestamp.
     *
     * \param  timestamp Set to current internal timestamp.
     * \return           true if time has been updated since KpiGroup was
     *                   created, false if it hasn't.  I.e. if false, then
     *                   timestamp is the time the object was created.
     */
    bool GetTimestamp(TimeWrap& timestamp) const;

    /**
     * Add and assign operator.  Merges 2 groups and adds together any KPIs
     * that exist in both.
     */
    KpiGroup& operator+=(const KpiGroup& rhs);

    /**
     * Equality operator.
     */
    bool operator==(const KpiGroup& rhs) const;

protected:

    /**
     * Validate that the KPI is a member of this group and is the correct type.
     *
     * \return true if valid.
     */
    bool ValidateKpiId(KpiId kpiId, KpiType kpiType) const;

private:
    /**
     * Map stores mix data types 
     */ 
    typedef std::map<boost::tuple<KpiId,u32>, boost::any> KpiCounts;

    /**
     * The definition of this group.  Relates to a set of KPIs.
     */
    const KpiGroupDefinition* m_groupDefinition;

    /**
     * Current KPI values for U32 type KPIs.
     */
    KpiCounts m_kpiCounts;

    /**
     * Timestamp.  This starts off as object creation time and
     * is set to current time when TouchTimestamp() is called
     * e.g. when the KpiCollector reports this KPI group - the
     * timestamp will be used as a reporting time.
     */
    TimeWrap m_timestamp;

    /**
     * Starts off false, set to true when TouchTimestamp() is called.
     */
    bool m_timestampUpdated;
};

/**
 * KpiVisitor
 */
class KpiGroupVisitor
{
public:
    virtual ~KpiGroupVisitor () {}

    /**
     * Visitor for a KpiGroup.
     *
     * \param kpiGroup KpiGroup object passed back to client.
     */
    virtual void VisitKpiGroup(const KpiGroup& kpiGroup) = 0;

};

}

#endif
