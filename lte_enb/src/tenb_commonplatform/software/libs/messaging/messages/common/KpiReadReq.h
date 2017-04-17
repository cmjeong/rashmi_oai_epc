///////////////////////////////////////////////////////////////////////////////
//
// KpiReadReq.h
//
// Read a KPI group from an entity that is collecting the KPI values.
// Optionally causes a reset of the current values.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __KpiReadReq_h_
#define __KpiReadReq_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////
using namespace std;
#include<set>

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>
#include <system/KpiGroup.h>

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class KpiReadReq : public threeway::Serialisable
{
public:
    static const u16 MAX_KPI_GROUPS = 100;
    // Typedefs
    typedef enum
    {
        READ_KPIS = 0,
        READ_AND_RESET_KPIS
    } KpiReadMode;

    /**
     * Default constructor.  For messaging internal use only.
     */
    KpiReadReq();

    /**
     * Construct a KPI read request message.
     *
     * \param kpiGroupIdList        List of Groups to read.
     * \param kpiMeasurementSet Which of the independent sets of measurements to read?
     * \param readMode          Whether to reset the counts or not.
     * \param isCollectionReqPending Indicates whether a upload request that has to be sent to TR069 Process is pending.
     * \param uploadIntervalinSecs   Indicates the interval at which upload request has to be sent to TR069 Process.
     */
    KpiReadReq(std::set<KpiGroupId> kpiGroupIdList, u8 kpiMeasurementSet, KpiReadMode readMode, bool isCollectionReqPending = false, u32 uploadIntervalinSecs = 0);

    virtual ~KpiReadReq() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_KPI_READ_REQ; };
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);
    virtual std::string ToString() const;

    /**
     * Getters.
     */
    set<KpiGroupId>  GetKpiGroupIdList() const { return m_kpiGroupIdList; }
    u8          GetKpiMeasurementSet() const { return m_kpiMeasurementSet; };
    KpiReadMode GetKpiReadMode() const { return m_kpiReadMode; };
    bool isCollectionreqPending() const { return m_isCollectionReqPending; }
    u32 getPeriodicUploadIntervalInSecs() const { return m_periodicUploadIntervalInSecs; }

private:

    std::set<KpiGroupId> m_kpiGroupIdList;
    u8 m_kpiMeasurementSet;
    KpiReadMode m_kpiReadMode;
    bool m_isCollectionReqPending;
    u32 m_periodicUploadIntervalInSecs; 
};

#endif
