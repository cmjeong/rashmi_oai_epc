///////////////////////////////////////////////////////////////////////////////
//
// NASAppPayload.h
//
//
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __NASAppPayload_h_
#define __NASAppPayload_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <System3Way.h>
#include <HLRMessageStructure.h>
#include <SMSCMessageStructure.h>
#include <SMSMessageStructure.h>
#include <AuthenticationTypes.h>

///////////////////////////////////////////////////////////////////////////////
// NAS CORE Transport Mechanism.
///////////////////////////////////////////////////////////////////////////////

typedef struct tagNASAppPayload
{
    // Field below indicates which of the items in the union is valid.
    NASAppMessage messageType;

    union
    {
        // Contains a low level L3 message from/to the UE, carried on the link
        // between NASCore + the RRC_LinkLayer.
        L3MessageStructure l3Msg;

        // When establishing a pysical radio link, this union element will contain
        // the radio bearer type & numbering information.
        RABMessageStructure rbMsg;

        // Used to query information about a subscriber in the HLR,  Sent on the
        // link between the NAS_Core + NAS_HLR.
        //HLRMessageStructure hlrMsg;

        // Used to transport
        // a) authentication and cyphering information after a
        //    successful AUTHENTICATION-PROCEDURE over the air interface.
        //    In this case, the failure cause field is the only irrelevant field.
        // b) the failure cause when the security mode procedure over the
        //    air-interface fails.
        //    In this case, the failure cause field is the only relevant field.
        //Sent on the link between the NAS_Core + NAS_RRCLinkLayer.
        CypherMessageStructure cyphMsg;

        // When the AUTH-REQ / RESP procedure is underway, the CORE will request
        // these authentication key values for use in the L3 messaging.  Sent on
        // the link between the NAS_Core + NAS_HLR.  Note that this one is used
        // for CS authentication ONLY.
        //AUTNKeys authMsg;

        // And this structure is the one used for PS authentication.
        //AUTNKeysPS authMsgPS;

        // If the message type indicates call failure, this reason cause
        // will be populated, and forward to the UE.
        u32 callReleaseCause;

        // Communications between the CORE and SMSC use this structure to relay SMS information.
        //SMSMessageStructure smsMsg;

        // Carefull now: we exchange very different information between the SMSC and SIP Relay
        // applications, hence the different structure.
        //SMSCMessageStructure smscMsg;

        // For SM<->RABM communications.
        RABMMessageStructure rabmMsg;

        // For GGSN<->SM communications.
        GGSNMessageStructure ggsnMsg;

        // For exchanging handover information between RRC + CORE.
        HandoverMessageStructure handoverMsg;
    }u;
}NASAppPayload;

typedef struct tagCOREMessageStructure
{
    // Identifies the CORE_Connection objectinstance handling this
    // connection in the SENDING application.
    CORE_ConnectionIdentifier sourceConnectionId;

    // Identifies the CORE_Connection objectinstance handling this
    // connection in the RECEIVING application.  Will be set to the
    // Unused value in a CNXN_REQ message.
    CORE_ConnectionIdentifier destConnectionId;

    // This contains a union, holding the various messages that can be transported
    // by the NAS Messaging infrastructure.  Note that this item should not
    // exceed 8180 Bytes (that's 8192 Bytes in the NASMessageStructure, minus the
    // 12 Bytes already allocated above).
    NASAppPayload thePayload;

}COREMessageStructure;

#endif
