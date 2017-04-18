///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyRemGsmRssiScanCnf.cpp 5567 2008-05-30 11:13:47Z mm $
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
#include <system/Trace.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "CPhyRemGsmRssiScanCnf.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CPhyRemGsmRssiScanCnf::CPhyRemGsmRssiScanCnf(const CphyRemGsmRssiScanCnf *cStruct)
{
    m_Struct = *cStruct;
}

s32 CPhyRemGsmRssiScanCnf::Serialise(u8 *data, u32 dataMaxBytes) const
{
    return CphyRemGsmRssiScanCnf_Serialise(&m_Struct, data, dataMaxBytes);
}

bool CPhyRemGsmRssiScanCnf::DeSerialise(const u8* data, u32 dataLen)
{
    if(CphyRemGsmRssiScanCnf_Deserialise(data, dataLen, &m_Struct) < 0)
        return false;
    else
        return true;
}

u32 CPhyRemGsmRssiScanCnf::GetStruct(CphyMessageData *const msg)
{
    msg->remGsmRssiScanCnf = &m_Struct;

    return GetSerialisationId();
}

string CPhyRemGsmRssiScanCnf::ToString() const
{
    ostringstream stream;
    u16 t;

    RSYS_ASSERT(m_Struct.numCells <= MAX_REM_GSM_RSSI_SCAN_FREQS);

    stream << "CphyRemGsmRssiScanCnf" << endl;
    stream << "{ frequency[" << m_Struct.numCells << "]={ ";

    for(t = 0; t < m_Struct.numCells; t++)
    {
        if(t != 0) stream << "                   ";
        stream << m_Struct.frequency[t] << " =";
        stream << ((m_Struct.rssi[t]) / 8.0f) << "dBm";
        if(t == m_Struct.numCells - 1) stream << "}";
        stream << endl;
    }

    stream << "  band=" << CphyBandToString(m_Struct.band) << endl;
    stream << "}" << endl;

    return(stream.str());
}

string CPhyRemGsmRssiScanCnf::ToBriefString() const
{
    ostringstream stream;

    stream << "nFreq=" << m_Struct.numCells
           << " band=" << CphyBandToString(m_Struct.band);

    return(stream.str());
}

extern "C"
{


s32 CphyRemGsmRssiScanCnf_Serialise(const CphyRemGsmRssiScanCnf *msg, u8 *const buffer, u32 maxLen)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyRemGsmRssiScanCnf))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(buffer, msg, sizeof(CphyRemGsmRssiScanCnf));
    return sizeof(CphyRemGsmRssiScanCnf);
}


s32 CphyRemGsmRssiScanCnf_Deserialise(const u8 *buffer, u32 maxLen, CphyRemGsmRssiScanCnf *const msg)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyRemGsmRssiScanCnf))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(msg, buffer, sizeof(CphyRemGsmRssiScanCnf));

    return sizeof(CphyRemGsmRssiScanCnf);
}

}

// END OF FILE
