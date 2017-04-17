///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyRemSibDecodeInd.h 28519 2010-07-21 14:39:46Z mmcternan $
//
// CPhyRemSibDecodeInd message.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CPhyRemSibDecodeInd_h_
#define __CPhyRemSibDecodeInd_h_

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

/*Pradeep start*/
typedef struct wcdmaBcchInfoTag
{
    /** If TRUE, the CRC on the transport block passed. */
    bool       crcPass;
    
    /** Decoded transport block, valid if \a crcPass is TRUE. */
    u8         data[BCH_TRCH_BLOCK_SIZE_BYTES];
}wcdmaBcchInfo_t;

/*Pradeep end*/

/** SIB decode indication.
 * This is sent from Layer 1 when a BCH transport block has been decoded.
 * It is sent regardless of whether the CRC16 passed or failed, such that the
 * controlling entity may decide to abandon a cell after repeated decode
 * failures.
 *
 * \ingroup CPhyRemWcdma
 */
typedef struct CphyRemSibDecodeIndTag
{
    /** Layer 1 status. */
    l1status_t status;

    /** PSC of the target cell. */
    upsc_t     psc;
    
/*Pradeep start*/
    int16_t    numBlk;

    wcdmaBcchInfo_t bchInfo[MAX_NUM_BCH_TRANSPORT_BLOCKS];
/*Pradeep end*/    
}
CphyRemSibDecodeInd;

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

/** Function to serialise a CphyRemSibDecodeInd structure to a buffer.
 * Serialisation of this message can be performed by this function.
 *
 * \param[in] msg         The message to serialise.
 * \param[in,out] buffer  The data buffer into which the data is serialised.
 * \param[in] maxLen       Pointer to size of \a buffer.
 * \returns  Either a negative error code, or the length of the data.
 */
s32 CphyRemSibDecodeInd_Serialise(const CphyRemSibDecodeInd *msg,
                                  u8 *const                  buffer,
                                  u32                        maxLen);


/** Function to deserialise a CphyRemSibDecodeInd structure from a buffer.
 * Deserialisation of this message can be performed by this function.
 *
 * \param[in]     buffer  The buffer into which the structure has been stored.
 * \param[in]     maxLen  Size of \a buffer[].
 * \param[in,out] msg     Pointer to structure for population with deserialised
 *                         message.
 * \returns Size of the deserialised message if successful, otherwise a
 *           negative error code.
 */
s32 CphyRemSibDecodeInd_Deserialise(const u8                  *buffer,
                                    u32                        maxLen,
                                    CphyRemSibDecodeInd *const msg);

#ifdef __cplusplus
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

namespace threeway
{

class CPhyRemSibDecodeInd : public CPhyMessage
{
public:
    /**
     * Construction / destruction.
     */
    CPhyRemSibDecodeInd() { memset(&m_Struct, 0, sizeof(m_Struct)); };
    CPhyRemSibDecodeInd(const CphyRemSibDecodeInd *msg);
    virtual ~CPhyRemSibDecodeInd() {};
    CPhyRemSibDecodeInd(upsc_t psc);

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32  GetSerialisationId() const { return SERIALISATION_ID_CPHY_REM_SIB_DECODE_IND; };
    virtual s32  Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    /**
     * Implement CPhyMessage pure virtual.
     */
    virtual u32 GetStruct(CphyMessageData *const msg);

    /**
     * Accessor: return the bchInfo structure within CphyRemSibDecodeInd
     */
    wcdmaBcchInfo_t *getData() {return m_Struct.bchInfo; };
	
    /**
     * Convert to string for debug.
     */
    virtual std::string ToString() const;
    virtual std::string ToBriefString() const;

private:

    /** Embedded C structure carrying parameters.
     */
    CphyRemSibDecodeInd m_Struct;
};

}

#endif // __cplusplus

#endif // __CPhyHwConfigInd_h_
