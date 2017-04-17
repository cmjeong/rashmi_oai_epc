///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyRemSibDecodeCnf.h 15300 2009-06-29 11:38:31Z dallwright $
//
// CPhyRemSibDecodeCnf message.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CPhyRemSibDecodeCnf_h_
#define __CPhyRemSibDecodeCnf_h_

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
 #define MAX_PSC_PER_FREQ 6

///////////////////////////////////////////////////////////////////////////////
// Message Structures
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

/** Confirmation that SIB decoding will start or stop.
 * This is sent in response to a CphyRemSibDecodeReq, and confirms that the
 * request has been correctly handled.  If \a L1_SOK is returned as the status,
 * this message will be followed by one or more #CphyRemSibDecodeInd messages
 * that give the actual decoded data.
 *
 * \ingroup CPhyRemWcdma
 */
typedef struct CphyRemSibDecodeCnfTag
{
    l1status_t status;
    
    upsccnt_t  count;
    /** PSC of requested cell for decode. */
    upsc_t     psc[MAX_PSC_PER_FREQ];
}
CphyRemSibDecodeCnf;

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

/** Function to serialise a CphyRemSibDecodeCnf structure to a buffer.
 * Serialisation of this message can be performed by this function.
 *
 * \param[in] msg         The message to serialise.
 * \param[in,out] buffer  The data buffer into which the data is serialised.
 * \param[in] maxLen       Pointer to size of \a buffer.
 * \returns  Either a negative error code, or the length of the data.
 */
s32 CphyRemSibDecodeCnf_Serialise(const CphyRemSibDecodeCnf *msg,
                                  u8 *const                  buffer,
                                  u32                        maxLen);


/** Function to deserialise a CphyRemSibDecodeCnf structure from a buffer.
 * Deserialisation of this message can be performed by this function.
 *
 * \param[in]     buffer  The buffer into which the structure has been stored.
 * \param[in]     maxLen  Size of \a buffer[].
 * \param[in,out] msg     Pointer to structure for population with deserialised
 *                         message.
 * \returns Size of the deserialised message if successful, otherwise a
 *           negative error code.
 */
s32 CphyRemSibDecodeCnf_Deserialise(const u8                  *buffer,
                                    u32                        maxLen,
                                    CphyRemSibDecodeCnf *const msg);

#ifdef __cplusplus
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

namespace threeway
{

class CPhyRemSibDecodeCnf : public CPhyMessage
{
public:
    /**
     * Construction / destruction.
     */
    CPhyRemSibDecodeCnf() { memset(&m_Struct, 0, sizeof(m_Struct)); };
    CPhyRemSibDecodeCnf(const CphyRemSibDecodeCnf *msg);
    virtual ~CPhyRemSibDecodeCnf() {};
    CPhyRemSibDecodeCnf(upsc_t psc);

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32  GetSerialisationId() const { return SERIALISATION_ID_CPHY_REM_SIB_DECODE_CNF; };
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
    CphyRemSibDecodeCnf m_Struct;
};

}

#endif // __cplusplus

#endif // __CPhyHwConfigCnf_h_
