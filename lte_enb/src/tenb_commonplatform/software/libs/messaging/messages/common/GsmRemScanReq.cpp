///////////////////////////////////////////////////////////////////////////////
//
// GsmRemScanReq.cpp
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <string>
#include <set>

#include <system/Trace.h>
#include <system/NumberConversions.h>
#include <system/SerialisationUtils.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "GsmRemScanReq.h"

using namespace threeway;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

GsmRemScanReq::GsmRemScanReq():m_numGsmDcsFreqsInserted(0),
                                         m_numPcsFreqsInserted(0),
                                         m_scanAllGsmDcs(false),
                                         m_scanAllPcs(false),
                                         m_wcdmaRemScanResult(REM_SCAN_RESULT_NOT_YET_PERFORMED),
                                         m_rssiScanLowerLimit(DEFAULT_RSSI_SCAN_LOWER_LIMIT),
                                         m_numCellsToReport(DEFAULT_NUM_CELLS_TO_REPORT),
                                         m_mcc(0),
                                         m_mnc(0),
                                         m_remScanType(GSM_REM_SCAN_FULL_NEIGHBOUR_CELL_SCAN),
                                         m_rejectNonOperatorCells(true),
                                         m_freqSyncTimeoutSecs(0),
                                         m_neighbourCellTimeoutSecs(0)

{
    memset(&m_gsm_dcs_Freqs, 0, sizeof(m_gsm_dcs_Freqs));
    memset(&m_pcs_Freqs, 0, sizeof(m_pcs_Freqs));
}

GsmRemScanReq::GsmRemScanReq(eRemScanType remScanTypeRequired):
        m_numGsmDcsFreqsInserted(0),
        m_numPcsFreqsInserted(0),
        m_scanAllGsmDcs(false),
        m_scanAllPcs(false),
        m_wcdmaRemScanResult(REM_SCAN_RESULT_NOT_YET_PERFORMED),
        m_rssiScanLowerLimit(DEFAULT_RSSI_SCAN_LOWER_LIMIT),
        m_numCellsToReport(DEFAULT_NUM_CELLS_TO_REPORT),
        m_mcc(0),
        m_mnc(0),
        m_remScanType(remScanTypeRequired),
        m_rejectNonOperatorCells(true),
        m_freqSyncTimeoutSecs(0),
        m_neighbourCellTimeoutSecs(0),
        m_oscDac(0)
{
    memset(&m_gsm_dcs_Freqs, 0, sizeof(m_gsm_dcs_Freqs));
    memset(&m_pcs_Freqs, 0, sizeof(m_pcs_Freqs));
}

void GsmRemScanReq::SetequivalentPlmnIds(u32 index,u32 mcc,u32 mnc)
{
    m_equivalentPlmnIds[index].m_equivMCC = mcc;
    m_equivalentPlmnIds[index].m_equivMNC = mnc;
}

bool GsmRemScanReq::AddAGsmDcsFreq(u32 freq)
{
    if(freq == ARFCN_VALUE_INDICATING_UNSET)
    {
        return false;
    }
    else
    {
        if(m_numGsmDcsFreqsInserted < NUM_GSM_DCS_FREQUENCIES)
        {
            m_gsm_dcs_Freqs[m_numGsmDcsFreqsInserted] = freq;
            m_numGsmDcsFreqsInserted++;
            return true;
        }
        else
        {
            return false;
        }
    }
}

bool GsmRemScanReq::AddAPcsFreq(u32 freq)
{
    if(freq == ARFCN_VALUE_INDICATING_UNSET)
    {
        return false;
    }
    else
    {
        if(m_numPcsFreqsInserted < NUM_PCS_FREQUENCIES)
        {
            m_pcs_Freqs[m_numPcsFreqsInserted] = freq;
            m_numPcsFreqsInserted++;
            return true;
        }
        else
        {
            return false;
        }
    }
}

s32 GsmRemScanReq::Serialise(u8* data, u32 dataMaxBytes) const
{
    // Complex message... fairly arbitrary test but should be plenty.  We validate this below.
    // This is more maintainable than trying to calculate the exact space requirement.
    static const u32 MAX_SERIALISED_BYTES = 2000;
    RSYS_ASSERT(dataMaxBytes >= MAX_SERIALISED_BYTES);

    u32 index;
    u8* pData = data;

    for(index = 0;index < NUM_GSM_DCS_FREQUENCIES;index++)
    {
        SerialiseIt(m_gsm_dcs_Freqs[index],pData);
    }

    SerialiseIt(m_numGsmDcsFreqsInserted,pData);

    SerialiseIt(m_scanAllGsmDcs,pData);

    for(index = 0;index < NUM_PCS_FREQUENCIES;index++)
    {
        SerialiseIt(m_pcs_Freqs[index],pData);
    }

    SerialiseIt(m_numPcsFreqsInserted,pData);

    SerialiseIt(m_scanAllPcs,pData);

    SerialiseIt(m_rssiScanLowerLimit, pData);

    SerialiseIt(m_numCellsToReport,pData);

    SerialiseIt((u32)m_wcdmaRemScanResult,pData);

    SerialiseIt(m_mcc,pData);

    SerialiseIt(m_mnc,pData);

    for(index = 0;index < NUM_EQUIVALENT_PLMN_IDS;index++)
    {
        SerialiseIt(((m_equivalentPlmnIds[index]).m_equivMCC),pData);
        SerialiseIt(((m_equivalentPlmnIds[index]).m_equivMNC),pData);
    }

    SerialiseIt((m_oscDac), pData);

    SerialiseIt((u32)m_remScanType,pData);

    SerialiseItU32Set(m_SImessagesToDecode,pData,(dataMaxBytes - (pData - data)));

    SerialiseIt(m_rejectNonOperatorCells,pData);
    SerialiseIt(m_freqSyncTimeoutSecs,pData);
    SerialiseIt(m_neighbourCellTimeoutSecs,pData);

    RSYS_ASSERT((u32)(pData - data) <= MAX_SERIALISED_BYTES);
    return (pData - data);
}

bool GsmRemScanReq::DeSerialise(const u8* data, u32 dataLen)
{
    u32 index;

    for(index = 0;index < NUM_GSM_DCS_FREQUENCIES;index++)
    {
        DeSerialiseIt(m_gsm_dcs_Freqs[index],data);
    }

    DeSerialiseIt(m_numGsmDcsFreqsInserted,data);

    DeSerialiseIt(m_scanAllGsmDcs,data);

    for(index = 0;index < NUM_PCS_FREQUENCIES;index++)
    {
        DeSerialiseIt(m_pcs_Freqs[index],data);
    }

    DeSerialiseIt(m_numPcsFreqsInserted,data);

    DeSerialiseIt(m_scanAllPcs,data);

    DeSerialiseIt(m_rssiScanLowerLimit, data);

    DeSerialiseIt(m_numCellsToReport,data);

    u32 tempEnumConvertor;
    DeSerialiseIt(tempEnumConvertor,data);
    m_wcdmaRemScanResult = (eRemScanResult)tempEnumConvertor;

    DeSerialiseIt(m_mcc,data);

    DeSerialiseIt(m_mnc,data);

    for(index = 0;index < NUM_EQUIVALENT_PLMN_IDS;index++)
    {
        DeSerialiseIt(((m_equivalentPlmnIds[index]).m_equivMCC),data);
        DeSerialiseIt(((m_equivalentPlmnIds[index]).m_equivMNC),data);
    }

    DeSerialiseIt(m_oscDac, data);

    DeSerialiseIt(tempEnumConvertor,data);
    m_remScanType = (eRemScanType)tempEnumConvertor;

    DeSerialiseItU32Set(m_SImessagesToDecode,data,GSMBCCHMessage::NUM_SI_MESSAGES);

    DeSerialiseIt(m_rejectNonOperatorCells,data);
    DeSerialiseIt(m_freqSyncTimeoutSecs,data);
    DeSerialiseIt(m_neighbourCellTimeoutSecs,data);

    return true;
}

string GsmRemScanReq::ToString() const
{
    ostringstream stream;
    u32 index;

    stream << "OSC DAC = " << m_oscDac << endl << endl;

    for(index = 0;index < m_numPcsFreqsInserted;index++)
    {
        stream << "PCS freq " << index << " = " << m_pcs_Freqs[index] << endl;
    }

    stream << "Scan all GSM/DCs = " << m_scanAllGsmDcs << "  Scan all PCSs = " << m_scanAllPcs << " m_wcdmaRemScanResult = " << m_wcdmaRemScanResult << endl ;

    u32 arfcnIndex;
    for(arfcnIndex = 0; arfcnIndex < m_numGsmDcsFreqsInserted;arfcnIndex++)
    {
        stream << "DCS GSM freq " << arfcnIndex << " = " << m_gsm_dcs_Freqs[arfcnIndex] << endl;
    }

    for(arfcnIndex = 0; arfcnIndex < m_numPcsFreqsInserted;arfcnIndex++)
    {
        stream << "PCS freq " << index << " = " <<  m_pcs_Freqs[arfcnIndex] << endl;
    }

    stream << "Scan all GSM/DCs = " << m_scanAllGsmDcs << "  Scan all PCSs = " << m_scanAllPcs << " m_wcdmaRemScanResult = " << m_wcdmaRemScanResult << endl ;

    stream << "GetRssiScanLowerLimit  =  " << m_rssiScanLowerLimit << endl;

    stream << "m_rejectNonOperatorCells = " << m_rejectNonOperatorCells << endl;

    for(u32 plmnIdIndex = 0; plmnIdIndex < GsmRemScanReq::NUM_EQUIVALENT_PLMN_IDS; plmnIdIndex++)
    {
        stream << "equivalent PLMN id " << plmnIdIndex << " mcc = " << (m_equivalentPlmnIds[plmnIdIndex]).m_equivMCC << " mnc = " << (m_equivalentPlmnIds[plmnIdIndex]).m_equivMNC << endl;
    }

    for (std::set<u8>::iterator it = m_SImessagesToDecode.begin();(it != m_SImessagesToDecode.end());it++)
    {
        stream << "scan SI type? " << (u32)(*it) << endl;
    }

    stream << "mcc = " << m_mcc << "mnc = " << m_mnc << endl;

    stream << "Rem Scan Type = " << m_remScanType << endl;

    stream << "m_freqSyncTimeoutSecs = " << m_freqSyncTimeoutSecs << endl;

    stream << "m_neighbourCellTimeoutSecs" << m_neighbourCellTimeoutSecs << endl;

    return stream.str();
}
