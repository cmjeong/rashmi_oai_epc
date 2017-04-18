///////////////////////////////////////////////////////////////////////////////
//
// KpiRegisterReq.h
//
// Register a set of KPIs managed by a particular entity.
// Entity sends this to OAM to let it know where KPI groups are being collected
// so OAM knows where to send KpiReadReq's.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __KpiRegisterReq_h_
#define __KpiRegisterReq_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <set>
#include <system/Serialisable.h>
#include <system/SerialisationIds.h>
#include <platform/KpiTypes.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class KpiRegisterReq : public threeway::Serialisable
{
public:

    /**
     * Default constructor.  For messaging internal use only.
     */
    KpiRegisterReq() {};

    /**
     * Construct a KPI read request message.
     *
     * \param kpiGroupId Group to read.
     * \param readMode   Whether to reset the counts or not.
     */
    KpiRegisterReq(std::set<KpiGroupId> kpiGroupIds);

    virtual ~KpiRegisterReq() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_KPI_REGISTER_REQ; };
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);
    virtual std::string ToString() const;

    /**
     * Getters.
     */
    std::set<KpiGroupId> GetKpiGroupIds() const { return m_kpiGroupIds; };

private:

    std::set<KpiGroupId> m_kpiGroupIds;
};

}

#endif
