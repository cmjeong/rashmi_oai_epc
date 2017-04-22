///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyNodeBConfigReq.h 29075 2010-08-11 08:45:04Z mmcternan $
//
// CPhyNodeBConfigReq message.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CPhyNodeBConfigReq_h_
#define __CPhyNodeBConfigReq_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
#include <string.h>
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

/** Number of uplink scrambling codes sent in the message.
 */
#define NUM_CPHY_UL_SCRAMBLING_CODES 4

///////////////////////////////////////////////////////////////////////////////
// Message Structures
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

/** Channels for which the Tx gain can be independently set.
 */
typedef enum
{
    CPHY_NODEB_TX_POWER_OFFSET_PCCPCH = 0,
    CPHY_NODEB_TX_POWER_OFFSET_SCH,
    CPHY_NODEB_TX_POWER_OFFSET_SCCPCH,
    CPHY_NODEB_TX_POWER_OFFSET_PICH,
    CPHY_NODEB_TX_POWER_OFFSET_AICH,
    CPHY_NODEB_TX_POWER_OFFSET_HSSCCH,

    NUM_CPHY_NODEB_TX_CTRL_CHAN_POWER_OFFSETS
}
cphy_nodeb_tx_channel_gain_t;

/** Node B configuration parameters.
 * \ingroup CPhyNodeB
 */
typedef struct CphyNodeBConfigReqTag
{
    /** Downlink ARFCN on which to transmit. */
    uarfcn_t    dlArfcn;

    /** Band of operation. */
    uband_t     band;

    /** Primary Scrambling Code, as used on the downlink P-CCPCH. */
    uint16_t    psc;

    /** Transmit power given in 1/8ths of a dBm. */
    int16_t     txPowerDbm8;

    /** Transmit CPICH power in 1/8ths of a dBm.
     * Transmit CPICH power in 1/8ths of a dBm. Valid range is -10dBm to +10dBm.
     */
    int16_t     cpichPowerDbm8;

    /** Transmit control channel power offsets in 1/8ths of a dB.
     * Transmit control channel power offsets relative to CPICH power in 1/8ths
     * of a dB. Valid range is TBC (-22dB to +9dB).
     */
    int16_t     txCtrlChannelPowerOffsetDb8[NUM_CPHY_NODEB_TX_CTRL_CHAN_POWER_OFFSETS];

    /** Maximum DPCH power offset in 1/8ths of a dB.
     * Maximum DPCH power offset relative to maximum transmit power in 1/8ths of a dB.
     * Valid range is -28dB to -3dB.
     */
    int16_t     txMaxDpchPowerOffsetDb8;

    /** Maximum HS-PDSCH power offset in 1/8ths of a dB.
     * Maximum HS-PDSCH power offset relative to CPICH power in 1/8ths of a dB. Valid
     * range is -6dB to +13dB.
     */
    int16_t     txMaxHspdschPowerOffsetDb8;

    /** T_RLFAILURE timer to use, given in 10ms ticks.
     */
    uint16_t    t_rfFailure;

    /** N_INSYNC_IND value to use.
     */
    uint16_t    n_insync_ind;

    /** N_OUTSYNC_IND value to use.
     */
    uint16_t    n_outsync_ind;
}
CphyNodeBConfigReq;

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

/** Function to serialise a CphyNodeBConfigReq structure to a buffer.
 * Serialisation of this message can be performed by this function.
 *
 * \param[in] msg         The message to serialise.
 * \param[in,out] buffer  The data buffer into which the data is serialised.
 * \param[in] maxLen       Pointer to size of \a buffer.
 * \returns  Either a negative error code, or the length of the data.
 */
s32 CphyNodeBConfigReq_Serialise(const CphyNodeBConfigReq *msg,
                                 u8 *const buffer,
                                 u32       maxLen);


/** Function to deserialise a CphyNodeBConfigReq structure from a buffer..
 * Deserialisation of this message can be performed by this function.
 *
 * \param[in]     buffer  The buffer into which the structure has been stored.
 * \param[in]     maxLen  Size of \a buffer[].
 * \param[in,out] msg     Pointer to structure for population with deserialised
 *                         message.
 * \returns Size of the deserialised message if successful, otherwise a
 *           negative error code.
 */
s32 CphyNodeBConfigReq_Deserialise(const u8 *buffer,
                                   u32       maxLen,
                                   CphyNodeBConfigReq *const msg);

#ifdef __cplusplus
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

namespace threeway
{

class CPhyNodeBConfigReq : public CPhyMessage
{
public:
    /**
     * Construction / destruction.
     */
    CPhyNodeBConfigReq() { memset(&m_Struct, 0, sizeof(m_Struct)); };
    CPhyNodeBConfigReq(const CphyNodeBConfigReq *msg);
    virtual ~CPhyNodeBConfigReq() {};
    CPhyNodeBConfigReq(upsc_t psc, bool updateDac);

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32  GetSerialisationId() const { return SERIALISATION_ID_CPHY_NODEB_CONFIG_REQ; };
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
    CphyNodeBConfigReq m_Struct;
};

}

#endif // __cplusplus

#endif // __CPhyNodeBConfigReq_h_
