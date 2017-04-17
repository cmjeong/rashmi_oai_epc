///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyNodeBPchRemoveReq.h 28647 2010-07-26 08:55:18Z mmcternan $
//
// CPhyNodeBPchRemoveReq message.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CPhyNodeBPchRemoveReq_h_
#define __CPhyNodeBPchRemoveReq_h_

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

/** Request to remove a paging block from the scheduling roster.
 *
 * \see CphyNodeBPchRemoveCnf
 * \ingroup CPhyNodeB
 */
typedef struct CphyNodeBPchRemoveReqTag
{
    /** Offset into frame at which the paging block should be placed.
     * This is computed by higher layers as (IMSI / K) mod (DRX cycle)
     * where K is the number of S-CCPCH channels on the cell, 1 for the
     * FAP.
     */
    uint16_t             sfnOffset;
}
CphyNodeBPchRemoveReq;

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

/** Function to serialise a CphyNodeBPchRemoveReq structure to a buffer.
 * Serialisation of this message can be performed by this function.
 *
 * \param[in] msg         The message to serialise.
 * \param[in,out] buffer  The data buffer into which the data is serialised.
 * \param[in] maxLen       Pointer to size of \a buffer.
 * \returns  Either a negative error code, or the length of the data.
 */
s32 CphyNodeBPchRemoveReq_Serialise(const CphyNodeBPchRemoveReq *msg,
                              u8 *const buffer,
                              u32       maxLen);


/** Function to deserialise a CphyNodeBPchRemoveReq structure from a buffer..
 * Deserialisation of this message can be performed by this function.
 *
 * \param[in]     buffer  The buffer into which the structure has been stored.
 * \param[in]     maxLen  Size of \a buffer[].
 * \param[in,out] msg     Pointer to structure for population with deserialised
 *                         message.
 * \returns Size of the deserialised message if successful, otherwise a
 *           negative error code.
 */
s32 CphyNodeBPchRemoveReq_Deserialise(const u8 *buffer,
                                u32       maxLen,
                                CphyNodeBPchRemoveReq *const msg);

#ifdef __cplusplus
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

namespace threeway
{

class CPhyNodeBPchRemoveReq : public CPhyMessage
{
public:
    /**
     * Construction / destruction.
     */
    CPhyNodeBPchRemoveReq() { memset(&m_Struct, 0, sizeof(m_Struct)); };
    CPhyNodeBPchRemoveReq(u16 sfnOffset);
    CPhyNodeBPchRemoveReq(const CphyNodeBPchRemoveReq *msg);
    virtual ~CPhyNodeBPchRemoveReq() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32  GetSerialisationId() const { return SERIALISATION_ID_CPHY_NODEB_PCH_REMOVE_REQ; };
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
    CphyNodeBPchRemoveReq m_Struct;
};

}

#endif // __cplusplus

#endif // __CPhyNodeBPchRemoveReq_h_
