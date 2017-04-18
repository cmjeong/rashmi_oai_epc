///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyNodeBPchAddReq.h 28331 2010-07-17 15:25:20Z mmcternan $
//
// CPhyNodeBPchAddReq message.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CPhyNodeBPchAddReq_h_
#define __CPhyNodeBPchAddReq_h_

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

/** Special SFN offset value used to control the default PCH block.
 * \see CphyNodeBPchAddReq
 */
#define CPHY_NODEB_PCH_SET_FILL 0xffff

///////////////////////////////////////////////////////////////////////////////
// Message Structures
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif


/** Add a paging block to the scheduling roster.
 * This adds a paging block at some SFN to the scheduling roster.  If
 * a block already exists for the given \a sfnOffset, the CphyNodeBPchAddCnf
 * will contain an error code such as L1_SBUSY, and a PchRemoveReq must either
 * be used to remove the block, or some time waited for to allow \a nRepeat to
 * expire.
 *
 * \see CphyNodeBPchAddCnf, CphyNodeBPchRemoveReq
 * \ingroup CPhyNodeB
 */
typedef struct CphyNodeBPchAddReqTag
{
    /** Bit map giving the Paging Indicators that should be set.
     * Each bit represents a Paging Indictor in the frame corresponding to
     * that needed to advertise presence of the PCH block.  Setting a bit
     * to 1 in this map causes the corresponding paging indicator to be set,
     * otherwise it is cleared.
     *
     * \note This is dimensioned for the worst case of 144 PI's per frame.
     *        If less are configured, the extra storage is ignored in L1.
     */
    pi_t                 pi;

    /** Offset into frame at which the paging block should be placed.
     * This is computed by higher layers as (IMSI / K) mod (DRX cycle)
     * where K is the number of S-CCPCH channels on the cell, 1 for the
     * FAP.
     *
     * In the special case that \a sfnOffset is CPHY_NODEB_PCH_SET_FILL, the
     * paging block replaces or sets the fill block used when no other
     * specific block is scheduled for transmission.  In this case
     * \a nRepeat gives the count of consecutive DRX cycles for which
     * the block will be broadcast.
     */
    uint16_t             sfnOffset;

    /** Number of times to retransmit the block on the S-CCPCH.
     * This gives the number of times the block should be transmitted before
     * being automatically removed from the schedule.  If specified as 0, the
     * block will be repeatedly indefinately until explicity removed with a
     * #CphyNodeBPchRemoveReq,
     */
    uint16_t             nRepeat;

    /** Block of data to transmit. */
    uint8_t              data[PCH_TRCH_BLOCK_SIZE_BYTES];
}
CphyNodeBPchAddReq;

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

/** Function to serialise a CphyNodeBPchAddReq structure to a buffer.
 * Serialisation of this message can be performed by this function.
 *
 * \param[in] msg         The message to serialise.
 * \param[in,out] buffer  The data buffer into which the data is serialised.
 * \param[in] maxLen       Pointer to size of \a buffer.
 * \returns  Either a negative error code, or the length of the data.
 */
s32 CphyNodeBPchAddReq_Serialise(const CphyNodeBPchAddReq *msg,
                              u8 *const buffer,
                              u32       maxLen);


/** Function to deserialise a CphyNodeBPchAddReq structure from a buffer..
 * Deserialisation of this message can be performed by this function.
 *
 * \param[in]     buffer  The buffer into which the structure has been stored.
 * \param[in]     maxLen  Size of \a buffer[].
 * \param[in,out] msg     Pointer to structure for population with deserialised
 *                         message.
 * \returns Size of the deserialised message if successful, otherwise a
 *           negative error code.
 */
s32 CphyNodeBPchAddReq_Deserialise(const u8 *buffer,
                                u32       maxLen,
                                CphyNodeBPchAddReq *const msg);

#ifdef __cplusplus
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

namespace threeway
{

class CPhyNodeBPchAddReq : public CPhyMessage
{
public:
    /**
     * Construction / destruction.
     */
    CPhyNodeBPchAddReq() : m_Struct() { };
    CPhyNodeBPchAddReq(u16 sfnOffset, pi_t *pi, u16 nRepeat, const u8 *data, u32 dataLen);
    CPhyNodeBPchAddReq(const CphyNodeBPchAddReq *msg);
    virtual ~CPhyNodeBPchAddReq() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32  GetSerialisationId() const { return SERIALISATION_ID_CPHY_NODEB_PCH_ADD_REQ; };
    virtual s32  Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    /**
     * Implement CPhyMessage pure virtual.
     */
    virtual u32 GetStruct(CphyMessageData *const msg);

    /**
     * Accessors.
     */

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
    CphyNodeBPchAddReq m_Struct;
};

}

#endif // __cplusplus

#endif // __CPhyNodeBPchAddReq_h_
