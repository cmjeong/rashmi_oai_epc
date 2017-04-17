///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyRemGsmRssiScanReq.h 5567 2008-05-30 11:13:47Z mm $
//
// CPhyRemGsmRssiScanReq message.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CPhyRemGsmRssiScanReq_h_
#define __CPhyRemGsmRssiScanReq_h_

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

///////////////////////////////////////////////////////////////////////////////
// Message Constants
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Message Structures
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

/** Do rssi scan on one or more ARFCNs.
 * \ingroup CPhyRemGsm
 */
typedef struct CphyRemGsmRssiScanReqTag
{
    /** The List of frequencies to search.
     *  ARFCN range for GSM & E-GSM: 0-124
     *  Thus maximum number of ARFCNs can be hold in this list is thus 125.
     */
    arfcn_t   frequency[MAX_REM_GSM_RSSI_SCAN_FREQS];

    /** Number of frequencies in the list.
     */
    uint16_t  nFrequencies;

    /** The band to search.
     *  Downlink frequency bands: E-GSM 900 (includes stardard GSM 900) and DCS 1800
     */
    band_t    band;

}
CphyRemGsmRssiScanReq;

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

/** Function to serialise a CphyRemGsmRssiScanReq structure to a buffer.
 * Serialisation of this message can be performed by this function.
 *
 * \param[in] msg         The message to serialise.
 * \param[in,out] buffer  The data buffer into which the data is serialised.
 * \param[in] maxLen       Pointer to size of \a buffer.
 * \returns  Either a negative error code, or the length of the data.
 */
s32 CphyRemGsmRssiScanReq_Serialise(const CphyRemGsmRssiScanReq *msg, u8 *const buffer, u32 maxLen);


/** Function to deserialise a CphyRemGsmRssiScanReq structure from some buffer
 * Deserialisation of this message can be performed by this function.
 *
 * \param[in]     buffer  The buffer into which the structure has been stored.
 * \param[in]     maxLen  Size of \a buffer[].
 * \param[in,out] msg     Pointer to structure for population with deserialised
 *                         message.
 * \returns Size of the deserialised message if successful, otherwise a
 *           negative error code.
 */
s32 CphyRemGsmRssiScanReq_Deserialise(const u8 *buffer, u32 maxLen, CphyRemGsmRssiScanReq *const msg);

#ifdef __cplusplus
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

namespace threeway
{

class CPhyRemGsmRssiScanReq : public CPhyMessage
{
public:
    /**
     * Construction / destruction.
     */
    CPhyRemGsmRssiScanReq() { memset(&m_Struct, 0, sizeof(m_Struct)); };
    CPhyRemGsmRssiScanReq(const CphyRemGsmRssiScanReq *msg);
    virtual ~CPhyRemGsmRssiScanReq() {};
    CPhyRemGsmRssiScanReq(arfcn_t freq, band_t band);
    CPhyRemGsmRssiScanReq(band_t band);

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32  GetSerialisationId() const { return SERIALISATION_ID_CPHY_REM_GSM_RSSI_SCAN_REQ; };
    virtual s32  Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    /**
     * Implement CphyMessage pure virtual.
     */
    virtual u32 GetStruct(CphyMessageData *const msg);

    bool IsMessageFull() {return (m_Struct.nFrequencies >= MAX_REM_GSM_RSSI_SCAN_FREQS);}
    void Reset() {m_Struct.nFrequencies = 0;}

    /**
     * Accessors.
     */
    void     AddArfcn(arfcn_t f);
    void     SetBand(band_t b);
    band_t   GetBand(void) const;
    uint8_t GetNumFreqs() {return m_Struct.nFrequencies;}

    arfcn_t GetFrequency(uint8_t n) const { return m_Struct.frequency[n]; }

    /**
     * Convert to string for debug.
     */
    virtual std::string ToString() const;
    virtual std::string ToBriefString() const;

private:

    /** Embedded C structure carrying parameters.
     */
    CphyRemGsmRssiScanReq m_Struct;
};

}

#endif // __cplusplus

#endif // __CPhyRemGsmRssiScanReq_h_
