///////////////////////////////////////////////////////////////////////////////
//
// $Id: CphyNodeBTxDpchEnableReq.cpp 5567 2008-05-30 11:13:47Z mm $
//
// See header file for documentation.
//
// Copyright � Radisys Ltd
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

#include "CPhyNodeBTxDpchEnableReq.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CPhyNodeBTxDpchEnableReq::CPhyNodeBTxDpchEnableReq(const CphyNodeBTxDpchEnableReq *msg)
{
    m_Struct = *msg;
}

CPhyNodeBTxDpchEnableReq::CPhyNodeBTxDpchEnableReq(u8 dpchId, bool enable)
{
    m_Struct.dpchId = dpchId;
    m_Struct.enable = enable;
}

s32 CPhyNodeBTxDpchEnableReq::Serialise(u8 *data, u32 dataMaxBytes) const
{
    return CphyNodeBTxDpchEnableReq_Serialise(&m_Struct, data, dataMaxBytes);
}

bool CPhyNodeBTxDpchEnableReq::DeSerialise(const u8* data, u32 dataLen)
{
    if(CphyNodeBTxDpchEnableReq_Deserialise(data, dataLen, &m_Struct) < 0)
        return false;
    else
        return true;
}

u32 CPhyNodeBTxDpchEnableReq::GetStruct(CphyMessageData *const msg)
{
    msg->nodeBTxDpchEnableReq = &m_Struct;

    return GetSerialisationId();
}

string CPhyNodeBTxDpchEnableReq::ToString() const
{
    ostringstream stream;

    stream << "CPhyNodeBTxDpchEnableReq " << endl;
    stream << "{ dpchId= " << (u16)m_Struct.dpchId << endl;
    stream << "  enable= " << (u16)m_Struct.enable << endl;
    stream << "}" << endl;

    return(stream.str());
}


extern "C"
{


s32 CphyNodeBTxDpchEnableReq_Serialise(const CphyNodeBTxDpchEnableReq *msg, u8 *const buffer, u32 maxLen)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyNodeBTxDpchEnableReq))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(buffer, msg, sizeof(CphyNodeBTxDpchEnableReq));
    return sizeof(CphyNodeBTxDpchEnableReq);
}


s32 CphyNodeBTxDpchEnableReq_Deserialise(const u8 *buffer, u32 maxLen, CphyNodeBTxDpchEnableReq *const msg)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyNodeBTxDpchEnableReq))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(msg, buffer, sizeof(CphyNodeBTxDpchEnableReq));

    return sizeof(CphyNodeBTxDpchEnableReq);
}

}

// END OF FILE
