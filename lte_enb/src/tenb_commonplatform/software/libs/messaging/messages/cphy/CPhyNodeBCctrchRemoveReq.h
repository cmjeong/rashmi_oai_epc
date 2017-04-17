///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyNodeBCctrchRemoveReq.h 7672 2008-09-09 17:17:30Z manderson $
//
// CPhyNodeBCctrchRemoveReq message.
//
// Copyright radisys Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CPhyNodeBCctrchRemoveReq_h_
#define __CPhyNodeBCctrchRemoveReq_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

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

/** Radio link removal.
 *
 * \ingroup CPhyNodeB
 */
typedef struct CphyNodeBCctrchRemoveReqTag
{
    /** Activation time. */
    l1_activation_time_t actTime;

    /** Ue number, 0 - ... */
    uint8_t              ue;

    /** Instance Id */
    uint32_t             instanceId;
}
CphyNodeBCctrchRemoveReq;

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

/** Function to serialise a CPhyNodeBCctrchRemoveReq structure to a buffer.
 * Serialisation of this message can be performed by this function.
 *
 * \param[in] msg         The message to serialise.
 * \param[in,out] buffer  The data buffer into which the data is serialised.
 * \param[in] maxLen       Pointer to size of \a buffer.
 * \returns  Either a negative error code, or the length of the data.
 */
s32 CPhyNodeBCctrchRemoveReq_Serialise(const CphyNodeBCctrchRemoveReq *msg,
                                       u8 *const buffer,
                                       u32       maxLen);


/** Function to deserialise a CPhyNodeBCctrchRemoveReq structure from a buffer..
 * Deserialisation of this message can be performed by this function.
 *
 * \param[in]     buffer  The buffer into which the structure has been stored.
 * \param[in]     maxLen  Size of \a buffer[].
 * \param[in,out] msg     Pointer to structure for population with deserialised
 *                         message.
 * \returns Size of the deserialised message if successful, otherwise a
 *           negative error code.
 */
s32 CPhyNodeBCctrchRemoveReq_Deserialise(const u8 *buffer,
                                         u32       maxLen,
                                         CphyNodeBCctrchRemoveReq *const msg);

#ifdef __cplusplus
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

namespace threeway
{

class CPhyNodeBCctrchRemoveReq : public CPhyMessage
{
public:
    /**
     * Construction / destruction.
     */
    CPhyNodeBCctrchRemoveReq  ();
    CPhyNodeBCctrchRemoveReq (uint8_t ueNumber, uint32_t instanceId); // Default activationTime to NOW
    CPhyNodeBCctrchRemoveReq (uint8_t ueNumber, uint32_t instanceId, uint16_t activationTime);
    CPhyNodeBCctrchRemoveReq(const CPhyNodeBCctrchRemoveReq &cctrchRemove);
    virtual ~CPhyNodeBCctrchRemoveReq() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32  GetSerialisationId() const { return SERIALISATION_ID_CPHY_NODEB_CCTRCH_REMOVE_REQ; };
    virtual s32  Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    /**
     * Implement CPhyMessage pure virtual.
     */
    virtual u32 GetStruct(CphyMessageData *const msg);

    /**
     * Accessors.
     */
    const l1_activation_time_t &GetActivationTime () const { return m_cctrchRemoveReq.actTime; }
    uint8_t GetUeNumber () const { return m_cctrchRemoveReq.ue; }
    uint32_t GetInstanceId () const { return m_cctrchRemoveReq.instanceId; }

    /**
     * Convert to string for debug.
     */
    virtual std::string ToString() const;
    virtual std::string ToBriefString() const;

private:

    /** Embedded C structure carrying parameters.
     */
    CphyNodeBCctrchRemoveReq m_cctrchRemoveReq;
};

}

#endif // __cplusplus

#endif // __CPhyNodeBCctrchRemoveReq_h_
