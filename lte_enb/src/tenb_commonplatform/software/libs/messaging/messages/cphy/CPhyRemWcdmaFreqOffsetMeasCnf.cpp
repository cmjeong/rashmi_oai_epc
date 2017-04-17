///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyRemWcdmaFreqOffsetMeasCnf.cpp 28519 2010-07-21 14:39:46Z mmcternan $
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

#include "CPhyRemWcdmaFreqOffsetMeasCnf.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CPhyRemWcdmaFreqOffsetMeasCnf::CPhyRemWcdmaFreqOffsetMeasCnf(const CphyRemWcdmaFreqOffsetMeasCnf *msg)
{
    m_Struct = *msg;
}

s32 CPhyRemWcdmaFreqOffsetMeasCnf::Serialise(u8 *data, u32 dataMaxBytes) const
{
    return CphyRemWcdmaFreqOffsetMeasCnf_Serialise(&m_Struct, data, dataMaxBytes);
}

bool CPhyRemWcdmaFreqOffsetMeasCnf::DeSerialise(const u8* data, u32 dataLen)
{
    if(CphyRemWcdmaFreqOffsetMeasCnf_Deserialise(data, dataLen, &m_Struct) < 0)
        return false;
    else
        return true;
}

u32 CPhyRemWcdmaFreqOffsetMeasCnf::GetStruct(CphyMessageData *const msg)
{
    msg->remWcdmaFreqOffsetMeasCnf = &m_Struct;

    return GetSerialisationId();
}

string CPhyRemWcdmaFreqOffsetMeasCnf::ToString() const
{
    ostringstream stream;

    stream << "CPhyRemWcdmaFreqOffsetMeasCnf " << endl;
    stream << "{ status=" << CphyL1StatusToString(m_Struct.status) << endl;
    stream << "  psc= " << m_Struct.psc << endl;
    stream << "  dacVal=" << m_Struct.dacVal << endl;
    stream << "}" << endl;

    return(stream.str());
}

string CPhyRemWcdmaFreqOffsetMeasCnf::ToBriefString() const
{
    ostringstream stream;

    stream << "status=" << CphyL1StatusToString(m_Struct.status)
           << " psc=" << m_Struct.psc
           << " dacVal=" << m_Struct.dacVal;

    return(stream.str());
}


extern "C"
{


s32 CphyRemWcdmaFreqOffsetMeasCnf_Serialise(const CphyRemWcdmaFreqOffsetMeasCnf *msg, u8 *const buffer, u32 maxLen)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyRemWcdmaFreqOffsetMeasCnf))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(buffer, msg, sizeof(CphyRemWcdmaFreqOffsetMeasCnf));
    return sizeof(CphyRemWcdmaFreqOffsetMeasCnf);
}


s32 CphyRemWcdmaFreqOffsetMeasCnf_Deserialise(const u8 *buffer, u32 maxLen, CphyRemWcdmaFreqOffsetMeasCnf *const msg)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyRemWcdmaFreqOffsetMeasCnf))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(msg, buffer, sizeof(CphyRemWcdmaFreqOffsetMeasCnf));

    return sizeof(CphyRemWcdmaFreqOffsetMeasCnf);
}

}

// END OF FILE
