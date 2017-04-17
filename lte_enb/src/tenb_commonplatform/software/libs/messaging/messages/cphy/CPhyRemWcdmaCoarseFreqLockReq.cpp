///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyRemWcdmaCoarseFreqLockReq.cpp 28519 2010-07-21 14:39:46Z mmcternan $
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

#include "CPhyRemWcdmaCoarseFreqLockReq.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CPhyRemWcdmaCoarseFreqLockReq::CPhyRemWcdmaCoarseFreqLockReq(u16      afcDacCentre,
                                                             uband_t  band,
                                                             uarfcn_t frequency,
                                                             bool     updateDac)
{
    m_Struct.afcDacCentre         = afcDacCentre;
    m_Struct.band                 = band;
    m_Struct.frequency            = frequency;
    m_Struct.updateDac            = updateDac;
}

s32 CPhyRemWcdmaCoarseFreqLockReq::Serialise(u8 *data, u32 dataMaxBytes) const
{
    return CphyRemWcdmaCoarseFreqLockReq_Serialise(&m_Struct, data, dataMaxBytes);
}

bool CPhyRemWcdmaCoarseFreqLockReq::DeSerialise(const u8* data, u32 dataLen)
{
    if(CphyRemWcdmaCoarseFreqLockReq_Deserialise(data, dataLen, &m_Struct) < 0)
        return false;
    else
        return true;
}

u32 CPhyRemWcdmaCoarseFreqLockReq::GetStruct(CphyMessageData *const msg)
{
    msg->remWcdmaCoarseFreqLockReq = &m_Struct;

    return GetSerialisationId();
}

string CPhyRemWcdmaCoarseFreqLockReq::ToString() const
{
    ostringstream stream;

    stream << "CPhyRemWcdmaCoarseFreqLockReq " << endl;
    stream << "{ frequency= " << m_Struct.frequency << endl;
    stream << "  band=" << UmtsBandIdToString(m_Struct.band) << endl;
    stream << "  afcDacCentre=" << m_Struct.afcDacCentre << endl;
    stream << "}" << endl;

    return(stream.str());
}

string CPhyRemWcdmaCoarseFreqLockReq::ToBriefString() const
{
    ostringstream stream;

    stream << "freq=" << m_Struct.frequency
           << " band=" << UmtsBandIdToString(m_Struct.band)
           << " afcDacCentre=" << m_Struct.afcDacCentre;

    return(stream.str());
}


extern "C"
{


s32 CphyRemWcdmaCoarseFreqLockReq_Serialise(const CphyRemWcdmaCoarseFreqLockReq *msg, u8 *const buffer, u32 maxLen)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyRemWcdmaCoarseFreqLockReq))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(buffer, msg, sizeof(CphyRemWcdmaCoarseFreqLockReq));
    return sizeof(CphyRemWcdmaCoarseFreqLockReq);
}


s32 CphyRemWcdmaCoarseFreqLockReq_Deserialise(const u8 *buffer, u32 maxLen, CphyRemWcdmaCoarseFreqLockReq *const msg)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyRemWcdmaCoarseFreqLockReq))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(msg, buffer, sizeof(CphyRemWcdmaCoarseFreqLockReq));

    return sizeof(CphyRemWcdmaCoarseFreqLockReq);
}

}

// END OF FILE
