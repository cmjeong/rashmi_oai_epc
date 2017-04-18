///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyRemGsmRssiScanCnf.h 5567 2008-05-30 11:13:47Z mm $
//
// CPhyRemGsmRssiScanCnf message.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CPhyRemGsmRssiScanCnf_h_
#define __CPhyRemGsmRssiScanCnf_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
#include <string.h> // for memset
#endif
#include <system/SerialisationIds.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "CPhyTypes.h"
#include "CPhyMessage.h"
#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Message Constants
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Message Structures
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

/** Response to a CphyRemGsmRssiScanReq.
 * \ingroup CPhyRemGsm
 * Sent in response to a CphyRemGsmRssiScanReq, this returns the count of frequencies
 * that have been identified, as well as their identity and basic signal
 * strength measurements.
 */
typedef struct CphyRemGsmRssiScanCnfTag
{
    /** Status code.
     * Normally indicates a sucessful search, but may also indicate errors
     * such as an unsupported band or frequency, or the number of frequencies
     * to scan exceeds maximum supported value.
     */
    l1status_t status;

    /** Count of how many frequencies were scanned.
     */
    uint16_t numCells;

    /** The arfcns that were scanned.
     */
    uint16_t frequency[MAX_REM_GSM_RSSI_SCAN_FREQS];

    /** Wideband signal strength indication for the scanned frequency in dBm.
     */
    int16_t rssi[MAX_REM_GSM_RSSI_SCAN_FREQS];

    /** The band that was scanned.
     *  Downlink frequency bands: E-GSM 900 (includes stardard GSM 900) and DCS 1800
     */
    band_t  band;
}
CphyRemGsmRssiScanCnf;

#ifdef __cplusplus
}
#endif


///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Functions
///////////////////////////////////////////////////////////////////////////////


#ifdef __cplusplus
extern "C" {
#endif

/** Function to serialise a CphyRemGsmRssiScanCnf structure to a buffer.
 * Serialisation of this message can be performed by this function.
 *
 * \param[in] msg         The message to serialise.
 * \param[in,out] buffer  The data buffer into which the data is serialised.
 * \param[in] maxLen       Pointer to size of \a buffer.
 * \returns  Either a negative error code, or the length of the data.
 */
s32 CphyRemGsmRssiScanCnf_Serialise(const CphyRemGsmRssiScanCnf *msg, u8 *const buffer, u32 maxLen);


/** Function to deserialise a CphyRemGsmRssiScanCnf structure from some buffer
 * Deserialisation of this message can be performed by this function.
 *
 * \param[in]     buffer  The buffer into which the structure has been stored.
 * \param[in]     maxLen  Size of \a buffer[].
 * \param[in,out] msg     Pointer to structure for population with deserialised
 *                         message.
 * \returns Size of the deserialised message if successful, otherwise a
 *           negative error code.
 */
s32 CphyRemGsmRssiScanCnf_Deserialise(const u8 *buffer, u32 maxLen, CphyRemGsmRssiScanCnf *const msg);

#ifdef __cplusplus
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

namespace threeway
{

class CPhyRemGsmRssiScanCnf : public CPhyMessage
{
public:
    /**
     * Construction / destruction.
     */
    CPhyRemGsmRssiScanCnf() { memset(&m_Struct, 0, sizeof(m_Struct)); };
    CPhyRemGsmRssiScanCnf(const CphyRemGsmRssiScanCnf *cStruct);
    virtual ~CPhyRemGsmRssiScanCnf() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32  GetSerialisationId() const { return SERIALISATION_ID_CPHY_REM_GSM_RSSI_SCAN_CNF; };
    virtual s32  Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    /**
     * Implement CphyMessage pure virtual.
     */
    virtual u32 GetStruct(CphyMessageData *const msg);

    /**
     * Accessors.
     */
     l1status_t GetStatus() const { return m_Struct.status; }

     /** Count of how many arfcn were found. */
     //restricted to MAX_REM_GSM_RSSI_SCAN_FREQS to keep Cockwork happy
     uint16_t  GetNumCells() const { RSYS_ASSERT(m_Struct.numCells <= MAX_REM_GSM_RSSI_SCAN_FREQS); return m_Struct.numCells; }

     /** The frequency that was searched. */

     arfcn_t GetFrequency(uint16_t n) const { return m_Struct.frequency[n]; }

     /** The band that was searched. */
     band_t  GetBand() const { return m_Struct.band; }

     /** Wideband signal strength indication for the searched frequency. */
     int16_t GetRssi(uint16_t n) const { return m_Struct.rssi[n]; }

    /**
     * Convert to string for debug.
     */
    virtual std::string ToString() const;
    virtual std::string ToBriefString() const;

private:

    /** Embedded C structure carrying parameters.
     */
    CphyRemGsmRssiScanCnf m_Struct;
};

}

#endif /* __cplusplus */

#endif
