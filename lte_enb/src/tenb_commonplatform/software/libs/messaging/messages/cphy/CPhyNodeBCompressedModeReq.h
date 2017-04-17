///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyNodeBCompressedModeReq.h 28742 2010-07-28 17:53:13Z dmorrison $
//
// CPhyNodeBCompressedModeReq message.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CPhyNodeBCompressedModeReq_h_
#define __CPhyNodeBCompressedModeReq_h_

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

/** Compressed mode controls for some already established Cctrch.
 * \ingroup CPhyNodeB
 */
typedef struct CphyNodeBCompressedModeReqTag
{
    /** Activation time at which to make the configuration change. */
    l1_activation_time_t actTime;

    /** If TRUE, enable DL compressed mode, otherwise disable. */
    bool  enableCompModeDl;

    /** If TRUE, enable UL compressed mode, otherwise disable. */
    bool  enableCompModeUl;

    /** Ue number.
     * Zero based UE number.
     */
    uint8_t              ue;

    /** DlChanCode
     * Position in the downlink spreading code tree where the compressed mode
     * radio bearer exists.
     */
    uint8_t  downlinkChannelisationCode;

    /** Transmission gap pattern sequence id.
     * This is the id of the transmission gap pattern sequence to configure. The L1
     * compressed mode gap pattern generator supports up to #NUM_MAX_CM_TGP_SEQUENCES
     * number of concurrent transmission gap pattern sequences and this parameter
     * uniquely identifies each instance.
     */
    uint8_t  seqId;

    /** TGSN - Transmission Gap starting Slot Number.
     * This is the slot number of the first transmission gap slot within the
     * first radio frame of the transmission gap pattern.
     *   Valid number range: 0..14.
     */
    uint8_t  tgsn;

    /** TGL1 - Transmission Gap 1 Length.
     * This is the duration of the first transmission gap within the transmission
     * gap pattern, expressed in number of slots.
     *   Valid numbers: 3, 4, 5, 7, 10 or 14.
     */
    uint8_t  tgl1;

    /** TGL2 - Transmission Gap 2 Length.
     * This is the duration of the second transmission gap within the transmission
     * gap pattern, expressed in number of slots.
     *   Valid numbers: 3, 4, 5, 7, 10 or 14.
     */
    uint8_t  tgl2;

    /** TGD - Transmission Gap start Distance.
     * This is the duration between the starting slots of two consecutive
     * transmission gaps within a transmission gap pattern, expressed in number
     * of slots.
     *   Valid number range: 15..269 or 0 if  there is only one gap in the TGP.
     */
    uint16_t  tgd;

    /** TGPL1 - Transmission Gap Pattern 1 Length.
     * This is the duration of transmission gap pattern 1, expressed in number
     * of frames.
     *   Valid number range: 1..144.
     */
    uint16_t  tgpl1;

    /** TGPRC - Transmission Gap Pattern Repetition Count.
     * This is the number of transmission gap patterns within the transmission
     * gap pattern sequence.
     *   Valid numbers: 1..511 or 0 if the repetition count is infinity.
     */
    uint16_t  tgprc;
}
CphyNodeBCompressedModeReq;

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

/** Function to serialise a CphyNodeBCompressedModeReq structure to a buffer.
 * Serialisation of this message can be performed by this function.
 *
 * \param[in] msg         The message to serialise.
 * \param[in,out] buffer  The data buffer into which the data is serialised.
 * \param[in] maxLen       Pointer to size of \a buffer.
 * \returns  Either a negative error code, or the length of the data.
 */
s32 CphyNodeBCompressedModeReq_Serialise(const CphyNodeBCompressedModeReq *msg,
                                         u8 *const buffer,
                                         u32       maxLen);


/** Function to deserialise a CphyNodeBCompressedModeReq structure from a buffer..
 * Deserialisation of this message can be performed by this function.
 *
 * \param[in]     buffer  The buffer into which the structure has been stored.
 * \param[in]     maxLen  Size of \a buffer[].
 * \param[in,out] msg     Pointer to structure for population with deserialised
 *                         message.
 * \returns Size of the deserialised message if successful, otherwise a
 *           negative error code.
 */
s32 CphyNodeBCompressedModeReq_Deserialise(const u8 *buffer,
                                   u32       maxLen,
                                   CphyNodeBCompressedModeReq *const msg);

#ifdef __cplusplus
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

namespace threeway
{

class CPhyNodeBCompressedModeReq : public CPhyMessage
{
public:
    /**
     * Construction / destruction.
     */
    CPhyNodeBCompressedModeReq () { memset(&m_Struct, 0, sizeof(m_Struct)); };
    CPhyNodeBCompressedModeReq(const l1_activation_time_t &activationTime,
            const bool enableDl, const bool enableUl, u8 zeroBasedUeNumber, u8 chanCode, u8 seqId, u8 tgsn,
            u8 tgl1, u8 tgl2, u16 tgd, u16 tgpl1, u16 tgprc);
    CPhyNodeBCompressedModeReq(const CphyNodeBCompressedModeReq *msg);
    virtual ~CPhyNodeBCompressedModeReq() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32  GetSerialisationId() const { return SERIALISATION_ID_CPHY_NODEB_COMPRESSED_MODE_REQ; };
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
    CphyNodeBCompressedModeReq m_Struct;
};

}

#endif // __cplusplus

#endif // __CPhyNodeBCompressedModeReq_h_
