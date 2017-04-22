///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyNodeBPchAddCnf.h 28331 2010-07-17 15:25:20Z mmcternan $
//
// CPhyNodeBPchAddCnf message.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CPhyNodeBPchAddCnf_h_
#define __CPhyNodeBPchAddCnf_h_

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

/** Paging block addition confirmation.
 * This is sent in response to a #CphyNodeBPchAddReq to indicate whether the
 * request suceeded or failed.  It contains both the requested \a sfnOffset
 * and \a tag such that the response can be matched to its request in the case
 * that multiple #CphyNodeBPchAddReq messages are sent.
 *
 * \see CphyNodeBPchAddReq
 * \ingroup CPhyNodeB
 */

typedef struct CphyNodeBPchAddCnfTag
{
    l1status_t     status;     /**< Return status. */
    uint16_t       sfnOffset;  /**< SFN at which the block was added */
}
CphyNodeBPchAddCnf;

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

/** Function to serialise a CphyNodeBPchAddCnf structure to a buffer.
 * Serialisation of this message can be performed by this function.
 *
 * \param[in] msg         The message to serialise.
 * \param[in,out] buffer  The data buffer into which the data is serialised.
 * \param[in] maxLen       Pointer to size of \a buffer.
 * \returns  Either a negative error code, or the length of the data.
 */
s32 CphyNodeBPchAddCnf_Serialise(const CphyNodeBPchAddCnf *msg,
                              u8 *const buffer,
                              u32       maxLen);


/** Function to deserialise a CphyNodeBPchAddCnf structure from a buffer..
 * Deserialisation of this message can be performed by this function.
 *
 * \param[in]     buffer  The buffer into which the structure has been stored.
 * \param[in]     maxLen  Size of \a buffer[].
 * \param[in,out] msg     Pointer to structure for population with deserialised
 *                         message.
 * \returns Size of the deserialised message if successful, otherwise a
 *           negative error code.
 */
s32 CphyNodeBPchAddCnf_Deserialise(const u8 *buffer,
                                u32       maxLen,
                                CphyNodeBPchAddCnf *const msg);

#ifdef __cplusplus
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

namespace threeway
{

class CPhyNodeBPchAddCnf : public CPhyMessage
{
public:
    /**
     * Construction / destruction.
     */
    CPhyNodeBPchAddCnf() { memset(&m_Struct, 0, sizeof(m_Struct)); };
    CPhyNodeBPchAddCnf(const CphyNodeBPchAddCnf *msg);
    virtual ~CPhyNodeBPchAddCnf() {};
    CPhyNodeBPchAddCnf(upsc_t psc, bool updateDac);

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32  GetSerialisationId() const { return SERIALISATION_ID_CPHY_NODEB_PCH_ADD_CNF; };
    virtual s32  Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    /**
     * Implement CPhyMessage pure virtual.
     */
    virtual u32 GetStruct(CphyMessageData *const msg);

    /**
     * Accessors.
     */
    l1status_t GetStatus() const;

    /**
     * Convert to string for debug.
     */
    virtual std::string ToString() const;
    virtual std::string ToBriefString() const;

private:

    /** Embedded C structure carrying parameters.
     */
    CphyNodeBPchAddCnf m_Struct;
};

}

#endif // __cplusplus

#endif // __CPhyNodeBPchAddCnf_h_
