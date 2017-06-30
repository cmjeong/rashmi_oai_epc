///////////////////////////////////////////////////////////////////////////////
//
// KpiConfigureReq.h
//
// Send this to OAM to set up a set of KPIs to measure.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __KpiConfigureReq_h_
#define __KpiConfigureReq_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <set>

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>
#include <system/KpiGroup.h>

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class KpiConfigureReq : public threeway::Serialisable
{
public:

    static const u16 MAX_KPI_GROUPS = 100;

    /**
     * Default constructor.  For messaging internal use only.
     */
    KpiConfigureReq();

    /**
     * Construct a KPI configure request message.
     */
    KpiConfigureReq(std::set<KpiGroupId> kpiGroupIds, u32 measurementIntervalSecs, u32 perodicUploadIntervalSecs, u32 perodicUploadPhaseAllign);

    virtual ~KpiConfigureReq() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_KPI_CONFIGURE_REQ; };
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);
    virtual std::string ToString() const;

    /**
     * Getters.
     */
    std::set<KpiGroupId> GetKpiGroupIds() const { return m_kpiGroupIds; };
    u32 GetMeasurementIntervalSecs() const { return m_measurementIntervalSecs; };
    u32 GetPerodicUploadIntervalSecs() const { return m_perodicUploadIntervalSecs; };
    u32 GetPerodicUploadPhaseAllignInMin() const { return m_perodicUploadPhaseAllignInMin; };

private:

    std::set<KpiGroupId> m_kpiGroupIds;
    u32 m_measurementIntervalSecs;
    u32 m_perodicUploadIntervalSecs;
    u32 m_perodicUploadPhaseAllignInMin;
};

#endif
