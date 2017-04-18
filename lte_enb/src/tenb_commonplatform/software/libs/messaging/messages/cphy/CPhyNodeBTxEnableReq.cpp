///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyNodeBTxEnableReq.cpp 28889 2010-08-03 17:43:47Z mmcternan $
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

#include "CPhyNodeBTxEnableReq.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CPhyNodeBTxEnableReq::CPhyNodeBTxEnableReq(const CphyNodeBTxEnableReq *msg)
{
    m_Struct = *msg;
}

CPhyNodeBTxEnableReq::CPhyNodeBTxEnableReq(bool enableTx)
{
    m_Struct.enableTx = enableTx;
}

s32 CPhyNodeBTxEnableReq::Serialise(u8 *data, u32 dataMaxBytes) const
{
    return CphyNodeBTxEnableReq_Serialise(&m_Struct, data, dataMaxBytes);
}

bool CPhyNodeBTxEnableReq::DeSerialise(const u8* data, u32 dataLen)
{
    if(CphyNodeBTxEnableReq_Deserialise(data, dataLen, &m_Struct) < 0)
        return false;
    else
        return true;
}

u32 CPhyNodeBTxEnableReq::GetStruct(CphyMessageData *const msg)
{
    msg->nodeBTxEnableReq = &m_Struct;

    return GetSerialisationId();
}

string CPhyNodeBTxEnableReq::ToString() const
{
    ostringstream stream;

    stream << "CPhyNodeBTxEnableReq " << endl;
    stream << "{ enableTx=" << (u16)m_Struct.enableTx << endl;
    stream << "}" << endl;

    return(stream.str());
}

string CPhyNodeBTxEnableReq::ToBriefString() const
{
    ostringstream stream;

    stream << "enableTx=" << (u16)m_Struct.enableTx;

    return(stream.str());
}


extern "C"
{


s32 CphyNodeBTxEnableReq_Serialise(const CphyNodeBTxEnableReq *msg, u8 *const buffer, u32 maxLen)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyNodeBTxEnableReq))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(buffer, msg, sizeof(CphyNodeBTxEnableReq));
    return sizeof(CphyNodeBTxEnableReq);
}


s32 CphyNodeBTxEnableReq_Deserialise(const u8 *buffer, u32 maxLen, CphyNodeBTxEnableReq *const msg)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyNodeBTxEnableReq))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(msg, buffer, sizeof(CphyNodeBTxEnableReq));

    return sizeof(CphyNodeBTxEnableReq);
}

}

// END OF FILE
