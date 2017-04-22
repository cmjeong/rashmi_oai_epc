///////////////////////////////////////////////////////////////////////////////
//
// 3 Way Networks Source File
//
///////////////////////////////////////////////////////////////////////////////
//
// LIB24008L3UplinkSS.h
//
// Base class holding data common across all of the L3 Supplementary Service
// messages.
//
// Copyright ? 3 Way Networks, Ltd.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __LIB24008L3UplinkSS_h_
#define __LIB24008L3UplinkSS_h_

///////////////////////////////////////////////////////////////////////////////
// Encodix Includes
///////////////////////////////////////////////////////////////////////////////

#include <Encodix24008.h>

///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////

#include "LIB24008Uplink.h"

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

typedef enum enumSSVersionIndicator
{
	PHASE_2_SERVICE = 0x00,
	VERSION_3_SUPPORTED = 0x01,
	SS_VERSION_NOT_PRESENT = 0xff
}SSVersionIndicator;

typedef enum enumComponentTypeTag
{
	COMPONENT_TYPE_TAG_INVOKE = 0xA1,
	COMPONENT_TYPE_TAG_RETURN_RESULT = 0xA2,
	COMPONENT_TYPE_TAG_RETURN_ERROR = 0xA3,
	COMPONENT_TYPE_TAG_REJECT = 0xA4
}ComponentTypeTag;

///////////////////////////////////////////////////////////////////////////////
// Class: LIB24008L3UplinkSS
// Desc:  We don't want to have the memory management of the structures
//        exposed to the main applications to prevent memory leaks.
///////////////////////////////////////////////////////////////////////////////

class LIB24008L3UplinkSS : public LIB24008Uplink
{
public:
	// Constructor / destructor.
	LIB24008L3UplinkSS ();
	LIB24008L3UplinkSS (const u8 ssMessage [], u16 ssMessageLength);
	virtual ~LIB24008L3UplinkSS ();

	// Accessors for the generated message.
	GSM0408SsMessageType GetMessageType () const;

	// Retrieve Layer 3 protocol discriminator.
	virtual GSM0408ProtocolDiscrim GetPD () const;
	u8 GetTransactionId () const;
	u8 GetSSMessage (u8 *ssMessage) const;

private:

	const u8 *DecodeFacility (const u8 *ieFacility);

private:

	// Which type of SS message has been received from the UE?
	GSM0408SsMessageType m_ssMessageType;

	// 24.007 if you want an explanation of the TId.
	u8 m_transactionId;

	// If present (it's an OPTIONAL), this contains the IE value.
	SSVersionIndicator m_ssVersionIndicator;

	// Not decoded yet, the FACILITY IE.
	u8 m_facilityLength;
	u8 m_facilityComponents [256];

	// The entire, raw layer 3 message.  I'm storing the contiguous hex message
	// for now as we are not sure how this will be presented to the external network.
	// And indeed, the presentation may change depending on what is on the other side
	// of the SIP interface >:-)
	u8 m_ssMessageLength;
	u8 m_ssMessage [256];
};

#endif
