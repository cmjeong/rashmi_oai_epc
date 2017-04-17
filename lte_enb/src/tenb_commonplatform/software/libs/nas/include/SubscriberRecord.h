///////////////////////////////////////////////////////////////////////////////
//
// 3 Way Networks Source File
//
///////////////////////////////////////////////////////////////////////////////
//
// SubscriberRecord.h
//
// This record contains all of the information required to handle a single
// subscriber on the network, be they roaming or not.
//
// Copyright ? 3 Way Networks, Ltd.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __SubscriberRecord_h_
#define __SubscriberRecord_h_

///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////
//CODE_CLEANUP
#if 0
#include <ed_c.h>

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

typedef enum enumAttachStatus
{
	YES = 1,
	NO = 2,
	MAYBE = 3,
	DONT_KNOW = 4
}AttachStatus;

#define ATTACH_STATUS(x,y) \
if (x == YES) strcat (y, "YES"); \
else if (x == NO) strcat (y, "NO"); \
else if (x == MAYBE) strcat (y, "MAYBE"); \
else if (x == DONT_KNOW) strcat (y, "DON'T KNOW"); \
else strcat (y, "UNKNOWN");

// Each item in the HLR 'database' is of this format.
typedef struct structSubscriberRecord
{
	// IMSI Identity of this subscriber, maximum 15 digits.
	c_MobileId subscriberImsi;

	// IMEI Identity of this subscriber, maximum of 15 digits.
	c_MobileId subscriberImei;

	// Fixed number of 8 digits in a TMSI at this time.  This is the
	// temporary identity in the CS domain.
	c_MobileId subscriberTmsi;

	// This is the temporary identity in the PS domain.
	c_MobileId subscriberPTmsi;

	// This it the PTMSI Signature attached to the PTMSI above.  It is actually
	// 3 octets long, so the MSB of this quantity is unused.
	u32 ptmsiSignature;

	// Do we have a roaming subscriber here, or is it one of our home
	// network subscribers?
	bool subscriberIsGuest;

	// Authentication + cyphering key 'K'.  See 3GPP docs 33.201 - 206 for
	// specifics on how it is used.
	u8 subscriberK [K_KEY_SIZE];

	// Authentication vectors, that will be either generated locally for a
	// home network subscriber, or generated on the other side of the SIP
	// IWF for a guest.
	AuthVectors authVectors;

	// The phone number that is dialled to contact this subscriber.  I'm
	// taking the digit limit from 24.008, although I could be wrong: ever
	// seen a phone number with more than 26 digits??
	u8 subscriberNumberLength;
	u8 subscriberNumber [MAX_E164_DIGITS];

	// Is this subscriber currently, as far as we know, connected to
	// the circuit network?  This will be set when the user completes a CS
	// LocationAreaUpdate.
	u8 subscriberAttachedCS;

	// Is this subscriber currently, as far as we know, connected to
	// the packet network?  This will be set when the user completes a PS
	// RoutingAreaUpdate.
	u8 subscriberAttachedPS;

	// The time of the most recent attach from this user: we will mark
	// a user as 'gone away' after period x.
	time_t timeOfLastAttachCS;
	time_t timeOfLastAttachPS;

	// Last known location of this subscriber in the CS domain.
	c_LocationAreaId subscriberLocationCS;

	// Last known location of this subscriber in the PS domain.
	c_RoutingAreaIdenti subscriberLocationPS;

    // Support for access control testing; we may want to send some
    // interesting LAI information to the UE the *first* time it attempts
    // to location/routing update.
    bool tormentingThisUe;

    // Support for access control testing; flag to enable us to temporarily
    // disable this subscriber
    bool isDisabled;

}SubscriberRecord;

#endif/*0*/
#endif

