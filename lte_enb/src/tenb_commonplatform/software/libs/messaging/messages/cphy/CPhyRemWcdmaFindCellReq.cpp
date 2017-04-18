///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyRemWcdmaFindCellReq.cpp 28519 2010-07-21 14:39:46Z mmcternan $
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

#include "CPhyRemWcdmaFindCellReq.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CPhyRemWcdmaFindCellReq::CPhyRemWcdmaFindCellReq(uarfcn_t freq, uband_t band, bool freqUnlocked)
{
    m_Struct.frequency[0]    = freq; /*KS: List of freq to be*/
    m_Struct.band         = band;
    m_Struct.freqUnlocked = freqUnlocked;
}

CPhyRemWcdmaFindCellReq::CPhyRemWcdmaFindCellReq(uarfcn_t* freq, uband_t band, bool freqUnlocked, u8 count)
{
    u8 i;
    m_Struct.count           = count;
    for(i = 0; i < count; i++)
    {
       m_Struct.frequency[i] = *freq; /*KS: List of freq to be*/
       freq++;
    }
    m_Struct.band            = band;
    m_Struct.freqUnlocked    = freqUnlocked;
}

s32 CPhyRemWcdmaFindCellReq::Serialise(u8 *data, u32 dataMaxBytes) const
{
    return CphyRemWcdmaFindCellReq_Serialise(&m_Struct, data, dataMaxBytes);
}

bool CPhyRemWcdmaFindCellReq::DeSerialise(const u8* data, u32 dataLen)
{
    if(CphyRemWcdmaFindCellReq_Deserialise(data, dataLen, &m_Struct) < 0)
        return false;
    else
        return true;
}

u32 CPhyRemWcdmaFindCellReq::GetStruct(CphyMessageData *const msg)
{
    msg->remWcdmaFindCellReq = &m_Struct;

    return GetSerialisationId();
}

void CPhyRemWcdmaFindCellReq::SetUarfcn(uarfcn_t f)
{
    m_Struct.frequency[0] = f;
}

uarfcn_t CPhyRemWcdmaFindCellReq::GetUarfcn(void) const
{
    return m_Struct.frequency[0];
}

void CPhyRemWcdmaFindCellReq::SetBand(uband_t b)
{
    m_Struct.band = b;
}

uband_t CPhyRemWcdmaFindCellReq::GetBand(void) const
{
    return m_Struct.band;
}

string CPhyRemWcdmaFindCellReq::ToString() const
{
    ostringstream stream;
    u8 i;

    stream << "CPhyRemWcdmaFindCellReq" << endl;
    stream << "{ count=" << (u32)m_Struct.count << endl;
    for(i = 0; i < m_Struct.count; i++)
    {
      stream << "  frequency=" << m_Struct.frequency[i] << endl;
    }
    stream << "  band=" << UmtsBandIdToString(m_Struct.band) << endl;
    stream << "  freqUnlocked=" << (u32)m_Struct.freqUnlocked << endl;
    stream << "}" << endl;

    return(stream.str());
}

string CPhyRemWcdmaFindCellReq::ToBriefString() const
{
    ostringstream stream;

    stream << "freq=" << m_Struct.frequency
           << " band=" << UmtsBandIdToString(m_Struct.band)
           << " freqUnlocked=" << (u32)m_Struct.freqUnlocked;

    return(stream.str());
}

extern "C"
{


s32 CphyRemWcdmaFindCellReq_Serialise(const CphyRemWcdmaFindCellReq *msg, u8 *const buffer, u32 maxLen)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyRemWcdmaFindCellReq))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(buffer, msg, sizeof(CphyRemWcdmaFindCellReq));
    return sizeof(CphyRemWcdmaFindCellReq);
}


s32 CphyRemWcdmaFindCellReq_Deserialise(const u8 *buffer, u32 maxLen, CphyRemWcdmaFindCellReq *const msg)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyRemWcdmaFindCellReq))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(msg, buffer, sizeof(CphyRemWcdmaFindCellReq));

    return sizeof(CphyRemWcdmaFindCellReq);
}

}

// END OF FILE
