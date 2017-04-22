///////////////////////////////////////////////////////////////////////////////
//
// Gtp.h
//
// GPRS Tunnelling Protocol functions.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Gtp_h_
#define __Gtp_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <3waytypes.h>
#include <comms/SimplePDU.h>
#include <comms/IPv4Address.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

namespace threeway
{

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class Gtp
{
public:
    // GTP-U port numbers.
    static const u16 GTP_U_DESTINATION_PORT = 2152;
    
    // GTP Header
    // Mandatory length is 8, 4 optional extra octets.
    static const u8 GTP_U_HEADER_MIN_SIZE_BYTES = 8;
    static const u8 GTP_U_HEADER_MAX_SIZE_BYTES = 12;
    
    // GTP-U message types.
    static const u8 MESSAGE_TYPE_ECHO_REQ   = 1;
    static const u8 MESSAGE_TYPE_ECHO_RSP   = 2;
    static const u8 MESSAGE_TYPE_ERROR_IND  = 26;
    static const u8 MESSAGE_TYPE_SUPPORTED_EXTENSION_HEADERS_NOTIFICATION = 31;
    static const u8 MESSAGE_TYPE_G_PDU      = 255;

    // GTP IEs.
    static const u8 IEI_TYPE_RECOVERY        = 14;
    static const u8 IEI_TYPE_TE_ID_DATA_I    = 16;
    static const u8 IEI_TYPE_GSN_ADDRESS     = 133;
    static const u8 IEI_TYPE_PRIVATE_EXTENSION = 255;
    
    enum
    {
        ERROR_CODE_MISSING_MANDATORY_IE = 0,
        ERROR_CODE_MANDATORY_IE_INCORRECT,
        ERROR_CODE_INVALID_MESSAGE_FORMAT,
        ERROR_CODE_OPTIONAL_IE_INCORRECT
    } ErrorCode;
    
    /**
     * Add GTP header to payloadPdu by extending head of PDU.
     */
    static void AddGtpHeader(bool sequenceNumPresent, u16 sequenceNum,
                             bool nPduNumberPresent, u8 nPduNumber,
                             u8 messageType,
                             u32 teId,
                             SimplePDU& payloadPdu);

    /**
     * Remove GTP header and return message type and TE ID.
     * 
     * \param gtpPdu        GTP packet.
     * \param messageType   Set to the recovered GTP message type.
     * \param teId          Set to the recovered tunnel endpoint ID.
     * \return              true on successful decode, false otherwise.
     */
    static bool RemoveGtpHeader(SimplePDU& gtpPdu,
                                u8& messageType,
                                u32& teId);

    /**
     * Encode an Echo Response message including GTP header.
     * 
     * \param teId          Tunnel endpoint identifier.
     * \param gtpPdu        PDU to fill in with echo response message.
     */
    static void EncodeEchoRsp(u32 teId, SimplePDU& echoRspGtpPdu);
    
    /**
     * Decode an Error Ind (once header removed).
     * 
     * \param errorIndPdu   PDU containing error ind, starting at byte following GTP header.
     * \param teIdDataI     Set to decoded tunnel endpoint identifier data I field.
     * \param gsnAddress    Set to decoded GSN address.
     */
    static void DecodeErrorInd(SimplePDU& errorIndPdu, u32& teIdDataI, IPv4Address& gsnAddress);
    
};

}

#endif
