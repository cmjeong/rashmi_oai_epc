///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyModeChangeReq.h 28519 2010-07-21 14:39:46Z mmcternan $
//
// CPhyModeChangeReq message.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CPhyModeChangeReq_h_
#define __CPhyModeChangeReq_h_

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

///////////////////////////////////////////////////////////////////////////////
// Message Structures
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

/** Request Layer 1 to change operating mode.
 * This requests Layer 1 to change to a new operating mode.  This can only
 * be used to leave NULL state to Node B or a REM state, or to return from
 * one of the operational states to NULL.  It cannot be used to transition
 * from the pre-init state; a #CphyHwConfigReq must be used for that.
 * \ingroup CPhyNull
 */
typedef struct CphyModeChangeReqTag
{
   l1mode_t mode;       /**< The new desired operating mode. */

   /*If mode is L1_MODE_REM_WCDMA below timers are for WCDMA.
    *If mode is L1_MODE_REM_GSM below timers are for GSM
    *If mode is L1_MODE_NODEB below timers are not valid
    */
   uint32_t maxCellSearchTime; /**< 0 - Invalid*/
   uint32_t maxBcchDecTime; /**< 0 - Invalid*/
   uint32_t maxRssiScanTime; /**< 0 - Invalid*/
     
}
CphyModeChangeReq;

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

/** Function to serialise a CphyModeChangeReq structure to a buffer.
 * Serialisation of this message can be performed by this function.
 *
 * \param[in] msg         The message to serialise.
 * \param[in,out] buffer  The data buffer into which the data is serialised.
 * \param[in] maxLen       Pointer to size of \a buffer.
 * \returns  Either a negative error code, or the length of the data.
 */
s32 CphyModeChangeReq_Serialise(const CphyModeChangeReq *msg, u8 *const buffer, u32 maxLen);


/** Function to deserialise a CphyModeChangeReq structure from some buffer
 * Deserialisation of this message can be performed by this function.
 *
 * \param[in]     buffer  The buffer into which the structure has been stored.
 * \param[in]     maxLen  Size of \a buffer[].
 * \param[in,out] msg     Pointer to structure for population with deserialised
 *                         message.
 * \returns Size of the deserialised message if successful, otherwise a
 *           negative error code.
 */
s32 CphyModeChangeReq_Deserialise(const u8 *buffer, u32 maxLen, CphyModeChangeReq *const msg);


#ifdef __cplusplus
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

namespace threeway
{

class CPhyModeChangeReq : public CPhyMessage
{
public:
    /**
     * Construction / destruction.
     */
    CPhyModeChangeReq() { memset(&m_Struct, 0, sizeof(m_Struct)); };
    CPhyModeChangeReq(const CphyModeChangeReq *cStruct);
    CPhyModeChangeReq(const l1mode_t mode,
						uint32_t maxCellSearchTime =0,
						uint32_t maxBcchDecTime = 0, 
						uint32_t maxRssiScanTime = 0);

    virtual ~CPhyModeChangeReq() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32  GetSerialisationId() const { return SERIALISATION_ID_CPHY_MODE_CHANGE_REQ; };
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
    virtual std::string ToBriefString() const;

private:

    /** Embedded C structure carrying parameters.
     */
    CphyModeChangeReq m_Struct;
};

}

#endif /* __cplusplus */

#endif
