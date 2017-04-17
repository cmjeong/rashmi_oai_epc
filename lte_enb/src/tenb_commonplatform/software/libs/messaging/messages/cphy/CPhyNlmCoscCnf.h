///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyNlmCoscCnf.h 28519 2010-07-21 14:39:46Z mmcternan $
//
// CPhyNlmCoscCnf message.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CPhyNlmCoscCnf_h_
#define __CPhyNlmCoscCnf_h_

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
 * \ingroup CPhyRemGsm
 */

typedef struct CphyNlmCoscCnfTag
{
    /** Status code
     * Normally indicates a sucessful search, but may also indicate errors
     * such as an unsupported band or frequency, or the number of frequencies
     * to scan exceeds maximum supported value.
     */
    l1status_t    status;
    arfcn_t       arfcn;

}
CphyNlmCoscCnf;

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

/** Function to serialise a CphyNlmCoscCnf structure to a buffer.
 * Serialisation of this message can be performed by this function.
 *
 * \param[in] msg         The message to serialise.
 * \param[in,out] buffer  The data buffer into which the data is serialised.
 * \param[in] maxLen       Pointer to size of \a buffer.
 * \returns  Either a negative error code, or the length of the data.
 */
s32 CphyNlmCoscCnf_Serialise(const CphyNlmCoscCnf *msg,
                                    u8 *const                  buffer,
                                    u32                        maxLen);


/** Function to deserialise a CphyNlmCoscCnf structure from a buffer.
 * Deserialisation of this message can be performed by this function.
 *
 * \param[in]     buffer  The buffer into which the structure has been stored.
 * \param[in]     maxLen  Size of \a buffer[].
 * \param[in,out] msg     Pointer to structure for population with deserialised
 *                         message.
 * \returns Size of the deserialised message if successful, otherwise a
 *           negative error code.
 */
s32 CphyNlmCoscCnf_Deserialise(const u8                  *buffer,
                                      u32                        maxLen,
                                      CphyNlmCoscCnf *const msg);

#ifdef __cplusplus
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

namespace threeway
{

class CPhyNlmCoscCnf : public CPhyMessage
{
public:
    /**
     * Construction / destruction.
     */
    CPhyNlmCoscCnf() { memset(&m_Struct, 0, sizeof(m_Struct)); };
    CPhyNlmCoscCnf(const CphyNlmCoscCnf *msg);
    virtual ~CPhyNlmCoscCnf() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32  GetSerialisationId() const { return SERIALISATION_ID_CPHY_NLM_COSC_CNF; };
    virtual s32  Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    /**
     * Implement CPhyMessage pure virtual.
     */
    virtual u32 GetStruct(CphyMessageData *const msg);

    /**
     * Accessors.
     */
    CphyNlmCoscCnf GetActualStruct() { return m_Struct; }
    l1status_t GetStatus() { return m_Struct.status; }
    uint16_t GetCoscArfcn() {return m_Struct.arfcn;}

    /**
     * Convert to string for debug.
     */
    virtual std::string ToString() const;
    virtual std::string ToBriefString() const;

private:

    /** Embedded C structure carrying parameters.
     */
    CphyNlmCoscCnf m_Struct;
};

}

#endif // __cplusplus

#endif // __CPhyHwConfigCnf_h_
