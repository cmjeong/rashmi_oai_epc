///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyNodeBConfigReq.cpp 29075 2010-08-11 08:45:04Z mmcternan $
//
// See header file for documentation.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "CPhyNodeBConfigReq.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CPhyNodeBConfigReq::CPhyNodeBConfigReq(const CphyNodeBConfigReq *msg)
{
    m_Struct = *msg;
}

s32 CPhyNodeBConfigReq::Serialise(u8 *data, u32 dataMaxBytes) const
{
    return CphyNodeBConfigReq_Serialise(&m_Struct, data, dataMaxBytes);
}

bool CPhyNodeBConfigReq::DeSerialise(const u8* data, u32 dataLen)
{
    if(CphyNodeBConfigReq_Deserialise(data, dataLen, &m_Struct) < 0)
        return false;
    else
        return true;
}

u32 CPhyNodeBConfigReq::GetStruct(CphyMessageData *const msg)
{
    msg->nodeBConfigReq = &m_Struct;

    return GetSerialisationId();
}

string CPhyNodeBConfigReq::ToString() const
{
    ostringstream stream;
    uint8_t      t;

    stream << "CPhyNodeBConfigReq " << endl;
    stream << "{ dlArfcn= " << m_Struct.dlArfcn << endl;
    stream << "  band= " << UmtsBandIdToString(m_Struct.band) << endl;
    stream << "  psc= " << m_Struct.psc << endl;
    stream << "  txPowerDbm8=" << m_Struct.txPowerDbm8 << endl;
    stream << "  cpichPowerDbm8=" << m_Struct.cpichPowerDbm8 << endl;

    stream << "  txCtrlChannelPowerOffsetDb8={";
    for(t = 0; t < NUM_CPHY_NODEB_TX_CTRL_CHAN_POWER_OFFSETS; t++)
    {
        stream << m_Struct.txCtrlChannelPowerOffsetDb8[t];
        if(t != NUM_CPHY_NODEB_TX_CTRL_CHAN_POWER_OFFSETS - 1)
        {
            stream << ", ";
        }
    }
    stream << " }" << endl;

    stream << "  txMaxDpchPowerOffsetDb8=" << m_Struct.txMaxDpchPowerOffsetDb8 << endl;
    stream << "  txMaxHspdschPowerOffsetDb8=" << m_Struct.txMaxHspdschPowerOffsetDb8 << endl;
    stream << "  t_rfFailure=" << m_Struct.t_rfFailure << endl;
    stream << "  n_insync_ind=" << m_Struct.n_insync_ind << endl;
    stream << "  n_outsync_ind=" << m_Struct.n_outsync_ind << endl;
    stream << "}" << endl;

    return(stream.str());
}

string CPhyNodeBConfigReq::ToBriefString() const
{
    ostringstream stream;

    stream << "dlArfcn= " << m_Struct.dlArfcn;
    stream << "/" << UmtsBandIdToString(m_Struct.band);
    stream << " psc= " << m_Struct.psc;

    return(stream.str());
}

extern "C"
{


s32 CphyNodeBConfigReq_Serialise(const CphyNodeBConfigReq *msg, u8 *const buffer, u32 maxLen)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyNodeBConfigReq))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(buffer, msg, sizeof(CphyNodeBConfigReq));
    return sizeof(CphyNodeBConfigReq);
}


s32 CphyNodeBConfigReq_Deserialise(const u8 *buffer, u32 maxLen, CphyNodeBConfigReq *const msg)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyNodeBConfigReq))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(msg, buffer, sizeof(CphyNodeBConfigReq));

    return sizeof(CphyNodeBConfigReq);
}

}

// END OF FILE
