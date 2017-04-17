///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyRemWcdmaFreqOffsetMeasReq.h 28519 2010-07-21 14:39:46Z mmcternan $
//
// CPhyRemWcdmaFreqOffsetMeasReq message.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CPhyRemWcdmaFreqOffsetMeasReq_h_
#define __CPhyRemWcdmaFreqOffsetMeasReq_h_

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

/** Measure and optionally cancel frequency offset against some cell.
 * This requests that the frequency offset between the baseband oscillator and
 * some cell is measured and optionally cancelled by adjusting the osciallator
 * DAC.  A specific cell from a recent #CphyRemWcdmaFindCellCnf result must be
 * chosen for measurement in this signal, as this message does not start cell
 * identification itself.  It does however run MPS for the target cell such
 * that that target cell timing is updated and optimised prior to frequency
 * offset measurement.
 *
 * Similarly to the #CphyRemWcdmaFindCellReq, this can be used in both a locked and
 * unlocked manner.  If used in an unlocked manner to correct the frequency
 * error, completion of the unlocked proceedure should be followed by a
 * subsequent offset correction in the locked mode to ensure greatest accuracy.
 *
 * \see ChyRemWcdmaFindCelReq
 * \ingroup CPhyRemWcdma
 */
typedef struct CphyRemWcdmaFreqOffsetMeasReqTag
{
    /** The cell against which to measure the offset.
     * The primary scrambling code of the cell against which to measure
     * frequency offset.  This must have been returned in the last
     * #CphyRemWcdmaFindCellCnf to have been sent from the PHY.
     */
    uarfcn_t   psc;

    /** If TRUE, update the DAC to remove error.
     * Select whether to correct or just measure the frequency error.
     */
    bool       updateDac;

    /** Set to TRUE to indicate that the baseband frequency is not locked.
     * Setting this to TRUE causes the measurement to operate in a way that
     * can measure at  upto +/-3.5 ppm error, but with a reduction in
     * sensitivity and accuracy.  When set to FALSE, cells with a error of
     * +/-0.35 ppm maybe measured with greater sensitivity and accuracy.
     */
    bool       freqUnlocked;
}
CphyRemWcdmaFreqOffsetMeasReq;

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

/** Function to serialise a CphyRemWcdmaFreqOffsetMeasReq structure to a buffer.
 * Serialisation of this message can be performed by this function.
 *
 * \param[in] msg         The message to serialise.
 * \param[in,out] buffer  The data buffer into which the data is serialised.
 * \param[in] maxLen       Pointer to size of \a buffer.
 * \returns  Either a negative error code, or the length of the data.
 */
s32 CphyRemWcdmaFreqOffsetMeasReq_Serialise(const CphyRemWcdmaFreqOffsetMeasReq *msg,
                                            u8 *const buffer,
                                            u32       maxLen);


/** Function to deserialise a CphyRemWcdmaFreqOffsetMeasReq structure from a buffer..
 * Deserialisation of this message can be performed by this function.
 *
 * \param[in]     buffer  The buffer into which the structure has been stored.
 * \param[in]     maxLen  Size of \a buffer[].
 * \param[in,out] msg     Pointer to structure for population with deserialised
 *                         message.
 * \returns Size of the deserialised message if successful, otherwise a
 *           negative error code.
 */
s32 CphyRemWcdmaFreqOffsetMeasReq_Deserialise(const u8 *buffer,
                                              u32       maxLen,
                                              CphyRemWcdmaFreqOffsetMeasReq *const msg);

#ifdef __cplusplus
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

namespace threeway
{

class CPhyRemWcdmaFreqOffsetMeasReq : public CPhyMessage
{
public:
    /**
     * Construction / destruction.
     */
    CPhyRemWcdmaFreqOffsetMeasReq() { memset(&m_Struct, 0, sizeof(m_Struct)); };
    virtual ~CPhyRemWcdmaFreqOffsetMeasReq() {};
    CPhyRemWcdmaFreqOffsetMeasReq(upsc_t psc, bool updateDac, bool freqUnlocked);

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32  GetSerialisationId() const { return SERIALISATION_ID_CPHY_REM_WCDMA_FREQ_OFFSET_MEAS_REQ; };
    virtual s32  Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    /**
     * Implement CPhyMessage pure virtual.
     */
    virtual u32 GetStruct(CphyMessageData *const msg);

    /**
     * Accessors.
     */
    // None

    /**
     * Convert to string for debug.
     */
    virtual std::string ToString() const;
    virtual std::string ToBriefString() const;

private:

    /** Embedded C structure carrying parameters.
     */
    CphyRemWcdmaFreqOffsetMeasReq m_Struct;
};

}

#endif // __cplusplus

#endif // __CPhyRemWcdmaFreqOffsetMeasReq_h_
