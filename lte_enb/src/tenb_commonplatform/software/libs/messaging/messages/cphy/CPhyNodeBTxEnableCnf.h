///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyNodeBTxEnableCnf.h 28310 2010-07-16 15:27:29Z mmcternan $
//
// CPhyNodeBTxEnableCnf message.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CPhyNodeBTxEnableCnf_h_
#define __CPhyNodeBTxEnableCnf_h_

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
 * \ingroup CPhyNodeB
 */
typedef struct CphyNodeBTxEnableCnfTag
{
    l1status_t     status; /**< Return status. */
}
CphyNodeBTxEnableCnf;

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

/** Function to serialise a CphyNodeBTxEnableCnf structure to a buffer.
 * Serialisation of this message can be performed by this function.
 *
 * \param[in] msg         The message to serialise.
 * \param[in,out] buffer  The data buffer into which the data is serialised.
 * \param[in] maxLen       Pointer to size of \a buffer.
 * \returns  Either a negative error code, or the length of the data.
 */
s32 CphyNodeBTxEnableCnf_Serialise(const CphyNodeBTxEnableCnf *msg,
                              u8 *const buffer,
                              u32       maxLen);


/** Function to deserialise a CphyNodeBTxEnableCnf structure from a buffer..
 * Deserialisation of this message can be performed by this function.
 *
 * \param[in]     buffer  The buffer into which the structure has been stored.
 * \param[in]     maxLen  Size of \a buffer[].
 * \param[in,out] msg     Pointer to structure for population with deserialised
 *                         message.
 * \returns Size of the deserialised message if successful, otherwise a
 *           negative error code.
 */
s32 CphyNodeBTxEnableCnf_Deserialise(const u8 *buffer,
                                u32       maxLen,
                                CphyNodeBTxEnableCnf *const msg);

#ifdef __cplusplus
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

namespace threeway
{

class CPhyNodeBTxEnableCnf : public CPhyMessage
{
public:
    /**
     * Construction / destruction.
     */
    CPhyNodeBTxEnableCnf() { memset(&m_Struct, 0, sizeof(m_Struct)); };
    CPhyNodeBTxEnableCnf(const CphyNodeBTxEnableCnf *msg);
    virtual ~CPhyNodeBTxEnableCnf() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32  GetSerialisationId() const { return SERIALISATION_ID_CPHY_NODEB_TX_ENABLE_CNF; };
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
    CphyNodeBTxEnableCnf m_Struct;
};

}

#endif // __cplusplus

#endif // __CPhyNodeBTxEnableCnf_h_
