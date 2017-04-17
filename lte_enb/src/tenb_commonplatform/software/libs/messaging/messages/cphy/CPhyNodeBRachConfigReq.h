///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyNodeBRachConfigReq.h 19065 2009-10-21 14:41:58Z nmahasinghe $
//
// CPhyNodeBRachConfigReq message.
//
// Copyright radisys Uk Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CPhyNodeBRachConfigReq_h_
#define __CPhyNodeBRachConfigReq_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
#include <string.h> // memset
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

/** Max number of PRACH signatures supported by CPHY.
 * This defines the max number of PRACH signatures supported by CPHY
 */
#define NUM_CPHY_MAX_PRACH_SIGNATURES (2)

///////////////////////////////////////////////////////////////////////////////
// Message Structures
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

/** Request Layer 1 to configure RACH.
 * \ingroup CPhyNodeB
 */
typedef struct CphyNodeBRachConfigReqTag
{
    uint32_t  scramblingCode;                            /**< PRACH scrambling code to use.             */
    uint8_t   pdSnrThreshold;                            /**< Preamble detection SNR threshold in log2. */
    uint8_t   signature[NUM_CPHY_MAX_PRACH_SIGNATURES];  /**< PRACH signatures to use.                  */
}
CphyNodeBRachConfigReq;

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

/** Function to serialise a CphyNodeBRachConfigReq structure to a buffer.
 * Serialisation of this message can be performed by this function.
 *
 * \param[in] msg         The message to serialise.
 * \param[in,out] buffer  The data buffer into which the data is serialised.
 * \param[in] maxLen       Pointer to size of \a buffer.
 * \returns  Either a negative error code, or the length of the data.
 */
s32 CphyNodeBRachConfigReq_Serialise(const CphyNodeBRachConfigReq *msg, u8 *const buffer, u32 maxLen);


/** Function to deserialise a CphyNodeBRachConfigReq structure from some buffer
 * Deserialisation of this message can be performed by this function.
 *
 * \param[in]     buffer  The buffer into which the structure has been stored.
 * \param[in]     maxLen  Size of \a buffer[].
 * \param[in,out] msg     Pointer to structure for population with deserialised
 *                         message.
 * \returns Size of the deserialised message if successful, otherwise a
 *           negative error code.
 */
s32 CphyNodeBRachConfigReq_Deserialise(const u8 *buffer, u32 maxLen, CphyNodeBRachConfigReq *const msg);


#ifdef __cplusplus
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

namespace threeway
{

class CPhyNodeBRachConfigReq : public CPhyMessage
{
public:
    /**
     * Construction / destruction.
     */
    CPhyNodeBRachConfigReq() { memset(&m_Struct, 0, sizeof(m_Struct)); };
    CPhyNodeBRachConfigReq(const CphyNodeBRachConfigReq *cStruct);

    virtual ~CPhyNodeBRachConfigReq() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32  GetSerialisationId() const { return SERIALISATION_ID_CPHY_NODEB_RACH_CONFIG_REQ; };
    virtual s32  Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    /**
     * Implement CphyMessage pure virtual.
     */
    virtual u32 GetStruct(CphyMessageData *const msg);

    /**
     * Convert to string for debug.
     */
    virtual std::string ToString() const;

private:

    /** Embedded C structure carrying parameters.
     */
    CphyNodeBRachConfigReq m_Struct;
};

}

#endif /* __cplusplus */

#endif
