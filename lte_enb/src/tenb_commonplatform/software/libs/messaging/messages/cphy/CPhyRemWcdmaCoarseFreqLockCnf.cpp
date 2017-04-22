///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyRemWcdmaCoarseFreqLockCnf.cpp 28519 2010-07-21 14:39:46Z mmcternan $
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

#include "CPhyRemWcdmaCoarseFreqLockCnf.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CPhyRemWcdmaCoarseFreqLockCnf::CPhyRemWcdmaCoarseFreqLockCnf(const CphyRemWcdmaCoarseFreqLockCnf *msg)
{
    m_Struct = *msg;
}

s32 CPhyRemWcdmaCoarseFreqLockCnf::Serialise(u8 *data, u32 dataMaxBytes) const
{
    return CphyRemWcdmaCoarseFreqLockCnf_Serialise(&m_Struct, data, dataMaxBytes);
}

bool CPhyRemWcdmaCoarseFreqLockCnf::DeSerialise(const u8* data, u32 dataLen)
{
    if(CphyRemWcdmaCoarseFreqLockCnf_Deserialise(data, dataLen, &m_Struct) < 0)
        return false;
    else
        return true;
}

u32 CPhyRemWcdmaCoarseFreqLockCnf::GetStruct(CphyMessageData *const msg)
{
    msg->remWcdmaCoarseFreqLockCnf = &m_Struct;

    return GetSerialisationId();
}

string CPhyRemWcdmaCoarseFreqLockCnf::ToString() const
{
    ostringstream stream;

    stream << "CPhyRemWcdmaCoarseFreqLockCnf " << endl;
    stream << "{ status= " << CphyL1StatusToString(m_Struct.status) << endl;
    stream << "  afcDacValue=" << m_Struct.afcDacValue << endl;
    stream << "}" << endl;

    return(stream.str());
}

string CPhyRemWcdmaCoarseFreqLockCnf::ToBriefString() const
{
    ostringstream stream;

    stream << "status=" << CphyL1StatusToString(m_Struct.status)
           << " afcDacValue=" << m_Struct.afcDacValue;

    return(stream.str());
}

extern "C"
{


s32 CphyRemWcdmaCoarseFreqLockCnf_Serialise(const CphyRemWcdmaCoarseFreqLockCnf *msg, u8 *const buffer, u32 maxLen)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyRemWcdmaCoarseFreqLockCnf))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(buffer, msg, sizeof(CphyRemWcdmaCoarseFreqLockCnf));
    return sizeof(CphyRemWcdmaCoarseFreqLockCnf);
}


s32 CphyRemWcdmaCoarseFreqLockCnf_Deserialise(const u8 *buffer, u32 maxLen, CphyRemWcdmaCoarseFreqLockCnf *const msg)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyRemWcdmaCoarseFreqLockCnf))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(msg, buffer, sizeof(CphyRemWcdmaCoarseFreqLockCnf));

    return sizeof(CphyRemWcdmaCoarseFreqLockCnf);
}

}

// END OF FILE
