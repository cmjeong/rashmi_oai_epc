///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyModeChangeCnf.h 28310 2010-07-16 15:27:29Z mmcternan $
//
// CPhyModeChangeCnf message.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CPhyModeChangeCnf_h_
#define __CPhyModeChangeCnf_h_

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

/** Confirm Layer 1 operating state change.
 * \ingroup CPhyNull
 */
typedef struct CphyModeChangeCnfTag
{
    l1mode_t mode;       /**< The new desired operating mode. */
    l1status_t status;   /**< The result. */
}
CphyModeChangeCnf;

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

/** Function to serialise a CphyModeChangeCnf structure to a buffer.
 * Serialisation of this message can be performed by this function.
 *
 * \param[in] msg         The message to serialise.
 * \param[in,out] buffer  The data buffer into which the data is serialised.
 * \param[in] maxLen       Pointer to size of \a buffer.
 * \returns  Either a negative error code, or the length of the data.
 */
s32 CphyModeChangeCnf_Serialise(const CphyModeChangeCnf *msg, u8 *const buffer, u32 maxLen);


/** Function to deserialise a CphyModeChangeCnf structure from some buffer
 * Deserialisation of this message can be performed by this function.
 *
 * \param[in]     buffer  The buffer into which the structure has been stored.
 * \param[in]     maxLen  Size of \a buffer[].
 * \param[in,out] msg     Pointer to structure for population with deserialised
 *                         message.
 * \returns Size of the deserialised message if successful, otherwise a
 *           negative error code.
 */
s32 CphyModeChangeCnf_Deserialise(const u8 *buffer, u32 maxLen, CphyModeChangeCnf *const msg);

#ifdef __cplusplus
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

namespace threeway
{

class CPhyModeChangeCnf : public CPhyMessage
{
public:
    /**
     * Construction / destruction.
     */
    CPhyModeChangeCnf() { memset(&m_Struct, 0, sizeof(m_Struct)); };
    CPhyModeChangeCnf(const CphyModeChangeCnf *cStruct);
    virtual ~CPhyModeChangeCnf() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32  GetSerialisationId() const { return SERIALISATION_ID_CPHY_MODE_CHANGE_CNF; };
    virtual s32  Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    /**
     * Implement CphyMessage pure virtual.
     */
    virtual u32 GetStruct(CphyMessageData *const msg);

    /**
     * Accessors.
     */
    l1status_t GetStatus() const { return m_Struct.status; }
    l1mode_t GetMode() const { return m_Struct.mode; }

    /**
     * Convert to string for debug.
     */
    virtual std::string ToString() const;
    virtual std::string ToBriefString() const;

private:

    /** Embedded C structure carrying parameters.
     */
    CphyModeChangeCnf m_Struct;
};

}

#endif /* __cplusplus */

#endif
