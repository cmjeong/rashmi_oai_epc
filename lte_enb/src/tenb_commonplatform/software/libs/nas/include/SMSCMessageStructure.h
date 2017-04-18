///////////////////////////////////////////////////////////////////////////////
//
// SMSCMessageStructure.h
//
//
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __SMSCMessageStructure_h_
#define __SMSCMessageStructure_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////
//CODE_CLEANUP
#if 0
#include <BCDAddress.h>
#include <Radisys.h>

typedef struct tagSMSCMessageStructure
{
    // The direct dial number of the destination SMSC for this SMS.  The SIP
    // network needs this for routing the SMS to the recipient.
    BCDAddress smscDestinationNumber;

    // The MSISDN of the recipient of the SMS.
    BCDAddress destMsisdn;

    // The MSISDN of the sender of the SMS.  Can this be empty?  I don't think the
    // protocol allows you send to send anonymous SMS...
    BCDAddress sourceMsisdn;

    // And the (plain) SMS text, i.e. not 7 bit encoded.  No provision for multiple
    // pages of SMS text yet.
    char smsText [160];

    /*****************************************************************************
     * So these are not in use yet, but are (I think) how we'll support delivery *
     * of multi-page SMS messages.                                               *
     *****************************************************************************/

    // The number of pages to concatenate together to form the complete SMS.
    u8 numberOfPages;

    // And this message contains page X of numberOfPages.
    u8 currentPageNumber;

}SMSCMessageStructure;
#endif/*0*/
#endif
