///////////////////////////////////////////////////////////////////////////////
//
// SMSMessageStructure.h
//
//
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __SMSMessageStructure_h_
#define __SMSMessageStructure_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////
//CODE_CLEANUP
#if 0
#include <Radisys.h>
#include <ed_c.h>

typedef struct tagSMSMessageStructure
{
    // The TMSI of the subscriber that is sending the SMS.  Required if
    // we need to deliver the message via the SIP IWF.
    c_MobileId subscriberTmsi;

    // Context (i.e. message type) indicates the 'owner' of the MSISDN.  For
    // instance, when receiving an SMS from the UE it will be the MO MSISDN.
    // When delivering an SMS to an MT, it will be the MSISDN of the mobile
    // that needs to be paged.
    c_CallingPartyBcdNum subscriberMsisdn;

    // If there is an RP payload in the message, this is its length.
    u8 rpUserDataLength;

    // And this is its message content.
    u8 rpUserData[232];

    // SMS shutdown logic is a bit messy because of the various ways multi
    // page SMS, concatenated SMS + multiple SMS delivery are implemented.
    // Basically, in the direction SMSC -> CORE, this flag indicates that the
    // SMSC is finished with whatever it was doing, and the CORE can release
    // the link to the UE.
    bool procedureComplete;

}SMSMessageStructure;
#endif
#endif
