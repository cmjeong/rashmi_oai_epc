///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyRemGsmRssiScanReq.cpp 5567 2008-05-30 11:13:47Z mm $
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

#include "CPhyRemGsmRssiScanReq.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// MibParam Class Functions
///////////////////////////////////////////////////////////////////////////////

CPhyRemGsmRssiScanReq::CPhyRemGsmRssiScanReq(const CphyRemGsmRssiScanReq *cStruct)
{
    m_Struct = *cStruct;
}

CPhyRemGsmRssiScanReq::CPhyRemGsmRssiScanReq(arfcn_t freq, band_t band)
{
    m_Struct.frequency[0] = freq;
    m_Struct.nFrequencies = 1;
    m_Struct.band         = band;
}

CPhyRemGsmRssiScanReq::CPhyRemGsmRssiScanReq(band_t band)
{
#ifdef USE_CHMAP
   m_Struct.nFrequencies = ChMapPopulateGsmRaster(band,
         m_Struct.frequency,
         MAX_REM_GSM_RSSI_SCAN_FREQS);
#else
   u16 t;

   m_Struct.nFrequencies = 0;

   // Populate frequency raster for the Band
   switch(band)
   {
      case BAND_GSM900:

         for(t = 0; t <= 125; t++)
         {
            if(m_Struct.nFrequencies < MAX_REM_GSM_RSSI_SCAN_FREQS)
            {
               m_Struct.frequency[m_Struct.nFrequencies++] = t;
            }
         }

         for(t = 975; t <= 1023; t++)
         {
            if(m_Struct.nFrequencies < MAX_REM_GSM_RSSI_SCAN_FREQS)
            {
               m_Struct.frequency[m_Struct.nFrequencies++] = t;
            }
         }
         break;

      case BAND_DCS1800:

         for(t = 512; t <= 885; t++)
         {
            m_Struct.frequency[m_Struct.nFrequencies++] = t;
         }
         break;

      case BAND_PCS1900:
      default:
         RSYS_ASSERT_PRINTF(false, "Unsupported band: %u", band);
         break;
   }
#endif
   // Store the band
   m_Struct.band = band;
}

s32 CPhyRemGsmRssiScanReq::Serialise(u8 *data, u32 dataMaxBytes) const
{
    return CphyRemGsmRssiScanReq_Serialise(&m_Struct, data, dataMaxBytes);
}

bool CPhyRemGsmRssiScanReq::DeSerialise(const u8* data, u32 dataLen)
{
    if(CphyRemGsmRssiScanReq_Deserialise(data, dataLen, &m_Struct) < 0)
        return false;
    else
        return true;
}

u32 CPhyRemGsmRssiScanReq::GetStruct(CphyMessageData *const msg)
{
    msg->remGsmRssiScanReq = &m_Struct;

    return GetSerialisationId();
}

void CPhyRemGsmRssiScanReq::AddArfcn(arfcn_t f)
{
    RSYS_ASSERT_PRINTF((m_Struct.nFrequencies < MAX_REM_GSM_RSSI_SCAN_FREQS), "Arfcn = %d, nFreq = %d, band = %d",f, (m_Struct.nFrequencies), (m_Struct.band));

    m_Struct.frequency[m_Struct.nFrequencies] = f;
    m_Struct.nFrequencies++;
}

void CPhyRemGsmRssiScanReq::SetBand(band_t b)
{
    m_Struct.band = b;
}

band_t CPhyRemGsmRssiScanReq::GetBand(void) const
{
    return m_Struct.band;
}

string CPhyRemGsmRssiScanReq::ToString() const
{
    ostringstream stream;
    u16 t;

    stream << "CPhyRemGsmRssiScanReq" << endl;
    stream << "nFrequencies = " << m_Struct.nFrequencies << endl;
    stream << "{ frequency={ ";
    for(t = 0; t < m_Struct.nFrequencies && t < MAX_REM_GSM_RSSI_SCAN_FREQS; t++)
    {
        stream << m_Struct.frequency[t] << " ";
    }
    stream << " }" << endl;
    stream << "  band=" << CphyBandToString(m_Struct.band) << endl;
    stream << "}" << endl;

    return(stream.str());
}

string CPhyRemGsmRssiScanReq::ToBriefString() const
{
    ostringstream stream;

    stream << "nFrequencies=" << m_Struct.nFrequencies
           << "  band=" << CphyBandToString(m_Struct.band);

    return(stream.str());
}

extern "C"
{


s32 CphyRemGsmRssiScanReq_Serialise(const CphyRemGsmRssiScanReq *msg, u8 *const buffer, u32 maxLen)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyRemGsmRssiScanReq))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(buffer, msg, sizeof(CphyRemGsmRssiScanReq));
    return sizeof(CphyRemGsmRssiScanReq);
}


s32 CphyRemGsmRssiScanReq_Deserialise(const u8 *buffer, u32 maxLen, CphyRemGsmRssiScanReq *const msg)
{
    /* Check the buffer is large enough */
    if(maxLen < sizeof(CphyRemGsmRssiScanReq))
    {
        return -1;
    }

    /* Copy structure */
    memcpy(msg, buffer, sizeof(CphyRemGsmRssiScanReq));

    return sizeof(CphyRemGsmRssiScanReq);
}

}

// END OF FILE
