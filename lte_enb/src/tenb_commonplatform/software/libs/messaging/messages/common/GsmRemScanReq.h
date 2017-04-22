///////////////////////////////////////////////////////////////////////////////
//
// GsmRemScanReq.h
//
// TBD
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __GsmRemScanReq_h_
#define __GsmRemScanReq_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>
#include <string.h> // for memset
#include <set>
#include <messaging/messages/common/RemScanCnf.h>
#include <comms/GsmRemPDUs.h>


///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

typedef enum
{
    GSM_REM_SCAN_FREQUENCY_ONLY,
    GSM_REM_SCAN_FULL_NEIGHBOUR_CELL_SCAN
} eRemScanType;

typedef struct EquivalentPlmnId
{
    EquivalentPlmnId() : m_equivMCC(0), m_equivMNC(0) {}
    u32 m_equivMCC;
    u32 m_equivMNC;
} EquivalentPlmnId;

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class GsmRemScanReq : public threeway::Serialisable
{
public:

    static const u32 NUM_GSM_DCS_FREQUENCIES = 20;
    static const u32 NUM_PCS_FREQUENCIES = 20;
    static const u32 NUM_EQUIVALENT_PLMN_IDS = 15;
    static const u32 ARFCN_VALUE_INDICATING_UNSET = 0xFFFFFFFF;
    static const s32 DEFAULT_RSSI_SCAN_LOWER_LIMIT = -110;
    static const u32 DEFAULT_NUM_CELLS_TO_REPORT = 6;

    /**
     * Construction / destruction.
     */
    GsmRemScanReq();
    GsmRemScanReq(eRemScanType remScanTypeRequired);
    virtual ~GsmRemScanReq(){};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_GSM_REM_SCAN_REQ; }
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);


    bool AddAGsmDcsFreq(u32 freq);
    bool AddAPcsFreq(u32 freq);
    void SetScanAllGsmDcs(bool scanAllGsmDcs) {m_scanAllGsmDcs = scanAllGsmDcs;}
    void SetScanAllPcs(bool scanAllPcs) {m_scanAllPcs = scanAllPcs;}
    u32 GetGsmDcsFreqn(u32 index) {RSYS_ASSERT(index < NUM_GSM_DCS_FREQUENCIES); return m_gsm_dcs_Freqs[index];}
    u32 GetPcsFreqn(u32 index) {RSYS_ASSERT(index < NUM_PCS_FREQUENCIES); return m_pcs_Freqs[index];}
    bool GetScanAllGsmDcs() {return m_scanAllGsmDcs;}
    bool GetScanAllPcs() {return m_scanAllPcs;}
    void SetWcdmaRemScanSyncedOK(eRemScanResult wcdmaRemScanResult) {m_wcdmaRemScanResult = wcdmaRemScanResult;}
    eRemScanResult GetWcdmaRemScanSyncedOK(void) {return m_wcdmaRemScanResult;}
    u32 GetNumGsmDcsFreqs() {RSYS_ASSERT(m_numGsmDcsFreqsInserted <= NUM_GSM_DCS_FREQUENCIES); return m_numGsmDcsFreqsInserted;}
    u32 GetNumPcsFreqs() {RSYS_ASSERT(m_numPcsFreqsInserted <= NUM_PCS_FREQUENCIES); return m_numPcsFreqsInserted;}
    u32 GetNumCellsToReport() {return m_numCellsToReport;}
    void SetNumCellsToReport(u32 numCellsToReport) {m_numCellsToReport = numCellsToReport;}
    s16 GetRssiScanLowerLimit() {return m_rssiScanLowerLimit;}
    void SetRssiScanLowerLimit(s16 rssiScanLowerLimit) {m_rssiScanLowerLimit = rssiScanLowerLimit;}
    u32 GetOscDac() const { return m_oscDac; }
    void SetOscDac(u32 oscDac) { m_oscDac = oscDac; }
    void SetequivalentPlmnIds(u32 index,u32 mcc,u32 mnc);
    EquivalentPlmnId GetEquivPlmnId(u32 index) {RSYS_ASSERT(index < NUM_EQUIVALENT_PLMN_IDS); return m_equivalentPlmnIds[index];}
    void SetMCC(u32 mcc) {m_mcc = mcc;}
    void SetMNC(u32 mnc) {m_mnc = mnc;}
    u32 GetMCC(void) {return m_mcc;}
    u32 GetMNC(void) {return m_mnc;}
    eRemScanType GetScanType(void) {return m_remScanType;}
    void SetScanType(eRemScanType remScanType) {m_remScanType = remScanType;}
    void SetRejectNonOperatorCells(bool rejectNonOperatorCells) {m_rejectNonOperatorCells = rejectNonOperatorCells;}
    bool GetRejectNonOperatorCells(void) {return m_rejectNonOperatorCells;}
    std::set<u8>& GetSImessagesToDecode(void) {return m_SImessagesToDecode;}
    void SetfreqSyncTimeoutSecs(u32 freqSyncTimeoutSecs){m_freqSyncTimeoutSecs = freqSyncTimeoutSecs;}
    u32 GetfreqSyncTimeoutSecs(void){return m_freqSyncTimeoutSecs;}
    void SetneighbourCellTimeoutSecs(u32 neighbourCellTimeoutSecs){m_neighbourCellTimeoutSecs = neighbourCellTimeoutSecs;}
    u32 GetneighbourCellTimeoutSecs(void){return m_neighbourCellTimeoutSecs;}
    /**
     * Convert to string for debug.
     */
    virtual std::string ToString() const;

private:
    // The set of parameters to inform this entity about.
    /**
     * list of gsm/dcs frequencies to scan TODO replace with a set (probably)
     */
    u32 m_gsm_dcs_Freqs[NUM_GSM_DCS_FREQUENCIES];
    /**
     * number of hsm/dcs frequencies in teh pcs frequency list
     */
    u32 m_numGsmDcsFreqsInserted;
    /**
     * set this if we wish to scan all GSM/DCS arfcns. List of GSM/DCS arfcns must be empty
     */
    bool m_scanAllGsmDcs;
    /**
     * list of pcs frequencies to scan TODO replace with a set (probably)
     */
    u32 m_pcs_Freqs[NUM_PCS_FREQUENCIES];
    /**
     * number of pcs frequencies in teh pcs frequency list
     */
    u32 m_numPcsFreqsInserted;
    /**
     * set this if we wish to scan all PCS arfcns. List of PCS arfcns must be empty
     */
    bool m_scanAllPcs;
    /**
     * the result of the previous WCDMA rem-scan result
     */
    eRemScanResult m_wcdmaRemScanResult;
    /*
     * reject any cells whose RSSI value is worse than this value
     */
    s16 m_rssiScanLowerLimit;
    /*
     * Number of cells to report back
     */
    u32 m_numCellsToReport;
    /**
     * indicates whether we should reject cells that do not belong to us i.e. not on the list of EquivalentPlmnId. See below.
     */
    bool m_rejectNonOperatorCells;
    /*
     * list of EquivalentPlmnIds i.e. those that the operator owns and thus any scanned cells not on this list should be rejected TODO replace with a set (probably)
     */
    EquivalentPlmnId m_equivalentPlmnIds[NUM_EQUIVALENT_PLMN_IDS];

    /**
     * Oscillator DAC value (was in GsmHwConfigParams but we didn't use the rest of that struct)
     * TODO - why is this in this message?  And should it be live or factory value?
     */
    u32 m_oscDac;

    /**
     * the mcc of the fap
     */
    u32 m_mcc;
    /**
     * the mnc of the fap
     */
    u32 m_mnc;
    /**
     * What type of REM scan to do i.e. frequency cal or full neighbour cell
     */
    eRemScanType m_remScanType;
    /**
     * set of SI message types (the SIMessageType field in the BCCH) to be decoded
     */
    std::set<u8> m_SImessagesToDecode;

    /**
     * Timeout for frequency only scan in secs
     */
    u32 m_freqSyncTimeoutSecs;
    /**
     * Timeout for neighbour cell scan in secs
     */
    u32 m_neighbourCellTimeoutSecs;
};

#endif
