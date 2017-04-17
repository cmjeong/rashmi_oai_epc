///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyNodeBConfigCnf.h 28310 2010-07-16 15:27:29Z mmcternan $
//
// CPhyNodeBConfigCnf message.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CPhyNodeBConfigCnf_h_
#define __CPhyNodeBConfigCnf_h_

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

/** Node B configuration result.
 * Sent in response to a #CphyNodeBConfigReq, this indicates whether
 * configuration was sucessful or not.  Failure causes are likely to indicate
 * some problem with the parameters sent in the request (e.g. invalid
 * downlink UARFCN/band combination), or that Layer 1 is not configured for
 * Node B operation.
 *
 * \ingroup CPhyNodeB
 */
typedef struct CphyNodeBConfigCnfTag
{
    l1status_t     status; /**< Return status. */
}
CphyNodeBConfigCnf;

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

/** Function to serialise a CphyNodeBConfigCnf structure to a buffer.
 * Serialisation of this message can be performed by this function.
 *
 * \param[in] msg         The message to serialise.
 * \param[in,out] buffer  The data buffer into which the data is serialised.
 * \param[in] maxLen       Pointer to size of \a buffer.
 * \returns  Either a negative error code, or the length of the data.
 */
s32 CphyNodeBConfigCnf_Serialise(const CphyNodeBConfigCnf *msg,
                              u8 *const buffer,
                              u32       maxLen);


/** Function to deserialise a CphyNodeBConfigCnf structure from a buffer..
 * Deserialisation of this message can be performed by this function.
 *
 * \param[in]     buffer  The buffer into which the structure has been stored.
 * \param[in]     maxLen  Size of \a buffer[].
 * \param[in,out] msg     Pointer to structure for population with deserialised
 *                         message.
 * \returns Size of the deserialised message if successful, otherwise a
 *           negative error code.
 */
s32 CphyNodeBConfigCnf_Deserialise(const u8 *buffer,
                                u32       maxLen,
                                CphyNodeBConfigCnf *const msg);

#ifdef __cplusplus
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

namespace threeway
{

class CPhyNodeBConfigCnf : public CPhyMessage
{
public:
    /**
     * Construction / destruction.
     */
    CPhyNodeBConfigCnf() { memset(&m_Struct, 0, sizeof(m_Struct)); };
    CPhyNodeBConfigCnf(const CphyNodeBConfigCnf *msg);
    virtual ~CPhyNodeBConfigCnf() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32  GetSerialisationId() const { return SERIALISATION_ID_CPHY_NODEB_CONFIG_CNF; };
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
    CphyNodeBConfigCnf m_Struct;
};

}

#endif // __cplusplus

#endif // __CPhyNodeBConfigCnf_h_
