///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyNodeBCctrchCnf.h 8631 2008-10-16 09:55:40Z manderson $
//
// CPhyNodeBCctrchCnf message.
//
// Copyright radisys Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CPhyNodeBCctrchCnf_h_
#define __CPhyNodeBCctrchCnf_h_

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

/** Confirmations for Cctrch messages.
 *
 * \ingroup CPhyNodeB
 */
typedef struct CphyNodeBCctrchCnfTag
{
    /** Status code.
     * Either L1_SOK or an error code.  In the case of an error, no
     * configuration changes will have occured.  Likely error causes will be
     * due to requests for incomplete or missing functionality.
     */
    l1status_t          status;
}
CphyNodeBCctrchCnf;

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

/** Function to serialise a CPhyNodeBCctrchCnf structure to a buffer.
 * Serialisation of this message can be performed by this function.
 *
 * \param[in] msg         The message to serialise.
 * \param[in,out] buffer  The data buffer into which the data is serialised.
 * \param[in] maxLen       Pointer to size of \a buffer.
 * \returns  Either a negative error code, or the length of the data.
 */
s32 CPhyNodeBCctrchCnf_Serialise(const CphyNodeBCctrchCnf *msg,
                                 u8 *const buffer,
                                 u32       maxLen);


/** Function to deserialise a CPhyNodeBCctrchCnf structure from a buffer..
 * Deserialisation of this message can be performed by this function.
 *
 * \param[in]     buffer  The buffer into which the structure has been stored.
 * \param[in]     maxLen  Size of \a buffer[].
 * \param[in,out] msg     Pointer to structure for population with deserialised
 *                         message.
 * \returns Size of the deserialised message if successful, otherwise a
 *           negative error code.
 */
s32 CPhyNodeBCctrchCnf_Deserialise(const u8 *buffer,
                                   u32       maxLen,
                                   CphyNodeBCctrchCnf *const msg);

#ifdef __cplusplus
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

namespace threeway
{

class CPhyNodeBCctrchCnf : public CPhyMessage
{
public:
    /**
     * Construction / destruction.
     */
    CPhyNodeBCctrchCnf();
    CPhyNodeBCctrchCnf(l1status_t l1Status);
    CPhyNodeBCctrchCnf(const CPhyNodeBCctrchCnf *msg);
    virtual ~CPhyNodeBCctrchCnf() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32  GetSerialisationId() const { return SERIALISATION_ID_CPHY_NODEB_CCTRCH_CNF; };
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
    CphyNodeBCctrchCnf m_l1Status;
};

}

#endif // __cplusplus

#endif // __CPhyNodeBCctrchCnf_h_
