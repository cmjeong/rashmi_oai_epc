///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyRemWcdmaFreqOffsetMeasReq.cpp 28519 2010-07-21 14:39:46Z mmcternan $
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

#include "CPhyRemWcdmaFreqOffsetMeasReq.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CPhyRemWcdmaFreqOffsetMeasReq::CPhyRemWcdmaFreqOffsetMeasReq(upsc_t psc,
                                                             bool   updateDac,
                                                             bool   freqUnlocked)
{
    m_Struct.psc          = psc;
    m_Struct.updateDac    = updateDac;
    m_Struct.freqUnlocked = freqUnlocked;
}

s32 CPhyRemWcdmaFreqOffsetMeasReq::Serialise(u8 *data, u32 dataMaxBytes) const
{
    return CphyRemWcdmaFreqOffsetMeasReq_Serialise(&m_Struct, data, dataMaxBytes);
}

bool CPhyRemWcdmaFreqOffsetMeasReq::DeSerialise(const u8* data, u32 dataLen)
{
    if(CphyRemWcdmaFreqOffsetMeasReq_Deserialise(data, dataLen, &m_Struct) < 0)
        return false;
    else
        return true;
}

u32 CPhyRemWcdmaFreqOffsetMeasReq::GetStruct(CphyMessageData *const msg)
{
    msg->remWcdmaFreqOffsetMeasReq = &m_Struct;

    return GetSerialisationId();
}

string CPhyRemWcdmaFreqOffsetMeasReq::ToString() const
{
    ostringstream stream;

    stream << "CPhyRemWcdmaFreqOffsetMeasReq" << endl;
    stream << "{ psc=" << m_Struct.psc << endl;
    stream << "  updateDac=" << (u32)m_Struct.updateDac << endl;
    stream << "  freqUnlocked=" << (u32)m_Struct.freqUnlocked << endl;
    stream << "}" << endl;

    return(stream.str());
}

string CPhyRemWcdmaFreqOffsetMeasReq::ToBriefString() const
{
    ostringstream stream;

    stream << "psc=" << m_Struct.psc
           << " updateDac=" << (u32)m_Struct.updateDac
           << " freqUnlocked=" << (u32)m_Struct.freqUnlocked;

    return(stream.str());
}

extern "C"
{


s32 CphyRemWcdmaFreqOffsetMeasReq_Serialise(const CphyRemWcdmaFreqOffsetMeasReq *msg, u8 *const buffer, u32 maxLen)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyRemWcdmaFreqOffsetMeasReq))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(buffer, msg, sizeof(CphyRemWcdmaFreqOffsetMeasReq));
    return sizeof(CphyRemWcdmaFreqOffsetMeasReq);
}


s32 CphyRemWcdmaFreqOffsetMeasReq_Deserialise(const u8 *buffer, u32 maxLen, CphyRemWcdmaFreqOffsetMeasReq *const msg)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyRemWcdmaFreqOffsetMeasReq))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(msg, buffer, sizeof(CphyRemWcdmaFreqOffsetMeasReq));

    return sizeof(CphyRemWcdmaFreqOffsetMeasReq);
}

}

// END OF FILE
