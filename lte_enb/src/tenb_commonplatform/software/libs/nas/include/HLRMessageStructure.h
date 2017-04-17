///////////////////////////////////////////////////////////////////////////////
//
// HLRMessageStructure.h
//
//
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __HLRMessageStructure_h_
#define __HLRMessageStructure_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////
//CODE_CLEANUP
#if 0
#include <PagingCause.h>

#include "Encodix24008.h"

// The fields that are filled will depend on the message type.
typedef struct tagHLRMessageStructure
{
    // The type of the message indicates which of the fields are
    // present (i.e. which structure to use).
    NASAppMessage messageType;

    // Mobile Identity: can be IMSI, TMSI or IMEI depending on the
    // procedure taking place.
    c_MobileId subscriberIdentity;

    // We return the PAGING identity separately, so we can PAGE on an
    // independent identity .
    c_MobileId pagingIdentity;

    // MCC, MNC + LAC Information.
    c_LocationAreaId locationArea;

    // The number of the subscriber we are calling.  Naturally (?), only
    // present during call setup messages sent TO the HLR.
    c_CalledPartyBcdNum calledSubscriber;

    // The number of the subscriber we are calling.  Naturally (?), only
    // present during call setup messages sent FROM the HLR.
    c_CallingPartyBcdNum callingSubscriber;

    // When the registration of a subscriber takes place in an IMS network,
    // the contents of the successful 200 REGISTER event in nas-sip-relay will
    // cause the following two strings to be present, on the interface between
    // the nas-hlr + nas-sip_relay ONLY.

    // Number of digits in this string is fixed: the format is
    // XXXYYYZZZZTTTTTTTT,
    // where XXX = MCC, YYY = MNC, ZZZZ = LAC (HEX), TTTTTTTT = TMSI
    // So we have a maximum of 18 digits: add 1 for NULL terminator, and a
    // few for luck >:-)
    char imsAllocatedTMSIAndLAI [32];

    // This MSISDN number will have the international portion included, so
    // the format will be 44-7891597628, for example.  HLR will deal with this
    // when the number is entered into the database.
    char imsAllocatedMSISDN [32];

    // Have to transport the Paging Cause received from CN to RRC.
    // We have a PagingCause type in generated RANAP code, and another in generated RRC,
    // which is nice.  To prevent multiple symbol definitions use an internal type here.
    RadisysPagingCause pagingCause;

}HLRMessageStructure;
#endif/*0*/
#endif
