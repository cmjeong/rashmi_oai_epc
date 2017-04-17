///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyRemWcdmaCoarseFreqLockCnf.h 28519 2010-07-21 14:39:46Z mmcternan $
//
// CPhyRemWcdmaCoarseFreqLockCnf message.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CPhyRemWcdmaCoarseFreqLockCnf_h_
#define __CPhyRemWcdmaCoarseFreqLockCnf_h_

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

/** Return result of a coarse frequency locking attempt.
 * \ingroup CPhyRemWcdma
 */
typedef struct CphyRemWcdmaCoarseFreqLockCnfTag
{
    l1status_t status;      /**< Status of measurement. */
    uint16_t   afcDacValue; /**< DAC value result of search. */
}
CphyRemWcdmaCoarseFreqLockCnf;

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

/** Function to serialise a CphyRemWcdmaCoarseFreqLockCnf structure to a buffer.
 * Serialisation of this message can be performed by this function.
 *
 * \param[in] msg         The message to serialise.
 * \param[in,out] buffer  The data buffer into which the data is serialised.
 * \param[in] maxLen       Pointer to size of \a buffer.
 * \returns  Either a negative error code, or the length of the data.
 */
s32 CphyRemWcdmaCoarseFreqLockCnf_Serialise(const CphyRemWcdmaCoarseFreqLockCnf *msg,
                                                  u8 *const buffer,
                                                  u32       maxLen);


/** Function to deserialise a CphyRemWcdmaCoarseFreqLockCnf structure from a buffer..
 * Deserialisation of this message can be performed by this function.
 *
 * \param[in]     buffer  The buffer into which the structure has been stored.
 * \param[in]     maxLen  Size of \a buffer[].
 * \param[in,out] msg     Pointer to structure for population with deserialised
 *                         message.
 * \returns Size of the deserialised message if successful, otherwise a
 *           negative error code.
 */
s32 CphyRemWcdmaCoarseFreqLockCnf_Deserialise(const u8 *buffer,
                                                    u32       maxLen,
                                                    CphyRemWcdmaCoarseFreqLockCnf *const msg);

#ifdef __cplusplus
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

namespace threeway
{

class CPhyRemWcdmaCoarseFreqLockCnf : public CPhyMessage
{
public:
    /**
     * Construction / destruction.
     */
    CPhyRemWcdmaCoarseFreqLockCnf() { memset(&m_Struct, 0, sizeof(m_Struct)); };
    CPhyRemWcdmaCoarseFreqLockCnf(const CphyRemWcdmaCoarseFreqLockCnf *msg);
    virtual ~CPhyRemWcdmaCoarseFreqLockCnf() {};
    CPhyRemWcdmaCoarseFreqLockCnf(upsc_t psc, bool updateDac);

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32  GetSerialisationId() const { return SERIALISATION_ID_CPHY_REM_WCDMA_COARSE_FREQ_LOCK_CNF; };
    virtual s32  Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    /**
     * Implement CPhyMessage pure virtual.
     */
    virtual u32 GetStruct(CphyMessageData *const msg);

    /**
     * Accessors.
     */
    l1status_t GetStatus ()     const { return m_Struct.status; }
    u16        GetAfcDacValue() const { return m_Struct.afcDacValue; }

    /**
     * Convert to string for debug.
     */
    virtual std::string ToString() const;
    virtual std::string ToBriefString() const;

private:

    /** Embedded C structure carrying parameters.
     */
    CphyRemWcdmaCoarseFreqLockCnf m_Struct;
};

}

#endif // __cplusplus

#endif // __CPhyRemWcdmaCoarseFreqLockCnf_h_
