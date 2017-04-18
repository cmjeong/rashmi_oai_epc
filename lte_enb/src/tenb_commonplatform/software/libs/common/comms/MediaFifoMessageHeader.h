///////////////////////////////////////////////////////////////////////////////
//
// MediaFifoMessageHeader.h
//
// Helper class to encode / decide the message header sent on the Fifo
// between Cs User Plane and L1 L2 (Mac).
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MediaFifoMessageHeader_h_
#define __MediaFifoMessageHeader_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////


#include <media/fifo_messages.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

namespace threeway
{


///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class MediaFifoMessageHeader
{
public:
    /**
     * Default constructor that initialises the object to 0.
     */
    MediaFifoMessageHeader ();

    /**
     * Constructor that populates the provided buffer with the
     * arguments, formatted as per the header structure in fifo_messages.h
     */
    MediaFifoMessageHeader (u8 *headerBuffer, u32 dchNumber, u16 rtpSeqNumber, u32 rtpTimestamp, u16 mediaPayloadType, u16 mediaPayloadStatus, u16 numberOfPayloadBits);

    /**
     * Constructor that decodes a header structure as per the header in fifo_messages.h
     */
    MediaFifoMessageHeader (const u8 *headerBuffer);

    /**
     * Destructor.
     */
    virtual ~MediaFifoMessageHeader ();

    /**
     * Operations.
     */
    void DecodeHeaderBuffer (const u8 *headerBuffer);

    /**
     * Accessors.
     */
    u32 GetDchNumber () const;
    u16 GetRtpSeqNumber () const;
    u32 GetRtpTimestamp () const;
    u16 GetMediaPayloadType () const;
    u16 GetMediaPayloadStatus () const;
    u16 GetNumberOfPayloadBits () const;
    u16 GetNumberOfPayloadBytes () const;

    std::string ToString () const;

private:

    CsUpFifoMessageHeader m_header;
};

}

#endif

