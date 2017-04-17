///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyNlmErrInd.h 28519 2010-07-21 14:39:46Z mmcternan $
//
// CPhyNlmErrInd message.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CPhyNlmErrInd_h_
#define __CPhyNlmErrInd_h_

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
#define CPHY_REM_FIND_CELL_CNF_MAX_GSM_NBRS  32

///////////////////////////////////////////////////////////////////////////////
// Message Structures
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

/** Error code used by NLM for indicating errors.
 * 
 */
typedef enum
{
    NLM_COSC_LOST = 0,   /**< COSC lost on specific frequency. */
    NLM_COSC_NO_SERVICE  /**< COSC service not available. */
}
nlmErrCode_t; 
 
/** Confirmation that a cell search on some frequency has concluded.
 * This is sent once the cell search on some frequency, as directed by a
 * CphyNlmCoscReq has concluded, or that the search could not be
 * conducted for some reason.
 *
 * \note In error situations \a status will contain a reason code, while
 *        in cases where a cell was found the \a status will be L1_SOK.
 *        A failed search is indicated by a L1_SOK \a status, but with \a
 *        bsic of #INVALID_BSIC.
 *
 * \ingroup CPhyNlmGsm
 */

typedef struct CphyNlmErrIndTag
{
    /** Error cause
     * Normally indicates a sucessful search, but may also indicate errors
     * such as an unsupported band or frequency, or the number of frequencies
     * to scan exceeds maximum supported value.
     */
    nlmErrCode_t    errCode;
}
CphyNlmErrInd;

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

/** Function to serialise a CphyNlmErrInd structure to a buffer.
 * Serialisation of this message can be performed by this function.
 *
 * \param[in] msg         The message to serialise.
 * \param[in,out] buffer  The data buffer into which the data is serialised.
 * \param[in] maxLen       Pointer to size of \a buffer.
 * \returns  Either a negative error code, or the length of the data.
 */
s32 CphyNlmErrInd_Serialise(const CphyNlmErrInd *msg,
                                    u8 *const                  buffer,
                                    u32                        maxLen);


/** Function to deserialise a CphyNlmErrInd structure from a buffer.
 * Deserialisation of this message can be performed by this function.
 *
 * \param[in]     buffer  The buffer into which the structure has been stored.
 * \param[in]     maxLen  Size of \a buffer[].
 * \param[in,out] msg     Pointer to structure for population with deserialised
 *                         message.
 * \returns Size of the deserialised message if successful, otherwise a
 *           negative error code.
 */
s32 CphyNlmErrInd_Deserialise(const u8                  *buffer,
                                      u32                        maxLen,
                                      CphyNlmErrInd *const msg);

#ifdef __cplusplus
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

namespace threeway
{

class CPhyNlmErrInd : public CPhyMessage
{
public:
    /**
     * Construction / destruction.
     */
    CPhyNlmErrInd() { memset(&m_Struct, 0, sizeof(m_Struct)); };
    CPhyNlmErrInd(nlmErrCode_t nlmErrCode) { m_Struct.errCode = nlmErrCode; };
    CPhyNlmErrInd(const CphyNlmErrInd *msg);
    virtual ~CPhyNlmErrInd() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32  GetSerialisationId() const { return SERIALISATION_ID_CPHY_NLM_ERR_IND; };
    virtual s32  Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    /**
     * Implement CPhyMessage pure virtual.
     */
    virtual u32 GetStruct(CphyMessageData *const msg);

    /**
     * Accessors.
     */
    CphyNlmErrInd GetActualStruct() { return m_Struct; }
    nlmErrCode_t GetErrCode() { return m_Struct.errCode; }

    /**
     * Convert to string for debug.
     */
    virtual std::string ToString() const;

private:

    /** Embedded C structure carrying parameters.
     */
    CphyNlmErrInd m_Struct;
};

}

#endif // __cplusplus

#endif // __CPhyHwConfigCnf_h_
