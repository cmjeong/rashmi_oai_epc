///////////////////////////////////////////////////////////////////////////////
//
// Gtp.cpp
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Trace.h>
#include <system/NumberConversions.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Gtp.h"

using namespace std;

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Class Functions
///////////////////////////////////////////////////////////////////////////////

void Gtp::AddGtpHeader(bool sequenceNumPresent, u16 sequenceNum,
                       bool nPduNumberPresent, u8 nPduNumber,
                       u8 messageType,
                       u32 teId,
                       SimplePDU& payloadPdu)
{
    ENTER();

    // Header is variable length, allocate enough for biggest.
    u8 gtpHeader[GTP_U_HEADER_MAX_SIZE_BYTES];
    u32 headerLength;

    // Flags.
    gtpHeader[0] = (1 << 5) | // Version (3 bits)
                   (1 << 4) | // Protocol Type, PT (1 bit), 1=GTP
                   (0 << 2) | // Extension Header flag, E (1 bit), 0=Next Extension Header field not present or not meaningful, 1=Present and meaningful.
                   ((sequenceNumPresent?1:0) << 1) | // Sequence Number flag, S (1 bit), 0=Sequence Number field not present or not meaningful , 1=Present and meaningful.
                   (nPduNumberPresent?1:0);          // N-PDU Number flag, PN (1 bit), 0=N-PDU Number field not present or not meaningful , 1=Present and meaningful.

    // Message type.
    gtpHeader[1] = messageType;

    // Payload length - the length of everything after the header.
    // Guessing it is network byte order, spec doesn't seem to say....
    u32 length = payloadPdu.GetPacketLength();

    headerLength = GTP_U_HEADER_MIN_SIZE_BYTES;
    if(sequenceNumPresent || nPduNumberPresent)
    {
        // If either of these are present, then the header is extended by 4 octets
        // for Sequence Number (2 octets), N-PDU Number (1 octet) and Next Extension Header Type (1)
        length += 4;
        headerLength = GTP_U_HEADER_MAX_SIZE_BYTES;
    }

    if(length < 0x10000) // GTP header only supports length up to 0xffff.
    {
        gtpHeader[2] = (u8)((length >> 8) & 0xff);
        gtpHeader[3] = (u8)(length & 0xff);
    }
    else
    {
        TRACE_LEV(TRACE_WARNING, "AddGtpHeader(): Payload too big", length);
        gtpHeader[2] = 0;
        gtpHeader[3] = 0;
    }

    // Tunnel Endpoint identifier - assuming network byte order, spec doesn't seem to say....
    U32ToBytes(teId, &(gtpHeader[4]), &(gtpHeader[5]), &(gtpHeader[6]), &(gtpHeader[7]));

    // If any of Sequence Number, N-PDU Number or Next Extension Header Type are
    // present we need to add all three, even if the values of 1 or 2 of them
    // aren't used.
    if(sequenceNumPresent || nPduNumberPresent)
    {
        // Sequence Number.
        if(sequenceNumPresent)
        {
            gtpHeader[8] = (u8)((sequenceNum >> 8) & 0xff);
            gtpHeader[9] = (u8)(sequenceNum & 0xff);
        }
        else
        {
            gtpHeader[8] = 0;
            gtpHeader[9] = 0;
        }

        // N-PDU Number
        if(nPduNumberPresent)
        {
            gtpHeader[10] = nPduNumber;
        }
        else
        {
            gtpHeader[10] = 0;
        }

        // Next Extension Header Type
        gtpHeader[11] = 0;
    }

    // Add header to head of payloadPdu.
    payloadPdu.AddToHead(gtpHeader, headerLength);

    EXIT();
}

bool Gtp::RemoveGtpHeader(SimplePDU& gtpPdu,
                          u8& messageType,
                          u32& teId)
{
    ENTER();

    u32 gtpPacketLength = gtpPdu.GetPacketLength();
    const u8* gtpPacket = gtpPdu.GetPacket();
    const u8* gtpPacketIter = gtpPacket;

    if(gtpPacketLength < GTP_U_HEADER_MIN_SIZE_BYTES) // Sanity check that it is big enough to hold a minimal GTP header.
    {
        TRACE_LEV(TRACE_WARNING, "GTP PDU too small to hold valid GTP packet", gtpPacketLength);
        RETURN(false);
    }

    // Extract first byte flags and version number.
    u8 nPduNumFlag = gtpPacket[0] & 0x01;
    u8 seqNumFlag = (gtpPacket[0] & 0x02) >> 1;
    u8 extHeaderFlag = (gtpPacket[0] & 0x04) >> 2;
    //u8 protoType = (gtpPacket[0] & 0x10) >> 4;
    //u8 version = (gtpPacket[0] & 0xe0) >> 5;

    messageType = gtpPacket[1];
    u32 payloadLength = ((u16)gtpPacket[2] << 8) | gtpPacket[3]; // Length of everything after first 8 bytes of header.
    teId = BytesToU32(gtpPacket[4], gtpPacket[5], gtpPacket[6], gtpPacket[7]);

    gtpPacketIter += 8; // Skip over first (mandatory) 8 bytes.
    // Now point at either the additional header bytes or the start of the payload.

    // Validate GTP packet (the PDU) is long enough to contain the payload
    // it says it does.
    if(gtpPacketLength < (payloadLength + GTP_U_HEADER_MIN_SIZE_BYTES))
    {
        TRACE_PRINTF_LEV(TRACE_WARNING, "GTP PDU too small (%" PRIu32 ") to hold header (%u) + payload (%" PRIu32 ")",
                gtpPacketLength, GTP_U_HEADER_MIN_SIZE_BYTES, payloadLength);
        RETURN(false);
    }

    if(gtpPacketLength > (payloadLength + GTP_U_HEADER_MAX_SIZE_BYTES))
    {
        TRACE_PRINTF("GTP PDU is bigger (%" PRIu32 ") than expected (%" PRIu32 ")",
                gtpPacketLength, payloadLength + GTP_U_HEADER_MAX_SIZE_BYTES);
    }

    if(seqNumFlag || nPduNumFlag || extHeaderFlag)
    {
        // Header is extended.
        gtpPacketIter += 3; // Skip over Sequence Number (2 bytes) and N-PDU Number (1) and next ext header (1)

        // Now pointing at Next Extension Header Type (1)
        u8 nextExtHeaderType;
        do
        {
            // Need to evaluate extension header.
            nextExtHeaderType = *gtpPacketIter;
            // Skip over Next Extension Header Type field.
            gtpPacketIter++;

            if(nextExtHeaderType != 0)
            {
                // Now pointing at length field.

                // Get the length of the content field.
                u32 extHeaderLen = (*gtpPacketIter) * 4; // Length field is in units of 4 bytes.

                // Skip over length field.
                gtpPacketIter++;
                // Now pointing at Extension Header Content field.

                // Skip over content field.
                gtpPacketIter += extHeaderLen;
                // Now pointing at Next Extension Header Type field.
            }

        } while((nextExtHeaderType != 0) &&
                (gtpPacketIter < (gtpPacket + gtpPacketLength)) // Protect against dodgy formatted packets.
               );
    }

    // gtpPacketIter now points at the payload.
    // Get the payload length, current value of payloadLength includes the extra
    // header bytes above so we need to knock those off (if any).
    u32 headerLength = gtpPacketIter - gtpPacket;

    // Proceed with gtp header de-capsulation ONLY if the header size
    // evaluated as < the overall pdu length, else we'll assert in the TrimHead function
    // (Of course!)
    // Handled in response to mantis 1991, where we got a corrupt
    // packet from the network and we asserted within TrimHead()
    if (headerLength < gtpPacketLength)
    {
        // Trim the header off.
        gtpPdu.TrimHead(headerLength);
    }
    else
    {
        // In case the incoming packet is a corrupt one, then in the previous while loop
        // we could get some junk value for extHeaderLen (Say 420). Then we exit the
        // while loop and get here. Simply drop this corrupt packet (Mantis 1991)
        TRACE_PRINTF("GTP HEADER is bigger (%" PRIu32 ") than the entire packet (%" PRIu32 ")!!!!! Dropping it!",
                headerLength, gtpPacketLength);

        RETURN(false);
    }

    RETURN(true);
}

void Gtp::EncodeEchoRsp(u32 teId, SimplePDU& echoRspGtpPdu)
{
    ENTER();

    // Recovery type is mandatory but set to zero for GTP-U.
    u8 recoveryType = IEI_TYPE_RECOVERY;
    u8 recoveryCounter = 0;

    echoRspGtpPdu.Reset();
    echoRspGtpPdu.AddToTail(&recoveryType, 1);
    echoRspGtpPdu.AddToTail(&recoveryCounter, 1);

    AddGtpHeader(false, 0, // No sequence number
                 false, 0, // No PDU number
                 Gtp::MESSAGE_TYPE_ECHO_RSP,
                 teId,
                 echoRspGtpPdu);

    EXIT();
}

void Gtp::DecodeErrorInd(SimplePDU& errorIndPdu, u32& teIdDataI, IPv4Address& gsnAddress)
{
    ENTER();

    // Assuming that IEs are in the order specified in the spec - is this a valid assumption?
    // Hope so...

    const u8* errorInd = errorIndPdu.GetPacket();
    u32 remainingErrorIndLen = errorIndPdu.GetPacketLength();

    // Reset the output values.
    teIdDataI = 0;
    gsnAddress.Clear();

    // Look for TE ID Data I IE.
    if(remainingErrorIndLen < 5)
    {
        // Invalid packet.
        TRACE_PRINTF_LEV(TRACE_WARNING, "GTP ErrorInd too short for TE ID Data I IE, length=%" PRIu32, remainingErrorIndLen);
        RETURN_VOID();
    }

    if(*errorInd != IEI_TYPE_TE_ID_DATA_I)
    {
        // Invalid packet.
        TRACE_PRINTF_LEV(TRACE_WARNING, "GTP ErrorInd has invalid 1st IEI of %u (should be TE ID Data I = %u)", *errorInd, IEI_TYPE_TE_ID_DATA_I);
        RETURN_VOID();
    }

    errorInd++; // Skip the IEI.

    // Recover the TE ID Data I value.
    teIdDataI = BigEndianByteArrayToU32(errorInd);
    errorInd += 4; // Skip the value.
    remainingErrorIndLen -= 5; // Reduce remaining bytes.

    // Look for GSN Address IE.
    if(remainingErrorIndLen < 3)
    {
        // Invalid packet - too short.
        TRACE_PRINTF_LEV(TRACE_WARNING, "GTP ErrorInd too short for GSN Address IE, remaining length=%" PRIu32, remainingErrorIndLen);
        RETURN_VOID();
    }

    if(*errorInd != IEI_TYPE_GSN_ADDRESS)
    {
        // Invalid packet - wrong IEI.
        TRACE_PRINTF_LEV(TRACE_WARNING, "GTP ErrorInd has invalid 2nd IEI of %u (should be GSN Address = %u)", *errorInd, IEI_TYPE_GSN_ADDRESS);
        RETURN_VOID();
    }
    errorInd++; // Skip the IEI.

    // Recover the GSN Address length.
    u16 addressLength = BigEndianByteArrayToU16(errorInd);
    errorInd += 2; // Skip over the length

    // Now pointing at N bytes of GSN address...
    if(addressLength == 4)
    {
        // We have an IPv4 address.
        gsnAddress.SetDigits(errorInd[0], errorInd[1], errorInd[2], errorInd[3]);
    }
    else
    {
        TRACE_PRINTF_LEV(TRACE_WARNING, "GTP ErrorInd contains GSN Address that is not IPv4 i.e. currently unsupported (length=%u).", addressLength);
    }

    EXIT();
}

}
