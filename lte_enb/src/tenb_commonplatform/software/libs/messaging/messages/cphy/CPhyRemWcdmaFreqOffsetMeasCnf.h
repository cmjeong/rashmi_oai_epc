///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyRemWcdmaFreqOffsetMeasCnf.h 28519 2010-07-21 14:39:46Z mmcternan $
//
// CPhyRemWcdmaFreqOffsetMeasCnf message.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CPhyRemWcdmaFreqOffsetMeasCnf_h_
#define __CPhyRemWcdmaFreqOffsetMeasCnf_h_

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

/** Result from a frequency offset measurement.
 * \ingroup CPhyRemWcdma
 */
typedef struct CphyRemWcdmaFreqOffsetMeasCnfTag
{
    l1status_t status;      /**< Status of measurement. */
    upsc_t     psc;         /**< PSC of the measured cell. */
    uint16_t   dacVal;      /**< Computed DAC value that minimises frequency error. */
}
CphyRemWcdmaFreqOffsetMeasCnf;

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

/** Function to serialise a CphyRemWcdmaFreqOffsetMeasCnf structure to a buffer.
 * Serialisation of this message can be performed by this function.
 *
 * \param[in] msg         The message to serialise.
 * \param[in,out] buffer  The data buffer into which the data is serialised.
 * \param[in] maxLen       Pointer to size of \a buffer.
 * \returns  Either a negative error code, or the length of the data.
 */
s32 CphyRemWcdmaFreqOffsetMeasCnf_Serialise(const CphyRemWcdmaFreqOffsetMeasCnf *msg,
                                            u8 *const buffer,
                                            u32       maxLen);


/** Function to deserialise a CphyRemWcdmaFreqOffsetMeasCnf structure from a buffer..
 * Deserialisation of this message can be performed by this function.
 *
 * \param[in]     buffer  The buffer into which the structure has been stored.
 * \param[in]     maxLen  Size of \a buffer[].
 * \param[in,out] msg     Pointer to structure for population with deserialised
 *                         message.
 * \returns Size of the deserialised message if successful, otherwise a
 *           negative error code.
 */
s32 CphyRemWcdmaFreqOffsetMeasCnf_Deserialise(const u8 *buffer,
                                              u32       maxLen,
                                              CphyRemWcdmaFreqOffsetMeasCnf *const msg);

#ifdef __cplusplus
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

namespace threeway
{

class CPhyRemWcdmaFreqOffsetMeasCnf : public CPhyMessage
{
public:
    /**
     * Construction / destruction.
     */
    CPhyRemWcdmaFreqOffsetMeasCnf() { memset(&m_Struct, 0, sizeof(m_Struct)); };
    CPhyRemWcdmaFreqOffsetMeasCnf(const CphyRemWcdmaFreqOffsetMeasCnf *msg);
    virtual ~CPhyRemWcdmaFreqOffsetMeasCnf() {};
    CPhyRemWcdmaFreqOffsetMeasCnf(upsc_t psc, bool updateDac);

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32  GetSerialisationId() const { return SERIALISATION_ID_CPHY_REM_WCDMA_FREQ_OFFSET_MEAS_CNF; };
    virtual s32  Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    /**
     * Implement CPhyMessage pure virtual.
     */
    virtual u32 GetStruct(CphyMessageData *const msg);

    /**
     * Accessors.
     */
    l1status_t GetStatus () const { return m_Struct.status; }
    u16 GetPsc() const { return m_Struct.psc; }
    u16 GetDacVal() const { return m_Struct.dacVal; }

    /**
     * Convert to string for debug.
     */
    virtual std::string ToString() const;
    virtual std::string ToBriefString() const;

private:

    /** Embedded C structure carrying parameters.
     */
    CphyRemWcdmaFreqOffsetMeasCnf m_Struct;
};

}

#endif // __cplusplus

#endif // __CPhyRemWcdmaFreqOffsetMeasCnf_h_
