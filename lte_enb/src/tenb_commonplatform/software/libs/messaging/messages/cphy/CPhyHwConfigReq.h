///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyHwConfigReq.h 28310 2010-07-16 15:27:29Z mmcternan $
//
// CPhyHwConfigCnf message.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CPhyHwConfigReq_h_
#define __CPhyHwConfigReq_h_

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

/** Hardware configuration parameters.
 * Request to configure the hardware plaform such that the radio, FPGAs and
 * any other peripherals relating to Layer 1 functionality are made ready
 * for use.
 *
 * This message is only accepted by Layer 1 when in the pre-initialised state,
 * and upon success moves Layer 1 to \ref CPhyNull "NULL mode".
 *
 * \ingroup CPhyPreInit
 */
typedef struct CphyHwConfigReqTag
{
    uint8_t   hwType;           /**< Major hardware version number. */
    uint8_t   hwRevision;       /**< Minor hardware version. */
    uint8_t   hwModLevel;       /**< Hardware mod version. */
    uint16_t  afcDacValue;      /**< Desired AFC DAC output value. */
    int16_t   afcDacSlopePpt;   /**< AFC DAC slope given in parts-per-trillion. */
    uint32_t  txPowerAmpGaindB; /**< If an external PA is in use, the gain it provides in dB. */
    bool      allowDefaultCal;  /**< If true then the PHY is allowed to use default calibration data. */
}
CphyHwConfigReq;

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

/** Function to serialise a CphyHwConfigReq structure to a buffer.
 * Serialisation of this message can be performed by this function.
 *
 * \param[in] msg         The message to serialise.
 * \param[in,out] buffer  The data buffer into which the data is serialised.
 * \param[in] maxLen       Pointer to size of \a buffer.
 * \returns  Either a negative error code, or the length of the data.
 */
s32 CphyHwConfigReq_Serialise(const CphyHwConfigReq *msg,
                              u8 *const buffer,
                              u32       maxLen);


/** Function to deserialise a CphyHwConfigReq structure from a buffer..
 * Deserialisation of this message can be performed by this function.
 *
 * \param[in]     buffer  The buffer into which the structure has been stored.
 * \param[in]     maxLen  Size of \a buffer[].
 * \param[in,out] msg     Pointer to structure for population with deserialised
 *                         message.
 * \returns Size of the deserialised message if successful, otherwise a
 *           negative error code.
 */
s32 CphyHwConfigReq_Deserialise(const u8 *buffer,
                                u32       maxLen,
                                CphyHwConfigReq *const msg);

#ifdef __cplusplus
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

namespace threeway
{

class CPhyHwConfigReq : public CPhyMessage
{
public:
    /**
     * Construction / destruction.
     */
    CPhyHwConfigReq() { memset(&m_Struct, 0, sizeof(m_Struct)); };
    CPhyHwConfigReq(const CphyHwConfigReq *msg);
    virtual ~CPhyHwConfigReq() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32  GetSerialisationId() const { return SERIALISATION_ID_CPHY_HW_CONFIG_REQ; };
    virtual s32  Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    /**
     * Implement CPhyMessage pure virtual.
     */
    virtual u32 GetStruct(CphyMessageData *const msg);

    /**
     * Accessors.
     */
    u8 GetHardwareType() const { return m_Struct.hwType;}
    u8 GetHardwareRevision() const { return m_Struct.hwRevision;}
    u8 GetHardwareModState() const { return m_Struct.hwModLevel;}
    u16 GetAfcDacValue() const { return m_Struct.afcDacValue;}
    s16 GetAfcDacSlopePpt() const { return m_Struct.afcDacSlopePpt;}

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
    CphyHwConfigReq m_Struct;
};

}

#endif // __cplusplus

#endif // __CPhyHwConfigReq_h_
