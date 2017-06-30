///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyRemGsmFindCellReq.h 28519 2010-07-21 14:39:46Z mmcternan $
//
// CPhyRemGsmFindCellReq message.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CPhyRemGsmFindCellReq_h_
#define __CPhyRemGsmFindCellReq_h_

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
#define MAX_NUMBER_OF_ARFCN  32
///////////////////////////////////////////////////////////////////////////////
// Message Structures
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif



/** GSM cell search control.
 * This starts a GSM cell search and decode.  Once the search is complete a
 * CphyRemGsmFindCellCnf will return the results and if a cell is found, BCCH
 * decoding will automatically start.
 *
 * Setting \a updateDac causes the frequency offset measurement step of the
 * search to remove any frequency error by directly controlling the DAC.
 *
 * \ingroup CPhyRemGsm
 */
typedef struct CphyRemGsmFindCellReqTag
{
    /** Frequency on which to search for cells.
     * This gives a single ARFCN on which to search for GSM cells.
     */
    arfcn_t  arfcn[MAX_NUMBER_OF_ARFCN];

    /** The band to search.
     *  Downlink frequency bands: E-GSM 900 (includes stardard GSM 900) and DCS 1800
     */
    band_t   band;

    /** Signals whether we need to disable osc error measurement.
     * Just measure the error or measure and adjust the current osc dac value
     */
    updateOscMode_t     updateDacMode;

    /**Count with respect to the number of ARFCNs present in the req  
     */
    u8       count;
}
CphyRemGsmFindCellReq;

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

/** Function to serialise a CphyRemGsmFindCellReq structure to a buffer.
 * Serialisation of this message can be performed by this function.
 *
 * \param[in] msg         The message to serialise.
 * \param[in,out] buffer  The data buffer into which the data is serialised.
 * \param[in] maxLen       Pointer to size of \a buffer.
 * \returns  Either a negative error code, or the length of the data.
 */
s32 CphyRemGsmFindCellReq_Serialise(const CphyRemGsmFindCellReq *msg,
                                    u8 *const                  buffer,
                                    u32                        maxLen);


/** Function to deserialise a CphyRemGsmFindCellReq structure from a buffer.
 * Deserialisation of this message can be performed by this function.
 *
 * \param[in]     buffer  The buffer into which the structure has been stored.
 * \param[in]     maxLen  Size of \a buffer[].
 * \param[in,out] msg     Pointer to structure for population with deserialised
 *                         message.
 * \returns Size of the deserialised message if successful, otherwise a
 *           negative error code.
 */
s32 CphyRemGsmFindCellReq_Deserialise(const u8                  *buffer,
                                      u32                        maxLen,
                                      CphyRemGsmFindCellReq *const msg);

#ifdef __cplusplus
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

namespace threeway
{

class CPhyRemGsmFindCellReq : public CPhyMessage
{
public:
    /**
     * Construction / destruction.
     */
    //CPhyRemGsmFindCellReq() { memset(&m_Struct, 0, sizeof(m_Struct)); };
    CPhyRemGsmFindCellReq();
    CPhyRemGsmFindCellReq(const CphyRemGsmFindCellReq *msg);
    virtual ~CPhyRemGsmFindCellReq() {};
    CPhyRemGsmFindCellReq(uarfcn_t arfcn, band_t band, updateOscMode_t updateDacMode);

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32  GetSerialisationId() const { return SERIALISATION_ID_CPHY_REM_GSM_FIND_CELL_REQ; };
    virtual s32  Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    /**
     * Implement CPhyMessage pure virtual.
     */
    virtual u32 GetStruct(CphyMessageData *const msg);

    /**
     * Accessors.
     */
    arfcn_t  GetArfcn() {return m_Struct.arfcn[0];}
    band_t   GetBand(){return m_Struct.band;}

    /**
     * Convert to string for debug.
     */
    virtual std::string ToString() const;
    virtual std::string ToBriefString() const;

private:

    /** Embedded C structure carrying parameters.
     */
    CphyRemGsmFindCellReq m_Struct;
};

}

#endif // __cplusplus

#endif // __CPhyHwConfigReq_h_
