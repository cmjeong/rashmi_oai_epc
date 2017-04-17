///////////////////////////////////////////////////////////////////////////////
//
// SimplePDU.h
//
// Concrete PDU class for managing head and tail of a data packet.
//
// Idea is that the core data in the middle of the packet doesn't need to be
// copied as the PDU is passed up and down a stack.  The head and tail expand
// and shrink as the packet passes through different layers so we start off
// with some head room to allow the packet to expand.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __SimplePDU_h_
#define __SimplePDU_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <string>

#include <3waytypes.h>
#include <comms/PDU.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

static const u32 PDU_MAX_LENGTH = 4096;
static const u32 PDU_DEFAULT_START_OFFSET = 100;

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class SimplePDU : public PDU
{
public:
    /**
     * Construction / destruction.
     * Virtual destructor to allow specific types of SimplePDU to derive from this.
     * E.g. could have a class that includes encoding / decoding of
     * a particular protocol.
     */
    SimplePDU(u32 initialStartOffset = PDU_DEFAULT_START_OFFSET);
    SimplePDU(SimplePDU& simplePdu, u32 initialStartOffset = PDU_DEFAULT_START_OFFSET);
    virtual ~SimplePDU();

    /**
     * Get a pointer to the start of the data packet.
     */
    const u8* GetPacket() const;

    /**
     * Get a pointer to the start of the data packet for use when writing
     * data in.  Can be useful when calling functions to read data from some
     * external source e.g. a socket or FIFO, so that the data doesn't need
     * to be copied.
     * WARNING: Use this sparingly, this is exposing what should really be
     * private data.
     *
     * \param  maxLength Set to maximum available space at 'data'.
     * \return           Pointer to write packet data to.
     */
    u8* GetPacketRaw(u32& maxLength);

    /**
     * Get the length of the data packet in bytes.
     */
    u32  GetPacketLength() const;

    /**
     * Set the whole data packet in one go.
     * Normally only used when the packet is first created.
     */
    void SetPacket(const u8* data, u32 length);

    /**
     * Add data to the head of the SimplePDU.
     *
     * \param data   Pointer to data to add to head.  If NULL then no data copied.
     * \param length Length of data to add to head.
     */
    void AddToHead(const u8* data, u32 length);

    /**
     * Adjust the head pointer - assume data in new head space is garbage.
     * Same as AddToHead(NULL, length).
     *
     * \param length Length of data to add to head.
     */
    void AddToHead(u32 length);

    /**
     * Add data to the tail of the SimplePDU.
     *
     * \param data   Pointer to data to add to tail.  If NULL then no data copied.
     * \param length Length of data to add to tail.
     */
    void AddToTail(const u8* data, u32 length);

    /**
     * Adjust the tail pointer - assume data in new tail space is garbage.
     * Same as AddToTail(NULL, length).
     *
     * \param length Length of data to add to tail.
     */
    void AddToTail(u32 length);

    /**
     * Pad the packet with a particular byte value.
     */
    void PadHead(u8 padByte, u32 length);
    void PadTail(u8 padByte, u32 length);

    /**
     * Trim the SimplePDU.  Removes data from the head/tail.
     */
    void TrimHead(u32 trimLength);
    void TrimTail(u32 trimLength);

    /**
     * Reset the PDU - put it back to state at construction.
     */
    void Reset(u32 initialStartOffset = PDU_DEFAULT_START_OFFSET);

    /**
     * Get as a string for debug.
     */
    virtual std::string ToString() const;
    virtual std::string ToStringAsHex(u32 maxNumBytes = 0) const;

private:
	/**
	 * Convert to a string stream.
	 *
	 * \param stream    Stream to fill in with string representation of packet.
	 * \param shortText If true, don't stringify the data, just have length, etc
	 * \param asHex     Can be in ascii hex or individual printable chars (or '.' if not printable).
	 * \param maxNumBytes   Max number of bytes to show, or 0 for 'all'.
	 */
	void ToString(std::ostringstream& stream, bool shortText, bool asHex, u32 maxNumBytes = 0) const;

    // Storage area for the data packet.
    u8  m_dataPacket[PDU_MAX_LENGTH];

    // Offset into the above array where the packet starts.
    u32 m_startOffset;

    // Length of the data packet in the above array.
    u32 m_length;
};

}

#endif
