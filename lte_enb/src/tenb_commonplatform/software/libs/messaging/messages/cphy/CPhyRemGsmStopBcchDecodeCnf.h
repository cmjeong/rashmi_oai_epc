///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyRemGsmStopBcchDecodeCnf.h 28519 2010-07-21 14:39:46Z mmcternan $
//
// CPhyRemGsmStopBcchDecodeCnf message.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CPhyRemGsmStopBcchDecodeCnf_h_
#define __CPhyRemGsmStopBcchDecodeCnf_h_

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

/** Confirmation that BCCH decoding has stopped.
 * Sent in response to a CphyRemGsmStopBcchDecodeReq, this confirms that
 * decoding has been completed and that no further CphyRemGsmBcchDecodeInd
 * messages will be sent.  If decoding was not active at the time of the
 * stop request, this message will return an error status.
 *
 * \ingroup CPhyRemGsm
 */
typedef struct CphyRemGsmStopBcchDecodeCnfTag
{
    l1status_t  status;
}
CphyRemGsmStopBcchDecodeCnf;

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

/** Function to serialise a CphyRemGsmStopBcchDecodeCnf structure to a buffer.
 * Serialisation of this message can be performed by this function.
 *
 * \param[in] msg         The message to serialise.
 * \param[in,out] buffer  The data buffer into which the data is serialised.
 * \param[in] maxLen       Pointer to size of \a buffer.
 * \returns  Either a negative error code, or the length of the data.
 */
s32 CphyRemGsmStopBcchDecodeCnf_Serialise(const CphyRemGsmStopBcchDecodeCnf *msg,
                                          u8 *const                  buffer,
                                          u32                        maxLen);


/** Function to deserialise a CphyRemGsmStopBcchDecodeCnf structure from a buffer.
 * Deserialisation of this message can be performed by this function.
 *
 * \param[in]     buffer  The buffer into which the structure has been stored.
 * \param[in]     maxLen  Size of \a buffer[].
 * \param[in,out] msg     Pointer to structure for population with deserialised
 *                         message.
 * \returns Size of the deserialised message if successful, otherwise a
 *           negative error code.
 */
s32 CphyRemGsmStopBcchDecodeCnf_Deserialise(const u8                  *buffer,
                                            u32                        maxLen,
                                            CphyRemGsmStopBcchDecodeCnf *const msg);

#ifdef __cplusplus
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

namespace threeway
{

class CPhyRemGsmStopBcchDecodeCnf : public CPhyMessage
{
public:
    /**
     * Construction / destruction.
     */
    CPhyRemGsmStopBcchDecodeCnf() { memset(&m_Struct, 0, sizeof(m_Struct)); };
    CPhyRemGsmStopBcchDecodeCnf(const CphyRemGsmStopBcchDecodeCnf *msg);
    virtual ~CPhyRemGsmStopBcchDecodeCnf() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32  GetSerialisationId() const { return SERIALISATION_ID_CPHY_REM_GSM_STOP_BCCH_DECODE_CNF; };
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
    virtual std::string ToBriefString() const;

private:

    /** Embedded C structure carrying parameters.
     */
    CphyRemGsmStopBcchDecodeCnf m_Struct;
};

}

#endif // __cplusplus

#endif // __CPhyHwConfigCnf_h_
