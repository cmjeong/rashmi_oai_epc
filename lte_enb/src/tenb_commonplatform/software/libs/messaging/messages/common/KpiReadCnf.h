///////////////////////////////////////////////////////////////////////////////
//
// KpiReadCnf.h
//
// Message containing current KPI values.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __KpiReadCnf_h_
#define __KpiReadCnf_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>
#include <system/KpiGroup.h>

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class KpiReadCnf : public threeway::Serialisable
{
public:

    /**
     * Default constructor.  For messaging internal use only.
     */
    KpiReadCnf();

    /**
     * Construct an KPI read request message.
     *
     */
    KpiReadCnf(u8 kpiMeasurementSet, const threeway::KpiGroup& kpiGroup);

    virtual ~KpiReadCnf() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_KPI_READ_CNF; };
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);
    virtual std::string ToString() const;

    /**
     * Getters.
     */
    u8 GetKpiMeasurementSet() const { return m_kpiMeasurementSet; };
    const threeway::KpiGroup& GetKpiGroup() const { return m_kpiGroup; };

private:

    u8 m_kpiMeasurementSet;
    threeway::KpiGroup m_kpiGroup;
};

#endif
