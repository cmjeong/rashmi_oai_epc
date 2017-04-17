///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyRemGsmStopBcchDecodeReq.h 15300 2009-06-29 11:38:31Z dallwright $
//
// CPhyRemGsmStopBcchDecodeReq message.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CPhyRemGsmStopBcchDecodeReq_h_
#define __CPhyRemGsmStopBcchDecodeReq_h_

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

/** Stop any ongoing BCCH decoding.
 * After a sucessful cell search, BCCH decoding will automatically start.
 * Sending this message stops BCCH decoding such that a new search can then be
 * started or the Layer 1 mode changed.
 *
 * \ingroup CPhyRemGsm
 */
typedef struct CphyRemGsmStopBcchDecodeReqTag
{
    uint8_t dummy;
}
CphyRemGsmStopBcchDecodeReq;

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

/** Function to serialise a CphyRemGsmStopBcchDecodeReq structure to a buffer.
 * Serialisation of this message can be performed by this function.
 *
 * \param[in] msg         The message to serialise.
 * \param[in,out] buffer  The data buffer into which the data is serialised.
 * \param[in] maxLen       Pointer to size of \a buffer.
 * \returns  Either a negative error code, or the length of the data.
 */
s32 CphyRemGsmStopBcchDecodeReq_Serialise(const CphyRemGsmStopBcchDecodeReq *msg,
                                          u8 *const                  buffer,
                                          u32                        maxLen);


/** Function to deserialise a CphyRemGsmStopBcchDecodeReq structure from a buffer.
 * Deserialisation of this message can be performed by this function.
 *
 * \param[in]     buffer  The buffer into which the structure has been stored.
 * \param[in]     maxLen  Size of \a buffer[].
 * \param[in,out] msg     Pointer to structure for population with deserialised
 *                         message.
 * \returns Size of the deserialised message if successful, otherwise a
 *           negative error code.
 */
s32 CphyRemGsmStopBcchDecodeReq_Deserialise(const u8                  *buffer,
                                            u32                        maxLen,
                                            CphyRemGsmStopBcchDecodeReq *const msg);

#ifdef __cplusplus
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

namespace threeway
{

class CPhyRemGsmStopBcchDecodeReq : public CPhyMessage
{
public:
    /**
     * Construction / destruction.
     */
    CPhyRemGsmStopBcchDecodeReq() { memset(&m_Struct, 0, sizeof(m_Struct)); };
    CPhyRemGsmStopBcchDecodeReq(const CphyRemGsmStopBcchDecodeReq *msg);
    virtual ~CPhyRemGsmStopBcchDecodeReq() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32  GetSerialisationId() const { return SERIALISATION_ID_CPHY_REM_GSM_STOP_BCCH_DECODE_REQ; };
    virtual s32  Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    /**
     * Implement CPhyMessage pure virtual.
     */
    virtual u32 GetStruct(CphyMessageData *const msg);

    /**
     * Accessors.
     */
    // None

    /**
     * Convert to string for debug.
     */
    virtual std::string ToString() const;

private:

    /** Embedded C structure carrying parameters.
     */
    CphyRemGsmStopBcchDecodeReq m_Struct;
};

}

#endif // __cplusplus

#endif // __CPhyHwConfigReq_h_
