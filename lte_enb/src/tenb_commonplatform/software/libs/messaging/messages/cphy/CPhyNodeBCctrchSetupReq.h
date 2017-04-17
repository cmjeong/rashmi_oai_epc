///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyNodeBCctrchSetupReq.h 7672 2008-09-09 17:17:30Z manderson $
//
// CPhyNodeBCctrchSetupReq message.
//
// Copyright radisys Inc
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CPhyNodeBCctrchSetupReq_h_
#define __CPhyNodeBCctrchSetupReq_h_

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

/** Setup a Coded Composite Transport Channel for some UE.
 * This message sets up a new link for some UE.  The message contains all
 * the required parameters for the configuration to be effective immediately,
 * although an activation time maybe scheduled if the configuration need only
 * take effect at some point in the future.
 *
 * \ingroup CPhyNodeB
 */
typedef struct CphyNodeBCctrchSetupReqTag
{
    /** Activation time at which to make the configuration change. */
    l1_activation_time_t actTime;

    /** UE number.
     * Zero based UE number.
     */
    uint8_t             ue;

    /** Layer 2 Stack Instance
     */
    uint32_t            instanceId;

    /** Tdpch offset for the DPCH.
     */
    uint8_t             Tdpch;

    /** Uplink CCTRCH parameters.
     */
    l1_cctrch_param_t   ulCctrch;

    /** Downlink CCTRCH parameters.
     */
    l1_cctrch_param_t   dlCctrch;

    /** Uplink physical parameters.
     */
    l1_ulphy_param_t    ulPhy;

    /** Downlink physical parameters.
     */
    l1_dlphy_param_t    dlPhy;

    /** Outer loop power control parameters.
     */
    l1_olpc_param_t     olpc;

    /** Sync procedure to use when establishing the link.
     */
    l1_sync_procedure_t sync;

    /** HSDPA parameters.
     */
    l1_hsdpa_param_t  hsdpa;

    /** HSUPA parameters.
     */
    l1_hsupa_param_t  hsupa;
}
CphyNodeBCctrchSetupReq;

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

/** Function to serialise a CPhyNodeBCctrchSetupReq structure to a buffer.
 * Serialisation of this message can be performed by this function.
 *
 * \param[in] msg         The message to serialise.
 * \param[in,out] buffer  The data buffer into which the data is serialised.
 * \param[in] maxLen       Pointer to size of \a buffer.
 * \returns  Either a negative error code, or the length of the data.
 */
s32 CPhyNodeBCctrchSetupReq_Serialise(const CphyNodeBCctrchSetupReq *msg,
                                         u8 *const buffer,
                                         u32       maxLen);


/** Function to deserialise a CPhyNodeBCctrchSetupReq structure from a buffer..
 * Deserialisation of this message can be performed by this function.
 *
 * \param[in]     buffer  The buffer into which the structure has been stored.
 * \param[in]     maxLen  Size of \a buffer[].
 * \param[in,out] msg     Pointer to structure for population with deserialised
 *                         message.
 * \returns Size of the deserialised message if successful, otherwise a
 *           negative error code.
 */
s32 CPhyNodeBCctrchSetupReq_Deserialise(const u8 *buffer,
                                   u32       maxLen,
                                   CphyNodeBCctrchSetupReq *const msg);

#ifdef __cplusplus
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

namespace threeway
{

class CPhyNodeBCctrchSetupReq : public CPhyMessage
{
public:
    /**
     * Construction / destruction.
     */
    CPhyNodeBCctrchSetupReq  ();
    // No activationTime means PHY should configure this bearer NOW!
    CPhyNodeBCctrchSetupReq (uint8_t ueNumber, uint32_t instanceId);
    // Specify the CFN at which time the PHY shold configure this bearer.
    CPhyNodeBCctrchSetupReq (uint8_t ueNumber, uint32_t instanceId, uint16_t activationTime);
    CPhyNodeBCctrchSetupReq(const CphyNodeBCctrchSetupReq &cctrchSetup);
    virtual ~CPhyNodeBCctrchSetupReq() {};

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32  GetSerialisationId() const { return SERIALISATION_ID_CPHY_NODEB_CCTRCH_SETUP_REQ; };
    virtual s32  Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    /**
     * Implement CPhyMessage pure virtual.
     */
    virtual u32 GetStruct(CphyMessageData *const msg);

    /**
     * Accessors.
     */
    u8 AddUplinkTrch ();
    void ConfigureUplinkTrch (u8 trchIndex, uint8_t tti, coding_scheme_t coding, crc_length_t crc, uint8_t rmAttr, uint8_t macHeaderBit);
    void ConfigureUplinkTransportFormat (u8 trchIndex, uint8_t blockCount, uint16_t blockSize);
    void ConfigureUplinkTfcs (u8 trch, u8 tfci, u8 tfi);

    u8 AddDownlinkTrch ();
    void ConfigureDownlinkTrch (u8 trchIndex, uint8_t tti, coding_scheme_t coding, crc_length_t crc, uint8_t rmAttr);
    void ConfigureDownlinkTransportFormat (u8 trchIndex, uint8_t blockCount, uint16_t blockSize);
    void ConfigureDownlinkTfcs (u8 trch, u8 tfci, u8 tfi);

    void ConfigureUplinkPhy (upsc_t psc, spreading_factor_t minSf, uint8_t punctureLimit100, uint16_t maxDpdchBitsPerFrame);
    void ConfigureDownlinkPhy (bool dtxPositionFixed, spreading_factor_t sf, uint8_t ovsf, uint16_t tfciBitsPerSlot, uint16_t tpcBitsPerSlot, uint16_t pilotBitsPerSlot, uint16_t dataBitsPerSlot, uint16_t dataBitsPerFrame);

    void ConfigureHsupa (tti_length_t ttiLen);
    void ConfigureHsupaUl (uint8_t plNonMax, uint8_t trnsBlockTabId, uint8_t ueCat, spreading_factor_t minSf, bool rvFlag);
    void ConfigureHsupaDl (uint8_t ehichSig, uint8_t ehichSpreadingCode, uint16_t ernti);

    // blerToAchieve is in units of 0.1%, ie a value of 10 corresponds to a 1% bler target
    void ConfigurePowerControl (uint16_t const * const blerToAchieve);
    void ConfigurePowerControl (uint16_t const * const blerToAchieve, uint16_t const hsupaBler);
    void ConfigureHsdpa (bool active);

    void ConfigureSync(l1_sync_procedure_t procedure);

    const CphyNodeBCctrchSetupReq &GetCPhyNodeBCctrchSetupReq () const { return m_cctrchSetup; }

    /**
     * Convert to string for debug.
     */
    const char *CodingToString (coding_scheme_t coding) const;
    const char *CrcToString (crc_length_t crc) const;
    const char *SfToString (spreading_factor_t sf) const;
    std::string BlerToString (u16 bler) const;
    virtual std::string ToBriefString() const;
    virtual std::string ToString() const;
    std::string ToString (const l1_cctrch_param_t &cctrchParam) const;
    std::string ToString (const l1_hsdpa_param_t &hsdpa) const;
    std::string ToString (const l1_hsupa_param_t &hsupa) const;
    std::string ToString (const l1_olpc_param_t &olpc) const;

private:

    /** Embedded C structure carrying parameters.
     */
    CphyNodeBCctrchSetupReq m_cctrchSetup;
};

}

#endif // __cplusplus

#endif // __CPhyNodeBCctrchSetupReq_h_
