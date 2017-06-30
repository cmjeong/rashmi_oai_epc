///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyNodeBSccpchConfigReq.h 28310 2010-07-16 15:27:29Z mmcternan $
//
// CPhyNodeBSccpchConfigReq message.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CPhyNodeBSccpchConfigReq_h_
#define __CPhyNodeBSccpchConfigReq_h_

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

/** Secondary Common Control Physical Channel configuration request.
 *
 * \ingroup CPhyNodeB
 */
typedef struct CphyNodeBSccpchConfigReqTag
{
    /** Zero based number indicating to which S-CCPCH this message refers. */
    uint8_t              channelNumber;

    /** Physical Channel Parameters. */
    l1_dlphy_param_t     phyParams;

    /** Transport Channel Parameters. */
    l1_cctrch_param_t    trchParams;

    /** Paging cycle in frames.
     */
    uint16_t             pagingCycleFrames;

    /** PI's per frame.  18, 36, 72 or 144.
     */
    uint16_t             pagingIndicatorsPerFrame;
}
CphyNodeBSccpchConfigReq;

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

/** Function to serialise a CphyNodeBSccpchConfigReq structure to a buffer.
 * Serialisation of this message can be performed by this function.
 *
 * \param[in] msg         The message to serialise.
 * \param[in,out] buffer  The data buffer into which the data is serialised.
 * \param[in] maxLen       Pointer to size of \a buffer.
 * \returns  Either a negative error code, or the length of the data.
 */
s32 CphyNodeBSccpchConfigReq_Serialise(const CphyNodeBSccpchConfigReq *msg, u8 *const buffer, u32 maxLen);


/** Function to deserialise a CphyNodeBSccpchConfigReq structure from some buffer
 * Deserialisation of this message can be performed by this function.
 *
 * \param[in]     buffer  The buffer into which the structure has been stored.
 * \param[in]     maxLen  Size of \a buffer[].
 * \param[in,out] msg     Pointer to structure for population with deserialised
 *                         message.
 * \returns Size of the deserialised message if successful, otherwise a
 *           negative error code.
 */
s32 CphyNodeBSccpchConfigReq_Deserialise(const u8 *buffer, u32 maxLen, CphyNodeBSccpchConfigReq *const msg);


#ifdef __cplusplus
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

namespace threeway
{

class CPhyNodeBSccpchConfigReq : public CPhyMessage
{
public:
    /**
     * Construction / destruction.
     */
    CPhyNodeBSccpchConfigReq() { memset(&m_Struct, 0, sizeof(m_Struct)); };
    CPhyNodeBSccpchConfigReq(const CphyNodeBSccpchConfigReq *cStruct);

    virtual ~CPhyNodeBSccpchConfigReq() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32  GetSerialisationId() const { return SERIALISATION_ID_CPHY_NODEB_SCCPCH_CONFIG_REQ; };
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
    CphyNodeBSccpchConfigReq m_Struct;
};

}

#endif /* __cplusplus */

#endif
