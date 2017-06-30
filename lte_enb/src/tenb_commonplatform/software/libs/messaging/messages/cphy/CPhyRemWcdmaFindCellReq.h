///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyRemWcdmaFindCellReq.h 28519 2010-07-21 14:39:46Z mmcternan $
//
// CPhyRemWcdmaFindCellReq message.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CPhyRemWcdmaFindCellReq_h_
#define __CPhyRemWcdmaFindCellReq_h_

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
#define MAX_NUMBER_OF_FREQ 64
///////////////////////////////////////////////////////////////////////////////
// Message Structures
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

/** Search for cells on one or more UARFCNs.
 * This starts a search for cells on a specific frequency and band.  It can
 * be used in one of two modes, either frequency locked or unlocked.  The
 * unlocked mode is more tolerant of frequency errors upto +/-3.5ppm, but
 * may return false detections.  The locked mode it tolerant to only
 * +/-0.35ppm error on a cell, but will perform SFN detection to ensure
 * only cells for which the P-CCPCH can be decoded are returned.
 *
 * Results are returned in the #CphyRemWcdmaFindCellCnf, and should only be
 * considered as accurate if the corresponding #CphyRemWcdmaFindCellReq was ran
 * in the frequency locked mode.
 *
 * \see CphyRemWcdmaFreqOffsetMeasReq
 * \ingroup CPhyRemWcdma
 */
typedef struct CphyRemWcdmaFindCellReqTag
{ 
    /*The number of frequencies in the */
    u8 count;

    /** The frequency on which to search. */
    uarfcn_t   frequency[MAX_NUMBER_OF_FREQ];

    /** The band to search. */
    uband_t    band;

    /** Set to TRUE to indicate that the baseband frequency is not locked.
     * Setting this to TRUE causes the search to operate in a way that can
     * still find cells at upto +/-3.5 ppm error, but with a reduction in
     * sensitivity and accuracy.  When set to FALSE, cells with a error of
     * +/-0.35 ppm maybe found with greater sensitivity and accuracy.
     */
    bool       freqUnlocked;
}
CphyRemWcdmaFindCellReq;

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

/** Function to serialise a CphyRemWcdmaFindCellReq structure to a buffer.
 * Serialisation of this message can be performed by this function.
 *
 * \param[in] msg         The message to serialise.
 * \param[in,out] buffer  The data buffer into which the data is serialised.
 * \param[in] maxLen       Pointer to size of \a buffer.
 * \returns  Either a negative error code, or the length of the data.
 */
s32 CphyRemWcdmaFindCellReq_Serialise(const CphyRemWcdmaFindCellReq *msg, u8 *const buffer, u32 maxLen);


/** Function to deserialise a CphyRemWcdmaFindCellReq structure from some buffer
 * Deserialisation of this message can be performed by this function.
 *
 * \param[in]     buffer  The buffer into which the structure has been stored.
 * \param[in]     maxLen  Size of \a buffer[].
 * \param[in,out] msg     Pointer to structure for population with deserialised
 *                         message.
 * \returns Size of the deserialised message if successful, otherwise a
 *           negative error code.
 */
s32 CphyRemWcdmaFindCellReq_Deserialise(const u8 *buffer, u32 maxLen, CphyRemWcdmaFindCellReq *const msg);

#ifdef __cplusplus
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

namespace threeway
{

class CPhyRemWcdmaFindCellReq : public CPhyMessage
{
public:
    /**
     * Construction / destruction.
     */
    CPhyRemWcdmaFindCellReq() { memset(&m_Struct, 0, sizeof(m_Struct)); };
    virtual ~CPhyRemWcdmaFindCellReq() {};
    CPhyRemWcdmaFindCellReq(uarfcn_t freq, uband_t band, bool freqUnlocked);
    /*KS: to sort the nbr disc results*/
    CPhyRemWcdmaFindCellReq(uarfcn_t* freq, uband_t band, bool freqUnlocked, u8 count);

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32  GetSerialisationId() const { return SERIALISATION_ID_CPHY_REM_FIND_CELL_REQ; };
    virtual s32  Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    /**
     * Implement CphyMessage pure virtual.
     */
    virtual u32 GetStruct(CphyMessageData *const msg);

    /**
     * Accessors.
     */
    void     SetUarfcn(uarfcn_t f);
    uarfcn_t GetUarfcn(void) const;
    void     SetBand(uband_t b);
    uband_t  GetBand(void) const;

    /**
     * Convert to string for debug.
     */
    virtual std::string ToString() const;
    virtual std::string ToBriefString() const;

private:

    /** Embedded C structure carrying parameters.
     */
    CphyRemWcdmaFindCellReq m_Struct;
};

}

#endif // __cplusplus

#endif // __CPhyRemWcdmaFindCellReq_h_
