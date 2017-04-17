///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyRemGsmBcchDecodeInd.h 28519 2010-07-21 14:39:46Z mmcternan $
//
// CPhyRemGsmBcchDecodeInd message.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CPhyRemGsmBcchDecodeInd_h_
#define __CPhyRemGsmBcchDecodeInd_h_

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
typedef struct gsmBcchInfoTag
{
    /** Indication as to whether the CRC passed on the recieved block.
     * A crcPass == 1 indicates the successul decoding of BCCH.
     */
    bool            crcPass;

    /** The decoded data block.
     * In the case that \a crcPass if true, this contains the decoded data.
     * Otherwise the buffer is filled with 0xff to aid debugging.
     */
    u8              data[BCCH_GSM_BLOCK_SIZE_BYTES];    
}gsmBcchInfo_t;
/*Pradeep end*/

/** Indication that some BCCH block has been decoded.
 * After a sucessful CphyRemGsmBcchDecodeCnf has been sent, BCCH decoding
 * will comence.  At that point this message structure is used to pass decode
 * results and data block from Layer 1 to the stack.
 *
 * \ingroup CPhyRemGsm
 */
typedef struct CphyRemGsmBcchDecodeIndTag
{
    /** Status code
     * Normally indicates a sucessful search, but may also indicate errors
     * such as an unsupported band or frequency, or the number of frequencies
     * to scan exceeds maximum supported value.
     */
    l1status_t      status;

    /** Frequency of the cell being decoded.
     * In GSM900 and DCS1800.
     */
    arfcn_t         arfcn;

    /** Base Station Identity Code of cell being decoded.
     * INVALID_BSIC. In the case of a failed search, this will be set to INVALID_BSIC,
     * otherwise it is set to the decoded BSIC of the cell found on the searched ARFCN.
     * Structure of BSIC: NCC (Network colour code, MSB 3 bits) + BCC (Base station colour code, LSB 3 bits).
     */
    bsic_t          bsic;
    
/*Pradeep start*/
    /** number of bchInfo[] blocks.
     */
    uint32_t      numBlk;

    /** This contais the crc indication and BCCH transport block.
     */
    gsmBcchInfo_t bchInfo[MAX_BCCH_GSM_BLOCKS];
/*Pradeep end*/
}
CphyRemGsmBcchDecodeInd;

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

/** Function to serialise a CphyRemGsmBcchDecodeInd structure to a buffer.
 * Serialisation of this message can be performed by this function.
 *
 * \param[in] msg         The message to serialise.
 * \param[in,out] buffer  The data buffer into which the data is serialised.
 * \param[in] maxLen       Pointer to size of \a buffer.
 * \returns  Either a negative error code, or the length of the data.
 */
s32 CphyRemGsmBcchDecodeInd_Serialise(const CphyRemGsmBcchDecodeInd *msg,
                                    u8 *const                  buffer,
                                    u32                        maxLen);


/** Function to deserialise a CphyRemGsmBcchDecodeInd structure from a buffer.
 * Deserialisation of this message can be performed by this function.
 *
 * \param[in]     buffer  The buffer into which the structure has been stored.
 * \param[in]     maxLen  Size of \a buffer[].
 * \param[in,out] msg     Pointer to structure for population with deserialised
 *                         message.
 * \returns Size of the deserialised message if successful, otherwise a
 *           negative error code.
 */
s32 CphyRemGsmBcchDecodeInd_Deserialise(const u8                  *buffer,
                                      u32                        maxLen,
                                      CphyRemGsmBcchDecodeInd *const msg);

#ifdef __cplusplus
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

namespace threeway
{

class CPhyRemGsmBcchDecodeInd : public CPhyMessage
{
public:
    /**
     * Construction / destruction.
     */
    CPhyRemGsmBcchDecodeInd() { memset(&m_Struct, 0, sizeof(m_Struct)); };
    CPhyRemGsmBcchDecodeInd(const CphyRemGsmBcchDecodeInd *msg);
    virtual ~CPhyRemGsmBcchDecodeInd() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32  GetSerialisationId() const { return SERIALISATION_ID_CPHY_REM_GSM_BCCH_DECODE_IND; };
    virtual s32  Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    /**
     * Implement CPhyMessage pure virtual.
     */
    virtual u32 GetStruct(CphyMessageData *const msg);

    /**
     * Accessors.
     */

/*Pradeep start*/
/*
    bool GetCRCPass(void) {return m_Struct.crcPass;}
    u8 *GetData() {return m_Struct.data;};
*/
    u32 GetDataLen() {return BCCH_GSM_BLOCK_SIZE_BYTES;};
    gsmBcchInfo_t *GetData() {return m_Struct.bchInfo;}
/*Pradeep end*/

    // None

    /**
     * Convert to string for debug.
     */
    virtual std::string ToString() const;
    virtual std::string ToBriefString() const;

private:

    /** Embedded C structure carrying parameters.
     */
    CphyRemGsmBcchDecodeInd m_Struct;
};

}

#endif // __cplusplus

#endif // __CPhyHwConfigCnf_h_
