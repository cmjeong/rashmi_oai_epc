/*karan-qc_cl_changes*/
///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyRemSibDecodeComplete.h 28519 2010-07-21 14:39:46Z mmcternan $
//
// CPhyRemSibDecodeComplete message.
//
//
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CPhyRemSibDecodeComplete_h_
#define __CPhyRemSibDecodeComplete_h_

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
#define MAX_NUMBER_OF_PSCS 6
///////////////////////////////////////////////////////////////////////////////
// Message Structures
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

/*karan-qc_cl_changes*/
typedef struct wcdmaDecodeInfoTag
{
   /**
    psc of the cell for which the decoded SIB info is given
   **/
   upsc_t psc;

   /**
    plmn-type of the cell with specified psc
   **/
   plmnType_t plmnType;   

   /**
    plmnId of the cell with specified psc
   **/
   plmnId_t  plmnId;

   /**
    LAC of the cell 
   **/
   uint8_t lac[2];

   /**
    RAC of the cell
   **/
   uint8_t rac;

   /**
    Domain Ind for the cell
   **/


   /**
    CNType for the cell
   **/


   /**
    Cell Id of the cell
   **/
   uint32_t cellId;

}wcdmaDecodeInfo_t;
/**/

/** SIB decode complete 
 * This is sent from Layer 1 when a BCH block has been decoded.
 * It is sent regardless of whether the CRC16 passed or failed, such that the
 * controlling entity may decide to abandon a cell after repeated decode
 * failures.
 *
 * \ingroup CPhyRemWcdma
 */
typedef struct CphyRemSibDecodeCompleteTag
{
    /** Layer 1 status. */
    l1status_t status;

    /** Number of PSCs to be decoded in single req.Varies from 1 to 
        MAX_PSC_PER_FREQ+1 */
    upsccnt_t  count;

    wcdmaDecodeInfo_t sibDecodeInfo[MAX_NUMBER_OF_PSCS];
}
CphyRemSibDecodeComplete;

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

/** Function to serialise a CphyRemSibDecodeComplete structure to a buffer.
 * Serialisation of this message can be performed by this function.
 *
 * \param[in] msg         The message to serialise.
 * \param[in,out] buffer  The data buffer into which the data is serialised.
 * \param[in] maxLen       Pointer to size of \a buffer.
 * \returns  Either a negative error code, or the length of the data.
 */
s32 CphyRemSibDecodeComplete_Serialise(const CphyRemSibDecodeComplete *msg,
                                       u8 *const                  buffer,
                                       u32                        maxLen);


/** Function to deserialise a CphyRemSibDecodeComplete structure from a buffer.
 * Deserialisation of this message can be performed by this function.
 *
 * \param[in]     buffer  The buffer into which the structure has been stored.
 * \param[in]     maxLen  Size of \a buffer[].
 * \param[in,out] msg     Pointer to structure for population with deserialised
 *                         message.
 * \returns Size of the deserialised message if successful, otherwise a
 *           negative error code.
 */
s32 CphyRemSibDecodeComplete_Deserialise(const u8                  *buffer,
                                         u32                        maxLen,
                                         CphyRemSibDecodeComplete *const msg);

#ifdef __cplusplus
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

namespace threeway
{

class CPhyRemSibDecodeComplete : public CPhyMessage
{
public:
    /**
     * Construction / destruction.
     */
    CPhyRemSibDecodeComplete() { memset(&m_Struct, 0, sizeof(m_Struct)); };
    CPhyRemSibDecodeComplete(const CphyRemSibDecodeComplete *msg);
    virtual ~CPhyRemSibDecodeComplete() {};
    //CPhyRemSibDecodeComplete();

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32  GetSerialisationId() const { return SERIALISATION_ID_CPHY_REM_SIB_DECODE_COMPLETE; };
    virtual s32  Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    /**
     * Implement CPhyMessage pure virtual.
     */
    virtual u32 GetStruct(CphyMessageData *const msg);

    /**
     * Accessor: return the bchInfo structure within CphyRemSibDecodeComplete
     */
    //wcdmaDecodeInfo_t *getData() {return m_Struct.sibDecodeInfo[MAX_NUMBER_OF_PSCS]; };
	
    /**
     * Convert to string for debug.
     */
    virtual std::string ToString() const;
    virtual std::string ToBriefString() const;

private:

    /** Embedded C structure carrying parameters.
     */
    CphyRemSibDecodeComplete m_Struct;
};

}

#endif // __cplusplus

#endif // __CPhyRemSibDecodeComplete_h_ 
