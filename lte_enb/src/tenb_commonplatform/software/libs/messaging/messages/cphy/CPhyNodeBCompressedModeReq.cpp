///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyNodeBCompressedModeReq.cpp 28742 2010-07-28 17:53:13Z dmorrison $
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

#include "CPhyNodeBCompressedModeReq.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CPhyNodeBCompressedModeReq::CPhyNodeBCompressedModeReq(const l1_activation_time_t &activationTime,
        const bool enableDl, const bool enableUl, u8 zeroBasedUeNumber, u8 chanCode, u8 seqId,
        u8 tgsn, u8 tgl1, u8 tgl2, u16 tgd, u16 tgpl1, u16 tgprc)
{
    bzero (&m_Struct, sizeof (CphyNodeBCompressedModeReq));

    memcpy (&m_Struct.actTime, &activationTime, sizeof (l1_activation_time_t));
    m_Struct.enableCompModeDl = enableDl;
    m_Struct.enableCompModeUl = enableUl;
    m_Struct.ue = zeroBasedUeNumber;
    m_Struct.downlinkChannelisationCode = chanCode;
    m_Struct.seqId = seqId;
    m_Struct.seqId = seqId;
    m_Struct.tgsn = tgsn;
    m_Struct.tgl1 = tgl1;
    m_Struct.tgl2 = tgl2;
    m_Struct.tgd = tgd;
    m_Struct.tgpl1 = tgpl1;
    m_Struct.tgprc = tgprc;
}

CPhyNodeBCompressedModeReq::CPhyNodeBCompressedModeReq(const CphyNodeBCompressedModeReq *msg)
{
    m_Struct = *msg;
}

s32 CPhyNodeBCompressedModeReq::Serialise(u8 *data, u32 dataMaxBytes) const
{
    return CphyNodeBCompressedModeReq_Serialise(&m_Struct, data, dataMaxBytes);
}

bool CPhyNodeBCompressedModeReq::DeSerialise(const u8* data, u32 dataLen)
{
    if(CphyNodeBCompressedModeReq_Deserialise(data, dataLen, &m_Struct) < 0)
        return false;
    else
        return true;
}

u32 CPhyNodeBCompressedModeReq::GetStruct(CphyMessageData *const msg)
{
    msg->nodeBCompressedModeReq = &m_Struct;

    return GetSerialisationId();
}

string CPhyNodeBCompressedModeReq::ToString() const
{
    ostringstream stream;

    stream << "CPhyNodeBCompressedModeReq " << endl;
    stream << "{ actTime=" << endl;
    stream << "  { now=" << (m_Struct.actTime.now ? "true" : "false") << endl;
    stream << "    sfn=" << (u16)m_Struct.actTime.sfn << endl;
    stream << "  }" << endl;
    stream << "  CM enable DL =  " << (u16)m_Struct.enableCompModeDl << endl;
    stream << "  CM enable UL =  " << (u16)m_Struct.enableCompModeUl << endl;
    stream << "  ue=      " << (u16)m_Struct.ue << endl;
    stream << "  chanCode=" << (u16)m_Struct.downlinkChannelisationCode << endl;
    stream << "  seqId=  " << (u16)m_Struct.seqId << endl;

    // Printing if either is true
    if(m_Struct.enableCompModeDl || m_Struct.enableCompModeUl)
    {
        stream << "  tgsn=    " << (u16)m_Struct.tgsn << endl;
        stream << "  tgl1=    " << (u16)m_Struct.tgl1 << endl;
        stream << "  tgl2=    " << (u16)m_Struct.tgl2 << endl;
        stream << "  tgd=     " << (u16)m_Struct.tgd << endl;
        stream << "  tgpl1=   " << (u16)m_Struct.tgpl1 << endl;
        stream << "  tgprc=   " << (u16)m_Struct.tgprc << endl;
    }
    stream << "}" << endl;

    return(stream.str());
}


extern "C"
{


s32 CphyNodeBCompressedModeReq_Serialise(const CphyNodeBCompressedModeReq *msg, u8 *const buffer, u32 maxLen)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyNodeBCompressedModeReq))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(buffer, msg, sizeof(CphyNodeBCompressedModeReq));
    return sizeof(CphyNodeBCompressedModeReq);
}


s32 CphyNodeBCompressedModeReq_Deserialise(const u8 *buffer, u32 maxLen, CphyNodeBCompressedModeReq *const msg)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyNodeBCompressedModeReq))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(msg, buffer, sizeof(CphyNodeBCompressedModeReq));

    return sizeof(CphyNodeBCompressedModeReq);
}

}

// END OF FILE
