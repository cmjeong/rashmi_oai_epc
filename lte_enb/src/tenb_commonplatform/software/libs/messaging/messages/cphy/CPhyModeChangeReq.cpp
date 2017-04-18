///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyModeChangeReq.cpp 28519 2010-07-21 14:39:46Z mmcternan $
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
#include <string.h> // for memcpy

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "CPhyModeChangeReq.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CPhyModeChangeReq::CPhyModeChangeReq(const CphyModeChangeReq *cStruct)
{
    m_Struct = *cStruct;
}

CPhyModeChangeReq::CPhyModeChangeReq(const l1mode_t mode, 
                                        uint32_t maxCellSearchTime,
                                        uint32_t maxBcchDecTime,
                                        uint32_t maxRssiScanTime)
{
    m_Struct.mode = mode;
    m_Struct.maxCellSearchTime = maxCellSearchTime;
    m_Struct.maxBcchDecTime = maxBcchDecTime;
    m_Struct.maxRssiScanTime = maxRssiScanTime;
}

s32 CPhyModeChangeReq::Serialise(u8 *data, u32 dataMaxBytes) const
{
    return CphyModeChangeReq_Serialise(&m_Struct, data, dataMaxBytes);
}

bool CPhyModeChangeReq::DeSerialise(const u8* data, u32 dataLen)
{
    if(CphyModeChangeReq_Deserialise(data, dataLen, &m_Struct) < 0)
        return false;
    else
        return true;
}

u32 CPhyModeChangeReq::GetStruct(CphyMessageData *const msg)
{
    msg->modeChangeReq = &m_Struct;

    return GetSerialisationId();
}

string CPhyModeChangeReq::ToString() const
{
    ostringstream stream;

    stream << "CphyModeChangeReq" << endl;
    stream << "{ mode=" << CphyL1ModeToString(m_Struct.mode) << endl;
    stream << "}" << endl;

    return(stream.str());
}

string CPhyModeChangeReq::ToBriefString() const
{
    ostringstream stream;

    stream << "mode=" << CphyL1ModeToString(m_Struct.mode);

    return(stream.str());
}

extern "C"
{


s32 CphyModeChangeReq_Serialise(const CphyModeChangeReq *msg, u8 *const buffer, u32 maxLen)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyModeChangeReq))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(buffer, msg, sizeof(CphyModeChangeReq));
    return sizeof(CphyModeChangeReq);
}


s32 CphyModeChangeReq_Deserialise(const u8 *buffer, u32 maxLen, CphyModeChangeReq *const msg)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyModeChangeReq))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(msg, buffer, sizeof(CphyModeChangeReq));

    return sizeof(CphyModeChangeReq);
}

}

// END OF FILE
