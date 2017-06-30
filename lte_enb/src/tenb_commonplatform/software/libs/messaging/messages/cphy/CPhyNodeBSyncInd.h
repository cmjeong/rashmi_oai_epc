///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyNodeBSyncInd.h 28310 2010-07-16 15:27:29Z mmcternan $
//
// CPhyNodeBSyncInd message.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CPhyNodeBSyncInd_h_
#define __CPhyNodeBSyncInd_h_

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

/** Inidication that an uplink Cctrch is deemed in-sync.
 * \ingroup CPhyNodeB
 * \see 25.214, secion 4.3.3.2, "Uplink radio link failure/restore".
 */
typedef struct CphyNodeBSyncIndTag
{
    uint8_t         ue;     /**< The UE to which this applies. */
}
CphyNodeBSyncInd;

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

/** Function to serialise a CphyNodeBSyncInd structure to a buffer.
 * Serialisation of this message can be performed by this function.
 *
 * \param[in] msg         The message to serialise.
 * \param[in,out] buffer  The data buffer into which the data is serialised.
 * \param[in] maxLen       Pointer to size of \a buffer.
 * \returns  Either a negative error code, or the length of the data.
 */
s32 CphyNodeBSyncInd_Serialise(const CphyNodeBSyncInd *msg,
                               u8 *const buffer,
                               u32       maxLen);


/** Function to deserialise a CphyNodeBSyncInd structure from a buffer..
 * Deserialisation of this message can be performed by this function.
 *
 * \param[in]     buffer  The buffer into which the structure has been stored.
 * \param[in]     maxLen  Size of \a buffer[].
 * \param[in,out] msg     Pointer to structure for population with deserialised
 *                         message.
 * \returns Size of the deserialised message if successful, otherwise a
 *           negative error code.
 */
s32 CphyNodeBSyncInd_Deserialise(const u8 *buffer,
                                 u32       maxLen,
                                 CphyNodeBSyncInd *const msg);

#ifdef __cplusplus
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

namespace threeway
{

class CPhyNodeBSyncInd : public CPhyMessage
{
public:
    /**
     * Construction / destruction.
     */
    CPhyNodeBSyncInd() { memset(&m_Struct, 0, sizeof(m_Struct)); };
    CPhyNodeBSyncInd(const CphyNodeBSyncInd *msg);
    virtual ~CPhyNodeBSyncInd() {};
    CPhyNodeBSyncInd(upsc_t psc, bool updateDac);

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32  GetSerialisationId() const { return SERIALISATION_ID_CPHY_NODEB_SYNC_IND; };
    virtual s32  Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    /**
     * Implement CPhyMessage pure virtual.
     */
    virtual u32 GetStruct(CphyMessageData *const msg);

    /**
     * Accessors.
     */
    u32 GetUeNumber () const { return m_Struct.ue; }

    /**
     * Convert to string for debug.
     */
    virtual std::string ToString() const;
    virtual std::string ToBriefString() const;

private:

    /** Embedded C structure carrying parameters.
     */
    CphyNodeBSyncInd m_Struct;
};

}

#endif // __cplusplus

#endif // __CPhyNodeBSyncInd_h_
