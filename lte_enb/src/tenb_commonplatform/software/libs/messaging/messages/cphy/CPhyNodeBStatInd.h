///////////////////////////////////////////////////////////////////////////////
//
// $Id: CPhyNodeBStatInd.h 22599 2010-01-28 18:23:59Z mmcternan $
//
// CPhyNodeBStatInd message.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CPhyNodeBStatInd_h_
#define __CPhyNodeBStatInd_h_

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
#include "FapUserLimits.h"

///////////////////////////////////////////////////////////////////////////////
// Message Constants
///////////////////////////////////////////////////////////////////////////////

/** Number of physical DCH channels on which to report stats.
 */
#define NUM_CPHY_STAT_CHAN_DCH  MAX_DCH_USERS

/** Maximum number of AGC gain changes in a report period.
 */
#define NUM_CPHY_AGC_REPORTS 8

///////////////////////////////////////////////////////////////////////////////
// Message Structures
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

/** Node B operating statistics indication.
 * \ingroup CPhyNodeB
 * This is sent around every 2 seconds from the PHY such that the various
 * counters can be accumulated, displayed or stored as required.
 */
typedef struct CphyNodeBStatIndTag
{
    /** Number of frames that have passed during the collection of data. */
    uint32_t frameCount;

    /** Durations of passed frames in microseconds. */
    uint32_t minFrameDuration, totalFrameDuration, maxFrameDuration;

    /* PRACH error counts */

    /** Count of PRACH errors. */
    uint32_t prachErr;

    /** Count of PRACH blocks. */
    uint32_t prachCount;


    /* DCH TrCh block error counts */

    /** Count of TrCh blocks recieved per DCH that failed CRC. */
    uint32_t blerErr[NUM_CPHY_STAT_CHAN_DCH];

    /** Count of TrCh blocks recieved per DCH. */
    uint32_t blerCount[NUM_CPHY_STAT_CHAN_DCH];

    /* DCH1 TrCh bit error counts */

    /** Count of bits received in error on DCH1. */
    uint32_t berErr;

    /** Count of received bits on DCH1. */
    uint32_t berCount;

    /** Count of transmitted TFCs on the DPCHs. */
    uint32_t tfciCount[NUM_CPHY_STAT_CHAN_DCH][MAX_L1_TFCI];

    /* HSDPA Ack/Nack totals */

    /** Count of individual HSDPA Acks. */
    uint32_t hsdpaAck;

    /** Count of individual HSDPA Nacks. */
    uint32_t hsdpaNack;


    /* HSDPA buffer summaries */

    /** Count of HSDPA buffers that have been ACK'd. */
    uint32_t hsdpaBufAck;

    /** Count of HSDPA buffers that have been NACK'd. */
    uint32_t hsdpaBufNack;

    /** Count of empty HSDPA buffers. */
    uint32_t hsdpaBufEmpty;

    /** Record of recent transport block sizes. */
    uint16_t hsdpaSizeStats[20][2];
}
CphyNodeBStatInd;

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

/** Function to serialise a CphyNodeBStatInd structure to a buffer.
 * Serialisation of this message can be performed by this function.
 *
 * \param[in] msg         The message to serialise.
 * \param[in,out] buffer  The data buffer into which the data is serialised.
 * \param[in] maxLen       Pointer to size of \a buffer.
 * \returns  Either a negative error code, or the length of the data.
 */
s32 CphyNodeBStatInd_Serialise(const CphyNodeBStatInd *msg,
                               u8 *const buffer,
                               u32       maxLen);


/** Function to deserialise a CphyNodeBStatInd structure from a buffer..
 * Deserialisation of this message can be performed by this function.
 *
 * \param[in]     buffer  The buffer into which the structure has been stored.
 * \param[in]     maxLen  Size of \a buffer[].
 * \param[in,out] msg     Pointer to structure for population with deserialised
 *                         message.
 * \returns Size of the deserialised message if successful, otherwise a
 *           negative error code.
 */
s32 CphyNodeBStatInd_Deserialise(const u8 *buffer,
                                 u32       maxLen,
                                 CphyNodeBStatInd *const msg);

#ifdef __cplusplus
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

namespace threeway
{

class CPhyNodeBStatInd : public CPhyMessage
{
public:
    /**
     * Construction / destruction.
     */
    CPhyNodeBStatInd() { memset(&m_Struct, 0, sizeof(m_Struct)); };
    CPhyNodeBStatInd(const CphyNodeBStatInd *msg);
    virtual ~CPhyNodeBStatInd() {};
    CPhyNodeBStatInd(upsc_t psc, bool updateDac);

    /**
     * Implement Serialisable pure virtuals.
     */
    virtual u32  GetSerialisationId() const { return SERIALISATION_ID_CPHY_NODEB_STAT_IND; };
    virtual s32  Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    /**
     * Implement CPhyMessage pure virtual.
     */
    virtual u32 GetStruct(CphyMessageData *const msg);

    /**
     * Accessors.
     */
    // Define as required
    u32 GetFrameCount() const { return m_Struct.frameCount; }
    u32 GetDchErr(u32 index) const { return m_Struct.blerErr[index]; }
    u32 GetDchCount(u32 index) const { return m_Struct.blerCount[index]; }
    u32 GetPrachErr() const { return m_Struct.prachErr; }
    u32 GetPrachCount() const { return m_Struct.prachCount; }
    u32 GetBerErr() const { return m_Struct.berErr; }
    u32 GetBerCount() const { return m_Struct.berCount; }

    /**
     * Convert to string for debug.
     */
    virtual std::string ToString() const;

private:

    /** Embedded C structure carrying parameters.
     */
    CphyNodeBStatInd m_Struct;
};

}

#endif // __cplusplus

#endif // __CPhyNodeBStatInd_h_
