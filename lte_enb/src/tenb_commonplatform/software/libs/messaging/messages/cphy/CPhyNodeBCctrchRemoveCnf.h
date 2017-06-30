///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyNodeBCctrchRemoveCnf.h 7672 2008-09-09 17:17:30Z manderson $
//
// CPhyNodeBCctrchRemoveCnf message.
//
// Copyright radisys Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CPhyNodeBCctrchRemoveCnf_h_
#define __CPhyNodeBCctrchRemoveCnf_h_

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

/** Radio link removal confirmation.
 *
 * \ingroup CPhyNodeB
 */
typedef struct CphyNodeBCctrchRemoveCnfTag
{
    /** Ue number, 0 - ... */
    uint8_t              ue;

    /** Instance Id */
    uint32_t             instanceId;
}
CphyNodeBCctrchRemoveCnf;

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

/** Function to serialise a CPhyNodeBCctrchRemoveCnf structure to a buffer.
 * Serialisation of this message can be performed by this function.
 *
 * \param[in] msg         The message to serialise.
 * \param[in,out] buffer  The data buffer into which the data is serialised.
 * \param[in] maxLen       Pointer to size of \a buffer.
 * \returns  Either a negative error code, or the length of the data.
 */
s32 CPhyNodeBCctrchRemoveCnf_Serialise(const CphyNodeBCctrchRemoveCnf *msg,
                                       u8 *const buffer,
                                       u32       maxLen);


/** Function to deserialise a CPhyNodeBCctrchRemoveCnf structure from a buffer..
 * Deserialisation of this message can be performed by this function.
 *
 * \param[in]     buffer  The buffer into which the structure has been stored.
 * \param[in]     maxLen  Size of \a buffer[].
 * \param[in,out] msg     Pointer to structure for population with deserialised
 *                         message.
 * \returns Size of the deserialised message if successful, otherwise a
 *           negative error code.
 */
s32 CPhyNodeBCctrchRemoveCnf_Deserialise(const u8 *buffer,
                                         u32       maxLen,
                                         CphyNodeBCctrchRemoveCnf *const msg);

#ifdef __cplusplus
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

namespace threeway
{

class CPhyNodeBCctrchRemoveCnf : public CPhyMessage
{
public:
    /**
     * Construction / destruction.
     */
    CPhyNodeBCctrchRemoveCnf  ();
    CPhyNodeBCctrchRemoveCnf (uint8_t ueNumber, uint32_t instanceId);
    CPhyNodeBCctrchRemoveCnf(const CphyNodeBCctrchRemoveCnf &cctrchRemove);
    virtual ~CPhyNodeBCctrchRemoveCnf() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32  GetSerialisationId() const { return SERIALISATION_ID_CPHY_NODEB_CCTRCH_REMOVE_CNF; };
    virtual s32  Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    /**
     * Implement CPhyMessage pure virtual.
     */
    virtual u32 GetStruct(CphyMessageData *const msg);

    /**
     * Accessors.
     */
    uint8_t GetUeNumber () const { return m_cctrchRemoveCnf.ue; }
    uint32_t GetInstanceId () const { return m_cctrchRemoveCnf.instanceId; }

    /**
     * Convert to string for debug.
     */
    virtual std::string ToString() const;
    virtual std::string ToBriefString() const;

private:

    /** Embedded C structure carrying parameters.
     */
    CphyNodeBCctrchRemoveCnf m_cctrchRemoveCnf;
};

}

#endif // __cplusplus

#endif // __CPhyNodeBCctrchRemoveCnf_h_
