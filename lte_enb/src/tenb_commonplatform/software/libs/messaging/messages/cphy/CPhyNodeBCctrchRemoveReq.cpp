///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyNodeBCctrchRemoveReq.cpp 7696 2008-09-10 10:29:53Z manderson $
//
// See header file for documentation.
//
// Copyright radisys Ltd
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

#include "CPhyNodeBCctrchRemoveReq.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CPhyNodeBCctrchRemoveReq::CPhyNodeBCctrchRemoveReq ()
{
    bzero (&m_cctrchRemoveReq, sizeof (CphyNodeBCctrchRemoveReq));
}

CPhyNodeBCctrchRemoveReq::CPhyNodeBCctrchRemoveReq (uint8_t ueNumber, uint32_t instanceId)
{
    // Default behaviour puts UE ito Cell Idle...
    bzero (&m_cctrchRemoveReq, sizeof (CphyNodeBCctrchRemoveReq));
    m_cctrchRemoveReq.ue = ueNumber;
    m_cctrchRemoveReq.instanceId = instanceId;
    m_cctrchRemoveReq.actTime.now = true;
}

CPhyNodeBCctrchRemoveReq::CPhyNodeBCctrchRemoveReq (uint8_t ueNumber, uint32_t instanceId, uint16_t activationTime)
{
    bzero (&m_cctrchRemoveReq, sizeof (CphyNodeBCctrchRemoveReq));
    m_cctrchRemoveReq.ue = ueNumber;
    m_cctrchRemoveReq.instanceId = instanceId;
    m_cctrchRemoveReq.actTime.now = false;
    m_cctrchRemoveReq.actTime.sfn = activationTime;
}

CPhyNodeBCctrchRemoveReq::CPhyNodeBCctrchRemoveReq(const CPhyNodeBCctrchRemoveReq &cctrchRemoveReq)
{
    memcpy (&m_cctrchRemoveReq, &cctrchRemoveReq.m_cctrchRemoveReq, sizeof (CphyNodeBCctrchRemoveReq));
}

s32 CPhyNodeBCctrchRemoveReq::Serialise(u8 *data, u32 dataMaxBytes) const
{
    return CPhyNodeBCctrchRemoveReq_Serialise(&m_cctrchRemoveReq, data, dataMaxBytes);
}

bool CPhyNodeBCctrchRemoveReq::DeSerialise(const u8* data, u32 dataLen)
{
    if(CPhyNodeBCctrchRemoveReq_Deserialise(data, dataLen, &m_cctrchRemoveReq) < 0)
        return false;
    else
        return true;
}

u32 CPhyNodeBCctrchRemoveReq::GetStruct(CphyMessageData *const msg)
{
    msg->nodeBCctrchRemoveReq = &m_cctrchRemoveReq;

    return GetSerialisationId();
}

string CPhyNodeBCctrchRemoveReq::ToString() const
{
    ostringstream stream;

    stream << "CPhyNodeBCctrchRemoveReq v2" << endl;

    stream << "{ actTime=" << endl;
    stream << "  { now=" << (m_cctrchRemoveReq.actTime.now ? "yes" : "no") << endl;
    stream << "    sfn=" << (u16)m_cctrchRemoveReq.actTime.sfn << endl;
    stream << "  }" << endl;

    stream << "  ue=" << (u16)m_cctrchRemoveReq.ue << endl;
    stream << "  instanceId=" << m_cctrchRemoveReq.instanceId << endl;
    stream << "}" << endl;

    return(stream.str());
}

string CPhyNodeBCctrchRemoveReq::ToBriefString() const
{
    ostringstream stream;

    stream << "  ue=" << (u16)m_cctrchRemoveReq.ue << " sfn=";
    if(m_cctrchRemoveReq.actTime.now)
      stream << "now";
    else
      stream << (u16)m_cctrchRemoveReq.actTime.sfn;
    stream << " instance=" << m_cctrchRemoveReq.instanceId;

    return(stream.str());
}


extern "C"
{


s32 CPhyNodeBCctrchRemoveReq_Serialise(const CphyNodeBCctrchRemoveReq *msg, u8 *const buffer, u32 maxLen)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyNodeBCctrchRemoveReq))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(buffer, msg, sizeof(CphyNodeBCctrchRemoveReq));
    return sizeof(CphyNodeBCctrchRemoveReq);
}


s32 CPhyNodeBCctrchRemoveReq_Deserialise(const u8 *buffer, u32 maxLen, CphyNodeBCctrchRemoveReq *const msg)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyNodeBCctrchRemoveReq))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(msg, buffer, sizeof(CphyNodeBCctrchRemoveReq));
    return sizeof(CphyNodeBCctrchRemoveReq);
}

}

// END OF FILE
