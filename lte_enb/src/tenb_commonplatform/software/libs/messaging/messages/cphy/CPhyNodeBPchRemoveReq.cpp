///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyNodeBPchRemoveReq.cpp 28647 2010-07-26 08:55:18Z mmcternan $
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
#include <system/Trace.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "CPhyNodeBPchAddReq.h"
#include "CPhyNodeBPchRemoveReq.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CPhyNodeBPchRemoveReq::CPhyNodeBPchRemoveReq(u16 sfnOffset)
{
    m_Struct.sfnOffset = sfnOffset;
}

CPhyNodeBPchRemoveReq::CPhyNodeBPchRemoveReq(const CphyNodeBPchRemoveReq *msg)
{
    m_Struct = *msg;
}

s32 CPhyNodeBPchRemoveReq::Serialise(u8 *data, u32 dataMaxBytes) const
{
    return CphyNodeBPchRemoveReq_Serialise(&m_Struct, data, dataMaxBytes);
}

bool CPhyNodeBPchRemoveReq::DeSerialise(const u8* data, u32 dataLen)
{
    if(CphyNodeBPchRemoveReq_Deserialise(data, dataLen, &m_Struct) < 0)
        return false;
    else
        return true;
}

u32 CPhyNodeBPchRemoveReq::GetStruct(CphyMessageData *const msg)
{
    msg->nodeBPchRemoveReq = &m_Struct;

    return GetSerialisationId();
}

string CPhyNodeBPchRemoveReq::ToString() const
{
    ostringstream stream;

    stream << "CPhyNodeBPchRemoveReq " << endl;
    stream << "{ sfnOffset=" << m_Struct.sfnOffset << endl;
    stream << "}" << endl;

    return(stream.str());
}


string CPhyNodeBPchRemoveReq::ToBriefString() const
{
    ostringstream stream;

    if(m_Struct.sfnOffset == CPHY_NODEB_PCH_SET_FILL)
    {
        stream << "sfnOffset=FILL";
    }
    else
    {
        stream << "sfnOffset=" << m_Struct.sfnOffset;
    }

    return(stream.str());
}

extern "C"
{


s32 CphyNodeBPchRemoveReq_Serialise(const CphyNodeBPchRemoveReq *msg, u8 *const buffer, u32 maxLen)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyNodeBPchRemoveReq))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(buffer, msg, sizeof(CphyNodeBPchRemoveReq));
    return sizeof(CphyNodeBPchRemoveReq);
}


s32 CphyNodeBPchRemoveReq_Deserialise(const u8 *buffer, u32 maxLen, CphyNodeBPchRemoveReq *const msg)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyNodeBPchRemoveReq))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(msg, buffer, sizeof(CphyNodeBPchRemoveReq));

    return sizeof(CphyNodeBPchRemoveReq);
}

}

// END OF FILE
