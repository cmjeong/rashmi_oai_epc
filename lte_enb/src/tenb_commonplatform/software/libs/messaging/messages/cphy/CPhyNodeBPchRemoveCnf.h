///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyNodeBPchRemoveCnf.h 28647 2010-07-26 08:55:18Z mmcternan $
//
// CPhyNodeBPchRemoveCnf message.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CPhyNodeBPchRemoveCnf_h_
#define __CPhyNodeBPchRemoveCnf_h_

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

/** Confirmation that some block has been removed from the scheduling roster.
 * This is sent to indicate that some block has been removed from the PCH
 * transmission roster.  In the case that the block was found and removed,
 * #L1_SOK will be returned.  If the block could not be found, for example
 * because it has naturally expired, some other error code will be returned.
 *
 * \see CphyNodeBPchRemoveReq
 * \ingroup CPhyNodeB
 */
typedef struct CphyNodeBPchRemoveCnfTag
{
    l1status_t     status;     /**< Return status. */
    uint16_t       sfnOffset;  /**< SFN at which the block was removed */
}
CphyNodeBPchRemoveCnf;

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

/** Function to serialise a CphyNodeBPchRemoveCnf structure to a buffer.
 * Serialisation of this message can be performed by this function.
 *
 * \param[in] msg         The message to serialise.
 * \param[in,out] buffer  The data buffer into which the data is serialised.
 * \param[in] maxLen       Pointer to size of \a buffer.
 * \returns  Either a negative error code, or the length of the data.
 */
s32 CphyNodeBPchRemoveCnf_Serialise(const CphyNodeBPchRemoveCnf *msg,
                                    u8 *const buffer,
                                    u32       maxLen);


/** Function to deserialise a CphyNodeBPchRemoveCnf structure from a buffer..
 * Deserialisation of this message can be performed by this function.
 *
 * \param[in]     buffer  The buffer into which the structure has been stored.
 * \param[in]     maxLen  Size of \a buffer[].
 * \param[in,out] msg     Pointer to structure for population with deserialised
 *                         message.
 * \returns Size of the deserialised message if successful, otherwise a
 *           negative error code.
 */
s32 CphyNodeBPchRemoveCnf_Deserialise(const u8 *buffer,
                                      u32       maxLen,
                                      CphyNodeBPchRemoveCnf *const msg);

#ifdef __cplusplus
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

namespace threeway
{

class CPhyNodeBPchRemoveCnf : public CPhyMessage
{
public:
    /**
     * Construction / destruction.
     */
    CPhyNodeBPchRemoveCnf() { memset(&m_Struct, 0, sizeof(m_Struct)); };
    CPhyNodeBPchRemoveCnf(const CphyNodeBPchRemoveCnf *msg);
    virtual ~CPhyNodeBPchRemoveCnf() {};
    CPhyNodeBPchRemoveCnf(upsc_t psc, bool updateDac);

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32  GetSerialisationId() const { return SERIALISATION_ID_CPHY_NODEB_PCH_REMOVE_CNF; };
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
    CphyNodeBPchRemoveCnf m_Struct;
};

}

#endif // __cplusplus

#endif // __CPhyNodeBPchRemoveCnf_h_
