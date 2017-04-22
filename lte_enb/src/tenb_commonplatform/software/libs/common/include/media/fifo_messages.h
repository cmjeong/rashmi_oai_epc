///////////////////////////////////////////////////////////////////////////////
//
// fifo_messages.h
//
// This header file defines the messages sent across the RTP FIFOs
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __fifo_messages_h_
#define __fifo_messages_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <Radisys.h>

// TODO: Delete unused sections below.

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////


static const int MAX_CS_DL_BUFFER_SIZE = 256;

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////
// This is used to pass the dynamic parts of the RTP Headers across
// the FIFO. The static part can then be reconstituted with the
// pay-load and other headers (i.e. Iu Headers) at the destination
// Note dynamic - changes with every RTP Packet
//      static - the same with every RTP Packet
#pragma pack(push,1) // ensure no padding on byte boundary
typedef struct rtp_dynamic_header_part
{
    uint32_t timeStamp;
    uint16_t rtpSequenceNumber;
    uint8_t payloadType;
}rtp_dynamic_header_part;

#pragma pack(pop) // ensure all following structures are word aligned

#define INVALID_MEDIA_FIFO_HANDLE -1

#define MEDIA_PAYLOAD_TYPE_VIDEO 0x01
#define MEDIA_PAYLOAD_TYPE_AMR_122 0x02
#define MEDIA_PAYLOAD_TYPE_AMR_SID 0x03
#define MEDIA_PAYLOAD_TYPE_FLUSH 0x04
#define MEDIA_PAYLOAD_TYPE_UNKNOWN 0xff

#define MEDIA_PAYLOAD_STATUS_GOOD 0x01
#define MEDIA_PAYLOAD_STATUS_BAD 0x02
// In Transparent Mode, we don't know if the media
// is 'good' or 'bad'.  Since this is CS Video
// traffic only, it's not important.
#define MEDIA_PAYLOAD_STATUS_TRANSPARENT 0x03

#define MEDIA_FIFO_MAX_MESSAGE_SIZE 128

typedef struct structCsUpFifoMessageHeader
{
    u32 allocatedDchNumber;

    u32 mediaTimeStamp;

    u16 mediaSequenceNumber;

    /* mediaPayloadType will be one of:
       MEDIA_PAYLOAD_TYPE_VIDEO
       MEDIA_PAYLOAD_TYPE_AMR_122
       MEDIA_PAYLOAD_TYPE_AMR_SID
       MEDIA_PAYLOAD_TYPE_FLUSH
    */
    u16 mediaPayloadType;

    /* mediaPayloadStatus will be one of:
       MEDIA_PAYLOAD_STATUS_GOOD
       MEDIA_PAYLOAD_STATUS_BAD
    */
    u16 mediaPayloadStatus;

    u16 mediaPayloadNumberOfBits;

}CsUpFifoMessageHeader;

#define CsUpFifoMessageHeader_Size sizeof (CsUpFifoMessageHeader)

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////


#endif
