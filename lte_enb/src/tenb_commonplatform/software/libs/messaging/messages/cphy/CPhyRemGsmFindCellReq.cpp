///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyRemGsmFindCellReq.cpp 28519 2010-07-21 14:39:46Z mmcternan $
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

#include "CPhyRemGsmFindCellReq.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CPhyRemGsmFindCellReq::CPhyRemGsmFindCellReq(const CphyRemGsmFindCellReq *msg)
{
    m_Struct = *msg;
}

s32 CPhyRemGsmFindCellReq::Serialise(u8 *data, u32 dataMaxBytes) const
{
    return CphyRemGsmFindCellReq_Serialise(&m_Struct, data, dataMaxBytes);
}

bool CPhyRemGsmFindCellReq::DeSerialise(const u8* data, u32 dataLen)
{
    if(CphyRemGsmFindCellReq_Deserialise(data, dataLen, &m_Struct) < 0)
        return false;
    else
        return true;
}

CPhyRemGsmFindCellReq::CPhyRemGsmFindCellReq(uarfcn_t arfcn, band_t band, updateOscMode_t updateDacMode)
{
    m_Struct.arfcn[0]         = arfcn;
    m_Struct.band          = band;
    m_Struct.updateDacMode = updateDacMode;
}

CPhyRemGsmFindCellReq::CPhyRemGsmFindCellReq()
{
   memset(&m_Struct, 0, sizeof(m_Struct));
}

u32 CPhyRemGsmFindCellReq::GetStruct(CphyMessageData *const msg)
{
    msg->remGsmFindCellReq = &m_Struct;

    return GetSerialisationId();
}

string CPhyRemGsmFindCellReq::ToString() const
{
    ostringstream stream;

    stream << "CPhyRemGsmFindCellReq " << endl;
    stream << "{ arfcn= " << (u16)m_Struct.arfcn[0] << endl;
    stream << "  band = " << CphyBandToString(m_Struct.band) << endl;
    stream << "  updateDacMode= " << (u16)m_Struct.updateDacMode << endl;
    stream << "}" << endl;

    return(stream.str());
}

string CPhyRemGsmFindCellReq::ToBriefString() const
{
    ostringstream stream;

    stream << "arfcn=" << (u16)m_Struct.arfcn[0]
           << " band=" << CphyBandToString(m_Struct.band)
           << " updateDacMode=" << (u16)m_Struct.updateDacMode;

    return(stream.str());
}

extern "C"
{


s32 CphyRemGsmFindCellReq_Serialise(const CphyRemGsmFindCellReq *msg, u8 *const buffer, u32 maxLen)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyRemGsmFindCellReq))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(buffer, msg, sizeof(CphyRemGsmFindCellReq));
    return sizeof(CphyRemGsmFindCellReq);
}


s32 CphyRemGsmFindCellReq_Deserialise(const u8 *buffer, u32 maxLen, CphyRemGsmFindCellReq *const msg)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyRemGsmFindCellReq))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(msg, buffer, sizeof(CphyRemGsmFindCellReq));
    return sizeof(CphyRemGsmFindCellReq);
}

}

// END OF FILE
