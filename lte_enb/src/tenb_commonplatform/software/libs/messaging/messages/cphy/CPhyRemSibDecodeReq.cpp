///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyRemSibDecodeReq.cpp 28519 2010-07-21 14:39:46Z mmcternan $
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

#include "CPhyRemSibDecodeReq.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CPhyRemSibDecodeReq::CPhyRemSibDecodeReq(const CphyRemSibDecodeReq *msg)
{
    m_Struct = *msg;
}

s32 CPhyRemSibDecodeReq::Serialise(u8 *data, u32 dataMaxBytes) const
{
    return CphyRemSibDecodeReq_Serialise(&m_Struct, data, dataMaxBytes);
}

bool CPhyRemSibDecodeReq::DeSerialise(const u8* data, u32 dataLen)
{
    if(CphyRemSibDecodeReq_Deserialise(data, dataLen, &m_Struct) < 0)
        return false;
    else
        return true;
}

CPhyRemSibDecodeReq::CPhyRemSibDecodeReq(upsc_t psc, uarfcn_t freq, uband_t band, bool start)
{
    m_Struct.psc[0] = psc;
    m_Struct.frequency = freq;
    m_Struct.band = band;
    m_Struct.start = start;
}

CPhyRemSibDecodeReq::CPhyRemSibDecodeReq(upsc_t* psc, uarfcn_t freq, uband_t band, bool start, u8 count)
{
    u8 i;
    m_Struct.count = count;
    for(i = 0;i < count; i++)
    {
       m_Struct.psc[i] = psc[i];
       //psc++;
    }
    m_Struct.frequency = freq;
    m_Struct.band = band;
    m_Struct.start = start;
}

u32 CPhyRemSibDecodeReq::GetStruct(CphyMessageData *const msg)
{
    msg->remSibDecodeReq = &m_Struct;

    return GetSerialisationId();
}

string CPhyRemSibDecodeReq::ToString() const
{
    ostringstream stream;

    stream << "CPhyRemSibDecodeReq " << endl;
    stream << "{ psc= " << (u16)m_Struct.psc[0] << endl;
    stream << "  start= " << (u16)m_Struct.start << endl;
    stream << "}" << endl;

    return(stream.str());
}

string CPhyRemSibDecodeReq::ToBriefString() const
{
    ostringstream stream;

    stream << "psc= " << (u16)m_Struct.psc[0]
           << " start= " << (u16)m_Struct.start;

    return(stream.str());
}

extern "C"
{


s32 CphyRemSibDecodeReq_Serialise(const CphyRemSibDecodeReq *msg, u8 *const buffer, u32 maxLen)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyRemSibDecodeReq))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(buffer, msg, sizeof(CphyRemSibDecodeReq));
    return sizeof(CphyRemSibDecodeReq);
}


s32 CphyRemSibDecodeReq_Deserialise(const u8 *buffer, u32 maxLen, CphyRemSibDecodeReq *const msg)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyRemSibDecodeReq))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(msg, buffer, sizeof(CphyRemSibDecodeReq));
    return sizeof(CphyRemSibDecodeReq);
}

}

// END OF FILE
