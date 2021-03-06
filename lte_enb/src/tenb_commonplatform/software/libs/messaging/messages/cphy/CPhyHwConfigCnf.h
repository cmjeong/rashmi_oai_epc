///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyHwConfigCnf.h 28519 2010-07-21 14:39:46Z mmcternan $
//
// CPhyHwConfigCnf message.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CPhyHwConfigCnf_h_
#define __CPhyHwConfigCnf_h_

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

/** Hardware configuration confirmation.
 * This is sent in response to a #CphyHwConfigReq and indicates whether
 * initialisation was successful or not.  If the status is anything other than
 * #L1_SOK, initialisation failed.  Critically, after startup, failure to
 * initialise the hardware leaves Layer 1 in the pre-initialised state, and
 * Node B or REM modes of operation cannot be accessed.
 *
 * \ingroup CPhyPreInit
 */
typedef struct CphyHwConfigCnfTag
{
    l1status_t     status; /**< Return status. */
}
CphyHwConfigCnf;

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

/** Function to serialise a CphyHwConfigCnf structure to a buffer.
 * Serialisation of this message can be performed by this function.
 *
 * \param[in] msg         The message to serialise.
 * \param[in,out] buffer  The data buffer into which the data is serialised.
 * \param[in] maxLen       Pointer to size of \a buffer.
 * \returns  Either a negative error code, or the length of the data.
 */
s32 CphyHwConfigCnf_Serialise(const CphyHwConfigCnf *msg,
                              u8 *const buffer,
                              u32       maxLen);


/** Function to deserialise a CphyHwConfigCnf structure from a buffer..
 * Deserialisation of this message can be performed by this function.
 *
 * \param[in]     buffer  The buffer into which the structure has been stored.
 * \param[in]     maxLen  Size of \a buffer[].
 * \param[in,out] msg     Pointer to structure for population with deserialised
 *                         message.
 * \returns Size of the deserialised message if successful, otherwise a
 *           negative error code.
 */
s32 CphyHwConfigCnf_Deserialise(const u8 *buffer,
                                u32       maxLen,
                                CphyHwConfigCnf *const msg);

#ifdef __cplusplus
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

namespace threeway
{

class CPhyHwConfigCnf : public CPhyMessage
{
public:
    /**
     * Construction / destruction.
     */
    CPhyHwConfigCnf() { memset(&m_Struct, 0, sizeof(m_Struct)); };
    CPhyHwConfigCnf(const CphyHwConfigCnf *msg);
    virtual ~CPhyHwConfigCnf() {};
    CPhyHwConfigCnf(upsc_t psc, bool updateDac);

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32  GetSerialisationId() const { return SERIALISATION_ID_CPHY_HW_CONFIG_CNF; };
    virtual s32  Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    /**
     * Implement CPhyMessage pure virtual.
     */
    virtual u32 GetStruct(CphyMessageData *const msg);

    /**
     * Accessors.
     */
    l1status_t GetStatus() const;

    /**
     * Convert to string for debug.
     */
    virtual std::string ToString() const;
    virtual std::string ToBriefString() const;

private:

    /** Embedded C structure carrying parameters.
     */
    CphyHwConfigCnf m_Struct;
};

}

#endif // __cplusplus

#endif // __CPhyHwConfigCnf_h_
