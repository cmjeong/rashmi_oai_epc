///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyNodeBPchAddReq.cpp 28331 2010-07-17 15:25:20Z mmcternan $
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
#include <iomanip>
#include <system/Trace.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "CPhyNodeBPchAddReq.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CPhyNodeBPchAddReq::CPhyNodeBPchAddReq(u16 sfnOffset, pi_t *pi, u16 nRepeat, const u8 *data, u32 dataLen) :
    m_Struct()
{
    RSYS_ASSERT(dataLen <= PCH_TRCH_BLOCK_SIZE_BYTES);

    m_Struct.sfnOffset = sfnOffset;
    m_Struct.nRepeat   = nRepeat;
    memcpy(m_Struct.pi, pi, sizeof(pi_t));
    memcpy(m_Struct.data, data, dataLen);
}

CPhyNodeBPchAddReq::CPhyNodeBPchAddReq(const CphyNodeBPchAddReq *msg) :
    m_Struct( *msg )
{
}

s32 CPhyNodeBPchAddReq::Serialise(u8 *data, u32 dataMaxBytes) const
{
    return CphyNodeBPchAddReq_Serialise(&m_Struct, data, dataMaxBytes);
}

bool CPhyNodeBPchAddReq::DeSerialise(const u8* data, u32 dataLen)
{
    if(CphyNodeBPchAddReq_Deserialise(data, dataLen, &m_Struct) < 0)
        return false;
    else
        return true;
}

u32 CPhyNodeBPchAddReq::GetStruct(CphyMessageData *const msg)
{
    msg->nodeBPchAddReq = &m_Struct;

    return GetSerialisationId();
}

string CPhyNodeBPchAddReq::ToString() const
{
    ostringstream stream;
    u8            t;

    stream << "CPhyNodeBPchAddReq " << endl;

    if(m_Struct.sfnOffset == CPHY_NODEB_PCH_SET_FILL)
    {
        stream << "{ sfnOffset=CPHY_NODEB_PCH_SET_FILL" << endl;
    }
    else
    {
        stream << "{ sfnOffset=" << m_Struct.sfnOffset << endl;
    }
    stream << "  nRepeat  =" << m_Struct.nRepeat << endl;
    stream << std::hex;
    stream << "  pi       =" << (u32)m_Struct.pi[4] << (u32)m_Struct.pi[3] <<
                                (u32)m_Struct.pi[2] << (u32)m_Struct.pi[1] <<
                                (u32)m_Struct.pi[0] << endl;
    stream << "  data = { ";
    for(t = 0; t < PCH_TRCH_BLOCK_SIZE_BYTES; t++)
    {
        if(t != 0)
        {
            stream << ", ";
            if((t % 8) == 0)
            {
                stream << endl << "           ";
            }
        }
        stream << std::setw(2) << std::setfill('0') << (u16)(m_Struct.data[t]);
    }
    stream << " }" << endl;
    stream << "}" << endl;

    return(stream.str());
}


string CPhyNodeBPchAddReq::ToBriefString() const
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


s32 CphyNodeBPchAddReq_Serialise(const CphyNodeBPchAddReq *msg, u8 *const buffer, u32 maxLen)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyNodeBPchAddReq))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(buffer, msg, sizeof(CphyNodeBPchAddReq));
    return sizeof(CphyNodeBPchAddReq);
}


s32 CphyNodeBPchAddReq_Deserialise(const u8 *buffer, u32 maxLen, CphyNodeBPchAddReq *const msg)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyNodeBPchAddReq))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(msg, buffer, sizeof(CphyNodeBPchAddReq));

    return sizeof(CphyNodeBPchAddReq);
}

}

// END OF FILE
