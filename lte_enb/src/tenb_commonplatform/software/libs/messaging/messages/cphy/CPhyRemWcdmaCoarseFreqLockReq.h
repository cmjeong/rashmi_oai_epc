///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyRemWcdmaCoarseFreqLockReq.h 28519 2010-07-21 14:39:46Z mmcternan $
//
// CPhyRemWcdmaCoarseFreqLockReq message.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CPhyRemWcdmaCoarseFreqLockReq_h_
#define __CPhyRemWcdmaCoarseFreqLockReq_h_

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

/** Search for any cells on an UARFCN and attempt a coarse frequency lock.
 * This sweeps the AFC DAC through a range of values and attempts to find P-SCH
 * correlations for any cells on the specified frequency.  P-SCH correlations
 * are stored and ranked for each DAC setting which are later used to
 * approximate the ideal DAC setting.  This should bring the frequency error to
 * within +/-3.5ppm if at least one cell can be observed on the passed
 * frequency such that cell search and fine frequency locking may then succeed.
 *
 * \ingroup CPhyRemWcdma
 */
typedef struct CphyRemWcdmaCoarseFreqLockReqTag
{
    /** The frequency on which to search for cells.
     */
    uarfcn_t   frequency;

    /** The band of the frequency.
     */
    uband_t    band;

    /** The nominal AFC DAC value.
     * This should give the AFC DAC value which is estimated to be close to
     * ideal.  The search is then centred around this output value.
     */
    uint16_t   afcDacCentre;

    /** If TRUE, update the DAC to remove error.
     * Control whether to measure or cancel the frequency error.
     * \deprecated  This functionality it meaningless as it must update the DAC
     *               to perform the scan.  It should always be set to TRUE.
     */
    bool       updateDac;
}
CphyRemWcdmaCoarseFreqLockReq;

#ifdef __cplusplus
}
#endif


///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Functions
//////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

/** Function to serialise a CphyRemWcdmaCoarseFreqLockReq structure to a buffer.
 * Serialisation of this message can be performed by this function.
 *
 * \param[in] msg         The message to serialise.
 * \param[in,out] buffer  The data buffer into which the data is serialised.
 * \param[in] maxLen       Pointer to size of \a buffer.
 * \returns  Either a negative error code, or the length of the data.
 */
s32 CphyRemWcdmaCoarseFreqLockReq_Serialise(const CphyRemWcdmaCoarseFreqLockReq *msg,
                                            u8 *const                            buffer,
                                            u32                                  maxLen);


/** Function to deserialise a CphyRemWcdmaCoarseFreqLockReq structure from a buffer..
 * Deserialisation of this message can be performed by this function.
 *
 * \param[in]     buffer  The buffer into which the structure has been stored.
 * \param[in]     maxLen  Size of \a buffer[].
 * \param[in,out] msg     Pointer to structure for population with deserialised
 *                         message.
 * \returns Size of the deserialised message if successful, otherwise a
 *           negative error code.
 */
s32 CphyRemWcdmaCoarseFreqLockReq_Deserialise(const u8                            *buffer,
                                              u32                                  maxLen,
                                              CphyRemWcdmaCoarseFreqLockReq *const msg);

#ifdef __cplusplus
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

namespace threeway
{

class CPhyRemWcdmaCoarseFreqLockReq : public CPhyMessage
{
public:
    /**
     * Construction / destruction.
     */
    CPhyRemWcdmaCoarseFreqLockReq() { memset(&m_Struct, 0, sizeof(m_Struct)); };
    virtual ~CPhyRemWcdmaCoarseFreqLockReq() {};
    CPhyRemWcdmaCoarseFreqLockReq(u16      afcDacCentre,
                                  uband_t  band,
                                  uarfcn_t frequency,
                                  bool     updateDac);

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32  GetSerialisationId() const { return SERIALISATION_ID_CPHY_REM_WCDMA_COARSE_FREQ_LOCK_REQ; };
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
    CphyRemWcdmaCoarseFreqLockReq m_Struct;
};

}

#endif // __cplusplus

#endif // __CPhyRemWcdmaCoarseFreqLockReq_h_
