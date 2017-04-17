///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyNodeBTxDpchEnableReq.h 5567 2008-05-30 11:13:47Z mm $
//
// CPhyNodeBTxDpchEnableReq message.
//
// Copyright Radisys Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CPhyNodeBTxDpchEnableReq_h_
#define __CPhyNodeBTxDpchEnableReq_h_

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

/** Request to enable or disable a transmit DPCHs.
 * \ingroup CPhyNodeB
 */
typedef struct CphyNodeBTxDpchEnableReqTag
{
    /** DPCH id.
     * This is the DPCH id of the DPCH to enable or disable. Valid range is
     * 0 to 3 which corresponds to DPCH-1 to DPCH-4.
     */
    u8     dpchId;

    /** DPCH enable/disable flag.
     * This selects whether to enable or disable the specified DPCH.
     */
    bool   enable;
}
CphyNodeBTxDpchEnableReq;

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

/** Function to serialise a CphyNodeBTxDpchEnableReq structure to a buffer.
 * Serialisation of this message can be performed by this function.
 *
 * \param[in] msg         The message to serialise.
 * \param[in,out] buffer  The data buffer into which the data is serialised.
 * \param[in] maxLen       Pointer to size of \a buffer.
 * \returns  Either a negative error code, or the length of the data.
 */
s32 CphyNodeBTxDpchEnableReq_Serialise(const     CphyNodeBTxDpchEnableReq *msg,
                                       u8 *const buffer,
                                       u32       maxLen);


/** Function to deserialise a CphyNodeBTxDpchEnableReq structure from a buffer..
 * Deserialisation of this message can be performed by this function.
 *
 * \param[in]     buffer  The buffer into which the structure has been stored.
 * \param[in]     maxLen  Size of \a buffer[].
 * \param[in,out] msg     Pointer to structure for population with deserialised
 *                         message.
 * \returns Size of the deserialised message if successful, otherwise a
 *           negative error code.
 */
s32 CphyNodeBTxDpchEnableReq_Deserialise(const u8                       *buffer,
                                         u32                             maxLen,
                                         CphyNodeBTxDpchEnableReq *const msg);

#ifdef __cplusplus
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

namespace threeway
{

class CPhyNodeBTxDpchEnableReq : public CPhyMessage
{
public:
    /**
     * Construction / destruction.
     */
    CPhyNodeBTxDpchEnableReq() { memset(&m_Struct, 0, sizeof(m_Struct)); };
    CPhyNodeBTxDpchEnableReq(const CphyNodeBTxDpchEnableReq *msg);
    CPhyNodeBTxDpchEnableReq(u8 dpchId, bool enable);
    virtual ~CPhyNodeBTxDpchEnableReq() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32  GetSerialisationId() const { return SERIALISATION_ID_CPHY_NODEB_TX_DPCH_ENABLE_REQ; };
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

private:

    /** Embedded C structure carrying parameters.
     */
    CphyNodeBTxDpchEnableReq m_Struct;
};

}

#endif // __cplusplus

#endif // __CPhyNodeBTxDpchEnableReq_h_
