///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyNodeBTxDpchEnableCnf.h 5567 2008-05-30 11:13:47Z mm $
//
// CPhyNodeBTxDpchEnableCnf message.
//
// Copyright � Radisys Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CPhyNodeBTxDpchEnableCnf_h_
#define __CPhyNodeBTxDpchEnableCnf_h_

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

/** Confirm giving result of enabling or disabling a transmit DPCHs.
 * \ingroup CPhyNodeB
 */
typedef struct CphyNodeBTxDpchEnableCnfTag
{
    l1status_t     status; /**< Return status. */
}
CphyNodeBTxDpchEnableCnf;

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

/** Function to serialise a CphyNodeBTxDpchEnableCnf structure to a buffer.
 * Serialisation of this message can be performed by this function.
 *
 * \param[in] msg         The message to serialise.
 * \param[in,out] buffer  The data buffer into which the data is serialised.
 * \param[in] maxLen       Pointer to size of \a buffer.
 * \returns  Either a negative error code, or the length of the data.
 */
s32 CphyNodeBTxDpchEnableCnf_Serialise(const     CphyNodeBTxDpchEnableCnf *msg,
                                       u8 *const buffer,
                                       u32       maxLen);


/** Function to deserialise a CphyNodeBTxDpchEnableCnf structure from a buffer..
 * Deserialisation of this message can be performed by this function.
 *
 * \param[in]     buffer  The buffer into which the structure has been stored.
 * \param[in]     maxLen  Size of \a buffer[].
 * \param[in,out] msg     Pointer to structure for population with deserialised
 *                         message.
 * \returns Size of the deserialised message if successful, otherwise a
 *           negative error code.
 */
s32 CphyNodeBTxDpchEnableCnf_Deserialise(const u8 *buffer,
                                u32       maxLen,
                                CphyNodeBTxDpchEnableCnf *const msg);

#ifdef __cplusplus
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

namespace threeway
{

class CPhyNodeBTxDpchEnableCnf : public CPhyMessage
{
public:
    /**
     * Construction / destruction.
     */
    CPhyNodeBTxDpchEnableCnf() { memset(&m_Struct, 0, sizeof(m_Struct)); };
    CPhyNodeBTxDpchEnableCnf(const CphyNodeBTxDpchEnableCnf *msg);
    CPhyNodeBTxDpchEnableCnf(u8 dpchId, bool enable);
    virtual ~CPhyNodeBTxDpchEnableCnf() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32  GetSerialisationId() const { return SERIALISATION_ID_CPHY_NODEB_TX_DPCH_ENABLE_CNF; };
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

private:

    /** Embedded C structure carrying parameters.
     */
    CphyNodeBTxDpchEnableCnf m_Struct;
};

}

#endif // __cplusplus

#endif // __CPhyNodeBTxDpchEnableCnf_h_
