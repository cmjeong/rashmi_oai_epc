///////////////////////////////////////////////////////////////////////////////
//
// CPhyNodeBSibMessage.h
//
// Message for transfering SIB data to PHY layer.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CPhyNodeBSibMessage_h_
#define __CPhyNodeBSibMessage_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "CPhyTypes.h"

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

#define SIB_MESSAGE_SIZE  BCH_TRCH_BLOCK_SIZE_BYTES

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

namespace threeway
{

/** Message to populate Layer 1 BCH transmission roster.
 * BCH data blocks and scheduling information are encapsulated by this class
 * for addition to the Layer 1 transmission schedule.
 *
 * \ingroup CPhyNodeB
 */
class CPhyNodeBSibMessage : public threeway::Serialisable
{
public:
    /*
     * Construction / destruction.
     */
    CPhyNodeBSibMessage();

    /** Constructor to generate message from binary array.
     *
     * \param[in] sibNumber   The SIB number, or 0 for the MIB.
     * \param[in] sibRep      The SIB_REP parameter for scheduling the block.
     * \param[in] sibPos      The SIB_POS parameter for scheduling the block.
     * \param[in] blockNum    For segmented blocks, the segment number of the
     *                         block, or 0 is unsegmented.
     * \param[in] messageData Pointer to octet array giving raw SIB data,
     *                         including a holde for SFN'.
     * \param[in] sibLen      The length of the \a messageData block in bytes.
     */
    CPhyNodeBSibMessage(u32 sibNumber, u16 sibRep, u16 sibPos, u32 blockNum, const u8 *messageData, u32 sibLen);
    virtual ~CPhyNodeBSibMessage() {};

    /*
     * Implement Serialisable pure virtuals.
     */
    virtual u32  GetSerialisationId() const;
    virtual s32  Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);

    /** Get the number of the SIB encapsulated in this message.
     * Returns the SIB number of the encapsulated message or 0 for the MIB.
     */
    u8 GetSibNumber() const { return m_sibNumber; }

    /** Retrieves a pointer to the message data.
     */
    const u8 * GetData() const { return &m_messageData[0]; }

    /** Retrieves the SIB_REP scheduling parameter.
     */
    u16 GetRep() const { return m_sibRep; }

    /** Retrieves the SIB_POS scheduling parameter.
     */
    u16 GetPos() const { return m_sibPos; }

    /** Retrieves the length of the SIB in bytes.
     */
    u8 GetLen() const { return m_sibLen; }

    /** Retrieves the SIB block number for segmented SIBs.
     */
    u8 GetBlockNum() const { return m_blockNum; }

    /** Convert to string for debug.
     */
    virtual std::string ToString() const;
    virtual std::string ToBriefString() const;

protected:
    u8  m_sibNumber;
    u8  m_sibLen;
    u8  m_blockNum;
    u16 m_sibRep;
    u16 m_sibPos;
    u8  m_messageData[SIB_MESSAGE_SIZE];
};

}

#endif
